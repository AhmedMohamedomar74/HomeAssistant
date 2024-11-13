#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// WiFi credentials
const char* ssid = "almothaber";
const char* password = "awdr1234";

// MQTT Broker details
const char* mqtt_broker = "192.168.1.24";  // Replace with your broker address
const int mqtt_port = 1883;                // MQTT port
const char* mqtt_username = "mqtt_user";
const char* mqtt_password = "mqtt_pass";   // Replace with the actual password
const char* topic = "/home/bedroom/temperature";
const char* led_topic = "home/light/set"; // Topic for controlling the LED

// DHT Sensor settings
#define DHTPIN 13              // GPIO pin where the DHT sensor is connected
#define DHTTYPE DHT22          // Change to DHT11 if using DHT11 sensor
DHT dht(DHTPIN, DHTTYPE);

// GPIO pin for the LED
const int ledPin = 12;

// MQTT client
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  // Initialize Serial monitor
  Serial.begin(115200);

  // Set LED pin as output
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Ensure the LED is off initially

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  // Set MQTT server and credentials
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback); // Set the MQTT callback function

  // Connect to the MQTT broker
  while (!client.connected()) {
    Serial.print("Connecting to MQTT broker...");
    if (client.connect("ESP32Client", mqtt_username, mqtt_password)) {
      Serial.println("connected");
      client.subscribe(led_topic); // Subscribe to the LED control topic
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }

  // Initialize DHT sensor
  dht.begin();
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  if (String(topic) == led_topic) {
    if (message == "ON") {
      digitalWrite(ledPin, HIGH); // Turn on the LED
      Serial.println("LED turned ON");
    } else if (message == "OFF") {
      digitalWrite(ledPin, LOW); // Turn off the LED
      Serial.println("LED turned OFF");
    }
  }
}

void loop() {
  // Ensure the MQTT client is connected
  if (!client.connected()) {
    while (!client.connected()) {
      if (client.connect("ESP32Client", mqtt_username, mqtt_password)) {
        client.subscribe(led_topic); // Resubscribe to the topic
      } else {
        delay(2000);
      }
    }
  }
  client.loop(); // Process MQTT messages

  // Read temperature from DHT sensor
  float temperature = dht.readTemperature();
  
  // Check if reading was successful
  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Publish temperature to MQTT
  client.publish(topic, String(temperature).c_str());
  Serial.print("Published temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Wait 1 second before sending the next reading
  delay(1000);
}
