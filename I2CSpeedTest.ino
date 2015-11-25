#include <Wire.h>

long speed[] = {
  50, 100, 200, 250, 400, 500, 600, 700, 800
};
const int speeds = sizeof(speed) / sizeof(speed[0]);

#define address 0x20
uint8_t initial_twbr = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  Serial.println("I2C speed test");
  Serial.println("Gives you an idea what changing bus speed makes");
  Serial.println("Time is given in microseconds (4us steps)");
  Serial.println("'*' Denotes the default I2C bus speed");
  Serial.println("--------------------------------------------------");
  Serial.println();
  Serial.print(" **   Using device address: 0x");
  Serial.print((address), HEX);
  Serial.println(" **");
  Serial.println();
  delay(100);
  initial_twbr = TWBR;
 
  bool found[speeds];
  uint16_t read_time[speeds];
  uint8_t twbr_val[speeds];
  for (uint8_t s = 0; s < speeds ; s++) {



    TWBR = (F_CPU / (speed[s] * 1000) - 16) / 2;
    twbr_val[s] = TWBR;
    uint16_t currentmicros = micros();
    Wire.beginTransmission (address);
    found[s] = (Wire.endTransmission () == 0);

    read_time[s] = (uint16_t)(micros() - currentmicros);

    // give device 100 millis
    delay(100);
  }

  Serial.println("  Speed     Found     Time   Def.");
  Serial.println("----------------------------------");
  for (uint8_t s = 0; s < speeds ; s++) {

    if (speed[s] == 50) {
      Serial.print("  ");
    }
    else {
      Serial.print(" ");
    }

    Serial.print(speed[s]);
    Serial.print(" kHz      ");
    /*
      Serial.print(twbr_val[s]);
      Serial.print("    ");
    */
    Serial.print(found[s]);
    Serial.print("        ");
    if (read_time[s] < 100) {
      Serial.print(" ");
    }
    Serial.print(read_time[s]);

    if (twbr_val[s] == initial_twbr) {
      Serial.print("    *");
    }

    Serial.println();

  }


}



void loop() {
}
