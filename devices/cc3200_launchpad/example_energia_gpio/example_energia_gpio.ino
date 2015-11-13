/**
This firmware is only for TI CC3200 Launchpad.
In order to test the COSSB system, we will support temporary open & public hardware platforms like TI Launchpad, Odroid, Raspberry Pi...
If you have any questions for this sample code, please contact us(bhhwang@nsynapse.com).
*/

#include <WiFi.h>
#include <WiFiUdp.h>
#include <WiFiServer.h>
#include <WiFiClient.h>
#include <aJSON.h>

#define USE_UART

#define DEFAULT_UDP_MEMBERSHIP  "225.0.0.37"
#define DEFAULT_UDP_PORT  21928
#define GPIN  5  //P61(GPIO5)

volatile int yellow_state = LOW;
volatile int red_state = LOW;
volatile int green_state = LOW;

//access point should only work for b and g
char ssid[] = "nsynapse";
char password[] = "elec6887";
const char* uuid = "71ba1b0e47e34a91abb4b1d1bae10960";
WiFiServer server(8000);
WiFiUDP Udp;
byte mac[6];
String mac_string;


int io_state = LOW;
int prev_io_state = LOW;

unsigned char btn = 0x00;
unsigned char btn_value = 0x00;

enum {IDLE = 0, ANNOUNCE=100, SERVICE=200 };
unsigned int process_state = IDLE;

aJsonObject* announce = aJson.createObject();
aJsonObject* frame = aJson.createObject();

void setup()
{
  pinMode(GPIN, INPUT_PULLUP);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);
  
#ifdef USE_UART
  Serial.begin(115200);
#endif
  
  WiFi.begin(ssid, password);
  
  while(WiFi.status()!=WL_CONNECTED) {
    net_led();
    delay(300);
  }
  
  while(WiFi.localIP() == INADDR_NONE) {
    net_led();
    delay(300);
  }
  
  WiFi.macAddress(mac);
  for(int i=0;i<sizeof(mac);i++) {
    mac_string += String(mac[sizeof(mac)-1-i],HEX);
    if(i<(sizeof(mac)-1))
      mac_string += ":";
  }
  
  printWifiStatus();

  server.begin();
  Udp.begin(DEFAULT_UDP_PORT);
  
  //device profile
  if(announce) {
    aJson.addStringToObject(announce, "devicename", "TI-CC3200");
    aJson.addStringToObject(announce, "uuid", uuid);
    aJson.addStringToObject(announce, "mac", mac_string.c_str());
    aJson.addStringToObject(announce, "manufacturer", "Texas Instrument");
    aJson.addStringToObject(announce, "author", "cossb");
    aJson.addStringToObject(announce, "component", "cc3200gpio");
    aJson.addStringToObject(announce, "protocol", "tcp");
    aJson.addNumberToObject(announce, "port", 8000);
    aJson.addStringToObject(announce, "command","auth");
  }
  
  if(frame) {
    aJson.addStringToObject(frame, "devicename", "TI-CC3200");
    aJson.addStringToObject(frame, "uuid", uuid);
    aJson.addStringToObject(frame, "mac", mac_string.c_str());
    aJson.addStringToObject(frame, "component", "cc3200gpio");
    aJson.addStringToObject(frame, "command","io");
    aJson.addBooleanToObject(frame, "switch", false);
  }
}

void loop()
{
  switch(process_state)
  {
    ///////////////////////// onlu connected to ap
    case IDLE: 
    {
      net_led();
      if(WiFi.status()==WL_CONNECTED) {
        process_state = ANNOUNCE;
        digitalWrite(GREEN_LED, HIGH);
      }
    }
    break;
    
    //////////////////////// service announce
    case ANNOUNCE: 
    {
      digitalWrite(YELLOW_LED, HIGH);
      if(announce)
      {
        Udp.beginPacket(DEFAULT_UDP_MEMBERSHIP, DEFAULT_UDP_PORT);
        Udp.write(aJson.print(announce));
        Udp.endPacket();
        process_state = SERVICE;
      }
    }
    break;
    
    
    //////////////////////// service run
    case SERVICE:
    { 
      WiFiClient client = server.available();
      if(client) {
        while(client.connected()) {
          digitalWrite(RED_LED, HIGH);
          
          io_state = digitalRead(GPIN);
          
          if(io_state!=prev_io_state) {
            if(io_state==HIGH) {
              update(GPIN, true);
            }
            else if(io_state==LOW) {
              update(GPIN, false);
            }
            client.print(aJson.print(frame));
            delay(50);
          }
              
          prev_io_state = io_state;
        }
        
        digitalWrite(RED_LED, LOW);
        client.stop();
        
        if(WiFi.status()!=WL_CONNECTED) {
          digitalWrite(YELLOW_LED, LOW);
          process_state = IDLE;
        }
      }
    }
    break;
  }
}


void printWifiStatus() {
#ifdef USE_UART
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  
  Serial.print("MAC: ");
  Serial.print(mac[5],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.println(mac[0],HEX);
#endif
}

boolean endsWith(char* inString, char* compString) {
  int compLength = strlen(compString);
  int strLength = strlen(inString);
  
  //compare the last "compLength" values of the inString
  int i;
  for (i = 0; i < compLength; i++) {
    char a = inString[(strLength - 1) - i];
    char b = compString[(compLength - 1) - i];
    if (a != b) {
      return false;
    }
  }
  return true;
}

void net_led()
{
  green_state = !green_state;
  digitalWrite(GREEN_LED, green_state);
}

void connect_led()
{
  yellow_state = !yellow_state;
  digitalWrite(YELLOW_LED, yellow_state);
}

void serve_led()
{
  red_state = !red_state;
  digitalWrite(RED_LED, red_state);
}


void update(unsigned char io, boolean value) 
{
  if(io==GPIN) {
    aJsonObject* gpio = aJson.getObjectItem(frame, "switch");
    gpio->valuebool = value;
  }
}
