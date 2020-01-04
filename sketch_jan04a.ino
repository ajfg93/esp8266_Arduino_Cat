#include <ESP8266WiFi.h>

const char ssid[] = "luminous";
const char pass[] = "zxcv78()[]";

IPAddress server(192,168,0,101);
int port = 12700;

WiFiClient client;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  Serial.println("");
  
  WiFi.begin(ssid, pass);
  delay(500);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".../");  
  }

  Serial.println("");
  //WiFi is connected
 
  if(client.connect(server, port)){
    Serial.println("connected to server");
  }else{
    Serial.println("Failed to connnect to server at setup().");
  }

}

int needToReconnect = 0;

void loop() {
  // put your main code here, to run repeatedly:
  while(!client.connected()){
       //failed to reconnect
       needToReconnect = 1;
       Serial.println("Failed to reconnect...");
       delay(500);
       client.connect(server,port);
  }

  // Use a flag to indicate if client was in reconnect procedure
  if(needToReconnect){
    Serial.println("Succeeded reconnecting...");
    needToReconnect = 0;
  }

  client.write(WiFi.RSSI());
  delay(100); // Add for nothing. Not sure if it's useful
  
  while(client.connected() && client.available() > 0){
    client.read();
  }

}
