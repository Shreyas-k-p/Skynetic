// No special library required for flex sensor or dummy pressure test

#define FLEX_PIN       3   // ADC pin connected to flex sensor
#define PRESSURE_PIN   4   // ADC pin connected to analog output of pressure sensor (if analog version used)
#define TOUCH_LED     33   // Green LED pin
#define SLAP_LED      32   // Red LED pin

#define FLEX_THRESHOLD       1800  // Change based on calibration
#define PRESSURE_TOUCH_MIN    300  // mbar value for soft touch
#define PRESSURE_SLAP_MIN    1000  // mbar value for slap

void setup() {
  Serial.begin(115200);

  pinMode(FLEX_PIN, INPUT);
  pinMode(PRESSURE_PIN, INPUT);
  pinMode(TOUCH_LED, OUTPUT);
  pinMode(SLAP_LED, OUTPUT);

  digitalWrite(TOUCH_LED, LOW);
  digitalWrite(SLAP_LED, LOW);
}

void loop() {
  int flexValue = analogRead(FLEX_PIN);
  int pressureValue = analogRead(PRESSURE_PIN);  // Simulating pressure in analog
  float mappedPressure = map(pressureValue, 0, 4095, 0, 1500); // Simulating mbar

  Serial.print("Flex: ");
  Serial.print(flexValue);
  Serial.print(" | Pressure: ");
  Serial.println(mappedPressure);

  // Decision Logic
  if (flexValue > FLEX_THRESHOLD) {
    if (mappedPressure > PRESSURE_SLAP_MIN) {
      digitalWrite(SLAP_LED, HIGH);
      digitalWrite(TOUCH_LED, LOW);
    } else if (mappedPressure > PRESSURE_TOUCH_MIN) {
      digitalWrite(TOUCH_LED, HIGH);
      digitalWrite(SLAP_LED, LOW);
    } else {
      digitalWrite(TOUCH_LED, LOW);
      digitalWrite(SLAP_LED, LOW);
    }
  } else {
    digitalWrite(TOUCH_LED, LOW);
    digitalWrite(SLAP_LED, LOW);
  }

  delay(200);
}