#include <ESP8266WiFi.h>
#include <MQTT.h>

const char* ssid = "ESPPolmanBandung";
const char* pass = "esppolmanbandung";
WiFiClient net;
MQTTClient client;

#define RED_PIN   D5
#define GREEN_PIN D6
#define BLUE_PIN  D7
#define BUTTON_A_PIN D1   // Push button A

String lastColor = "#000000";
bool lastButtonA = HIGH; // karena pakai INPUT_PULLUP
bool ledOn = false;

// untuk toggle servo
int servoPos = 0;  // posisi terakhir
bool servoToggle = false;

void setColor(int r, int g, int b) {
  analogWrite(RED_PIN, 255 - r);
  analogWrite(GREEN_PIN, 255 - g);
  analogWrite(BLUE_PIN, 255 - b);
  Serial.printf("RGB -> R:%d G:%d B:%d\n", r, g, b);
}

void messageReceived(String &topic, String &payload) {
  Serial.println("MQTT: " + topic + " = " + payload);

  if (topic == "perintah/rgb") {
    if (payload == "TOGGLE") {
      ledOn = !ledOn;
      if (ledOn) {
        setColor(255, 0, 0);
        lastColor = "#FF0000";
      } else {
        setColor(0, 0, 0);
        lastColor = "#000000";
      }
    } else {
      String hex = payload;
      if (hex.startsWith("#")) hex = hex.substring(1);
      long number = (long) strtol(hex.c_str(), NULL, 16);
      int r = (number >> 16) & 0xFF;
      int g = (number >> 8) & 0xFF;
      int b = number & 0xFF;
      setColor(r, g, b);
      lastColor = "#" + hex;
    }
    client.publish("status/rgb", lastColor, true, 1);
  }
}

void connect() {
  Serial.print("WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Terhubung WiFi!");

  client.setWill("status/device_rgb", "OFFLINE", true, 1);

  Serial.print("MQTT...");
  while (!client.connect("ESP8266-RGB", "nodered-mes", "trf4Lyf3Z0CjLhe8")) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Terhubung MQTT!");

  client.subscribe("perintah/rgb", 1);
  client.publish("status/device_rgb", "ONLINE", true, 1);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  analogWriteRange(255);
  setColor(0, 0, 0);

  pinMode(BUTTON_A_PIN, INPUT_PULLUP);

  client.begin("nodered-mes.cloud.shiftr.io", 1883, net);
  client.onMessage(messageReceived);
  connect();
}

void loop() {
  client.loop();
  if (!client.connected()) connect();

  // cek tombol A
  bool state = digitalRead(BUTTON_A_PIN);
  if (state == LOW && lastButtonA == HIGH) {
    servoToggle = !servoToggle;
    if (servoToggle) {
      servoPos = 180; // posisi maksimal
    } else {
      servoPos = 0;   // balik lagi
    }
    char buf[8];
    sprintf(buf, "%d", servoPos);
    client.publish("perintah/servo", buf); 

    Serial.printf("Button A ditekan -> Servo ke %d derajat\n", servoPos);
  }
  lastButtonA = state;

  yield();
}
