#include <WiFi.h>
#include <PubSubClient.h>
#include <M5StickC.h>

// Replace these values with your WiFi credentials
const char *ssid = "wifissid";
const char *password = "pas";

// Replace these values with your MQTT broker information
const char *mqtt_server = "192.168.xxx.x";// for self hosted broker
//const char *mqtt_server="test.mosquitto.org"  // free broker 
const int mqtt_port = 1883;

// MQTT topic to publish the integers
const char *mqtt_topic = "nums/val";

int val=1;

// Initialize the WiFi client and MQTT client
WiFiClient espClient;
PubSubClient client(espClient);

void pub (int i){
    char message[10];
    snprintf(message, sizeof(message), "%d", i);
    client.publish(mqtt_topic, message);
    Serial.printf("Published %d to %s\n",i, mqtt_topic);
    M5.Lcd.setCursor(45, 45);
    M5.Lcd.printf("%d",i);
    delay(100);
}

void LCD_Clear() {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.setTextSize(2);
}

void setup() {
  Serial.begin(115200);
  M5.begin();
  M5.Lcd.setRotation(1);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.setCursor(45, 20);
  M5.Lcd.printf("Send Data");
  M5.Lcd.setCursor(45, 45);
  M5.Lcd.printf("With MQTT");


  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Connect to MQTT broker
  client.setServer(mqtt_server, mqtt_port);
  while (!client.connected()) {
    if (client.connect("ESP32Client")) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("Failed to connect to MQTT broker, retrying in 5 seconds...");
      delay(5000);
    }
  }
  LCD_Clear();
  M5.Lcd.setCursor(45, 20);
  M5.Lcd.printf("Val Pub:");
  pub(val);
}

void loop() {
  // Publish integer values to the MQTT topic
    M5.update();
    if(M5.BtnA.wasReleased()){
    val++;
    LCD_Clear();}
    else if (M5.BtnB.wasPressed()){
      
    val=0;
    LCD_Clear();
    }
      M5.Lcd.setCursor(45, 20);
      M5.Lcd.printf("Val Pub:");
      pub(val);
  


  delay(100); }