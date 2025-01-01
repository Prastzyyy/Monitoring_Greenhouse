#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>

#include "web.h"

const char* ssid = "Prastzy.net";
const char* password = "123456781";

ESP8266WebServer server(80);

const int led = 2;  
float pH, PPM, suhu, tinggi_cm;
String kondisiOtomatisasi;
bool saklar = false;

unsigned long previousMillis = 0; // Waktu sebelumnya
const unsigned long interval = 1000; // Interval untuk pembaruan status
unsigned long startMillis = 0; // Waktu mulai otomatisasi
bool isAutomating = false; // Status otomatisasi

void handleRoot() {
  server.send(200, "text/html", SendHTML(pH, PPM, suhu, tinggi_cm, kondisiOtomatisasi));
}

void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
  message += " " + server.argName(i) + ": " + server.arg(i)+ "\n";
  }
  server.send(404, "text/plain", message);
}

void handleData() {
  //Serial.println("Endpoint /data accessed");
  //Serial.println("");
  String json = "{";
  json += "\"pH\":" + String(pH) + ",";
  json += "\"PPM\":" + String(PPM) + ",";
  json += "\"suhu\":" + String(suhu) + ",";
  json += "\"tinggi_cm\":" + String(tinggi_cm) + ",";
  json += "\"kondisiOtomatisasi\":\"" + kondisiOtomatisasi + "\"";
  json += "}";
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.send(200, "application/json", json);
}

void setup(void){
  pinMode(led, OUTPUT);
  Serial.begin(115200);
  digitalWrite(led, 1);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println(" ");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  if (MDNS.begin("esp8266")) {
  Serial.println("MDNS responder started");
  }
  IPAddress ip = WiFi.localIP();
  String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);

//====================================================
  server.on("/", [](){
    //server.send(200, "text/html", SendHTML(nilaiSuhu, nilaiKelembaban, kondisiLED)); 
    handleRoot();
  });
  
  server.on("/otomatisasi_on", [](){
    Serial.println("");
    Serial.print("/otomatisasi_on"); 
    Serial.println("");
    saklar = true;
    //server.send(200, "text/html", SendHTML(nilaiSuhu, nilaiKelembaban, kondisiLED)); 
    handleRoot();
  });
  
//====================================================
  server.on("/data", handleData);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
  
}

void loop(void){
  server.handleClient(); // Tangani permintaan HTTP

  // Perbarui nilai sensor secara acak
  int randomNumber = random(0, 41);  
  pH = 5.0 + (randomNumber * 0.1);
  PPM = random(550, 1050);
  suhu = random(25, 36);
  tinggi_cm = random(90, 101);
  
  unsigned long currentMillis = millis();

  // Tangani otomatisasi ketika saklar aktif
  if (saklar && !isAutomating) {
    kondisiOtomatisasi = "Sedang berjalan";
    Serial.println("Otomatisasi Sedang berjalan");
    digitalWrite(led, LOW); // Nyalakan LED
    startMillis = currentMillis; // Catat waktu mulai
    isAutomating = true; // Aktifkan status otomatisasi
  }

  // Jalankan otomatisasi selama 10 detik
  if (isAutomating) {
    if (currentMillis - startMillis >= 10000) { // Selesai otomatisasi setelah 10 detik
      kondisiOtomatisasi = "Otomatisasi Berhasil";
      Serial.println("Otomatisasi Berhasil");
      digitalWrite(led, HIGH); // Matikan LED
      saklar = false; // Nonaktifkan saklar
      isAutomating = false; // Nonaktifkan status otomatisasi
    }
  }

  // Perbarui data secara berkala
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
  }
}
