/**
This firmware is only for TI CC3200 Launchpad.
In order to test the COSSB system, we will support temporary open & public hardware platforms like TI Launchpad, Odroid, Raspberry Pi...
If you have any questions for this sample code, please contact us(bhhwang@nsynapse.com).
*/
#include <WiFi.h>
#include <WiFiUdp.h>
#include <WiFiServer.h>
#include <WiFiClient.h>



char ssid[] = "nsynapseap";
char password[] = "elec6887";
WiFiClient client = 0;

void printWifiStatus() {
  Serial.print("Network Name: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void setup()
{
  Serial.begin(115200);
  WiFi.init();
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
  
  Serial.print("Network Name: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  
}

void loop()
{
  mdnsAdvertiser(1, "CC3000", 6);
  
  /*client = server.available();
  int ret = 0;
  ret = mdnsAdvertise(1."cc3200", 6);
  Serial.println("MDNS Advertising returning");
  Serial.println(ret);*/
  delay(5000);
  
}


