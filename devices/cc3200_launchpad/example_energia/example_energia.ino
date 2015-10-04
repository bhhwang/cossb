/**
This firmware is only for TI CC3200 Launchpad.
In order to test the COSSB system, we will support temporary open & public hardware platforms like TI Launchpad, Odroid, Raspberry Pi...
If you have any questions for this sample code, please contact us(bhhwang@nsynapse.com).
*/

#include <WiFi.h>
#include <WiFiUdp.h>
#include <WiFiServer.h>
#include <WiFiClient.h>

volatile int yellow_state = LOW;
volatile int red_state = LOW;
volatile int green_state = LOW;

char ssid[] = "nsynapseap";
char password[] = "elec6887";
WiFiClient client;
WiFiServer server(8000);

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
  digitalWrite(GREEN_LED, HIGH);
  
  printWifiStatus();
  server.begin();
}


void loop()
{
  int i=0;
  client = server.available();
  
  int push1_state = LOW;
  int prev_push1_state = LOW;
  int push2_state = LOW;
  int prev_push2_state = LOW;
  
  unsigned char btn = 0x00;
  unsigned char btn_value = 0x00;
  
  connet_led();
  
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
  
  delay(300);
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

void connet_led()
{
  yellow_state = !yellow_state;
  digitalWrite(YELLOW_LED, yellow_state);
}


void send(unsigned char b, unsigned char v) {
  if(client.connected()) {
    unsigned char data[12] = {'/','S','T','A','R','T',b,v, '/','E','N','D'};
    client.write(data, sizeof(data));
  }
}
