
String programName = "ardOnTimer";
String date = "20200126";
String author = "Jon Sagebrand";
String email = "jonsagebrand@gmail.com";

/*******************************
   LCD setup
 *******************************/
// include the LCD library
#include <LiquidCrystal.h>
// set LCD pins
int LCD_RS = 2; // LCD RS, pin 4
int LCD_EN = 3; // LCD E, pin 6, Enable
int LCD_D4 = 4; // LCD D4, pin 11, databit 4
int LCD_D5 = 5; // LCD D5, pin 12, databit 5
int LCD_D6 = 6; // LCD D6, pin 13, databit 6
int LCD_D7 = 7; // LCD D7, pin 14, databit7
/* other pins on LCD are:
   VSS, pin 1, GND
   VDD, pin 2, +5V
   V0, pin 3, 10k potentiometer, ends to +5V and GND, middle pin to V0, contrast
   R/W, pin 5, GND, Read/Write
   A, pin 15, 220ohm resistor, one end to +5V, other to A, back light anode, ~+4.2V
   K, pin 16, GND, back light cathode
   D0, pin 7, databit 0, not used/connected
   D1, pin 8, databit 1, not used/connected
   D2, pin 9, databit 2, not used/connected
   D3, pin 10, databit 3, not used/connected
*/
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
// columns and rows of the LCD
int lcdColumns = 16;
int lcdRows = 2;

/*******************************
   Buttons setup
 *******************************/
const int startButtonPin = 8;
const int stopButtonPin = 9;
const int upButtonPin = 10;
const int downButtonPin = 11;

int startButtonState;             // the current reading from the start button pin
int lastStartButtonState = LOW;

int stopButtonState;             // the current reading from the stop button pin
int lastStopButtonState = LOW;

int upButtonState;             // the current reading from the up button pin
int lastUpButtonState = LOW;

int downButtonState;             // the current reading from the down button pin
int lastDownButtonState = LOW;

/*******************************
   Buzzer setup
 *******************************/
const int buzzerPin = 12;
int buzzerState = LOW;         // the current state of the buzzer pin

/*******************************
   Relay setup
 *******************************/
const int relayPin = 13;
int relayState = LOW;         // the current state of the relay pin

/*******************************
   Debouncing
 *******************************/
// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastStartDebounceTime = 0;  // the last time the output pin was toggled
unsigned long startDebounceDelay = 50;    // the debounce time; increase if the output flickers
unsigned long lastStopDebounceTime = 0;  // the last time the output pin was toggled
unsigned long stopDebounceDelay = 50;    // the debounce time; increase if the output flickers
unsigned long lastUpDebounceTime = 0;  // the last time the output pin was toggled
unsigned long upDebounceDelay = 50;    // the debounce time; increase if the output flickers
unsigned long lastDownDebounceTime = 0;  // the last time the output pin was toggled
unsigned long downDebounceDelay = 50;    // the debounce time; increase if the output flickers


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
  pinMode(stopButtonPin, INPUT);
  pinMode(upButtonPin, INPUT);
  pinMode(downButtonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(relayPin, OUTPUT);

  // set initial output states
  digitalWrite(buzzerPin, buzzerState);
  digitalWrite(relayPin, relayState);

  lcd.clear();

}

void loop() {
  /*******************************
    Read buttons
  *******************************/
  // read the state of the switch into a local variable:
  int startReading = digitalRead(startButtonPin);
  int stopReading = digitalRead(stopButtonPin);
  int upReading = digitalRead(upButtonPin);
  int downReading = digitalRead(downButtonPin);

  // If the switch changed, due to noise or pressing:
  if (startReading != lastStartButtonState) {
    // reset the debouncing timer
    lastStartDebounceTime = millis();
  }
  if (stopReading != lastStopButtonState) {
    // reset the debouncing timer
    lastStopDebounceTime = millis();
  }
  if (upReading != lastUpButtonState) {
    // reset the debouncing timer
    lastUpDebounceTime = millis();
  }
  if (downReading != lastDownButtonState) {
    // reset the debouncing timer
    lastDownDebounceTime = millis();
  }

  if ((millis() - lastStartDebounceTime) > startDebounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (startReading != startButtonState) {
      startButtonState = startReading;

      // only toggle the LED if the new button state is HIGH
      if (startButtonState == HIGH) {
        buzzerState = !buzzerState;
      }
    }
  }

  if ((millis() - lastStopDebounceTime) > stopDebounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (stopReading != stopButtonState) {
      stopButtonState = stopReading;

      // only toggle the LED if the new button state is HIGH
      //if (buttonState == HIGH) {
      //  ledState = !ledState;
      //}
    }
  }
  if ((millis() - lastUpDebounceTime) > upDebounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (upReading != upButtonState) {
      upButtonState = upReading;

      // only toggle the LED if the new button state is HIGH
      //if (buttonState == HIGH) {
      //  ledState = !ledState;
      //}
    }
  }
  if ((millis() - lastDownDebounceTime) > downDebounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (downReading != downButtonState) {
      downButtonState = downReading;

      // only toggle the LED if the new button state is HIGH
      //if (buttonState == HIGH) {
      //  ledState = !ledState;
      //}
    }
  }

  // set the relay:
  digitalWrite(relayPin, relayState);

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastStartButtonState = startReading;
  lastStopButtonState = stopReading;
  lastUpButtonState = upReading;
  lastDownButtonState = downReading;






}
