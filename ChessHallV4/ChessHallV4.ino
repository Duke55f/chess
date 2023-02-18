const int NUM_MULTIPLEXERS = 8;
const int NUM_SENSORS = 8;
const int MAIN_SELECT_PINS[3] = {2, 3, 4}; // Pin numbers for the S0, S1, and S2 selection pins of the main multiplexer
const int SUB_SELECT_PINS[3] = {5, 6, 7}; // Pin numbers for the S0, S1, and S2 selection pins of the sub-multiplexers
const int ANALOG_PIN = A0; // Pin for the analog input
int baselineValues[NUM_SENSORS]; // Array to store baseline readings for each sensor

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 3; i++) {
    pinMode(MAIN_SELECT_PINS[i], OUTPUT);
    pinMode(SUB_SELECT_PINS[i], OUTPUT);
  }
    createBaselineReadings();// Take a baseline reading for each sensor
}

void loop() {
  for (int mux = 0; mux < NUM_MULTIPLEXERS; mux++) {
    selectMainMultiplexer(mux); // Select the current sub-multiplexer using the main multiplexer
    for (int sensor = 0; sensor < NUM_SENSORS; sensor++) {
      selectSubMultiplexer(sensor); // Select the current sensor using the sub-multiplexer
      int sensorValue = analogRead(ANALOG_PIN); // Read the value of the current sensor
      int deviation = abs(sensorValue - baselineValues[sensor]); // Calculate the deviation from the baseline
      int binaryreading;
      if (deviation > 120){
          binaryreading = 1; 
          }
          else {binaryreading = 0;
          }
      Serial.print(binaryreading);
      Serial.print(", ");
    }
    Serial.println();
  }
  delay(100); // Delay for 1 second before reading the next multiplexer
  Serial.println();
}





void createBaselineReadings() {
  for (int sensor = 0; sensor < NUM_SENSORS; sensor++) {
    selectMainMultiplexer(0); // Select the first sub-multiplexer using the main multiplexer
    selectSubMultiplexer(sensor); // Select the current sensor using the sub-multiplexer
    int baselineValue = 0;
    for (int i = 0; i < 10; i++) { // Take 10 readings and average them
      baselineValue += analogRead(ANALOG_PIN);
      delay(10);
    }
    baselineValues[sensor] = baselineValue / 10; // Store the average reading as the baseline for this sensor
  }
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
