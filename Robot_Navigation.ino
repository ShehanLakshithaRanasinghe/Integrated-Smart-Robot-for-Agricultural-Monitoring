#include <Wire.h>
#include <VL53L0X.h>

// LED Pins
#define LED_FORWARD 7
#define LED_RIGHT   8
#define LED_LEFT    9

// XSHUT Pins
#define FRONT_LEFT_XSHUT  2
#define FRONT_RIGHT_XSHUT 3
#define SIDE_RIGHT_XSHUT  4
#define SIDE_LEFT_XSHUT   5

// Updated Thresholds (cm)
#define FRONT_CLEAR 20    // Forward when >20cm
#define SIDE_CLEAR 20     // Turn when side >20cm
#define RESUME_CLEAR 30   // Resume forward when >30cm
#define DANGER_ZONE 10    // New: Immediate obstacle threshold

VL53L0X frontLeft, frontRight, sideRight, sideLeft;

void setup() {
  Serial.begin(9600);
  
  // Initialize LEDs
  pinMode(LED_FORWARD, OUTPUT);
  pinMode(LED_RIGHT, OUTPUT);
  pinMode(LED_LEFT, OUTPUT);

  // Reset all sensors
  digitalWrite(FRONT_LEFT_XSHUT, LOW);
  digitalWrite(FRONT_RIGHT_XSHUT, LOW);
  digitalWrite(SIDE_RIGHT_XSHUT, LOW);
  digitalWrite(SIDE_LEFT_XSHUT, LOW);
  pinMode(FRONT_LEFT_XSHUT, OUTPUT);
  pinMode(FRONT_RIGHT_XSHUT, OUTPUT);
  pinMode(SIDE_RIGHT_XSHUT, OUTPUT);
  pinMode(SIDE_LEFT_XSHUT, OUTPUT);
  delay(10);

  // Initialize sensors
  initSensor(frontLeft, FRONT_LEFT_XSHUT, 0x30);
  initSensor(frontRight, FRONT_RIGHT_XSHUT, 0x31);
  initSensor(sideRight, SIDE_RIGHT_XSHUT, 0x32);
  initSensor(sideLeft, SIDE_LEFT_XSHUT, 0x33);

  Serial.println("System Ready - Danger Zone (10cm) Enabled");
}

void initSensor(VL53L0X &sensor, uint8_t xshutPin, uint8_t address) {
  digitalWrite(xshutPin, HIGH);
  delay(10);
  sensor.init();
  sensor.setAddress(address);
  sensor.startContinuous();
}

void loop() {
  // Read all sensors
  int fl = getDistance(frontLeft);
  int fr = getDistance(frontRight);
  int sr = getDistance(sideRight);
  int sl = getDistance(sideLeft);

  Serial.print("FL:"); Serial.print(fl);
  Serial.print("cm FR:"); Serial.print(fr);
  Serial.print("cm SR:"); Serial.print(sr);
  Serial.print("cm SL:"); Serial.print(sl);
  Serial.println("cm");

  // Danger detection (any sensor <10cm)
  if (fl < DANGER_ZONE  fr < DANGER_ZONE  sr < DANGER_ZONE || sl < DANGER_ZONE) {
    emergencyStop();
    return; // Skip rest of loop until next cycle
  }

  if (fl > FRONT_CLEAR && fr > FRONT_CLEAR) {
    setLEDs(HIGH, LOW, LOW); // Forward
  } 
  else {
    setLEDs(LOW, LOW, LOW); // Stop
    
    // Continuous turning with obstacle checking
    while (fl <= RESUME_CLEAR || fr <= RESUME_CLEAR) {
      fl = getDistance(frontLeft);
      fr = getDistance(frontRight);
      sr = getDistance(sideRight);
      sl = getDistance(sideLeft);

      // Danger check during turning
      if (sr < DANGER_ZONE || sl < DANGER_ZONE) {
        emergencyStop();
        break;
      }

      // Turn decision
      if (sr > SIDE_CLEAR && sl > SIDE_CLEAR) {
        // Both sides clear - prefer right
        setLEDs(LOW, HIGH, LOW);
      }
      else if (sr > SIDE_CLEAR) {
        setLEDs(LOW, HIGH, LOW); // Right turn
      } 
      else if (sl > SIDE_CLEAR) {
        setLEDs(LOW, LOW, HIGH); // Left turn
      }
      else {
        emergencyStop();
        break;
      }
      delay(100);
    }
  }
  delay(100);
}

void emergencyStop() {
  setLEDs(LOW, LOW, LOW);
  Serial.println("!DANGER! Obstacle <10cm detected");
  delay(1000); // Full stop for 1 second
}

int getDistance(VL53L0X &sensor) {
  return sensor.readRangeContinuousMillimeters() / 10; // mm to cm
}

void setLEDs(bool fwd, bool right, bool left) {
  digitalWrite(LED_FORWARD, fwd);
  digitalWrite(LED_RIGHT, right);
  digitalWrite(LED_LEFT, left);
}
