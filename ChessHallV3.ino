const int NUM_MULTIPLEXERS = 8;
const int NUM_SENSORS = 8;
const int MAIN_SELECT_PINS[3] = {2, 3, 4}; // Pin numbers for the S0, S1, and S2 selection pins of the main multiplexer
const int SUB_SELECT_PINS[3] = {5, 6, 7}; // Pin numbers for the S0, S1, and S2 selection pins of the sub-multiplexers
const int ANALOG_PIN = A0; // Pin for the analog input

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 3; i++) {
    pinMode(MAIN_SELECT_PINS[i], OUTPUT);
    pinMode(SUB_SELECT_PINS[i], OUTPUT);
  }
}

void loop() {
  for (int mux = 0; mux < NUM_MULTIPLEXERS; mux++) {
    selectMainMultiplexer(mux); // Select the current sub-multiplexer using the main multiplexer
    for (int sensor = 0; sensor < NUM_SENSORS; sensor++) {
      selectSubMultiplexer(sensor); // Select the current sensor using the sub-multiplexer
      int sensorValue = analogRead(ANALOG_PIN); // Read the value of the current sensor

      Serial.print(sensorValue);
      Serial.print(", ");
    }
    Serial.print("  ");
  }
  delay(100); // Delay for 1 second before reading the next multiplexer
  Serial.println();
}


void selectMainMultiplexer(int mux) {
  for (int i = 0; i < 3; i++) {
    digitalWrite(MAIN_SELECT_PINS[i], (mux >> i) & 1);
  }
}

void selectSubMultiplexer(int sensor) {
  for (int i = 0; i < 3; i++) {
    digitalWrite(SUB_SELECT_PINS[i], (sensor >> i) & 1);
  }
}
