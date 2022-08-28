

void secondsToHMS() // converts seconds to hour, minutes and seconds
{
  s = t % 60;

  t = (t - s) / 60;
  m = t % 60;

  t = (t - m) / 60;
  h = t;

  // --------hh:mm:ss
  // print hours
  lcd.setCursor(timeOffset, 0); // first hours digit
  if (h > 0)
  {
    if (h > 9) // hours is larger than 9
    {
      lcd.print(h);
    }
    else
    {
      lcd.print(" ");                   // prints space instead of first hour digit
      lcd.setCursor(timeOffset + 1, 0); // second hours digit
      lcd.print(h);
    }
    lcd.setCursor(timeOffset + 2, 0); // colon after hours
    lcd.print(":");
  }
  else
  {
    lcd.print("   "); // prints three spaces instead of hours and colon
  }

  // print minutes
  lcd.setCursor(timeOffset + 3, 0); // first minutes digit
  if (m > 9)
  {
    lcd.print(m);
  }
  else
  {
    if (h > 0) // if hours is 1 or higher
    {
      lcd.print("0");
    }
    else
    {
      lcd.print(" "); // prints space instead of first minute digit
    }
    lcd.setCursor(timeOffset + 4, 0); // second minutes digit
    lcd.print(m);
  }
  lcd.setCursor(timeOffset + 5, 0); // colon after minutes
  lcd.print(":");

  // print seconds
  lcd.setCursor(timeOffset + 6, 0); // first seconds digit
  if (s > 9)
  {
    lcd.print(s);
  }
  else
  {
    lcd.print("0");                   // prints 0 at first seconds digit
    lcd.setCursor(timeOffset + 7, 0); // second seconds digit
    lcd.print(s);
  }
}

/*******************************
    Wait/Standby screen
  *******************************/
void waitScreen()
{
  lcd.setCursor(0, 0);
  lcd.print("Timer ");

  t = dur;
  secondsToHMS();

  lcd.setCursor(0, 1);
  lcd.print("Start or Set");
}

/*******************************
    Run screen
  *******************************/
void runScreen()
{
  lcd.setCursor(0, 0);
  lcd.print("Run ");

  if (millis() - animationMillis >= 2000)
  { // run animation
    animationMillis = millis();
  }

  lcd.setCursor(4, 0);
  if (millis() - animationMillis >= 1500)
  {
    lcd.print("/");
  }
  else if (millis() - animationMillis >= 1000)
  {
    lcd.print("|");
  }
  else if (millis() - animationMillis >= 500)
  {
    // lcd.print("\\");
    lcd.write(byte(7)); // print our custom char backslash
  }
  else
  {
    lcd.print("-");
  }

  t = timeLeft;
  secondsToHMS();

  lcd.setCursor(0, 1);
  lcd.print("Stop");

  // line 2: 'Stop_---------->'
  // squares left: 10
  // percent per square: 100/10
  // time gone: dur-timeLeft
  // percent done: 100*(dur-timeLeft)/dur
  // how many squares should be used:

  progress = (100 * (dur - timeLeft) / dur); // progress in percent

  for (int i = 0; i <= (progress / 10); i++) // prints one '-' for each 10 percent done
  {
    lcd.setCursor(5 + i, 1);
    lcd.print("-");
  }

  lcd.setCursor(5 + i + progress / 10, 1); // print a dot for every other 2 percent done
  smallStepProgress = (progress % 10);

  if (smallStepProgress < 2) // no dots
  {
    lcd.print(">          "); // last position is always a '>'
  }
  else
  {
    if (smallStepProgress > 7) // print four dots
    {
      lcd.write(byte(4));
    }
    else if (smallStepProgress > 5) // print three dots
    {
      lcd.write(byte(3));
    }
    else if (smallStepProgress > 3) // print two dots
    {
      lcd.write(byte(2));
    }
    else if (smallStepProgress > 1) // print one dot
    {
      lcd.write(byte(1));
    }
    lcd.setCursor(6 + i + progress / 10, 1);
    lcd.print(">          "); // last position is always a '>'
  }
}

/*******************************
    Set screen
  *******************************/
void setScreen()
{
  lcd.setCursor(0, 0);
  lcd.print("Set ");

  t = newDur;
  secondsToHMS();

  lcd.setCursor(0, 1);
  lcd.print("Store,Exit or ");
  lcd.setCursor(14, 1);
  // lcd.print("U"); // up arrow (ascii 24 or 30 is up arrow, ascii 25 or 31 is down arrow ascii 18 is up-down arrow, see http://www.martyncurrey.com/wp-content/uploads/2017/03/LCDs_12_CharSet_01.jpg)
  lcd.write(byte(5)); // print our custom up arrow
  lcd.setCursor(15, 1);
  // lcd.print("D"); // down arrow ()
  lcd.write(byte(6)); // print our custom down arrow
}
