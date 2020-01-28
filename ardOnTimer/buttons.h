

void readButtons() {
  // read the state of the switch into a local variable:
  int startReading = digitalRead(startButtonPin);
  int setReading = digitalRead(setButtonPin);
  int upReading = digitalRead(upButtonPin);
  int downReading = digitalRead(downButtonPin);

  /*******************************
    Start/Stop/Store button
  *******************************/
  if (startReading != lastStartButtonState) {
    lastStartDebounceTime = millis();
  }

  if ((millis() - lastStartDebounceTime) > debounceDelay) {
    if (startReading != startButtonState) {
      startButtonState = startReading;

      if (startButtonState == HIGH && setMode == LOW) {
        relayState = !relayState;
        if (relayState == HIGH) {
          Serial.println("Starting timer");
          tone(buzzerPin, startTone, startLength);
          lcd.clear();
        }
        else {
          Serial.println("Stopping timer");
          Serial.println();
          counting = LOW;
          tone(buzzerPin, stopTone, stopLength);
          lcd.clear();
        }
        digitalWrite(relayPin, relayState);
      }
      else if (startButtonState == HIGH && setMode == HIGH) {
        dur = newDur;
        Serial.println("Stored new value");
        lcd.setCursor(0, 1);
        lcd.print("Stored          ");
        tone(buzzerPin, storeTone, storeLength);
        delay(storeLength);
      }
    }
  }

  /*******************************
    Set button
  *******************************/
  if (setReading != lastSetButtonState) {
    lastSetDebounceTime = millis();
  }

  if ((millis() - lastSetDebounceTime) > debounceDelay) {

    if (setReading != setButtonState) {
      setButtonState = setReading;

      if (setButtonState == HIGH && relayState == LOW) {
        setMode = !setMode;
        newDur = dur;
        if (setMode == HIGH) {
          Serial.println("Entering set mode");
        }
        else {
          Serial.println("Exiting set mode");
          Serial.println();
        }
        lcd.clear();
        tone(buzzerPin, setTone, setLength);
      }
    }
  }

  /*******************************
    Up button
  *******************************/
  if (upReading != lastUpButtonState) {
    lastUpDebounceTime = millis();
  }

  if ((millis() - lastUpDebounceTime) > debounceDelay) {

    if (upReading != upButtonState) {
      upButtonState = upReading;

      if (upButtonState == HIGH && setMode == HIGH) {
        if (newDur + incr < maxSeconds) {
          newDur = newDur + incr;
          Serial.print("Counting up. New timer value: ");
          Serial.println(dur);
          tone(buzzerPin, upTone, upLength);
        }
        else {
          Serial.println("Value too high. Can't increase");
          tone(buzzerPin, errorTone, errorLength);
        }
      }
    }
  }

  /*******************************
    Down button
  *******************************/
  if (downReading != lastDownButtonState) {
    lastDownDebounceTime = millis();
  }

  if ((millis() - lastDownDebounceTime) > debounceDelay) {

    if (downReading != downButtonState) {
      downButtonState = downReading;

      if (downButtonState == HIGH && setMode == HIGH) {
        if (newDur - incr  > 0 ) {
          newDur = newDur - incr;
          Serial.print("Counting down. New timer value: ");
          Serial.println(dur);
          tone(buzzerPin, downTone, downLength);
        }
        else {
          Serial.println("Value too low. Can't decrease");
          tone(buzzerPin, errorTone, errorLength);
        }
      }
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastStartButtonState = startReading;
  lastSetButtonState = setReading;
  lastUpButtonState = upReading;
  lastDownButtonState = downReading;
}
