// Blynk Template ID and Name
#define BLYNK_TEMPLATE_ID "TMPL3h4VcnZ3J"
#define BLYNK_TEMPLATE_NAME "Hamilton"


// Blynk credentials
char auth[] = "RJs1PyRcVcyw7zKxg2UZx4RPIZWfLOML";

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>


// WiFi credentials
const char* ssid = "Pheonix";
const char* pass = "random12345";


// Motor pins
#define ENA   D5  // Right motor
#define ENB   D6  // Left motor
#define IN_1  D1  // Right motor
#define IN_2  D2  // Right motor
#define IN_3  D3  // Left motor
#define IN_4  D4  // Left motor

// Servo pins
#define LEFT_SERVO_PIN D7
#define RIGHT_SERVO_PIN D8

// Initialize servos
Servo servoLeft;
Servo servoRight;

// Speed for motor control
int speedCar = 800; // Adjust as needed

#define BLYNK_PRINT Serial  // This enables Serial debug prints

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);

  // Attach servos to respective pins
  servoLeft.attach(LEFT_SERVO_PIN);
  servoRight.attach(RIGHT_SERVO_PIN);

  Serial.begin(115200);

  // Connecting to WiFi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  // Connecting to Blynk
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
}

// Blynk virtual pin functions
BLYNK_WRITE(V0) {
  int state = param.asInt();
  if (state) {
    accelerate();
  } else {
    brake();
  }
}

BLYNK_WRITE(V1) {
  int state = param.asInt();
  if (state) {
    brake();
  }
}

BLYNK_WRITE(V2) {
  int state = param.asInt();
  if (state) {
    turnLeft();
  }
}

BLYNK_WRITE(V3) {
  int state = param.asInt();
  if (state) {
    turnRight();
  }
}

void accelerate() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);
}

void brake() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);
}

void turnLeft() {
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, 0.6 * 1023);  // 60% of max speed

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);
  servoLeft.write(90 - 15);  // 15 degrees to the left
  servoRight.write(90 - 5);  // 5 degrees to the left
}

void turnRight() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, 0.6 * 1023);  // 60% of max speed
  servoLeft.write(90 + 5);  // 5 degrees to the right
  servoRight.write(90 + 15);  // 15 degrees to the right
}
