#include <ESP8266WiFi.h>

const char ssid[] = "luminous";
const char pass[] = "zxcv78()[]";

//Mac IP 192.168.1.101 
//PC IP 192.168.1.103

IPAddress server(192,168,0,103);
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
  }

}

// 3s client read timeout. I set this value casually. The server has a 5s timeout when reading data from client.
const unsigned long clientTimeout = 3000; 
                                              
void loop() {
  // put your main code here, to run repeatedly:

  if(client.connected()){
    client.write(WiFi.RSSI());
    delay(100); // Add for nothing. Not sure if it's useful
    unsigned long timeout = millis();
    //Client timeout, if client can't reach the server, it should start to reconnect the server
    while(client.available() == 0){
      if (millis() - timeout >= clientTimeout){
        Serial.println(">>> Client Timetout !");
        client.stop();
        break;
      }
    }
    //Client is connected and has data to read
    //discard all data
    client.flush();
  }else{
    //Try to reconnect to the server
    client.connect(server,port);
    delay(500); // Add for nothing. Not sure if it's useful
    while(!client.connected()){
       //failed to reconnect
       Serial.println("Failed to reconnect...");
       delay(500);
       client.connect(server,port);
    }
    //succeed reconnecting
    Serial.println("Succeeded reconnecting..");
  }
}
