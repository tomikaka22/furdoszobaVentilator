#include "DHTesp.h"
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <Preferences.h>
#include "svelteesp32.h"

#define DHT11PIN 14
#define RELAYPIN 13

int humidityThreshold = 75;
int temperatureThreshold = 10;
bool relay = false;
float temp = 0;
float hum = 0;
int fanTemporaryDuration = 0;
unsigned long fanTemporaryTimer = 0;

DHTesp dht;
AsyncWebServer server(80);
Preferences preferences;

bool readSensor(float humidity, float temperature) {

  if (humidity > 0) {
    hum = humidity;
    temp = temperature;

    Serial.print("Humidity Threshold (%): ");
    Serial.println(humidityThreshold);

    Serial.print("Humidity (%): ");
    Serial.println(hum);

    Serial.print("Temperature Threshold (˚C): ");
    Serial.println(temperatureThreshold);

    Serial.print("Temperature (˚C): ");
    Serial.println(temp);

    Serial.print("Fan: ");
    Serial.println(relay ? "ON" : "OFF");

    Serial.print("Local IP: ");
    Serial.println(WiFi.localIP());

    Serial.println();

    return true;
  } else {
    Serial.println("Sensing Failed!");

    return false;
  }
}

void connectToWiFi(const char * ssid, const char * pwd) {
  WiFi.begin(ssid, pwd);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
}

void fanTemporaryOff() {
  if (fanTemporaryTimer == 0)
    fanTemporaryTimer = millis();

  if (millis() - fanTemporaryTimer > abs(fanTemporaryDuration) || fanTemporaryTimer > millis()) {
    fanTemporaryTimer = 0;
    fanTemporaryDuration = 0;
  }

  if (millis() - fanTemporaryTimer < abs(fanTemporaryDuration)) {
    digitalWrite(RELAYPIN, HIGH);
    relay = false;
  }

  Serial.print("fanTemporaryDuration: ");
  Serial.println(abs(fanTemporaryDuration));

  Serial.print("Time left: ");
  Serial.println(abs(fanTemporaryDuration) - (millis() - fanTemporaryTimer));
  Serial.println();
}

void fanTemporaryOn() {

  if (fanTemporaryTimer == 0)
    fanTemporaryTimer = millis();

  if (millis() - fanTemporaryTimer > fanTemporaryDuration || fanTemporaryTimer > millis()) {
    fanTemporaryTimer = 0;
    fanTemporaryDuration = 0;
  }

  if (millis() - fanTemporaryTimer < fanTemporaryDuration) {
      digitalWrite(RELAYPIN, LOW);
      relay = true;
  }

  Serial.print("fanTemporaryDuration: ");
  Serial.println(fanTemporaryDuration);

  Serial.print("Time left: ");
  Serial.println(fanTemporaryDuration - (millis() - fanTemporaryTimer));
  Serial.println();
}

void decide() {
  if (fanTemporaryDuration == 0) {

    if (hum > humidityThreshold && temp > temperatureThreshold) {
      digitalWrite(RELAYPIN, LOW);
      relay = true;
    }
    else if (hum < humidityThreshold || temp < temperatureThreshold) {
      digitalWrite(RELAYPIN, HIGH);
      relay = false;
    }

  }
  else if (fanTemporaryDuration > 0) {
    fanTemporaryOn();
  }
  else if (fanTemporaryDuration < 0) {
    fanTemporaryOff();
  }
}

void setup() {
 	pinMode(RELAYPIN, OUTPUT);
  digitalWrite(RELAYPIN, HIGH);
  Serial.begin(115200);
  dht.setup(DHT11PIN, DHTesp::DHT11);
  preferences.begin("config", false); // false means read/write mode

  temperatureThreshold = preferences.getInt("temperatureThreshold", temperatureThreshold);
  humidityThreshold = preferences.getInt("humidityThreshold", humidityThreshold);
  
  Serial.println("Starting...");
  connectToWiFi("Vincze 2.4Ghz", "Vilidu-Szisza-Amogusz-Szusz-69420");
  wifi_set_sleep_type(LIGHT_SLEEP_T);

  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "GET, POST, PUT, OPTIONS");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "*");

  server.on("/hum", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", String(hum));
  });

  server.on("/temp", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", String(temp));
  });

  server.on("/relay", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", String(relay));
  });

  server.on("/thresh", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", String(humidityThreshold));
  });

  server.on("/tempThresh", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", String(temperatureThreshold));
  });

  server.on("/duration", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", String(fanTemporaryDuration));
  });

  server.on("/temporaryTimer", HTTP_GET, [](AsyncWebServerRequest *request){
    if (abs(fanTemporaryDuration) - (millis() - fanTemporaryTimer) <= abs(fanTemporaryDuration))
      request->send(200, "text/plain", String(abs(fanTemporaryDuration) - (millis() - fanTemporaryTimer)));
    else
      request->send(200, "text/plain", String(0));
  });

  server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request){

    if (request->hasParam("humidity", true)) {
      humidityThreshold = (request->getParam("humidity", true)->value()).toInt();
      preferences.putInt("humidityThreshold", humidityThreshold);

      request->send(200, "text/plain", String(humidityThreshold));
    }
    if (request->hasParam("temperature", true)) {
      temperatureThreshold = (request->getParam("temperature", true)->value()).toInt();
      preferences.putInt("temperatureThreshold", temperatureThreshold);

      request->send(200, "text/plain", String(temperatureThreshold));
    }
    if (request->hasParam("duration", true)) {
      fanTemporaryDuration = (request->getParam("duration", true)->value()).toInt();
      request->send(200, "text/plain", String(fanTemporaryDuration));
    }

    decide();
  });

  server.onNotFound([](AsyncWebServerRequest *request){
    if (request->method() == HTTP_OPTIONS) {
      request->send(200);
    } else {
      request->redirect("/");
    }
  });

  initSvelteStaticFiles(&server);
  server.begin();
}

void loop() {
  readSensor(dht.getHumidity(), dht.getTemperature());
  decide();

  delay(5000);
}
