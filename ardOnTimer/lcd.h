

void secondsToHMS() {
  //const uint32_t seconds
  //uint16_t &h
  //uint8_t &m
  //uint8_t &s

  //uint32_t t = seconds;

  t = seconds;

  s = t % 60;

  t = (t - s) / 60;
  m = t % 60;

  t = (t - m) / 60;
  h = t;

  if (m > 9) {
    lenm = 2;
  }
  else {
    lenm = 1;
  }

  if (s > 9) {
    lens = 2;
  }
  else {
    lens = 1;
  }

  lcd.setCursor(9, 0);
  lcd.print(m);

  lcd.setCursor(9 + lenm, 0);
  lcd.print(":");
  lcd.setCursor(9 + lenm + 1, 0);
  if (s < 10) {
    lcd.print("0");
    lcd.setCursor(9 + lenm + 1 + 1, 0);
    lcd.print(s);
    lcd.setCursor(9 + lenm + 1 + 1 + lens + 1, 0);
    lcd.print("  ");
  }
  else {
    lcd.print(s);
    lcd.setCursor(9 + lenm + 1 + lens, 0);
    lcd.print("  ");
  }
}

void waitScreen() {
  lcd.setCursor(0, 0);
  lcd.print("Time: ");

  seconds = dur;
  secondsToHMS();

  lcd.setCursor(0, 1);
  lcd.print("Start/Set");
}

void runScreen() {
  lcd.setCursor(0, 0);
  lcd.print("Running: ");

  seconds = timeLeft;
  secondsToHMS();

  lcd.setCursor(0, 1);
  lcd.print("Stop");
}

void setScreen() {
  lcd.setCursor(0, 0);
  lcd.print("Set: ");

  seconds = newDur;
  secondsToHMS();

  lcd.setCursor(0, 1);
  lcd.print("Up/Down");
}
