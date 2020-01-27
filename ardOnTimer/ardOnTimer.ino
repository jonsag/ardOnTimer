
#include "configuration.h";
#include "buttons.h";


void setup() {
  // start LCD
  lcd.begin(lcdColumns, lcdRows);
  // print name of this program and boot message to the LCD
  lcd.setCursor(0, 0);
  lcd.print(programName);
  lcd.setCursor(0, 1);
  lcd.print("Booting ...");

  // start serial port
  lcd.setCursor(0, 1);
  lcd.print("Starting serial ...");
  Serial.begin(9600);

  // print information
  Serial.println(programName);
  Serial.println(date);
  Serial.print("by ");
  Serial.print(author);
  Serial.println(email);
  Serial.println();

  // start in- and outputs
  Serial.println("Starting in- and outputs...");
  Serial.println();

  pinMode(startButtonPin, INPUT);
  pinMode(setButtonPin, INPUT);
  pinMode(upButtonPin, INPUT);
  pinMode(downButtonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(relayPin, OUTPUT);

  // set initial output states
  //digitalWrite(buzzerPin, buzzerState);
  digitalWrite(relayPin, relayState);

  lcd.clear();

}

void loop() {
  /*******************************
    Read buttons
  *******************************/
  readButtons();
  /*
  Serial.print("Start: ");
  Serial.print(startButtonState);
  Serial.print(", Set: ");
  Serial.print(setButtonState);
  Serial.print(", Up: ");
  Serial.print(upButtonState);
  Serial.print(", Down: ");
  Serial.print(downButtonState);
*/

  // set the relay:
  //digitalWrite(relayPin, relayState);

  /*
  Serial.print(", Buzzer: ");
  Serial.print(buzzerState);
  Serial.print(", Relay: ");
  Serial.println(relayState);
*/








}
