/**
This firmware is only for TI CC3200 Launchpad.
In order to test the COSSB system, we will support temporary open & public hardware platforms like TI Launchpad, Odroid, Raspberry Pi...
If you have any questions for this sample code, please contact us(bhhwang@nsynapse.com).
*/

#include <WiFi.h>
#include <WiFiUdp.h>
#include <WiFiServer.h>
#include <WiFiClient.h>

char ssid[] = "hellfire";
char password[] = "elec6887";
WiFiClient client = 0;
WiFiServer server(8000);

boolean bConnected = false;

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while(WiFi.status()!=WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  
  Serial.println("connected.");
  Serial.println("Getting Local IP Address");
  while(WiFi.localIP() == INADDR_NONE) {
    Serial.print(".");
    delay(300);
  }
  
  printWifiStatus();
  server.begin();
}


void loop()
{
  WiFiClient client = server.available();

  if(client) {
    if(!bConnected) {
      bConnected = true;
      client.flush();
      client.println("hello, client!!");
      Serial.println("client connected");
    }
    
    if(client.available() > 0) {
      char recv = client.read();
      server.write(recv);
      Serial.write(recv);
    }
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

