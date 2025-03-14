#include <BluetoothSerial.h>

// Define motor pins
#define MOTOR_A_PIN1  26
#define MOTOR_A_PIN2  27
#define MOTOR_B_PIN1  14
#define MOTOR_B_PIN2  12
#define ENA_PIN       25 // PWM capable pin
#define ENB_PIN       13 // PWM capable pin

BluetoothSerial SerialBT;

void setup() {
  // Initialize Serial port for debugging
  Serial.begin(115200);

  // Initialize Bluetooth serial communication
  SerialBT.begin("ESP32_RC_Car");

  // Set motor pins as outputs
  pinMode(MOTOR_A_PIN1, OUTPUT);
  pinMode(MOTOR_A_PIN2, OUTPUT);
  pinMode(MOTOR_B_PIN1, OUTPUT);
  pinMode(MOTOR_B_PIN2, OUTPUT);

  // Set ENA and ENB pins as outputs
  pinMode(ENA_PIN, OUTPUT);
  pinMode(ENB_PIN, OUTPUT);

  // Stop the motors initially
  stopMotors();
}

void loop() {
  if (SerialBT.available()) {
    char command = SerialBT.read();

    // Interpret received commands
    switch (command) {
      case 'F': // Move forward
        moveForward();
        break;
      case 'B': // Move backward
        moveBackward();
        break;
      case 'L': // Turn left
        turnLeft();
        break;
      case 'R': // Turn right
        turnRight();
        break;
      case 'S': // Stop
        stopMotors();
        break;
      default:
        break;
    }
  }
}

void moveForward() {
  digitalWrite(MOTOR_A_PIN1, HIGH);
  digitalWrite(MOTOR_A_PIN2, LOW);
  digitalWrite(MOTOR_B_PIN1, HIGH);
  digitalWrite(MOTOR_B_PIN2, LOW);
  analogWrite(ENA_PIN, 255); // Full speed
  analogWrite(ENB_PIN, 255); // Full speed
}

void moveBackward() {
  digitalWrite(MOTOR_A_PIN1, LOW);
  digitalWrite(MOTOR_A_PIN2, HIGH);
  digitalWrite(MOTOR_B_PIN1, LOW);
  digitalWrite(MOTOR_B_PIN2, HIGH);
  analogWrite(ENA_PIN, 255); // Full speed
  analogWrite(ENB_PIN, 255); // Full speed
}

void turnLeft() {
  digitalWrite(MOTOR_A_PIN1, LOW);
  digitalWrite(MOTOR_A_PIN2, HIGH);
  digitalWrite(MOTOR_B_PIN1, HIGH);
  digitalWrite(MOTOR_B_PIN2, LOW);
  analogWrite(ENA_PIN, 150); // Adjust speed as needed
  analogWrite(ENB_PIN, 150); // Adjust speed as needed
}

void turnRight() {
  digitalWrite(MOTOR_A_PIN1, HIGH);
  digitalWrite(MOTOR_A_PIN2, LOW);
  digitalWrite(MOTOR_B_PIN1, LOW);
  digitalWrite(MOTOR_B_PIN2, HIGH);
  analogWrite(ENA_PIN, 150); // Adjust speed as needed
  analogWrite(ENB_PIN, 150); // Adjust speed as needed
}

void stopMotors() {
  digitalWrite(MOTOR_A_PIN1, LOW);
  digitalWrite(MOTOR_A_PIN2, LOW);
  digitalWrite(MOTOR_B_PIN1, LOW);
  digitalWrite(MOTOR_B_PIN2, LOW);
}