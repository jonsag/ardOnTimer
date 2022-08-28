#include "buttonActions.h" // makes buttons do something

void readButtons()
{
  startButtonReading = digitalRead(startButtonPin); // read the state of the switches into a local variable
  setButtonReading = digitalRead(setButtonPin);
  upButtonReading = digitalRead(upButtonPin);
  downButtonReading = digitalRead(downButtonPin);

  /*******************************
    Start/Stop/Store button
  *******************************/
  if (startButtonReading != lastStartButtonState)
  {
    lastStartDebounceTime = millis();
  }

  if ((millis() - lastStartDebounceTime) > debounceDelay)
  {
    startButtonAction();
  }

  /*******************************
    Set button
  *******************************/
  if (setButtonReading != lastSetButtonState)
  {
    lastSetDebounceTime = millis();
  }

  if ((millis() - lastSetDebounceTime) > debounceDelay)
  {
    setButtonAction();
  }

  /*******************************
    Up button
  *******************************/
  if (upButtonReading != lastUpButtonState)
  {
    lastUpDebounceTime = millis();
  }

  if ((millis() - lastUpDebounceTime) > debounceDelay)
  {
    upButtonAction();
  }

  /*******************************
    Down button
  *******************************/
  if (downButtonReading != lastDownButtonState)
  {
    lastDownDebounceTime = millis();
  }

  if ((millis() - lastDownDebounceTime) > debounceDelay)
  {
    downButtonAction();
  }

  lastStartButtonState = startButtonReading; // save all readings
  lastSetButtonState = setButtonReading;
  lastUpButtonState = upButtonReading;
  lastDownButtonState = downButtonReading;
}
