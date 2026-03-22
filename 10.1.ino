#include <IRremote.hpp>

#define IR_PIN 6
#define RED_LED 3
#define GREEN_LED 5

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  Serial.begin(9600);
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
  if (IrReceiver.decode()) {
    uint32_t code = IrReceiver.decodedIRData.decodedRawData;

    Serial.print("Code: ");
    Serial.println(code, HEX);

    // Example logic:
    // Replace these values with your remote's actual codes
    if (code == 0xFFA25D) {  // Button 1
      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);
    }
    else if (code == 0xFF629D) {  // Button 2
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
    }
    else if (code == 0xFFE21D) {  // Button 3
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, LOW);
    }

    IrReceiver.resume(); // ready for next signal
  }
}
