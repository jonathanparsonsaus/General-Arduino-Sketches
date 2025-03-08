#include <IRremote.h>
#include <Servo.h>

#define IR_RECEIVE_PIN 3  // IR receiver connected to digital pin D3
#define SERVO_PIN 2        // Servo signal connected to digital pin D2
#define MIN_ANGLE 0        // Minimum servo angle
#define MAX_ANGLE 180      // Maximum servo angle

Servo myServo;
int servoAngle = 90; // Start at the middle position

void setup() {
    Serial.begin(115200);
    while (!Serial);  // Wait for Serial Monitor to open (optional)

    pinMode(IR_RECEIVE_PIN, INPUT_PULLUP); // Enable internal pull-up resistor
    Serial.println("IR Receiver Ready...");

    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start IR receiver
    
    myServo.attach(SERVO_PIN);
    myServo.write(servoAngle); // Set initial position
    Serial.print("Initial Servo Angle: ");
    Serial.println(servoAngle);
}

void loop() {
    if (IrReceiver.decode()) {
        uint32_t receivedCode = IrReceiver.decodedIRData.decodedRawData;
        Serial.print("Received IR Code: ");
        Serial.println(receivedCode, HEX); // Print received IR code in HEX

        // Check for the correct IR codes and update servo angle
        if (receivedCode == 0x587A) { // Decrease angle
            servoAngle = max(MIN_ANGLE, servoAngle - 10);
        } else if (receivedCode == 0x587B) { // Increase angle
            servoAngle = min(MAX_ANGLE, servoAngle + 10);
        }

        // Move the servo to the new angle and print the angle
        myServo.write(servoAngle); // Update servo position
        Serial.print("Servo Angle: ");
        Serial.println(servoAngle);
        
        IrReceiver.resume(); // Ready to receive the next signal
    }
}
