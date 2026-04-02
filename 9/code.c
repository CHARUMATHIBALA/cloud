#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHTesp.h>

char auth[] = "BLYNK_AUTH_TOKEN";
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

const int DHT_PIN = 15;

DHTesp dht;
BlynkTimer timer;

void sendSensor()
{
  TempAndHumidity data = dht.getTempAndHumidity();

  Serial.print("Temperature: ");
  Serial.print(data.temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(data.humidity);
  Serial.println(" %");

  Blynk.virtualWrite(V0, data.temperature);
  Blynk.virtualWrite(V1, data.humidity);
}

void setup()
{
  Serial.begin(115200);

  dht.setup(DHT_PIN, DHTesp::DHT22);

  Blynk.begin(auth, ssid, pass);

  timer.setInterval(1000L, sendSensor);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  Blynk.run();
  timer.run();
}