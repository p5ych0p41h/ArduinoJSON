#include <ArduinoJson.h>

StaticJsonDocument<48> doc;

void setup() {
  Serial.begin(9600);
}

void loop() {

  float h = random(100) + (float)random(100) / 100;
  float t = random(100) + (float)random(100) / 100;
  String  payload;
  if ( Serial.available() )
    payload = Serial.readStringUntil( '\n' );
  DeserializationError error = deserializeJson(doc, payload);
  if (error) {
    //Serial.println(error.c_str());
    h = random(100) + (float)random(100) / 100;
    t = random(100) + (float)random(100) / 100;
  }
  else {
    t = doc["temp"];
    h = doc["humidity"];
  }

  doc["temp"] = t;
  doc["humidity"] = h;

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from sensor!"));
    return;
  }

  serializeJson(doc, Serial);
  Serial.println();
  delay(500);
}
