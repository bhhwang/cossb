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
char ssid[] = "nsynapse";
char password[] = "elec6887";
WiFiClient client;
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

aJsonObject* root = aJson.createObject();

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
  if(root) {
    aJson.addStringToObject(root, "devicename", "TI_cc3200_1");
    aJson.addStringToObject(root, "componentname", "cc3200button");
    aJson.addStringToObject(root, "protocol", "tcp");
    aJson.addNumberToObject(root, "port", 8000);
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
      connect_led();
      if(root)
      {
        Udp.beginPacket(DEFAULT_UDP_MEMBERSHIP, DEFAULT_UDP_PORT);
        Udp.write(aJson.print(root));
        Udp.endPacket();
        process_state++;
      }
    }
    break;
    
    /*case ANNOUNCE+1: 
    {
      int packetsize = Udp.parsePacket();
      if(packetsize)
      {
        Serial.println(packetsize);
        process_state++;
      }
      process_state = ANNOUNCE;
      delay(1000);
    }
    break;*/
    
    case ANNOUNCE+1:
    {
      client = server.available();
      if(client) {
        process_state=SERVICE;
        digitalWrite(YELLOW_LED, HIGH);
      }
      else {
        process_state = ANNOUNCE;
        delay(1000);
      }
    }
    break;
    
    //////////////////////// service run
    case SERVICE:
    { 
      if(client) {
        while(client.connected()) {
          digitalWrite(RED_LED, HIGH);
        }
        client.stop();
        digitalWrite(RED_LED, LOW);
        process_state = IDLE;
      }
    }
    break;
  }
 
  /*
  int i=0;
  client = server.available();
  
  int push1_state = LOW;
  int prev_push1_state = LOW;
  int push2_state = LOW;
  int prev_push2_state = LOW;
  
  unsigned char btn = 0x00;
  unsigned char btn_value = 0x00;
  
  
  
  if(client) 
  {
    Serial.println("New client is connected.");
    //send(btn, btn_value);
    
    while(client.connected()) 
    {
      digitalWrite(YELLOW_LED, HIGH);
      
      push1_state = digitalRead(PUSH1);
      push2_state = digitalRead(PUSH2);
      
      if(push1_state!=prev_push1_state) {
        if(push1_state==HIGH) {
          Serial.println("Push1 High");
          send(PUSH1, HIGH);
        }
        else if(push1_state==LOW) {
          Serial.println("Push1 Low");
          send(PUSH1, LOW);
        }
      }
      
      if(push2_state!=prev_push2_state) 
      {
        if(push2_state==HIGH) {
          Serial.println("Push2 High");
          send(PUSH2, HIGH);
        }
        else if(push2_state==LOW) {
          Serial.println("Push2 Low");
          send(PUSH2, LOW);
        }
      }
      
      prev_push1_state = push1_state;
      prev_push2_state = push2_state;
      
      delay(10);
    }
    Serial.println("Client disconnected");
    client.stop();
  }
  
  delay(300);*/
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

///////////////////////////// IPAddress to string
String ip2string(IPAddress& ip)
{
  String addr="";
  for(int i=0;i<4;i++)
  {
    //addr+=ip[0]/100;
  }
  return addr;
}

void send(unsigned char b, unsigned char v) {
  if(client.connected()) {
    unsigned char data[12] = {'/','S','T','A','R','T',b,v, '/','E','N','D'};
    client.write(data, sizeof(data));
  }
}
