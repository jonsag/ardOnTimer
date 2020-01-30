#include "configuration.h" // sets all variables
#include "buttons.h" // handles the button presses
#include "lcd.h" // manages all info om LCD
#include "run.h" // handles the timer function


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
  lcd.print("Starting serial ");
  
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
  lcd.setCursor(0, 1);
  lcd.print("Starting in/out ");
  Serial.println("Starting in- and outputs...");
  Serial.println();

  pinMode(startButtonPin, INPUT);
  pinMode(setButtonPin, INPUT);
  pinMode(upButtonPin, INPUT);
  pinMode(downButtonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(relayPin, OUTPUT);

  digitalWrite(relayPin, relayState);   // set initial output states

  /*******************************
    Read time value from eeprom
  *******************************/
  lcd.setCursor(0, 1);
  lcd.print("Reading EEPROM  ");
  Serial.println("Reading last time from eeprom ...");

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
    Serial.println("Using it for timer");
    Serial.println();
    dur = f; // else use it as set point
  }

  /*******************************
      Build custom characters
    *******************************/
  lcd.setCursor(0, 1);
  lcd.print("Building chars  ");
  Serial.println("Building characters ...");
  Serial.println();

  lcd.createChar(1, customOneDot);
  lcd.createChar(2, customTwoDots);
  lcd.createChar(3, customThreeDots);
  lcd.createChar(4, customFourDots);
  lcd.createChar(5, customUpArrow);
  lcd.createChar(6, customDownArrow);
  lcd.createChar(7, customBackslash);

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
