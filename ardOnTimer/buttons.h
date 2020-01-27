

void readButtons() {
  // read the state of the switch into a local variable:
  int startReading = digitalRead(startButtonPin);
  int setReading = digitalRead(setButtonPin);
  int upReading = digitalRead(upButtonPin);
  int downReading = digitalRead(downButtonPin);

  // If the switch changed, due to noise or pressing:
  if (startReading != lastStartButtonState) {
    // reset the debouncing timer
    lastStartDebounceTime = millis();
  }
  if (setReading != lastSetButtonState) {
    // reset the debouncing timer
    lastSetDebounceTime = millis();
  }
  if (upReading != lastUpButtonState) {
    // reset the debouncing timer
    lastUpDebounceTime = millis();
  }
  if (downReading != lastDownButtonState) {
    // reset the debouncing timer
    lastDownDebounceTime = millis();
  }

  if ((millis() - lastStartDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (startReading != startButtonState) {
      startButtonState = startReading;

      // only toggle the relay if the new button state is HIGH
      if (startButtonState == HIGH) {
        relayState = !relayState;
        if (relayState == HIGH) {
          Serial.println("Starting timer");
          tone(buzzerPin, startTone, startLength);
        }
        else {
          Serial.println("Stopping timer");
          tone(buzzerPin, setTone, setLength);
        }
      }
    }
  }

  if ((millis() - lastSetDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (setReading != setButtonState) {
      setButtonState = setReading;

      // only toggle set status if the new button state is HIGH
      if (setButtonState == HIGH && relayState == LOW) {
        setMode = !setMode;
        if (setMode == HIGH) {
          Serial.println("Entering set mode");
        }
        else {
          Serial.println("Exiting set mode");
        }
        tone(buzzerPin, setTone, setLength);
      }
    }
  }

  if ((millis() - lastUpDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (upReading != upButtonState) {
      upButtonState = upReading;

      // only count up if the new button state is HIGH
      if (upButtonState == HIGH && setMode == HIGH) {
        dur = dur + incr;
        Serial.print("Counting up. New timer value: ");
        Serial.println(dur);
        tone(buzzerPin, upTone, upLength);
      }
    }
  }
  if ((millis() - lastDownDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (downReading != downButtonState) {
      downButtonState = downReading;

      // only count down if the new button state is HIGH
      if (downButtonState == HIGH && setMode == HIGH) {
        dur = dur - incr;
        Serial.print("Counting down. New timer value: ");
        Serial.println(dur);
        tone(buzzerPin, downTone, downLength);
      }
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastStartButtonState = startReading;
  lastSetButtonState = setReading;
  lastUpButtonState = upReading;
  lastDownButtonState = downReading;
}
