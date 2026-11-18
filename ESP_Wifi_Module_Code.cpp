#include <WiFi.h>
#include <WebServer.h>
const char* ssid = "NUME_WIFI";
const char* password = "PAROLA_WIFI";
WebServer server(80);
const int RX_PIN = 16;
const int TX_PIN = 17;
String statusBirou = "Astept date de la CM5";
void paginaPrincipala() {
  String html = "<html><head>";
  html += "<meta name='viewport' content='width=device-width'>";
  html += "<meta http-equiv='refresh' content='3'>";
  html += "</head><body>";
  html += "<h1>The Mess Destroyer</h1>";
  html += "<h2>Status: " + statusBirou + "</h2>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}
void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Adresa IP: ");
  Serial.println(WiFi.localIP());
  server.on("/", paginaPrincipala);
  server.begin();
}
void loop() {
  server.handleClient();
  if (Serial2.available()) {
    String mesaj = Serial2.readStringUntil('\n');
    mesaj.trim();
    if (mesaj == "MESSY") {
      statusBirou = "Biroul este dezordonat!";
    }
    else if (mesaj == "CLEAN") {
      statusBirou = "Biroul este ordonat!";
    }
    Serial.println(statusBirou);
  }
}