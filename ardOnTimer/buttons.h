

void readButtons() {
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

    // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastStartButtonState = startReading;
  lastStopButtonState = stopReading;
  lastUpButtonState = upReading;
  lastDownButtonState = downReading;
}
