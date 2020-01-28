
#include "configuration.h"
#include "buttons.h"
#include "run.h"
#include "set.h"
#include "lcd.h"


void setup() {
  // start LCD
  lcd.begin(lcdColumns, lcdRows);
  // print name of this program and boot message t  o the LCD
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
  Serial.println();https://rarbg.to/download.php?id=g1uc7vf&h=e99&f=21EroticAnal.19.04.06.Ivi.Rein.Youthful.Perfection.XXX.SD.MP4-KLEENEX-[rarbg.to].torrent

  pinMode(startButtonPin, INPUT);
  pinMode(setButtonPin, INPUT);
  pinMode(upButtonPin, INPUT);
  pinMode(downButtonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(relayPin, OUTPUT);

  // set initial output states
  digitalWrite(relayPin, relayState);

  lcd.clear();

}

void loop() {
  /*******************************
    Read buttons
  *******************************/
  readButtons();

  if(relayState == HIGH) {
    runScreen();
    countDown();
  }
  else if(setMode == HIGH) {
    setScreen();
    //setTime();
  }
  else {
    waitScreen();
  }











}
