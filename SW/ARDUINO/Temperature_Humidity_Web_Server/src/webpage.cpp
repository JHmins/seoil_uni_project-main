#include <stdio.h>
#include <stdint.h>
#include <string.h>

//#include "FS.h"                // SD Card ESP32
//#include "SD_MMC.h"            // SD Card ESP32
//#include "Wire.h"            // SD Card ESP32
#include "config.h"            // SD Card ESP32
#include "webpage.h"

//#include <SPI.h>

#include "drv_sht21.h"
//#include "sd_memory.h"


// Libraries to get time from NTP Server
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <WebServer.h>

#include "index.h"  //Web page header file

WebServer server(80);


// Replace with your network credentials
const char* ssid     = "WIFI_SSID";
const char* password = "WIFI_PASSWORD";

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

char value_str[80];
void handleSensor() {

 sprintf(value_str, "온도 %6.2f℃ 습도 %5.2f%%", temperature, humi);

 server.send(200, "text/plane", value_str); //Send ADC value only to client ajax request
}

void init_webServer(void) {
  WiFi.mode(WIFI_STA);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while(WiFi.waitForConnectResult() != WL_CONNECTED){      
    Serial.print("WIFI Connection error!\r\n\r\n");
      return;
    }
    
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
//----------------------------------------------------------------
 
  server.on("/", handleRoot);      //This is display page
  server.on("/readSensor", handleSensor);//To get update of ADC Value only
//  server.on("/readStatus", handleStatus);//To get update of ADC Value only
 
  server.begin();                  //Start server
  Serial.println("HTTP server started");  

}


void webServer_handler(void) {
  server.handleClient();  
}

 
