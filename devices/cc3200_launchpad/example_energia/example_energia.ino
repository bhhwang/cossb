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

#define DEFAULT_UDP_MEMBERSHIP  "225.0.0.37"
#define DEFAULT_UDP_PORT  21928

volatile int yellow_state = LOW;
volatile int red_state = LOW;
volatile int green_state = LOW;

//access point should only work for b and g
char ssid[] = "hellfire";
char password[] = "elec6887";
WiFiServer server(8000);
WiFiUDP Udp;

int push1_state = LOW;
int prev_push1_state = LOW;
int push2_state = LOW;
int prev_push2_state = LOW;

unsigned char btn = 0x00;
unsigned char btn_value = 0x00;

enum {IDLE = 0, ANNOUNCE=100, SERVICE=200 };
unsigned int process_state = IDLE;

aJsonObject* announce = aJson.createObject();
aJsonObject* frame = aJson.createObject();

void setup()
{
  pinMode(PUSH1, INPUT_PULLUP);
  pinMode(PUSH2, INPUT_PULLUP);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);
  
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while(WiFi.status()!=WL_CONNECTED) {
    net_led();
    delay(300);
  }
  
  while(WiFi.localIP() == INADDR_NONE) {
    net_led();
    delay(300);
  }
  
  printWifiStatus();
  server.begin();
  Udp.begin(DEFAULT_UDP_PORT);
  
  //device profile
  if(announce) {
    aJson.addStringToObject(announce, "devicename", "TI_cc3200_1");
    aJson.addStringToObject(announce, "componentname", "cc3200button");
    aJson.addStringToObject(announce, "protocol", "tcp");
    aJson.addNumberToObject(announce, "port", 8000);
    aJson.addStringToObject(announce, "command","auth");
  }
  
  if(frame) {
    aJson.addStringToObject(frame, "devicename", "TI_cc3200_1");
    aJson.addStringToObject(frame, "componentname", "cc3200button");
    aJson.addStringToObject(frame, "command","buttonread");
    aJson.addBooleanToObject(frame, "button1", false);
    aJson.addBooleanToObject(frame, "button2", false);
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
        Serial.println("new client");
        while(client.connected()) {
          digitalWrite(RED_LED, HIGH);
          
          push1_state = digitalRead(PUSH1);
          push2_state = digitalRead(PUSH2);
          
          if(push1_state!=prev_push1_state) {
            if(push1_state==HIGH) {
              Serial.println("Push1 High");
              update(PUSH1, true);
            }
            else if(push1_state==LOW) {
              Serial.println("Push1 Low");
              update(PUSH1, false);
            }
            client.print(aJson.print(frame));
            delay(50);
          }
          
          if(push2_state!=prev_push2_state) 
          {
            if(push2_state==HIGH) {
              Serial.println("Push2 High");
              update(PUSH2, true);
            }
            else if(push2_state==LOW) {
              Serial.println("Push2 Low");
              update(PUSH2, false);
            }
            client.print(aJson.print(frame));
            delay(50);
          }
         
          
          
          prev_push1_state = push1_state;
          prev_push2_state = push2_state;
        }
        Serial.println("connection closed");
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


void update(unsigned char button, boolean value) 
{
  if(button==PUSH1) {
    aJsonObject* button1 = aJson.getObjectItem(frame, "button1");
    button1->valuebool = value;
  }
  
  if(button==PUSH2) {
    aJsonObject* button2 = aJson.getObjectItem(frame, "button2");
    button2->valuebool = value;
  }
}
