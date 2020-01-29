
#include "configuration.h" // holds all variables
#include "buttons.h" // handles the button presses
#include "run.h" // handles the timer
#include "set.h" // nothing here at the moment
#include "lcd.h" // manages all info om LCD


void setup() {
  /*******************************
    Start LCD
  *******************************/
  lcd.begin(lcdColumns, lcdRows);
  lcd.setCursor(0, 0); // print name of this program and boot message to the LCD
  lcd.print(programName);
  lcd.setCursor(0, 1);
  lcd.print("Booting ...");

  /*******************************
    Start serial
  *******************************/
  lcd.setCursor(0, 1);
  lcd.print("Starting serial ...");
  Serial.begin(9600);

  Serial.println(programName); // print information
  Serial.println(date);
  Serial.print("by ");
  Serial.print(author);
  Serial.println(email);
  Serial.println();

  /*******************************
    Define in- and outputs
  *******************************/
  Serial.println("Starting in- and outputs...");

  pinMode(startButtonPin, INPUT);
  pinMode(setButtonPin, INPUT);
  pinMode(upButtonPin, INPUT);
  pinMode(downButtonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(relayPin, OUTPUT);

  // set initial output states
  digitalWrite(relayPin, relayState);

  /*******************************
    Read time value from eeprom
  *******************************/
  Serial.println("Reading last time from eeprom ...");
  lcd.setCursor(0, 1);
  lcd.print("Reading last time ...");
  f = 0.00f;
  EEPROM.get(eeAddr, f); // read time from eeprom
  Serial.print("Found time: ");
  Serial.print(f);
  Serial.print(" seconds");
  Serial.println();

  if (isnan(f)) { // check if there is a value stored in eeprom
    Serial.println("No value found in eeprom");
    Serial.print("Storing value: ");
    Serial.println(dur);
    Serial.println();
    EEPROM.put(eeAddr, dur); // if not, store the predefined time
  }
  else {
    Serial.print("Found time stored in eeprom: ");
    Serial.println(f);
    Serial.println("Using it as set point temperature");
    Serial.println();
    dur = f; // else use it as set point
  }

  lcd.clear();

}

void loop() {
  /*******************************
    Read buttons
  *******************************/
  readButtons();

  if (relayState == HIGH) { // timer is running
    runScreen();
    countDown();
  }
  else if (setMode == HIGH) { // in set mode
    setScreen();
    //setTime();
  }
  else {
    waitScreen();
  }











}
