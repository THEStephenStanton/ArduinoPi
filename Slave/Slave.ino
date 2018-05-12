#include <SPI.h>
#include <WiFi101.h>
#include "Secrets.h"

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASSWORD;

int status = WL_IDLE_STATUS;
WiFiServer server(80);
int ledPin = 6;
IPAddress ipAddress;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);

  connectToWifi();
  startServer();
}

void connectToWifi() {
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);

    status = WiFi.begin(ssid, pass);
    delay(5000); // Wait 5 seconds for connection

    if (status == WL_CONNECTED) {
      Serial.println("Connected to wifi");
    }
  }
}

void startServer() {
  server.begin();

  ipAddress = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ipAddress);
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    String request = getRequest(client);
    
    handleRequest(request);
    sendResponse(client);
    
    client.stop();
    Serial.println("client disonnected");
  }
}

String getRequest(WiFiClient client) {
  String currentLine = "";

  while (client.connected()) {
    if (client.available()) {
      char c = client.read();

      if (c == '\n') {
        if (currentLine.length() == 0) {
          break; // Time to end the request
        }
        else {
          // The first line we get should be the request
          return currentLine; 
        }
      }
      else if (c != '\r') {
        currentLine += c;
      }
    }
  }

  return currentLine;
}

void handleRequest(String request) {
  if (request == "GET /powerOn HTTP/1.1") {
    digitalWrite(ledPin, HIGH);
  }
  else if (request == "GET /powerOff HTTP/1.1") {
    digitalWrite(ledPin, LOW);
  }
}

void sendResponse(WiFiClient client) {
  client.println("HTTP/1.1 200 OK");
  client.println();
}

