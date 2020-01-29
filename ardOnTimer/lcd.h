

void secondsToHMS() { // converts seconds to hour, minutes and seconds
  s = t % 60;

  t = (t - s) / 60;
  m = t % 60;

  t = (t - m) / 60;
  h = t;

  // --------hh:mm:ss
  // print hours
  lcd.setCursor(timeOffset, 0); // first hours digit
  if (h > 0) {
    if (h > 9) { // hours is larger than 9
      lcd.print(h);
    }
    else {
      lcd.print(" "); // prints space instead of first hour digit
      lcd.setCursor(timeOffset + 1, 0); // second hours digit
      lcd.print(h);
    }
    lcd.setCursor(timeOffset + 2, 0); // colon after hours
    lcd.print(":");
  }
  else {
    lcd.print("   "); // prints three spaces instead of hours and colon
  }

  // print minutes
  lcd.setCursor(timeOffset + 3, 0); // first minutes digit
  if (m > 9) {
    lcd.print(m);
  }
  else {
    lcd.print(" "); // prints space instead of first minute digit
    lcd.setCursor(timeOffset + 4, 0); // second minutes digit
  }
  lcd.setCursor(timeOffset + 5, 0); // colon after minutes
  lcd.print(":");

  // print seconds
  lcd.setCursor(timeOffset + 6, 0); // first seconds digit
  if (s > 9) {
    lcd.print(s);
  }
  else {
    lcd.print("0"); // prints 0 at first seconds digit
    lcd.setCursor(timeOffset + 7, 0); // second seconds digit
    lcd.print(s);
  }
}

/*******************************
    Wait/Standby screen
  *******************************/
void waitScreen() {
  lcd.setCursor(0, 0);
  lcd.print("Timer: ");

  t = dur;
  secondsToHMS();

  lcd.setCursor(0, 1);
  lcd.print("Start or Set");
}

/*******************************
    Run screen
  *******************************/
void runScreen() {
  lcd.setCursor(0, 0);
  lcd.print("Running: ");

  t = timeLeft;
  secondsToHMS();

  lcd.setCursor(0, 1);
  lcd.print("Stop");
}

/*******************************
    Set screen
  *******************************/
void setScreen() {
  lcd.setCursor(0, 0);
  lcd.print("Set timer: ");

  t = newDur;
  secondsToHMS();

  lcd.setCursor(0, 1);
  lcd.print("Store,Exit or ");
  lcd.setCursor(14, 1);
  lcd.write(24); // up arrow (ascii 24 or 30 is up arrow, ascii 25 or 31 is down arrow ascii 18 is up-down arrow, see http://www.martyncurrey.com/wp-content/uploads/2017/03/LCDs_12_CharSet_01.jpg)
  lcd.setCursor(15, 1);
  lcd.write(25); // down arrow ()
  //
}
