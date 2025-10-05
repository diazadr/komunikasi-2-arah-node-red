#include <ESP8266WiFi.h>
#include <MQTT.h>
#include <Servo.h>

const char* ssid = "ESPPolmanBandung";
const char* pass = "esppolmanbandung";
WiFiClient net;
MQTTClient client;

Servo myServo;
#define SERVO_PIN D4
#define BUTTON_B_PIN D2

int currentAngle = 90;
bool lastButtonB = HIGH;

void messageReceived(String &topic, String &payload) {
  Serial.println("MQTT: " + topic + " = " + payload);

  if (topic == "perintah/servo") {
    int angle = payload.toInt();
    if (angle >= 0 && angle <= 180) {
      myServo.write(angle);
      currentAngle = angle;
      char buf[8];
      sprintf(buf, "%d", currentAngle);
      client.publish("status/servo", buf, true, 1);
      Serial.printf("Servo ke %d derajat\n", angle);
    }
  }
}

void connect() {
  Serial.print("WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Terhubung WiFi!");

  client.setWill("status/device_servo", "OFFLINE", true, 1);

  Serial.print("MQTT...");
  while (!client.connect("ESP8266-Servo", "nodered-mes", "trf4Lyf3Z0CjLhe8")) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Terhubung MQTT!");

  client.subscribe("perintah/servo", 1);
  client.publish("status/device_servo", "ONLINE", true, 1);

  char buf[8];
  sprintf(buf, "%d", currentAngle);
  client.publish("status/servo", buf, true, 1);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  myServo.attach(SERVO_PIN);
  myServo.write(currentAngle);

  pinMode(BUTTON_B_PIN, INPUT_PULLUP);

  client.begin("nodered-mes.cloud.shiftr.io", 1883, net);
  client.onMessage(messageReceived);
  connect();
}

void loop() {
  client.loop();
  if (!client.connected()) connect();

  // cek tombol B
  bool state = digitalRead(BUTTON_B_PIN);
  if (state == LOW && lastButtonB == HIGH) {
    Serial.println("Button B ditekan -> Kirim TOGGLE LED");
    client.publish("perintah/rgb", "TOGGLE");
  }
  lastButtonB = state;

  yield();
}