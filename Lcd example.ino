#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Create an LCD object with address 0x27, 16 columns, and 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Buzzer pin (digital I/O pin)
const int BUZZER_PIN = 8;

// Example custom character (a small heart)
byte heart[8] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000
};

// ---------------------------------------------------------------------------
// Setup
// ---------------------------------------------------------------------------
void setup() {
  pinMode(BUZZER_PIN, OUTPUT);

  // Initialize I2C and LCD
  Wire.begin();
  lcd.init();          // Initialize the LCD
  lcd.backlight();     // Turn on LCD backlight

  // Create a custom character (stored in slot 0)
  lcd.createChar(0, heart);

  // Start with a friendly beep
  tone(BUZZER_PIN, 1000, 300); // 1000 Hz for 300 ms
  delay(500);

  // Intro message
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Fantastic LCD!");
  lcd.setCursor(0, 1);
  lcd.print("with Buzzer :)");

  // Another quick beep
  tone(BUZZER_PIN, 1200, 300);
  delay(2000);
  noTone(BUZZER_PIN);
}

// ---------------------------------------------------------------------------
// Main Loop
// ---------------------------------------------------------------------------
void loop() {
  // 1) Demonstrate custom character
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("I ");
  lcd.write(byte(0)); // The heart character
  lcd.print(" Arduino!");
  beepBuzzer(2, 100); // beep 2 times, each 100 ms
  delay(2000);

  // 2) Scrolling text demo
  scrollText("Scrolling text is super fun!", 200);
  delay(1000);

  // 3) Blink text demo
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Blinking text...");
  for (int i = 0; i < 5; i++) {
    lcd.display();       // Turn LCD display on
    beepBuzzer(1, 150);  // Single short beep
    delay(500);
    lcd.noDisplay();     // Turn LCD display off
    delay(500);
  }
  lcd.display(); // Restore display
  delay(1000);
}

// ---------------------------------------------------------------------------
// Helper function to scroll text across the LCD
// ---------------------------------------------------------------------------
void scrollText(const String &message, int speedDelay) {
  lcd.clear();
  // Print the message one character at a time, shifting left
  for (int i = 0; i < message.length(); i++) {
    lcd.scrollDisplayLeft();
    lcd.setCursor(15, 0);         // Rightmost column, top row
    lcd.write(message[i]);
    beepBuzzer(1, 50);           // Subtle beep for each character
    delay(speedDelay);
  }
}

// ---------------------------------------------------------------------------
// Simple beep function (for a passive buzzer, tone freq matters more)
// times = how many beeps, duration = ms each beep
// ---------------------------------------------------------------------------
void beepBuzzer(int times, int duration) {
  for (int i = 0; i < times; i++) {
    tone(BUZZER_PIN, 1000, duration); // 1 kHz
    delay(duration + 50);
  }
}
