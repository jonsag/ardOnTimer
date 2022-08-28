String programName = "ardOnTimer";
String date = "20200130";
String author = "Jon Sagebrand";
String email = "jonsagebrand@gmail.com";

/*******************************
   EEPROM setup
 *******************************/
#include <EEPROM.h>   // include EEPROM library
const int eeAddr = 0; // address to store the time
int f;                // stores the time set in eeprom

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
const int setButtonPin = 9;
const int upButtonPin = 10;
const int downButtonPin = 11;

int startButtonReading;
int startButtonState; // the current reading from the start/stop/store button pin
int lastStartButtonState = LOW;

int setButtonReading;
int setButtonState; // the current reading from the set button pin
int lastSetButtonState = LOW;

int upButtonReading;
int upButtonState; // the current reading from the up button pin
int lastUpButtonState = LOW;
unsigned long repeatUpButton; // when was the button pressed

int downButtonReading;
int downButtonState; // the current reading from the down button pin
int lastDownButtonState = LOW;
unsigned long repeatDownButton; // when was the button pressed

/*******************************
   Buzzer setup
 *******************************/
const int buzzerPin = 13;

/*******************************
   Relay setup
 *******************************/
const int relayPin = 12;
int relayState = LOW; // the current state of the relay pin

/*******************************
   Debouncing
 *******************************/
unsigned long lastStartDebounceTime = 0; // the last time the output pin was toggled
unsigned long lastSetDebounceTime = 0;   // the last time the output pin was toggled
unsigned long lastUpDebounceTime = 0;    // the last time the output pin was toggled
unsigned long lastDownDebounceTime = 0;  // the last time the output pin was toggled

unsigned long debounceDelay = 20; // the debounce time; increase if the output flickers

/*******************************
   Tones
 *******************************/
const int startTone = 1500;
const int startLength = 200;

const int stopTone = 1500;
const int stopLength = 500;

const int setTone = 1750;
const int setLength = 200;

const int storeTone = 1750;
const int storeLength = 500;

const int upTone = 2000;
const int upLength = 100;

const int downTone = 1000;
const int downLength = 100;

const int errorTone = 500;
const int errorLength = 500;

/*******************************
   Times
 *******************************/
int dur = 180;      // default timer on-time
int timeLeft = dur; // counts down when timer is running

int seconds; // for converting seconds to hours, minutes and seconds
int h;
int m;
int s;
int t;

int newDur = dur;     // used when setting time
const int incr1 = 10; // increments for counting up/down
const int incr2 = 60;

int repeatTime = 500; // time to hold button down for increased speed

unsigned long startMillis; // used when timer is running

unsigned long animationMillis; // for animation in run screen

const unsigned int maxSeconds = 35999 - incr2; // max allowed value for timer, in seconds, min is 1 second (35999 = 9 hrs, 59 min, 59 sec, 65535 = 18 hrs, 12 min, 15 sec)

/*******************************
   Custom characters
 *******************************/
byte customUpArrow[8] = {
    0b00100,
    0b01110,
    0b10101,
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b00000};

byte customDownArrow[8] = {
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b10101,
    0b01110,
    0b00100,
    0b00000};

byte customBackslash[8] = {
    0b00000,
    0b10000,
    0b01000,
    0b00100,
    0b00010,
    0b00001,
    0b00000,
    0b00000};

/*******************************
   Progress bar
 *******************************/
byte customOneDot[8] = {
    0b00000,
    0b00000,
    0b00000,
    0b10000,
    0b00000,
    0b00000,
    0b00000,
    0b00000};

byte customTwoDots[8] = {
    0b00000,
    0b00000,
    0b00000,
    0b11000,
    0b00000,
    0b00000,
    0b00000,
    0b00000};

byte customThreeDots[8] = {
    0b00000,
    0b00000,
    0b00000,
    0b11100,
    0b00000,
    0b00000,
    0b00000,
    0b00000};

byte customFourDots[8] = {
    0b00000,
    0b00000,
    0b00000,
    0b11110,
    0b00000,
    0b00000,
    0b00000,
    0b00000};

int progress = 0;      // percent done
int smallStepProgress; // the remainder when first digit stripped from progress
int i;                 // counter

/*******************************
   Misc
 *******************************/
int counting = LOW; // HIGH when timer is running
int setMode = LOW;  // HIGH when in set mode

int timeOffset = 8; // where should time be printed on LCD
