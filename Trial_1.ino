#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "YOUR SSID";
const char* password = "YOUR PASSWORD";

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Menghubungkan dengan WIFI");

  WiFi.begin(ssid, password);
  int attempts = 0; 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");  // Hapus titik koma di sini
    attempts++;  // Hapus 'ze' di sini
    if (attempts > 20) {
      Serial.println("\nGagal terhubung dengan wifi, cek SSID atau Password");  // Perbaiki 'printlln' menjadi 'println'
      return;
    }
  }

  Serial.println("\nWifi terhubung");  // Tambahkan titik koma di sini
  Serial.println("IP address  : ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;  // Tambahkan variabel http di sini

    float suhu = random(200, 400) / 10.0;
    float kelembapan = random(700, 901) / 10.0;

    // Buat JSON 
    StaticJsonDocument<128> doc; 
    doc["esp_suhu"] = suhu;
    doc["esp_kelembapan"] = kelembapan;

    String jsonString;
    serializeJson(doc, jsonString);  // Hapus baris duplikat ini

    String server = "http://192.XXX.XXX.XX/iot-dashboard/insert.php";
    http.begin(server);
    http.addHeader("Content-Type", "application/json");

    Serial.print("📡 Kirim POST ke: ");
    Serial.println(server);
    Serial.print("📦 Payload JSON: ");
    Serial.println(jsonString);

    int httpCode = http.POST(jsonString);

    if (httpCode > 0) {
      Serial.print("HTTP response: ");  // Tambahkan titik dua
      Serial.println(httpCode);
      String response = http.getString();
      Serial.print("Server response: ");  // Tambahkan titik dua
      Serial.println(response);
    } else {
      Serial.print("X Gagal Kirim. Error: ");  // Tambahkan titik koma dan perbaiki 'Eror'
      Serial.println(http.errorToString(httpCode));  // Tambahkan titik koma
    }
    
    http.end();  // Tambahkan titik koma

  } else {
    Serial.println("WIFI TERPUTUS mau coba connect");  // Perbaiki 'serial' menjadi 'Serial' dan tambahkan titik koma
    WiFi.reconnect();  // Tambahkan titik koma
  }

  delay(1000);  // Tambahkan titik koma
}
