
/*******************************
  Start/Stop/Store button
*******************************/
void startButtonAction() {
  if (startButtonReading != startButtonState) {
    startButtonState = startButtonReading;

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
void setButtonAction() {
  if (setButtonReading != setButtonState) {
    setButtonState = setButtonReading;

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
void upButtonAction() {
      if (upButtonState == HIGH && setMode == HIGH && millis() - repeatUpButton > repeatTime) { // button has been pressed longer than repeat time
        if (newDur + incr2 < maxSeconds) { // we're under max allowed value
          newDur = newDur + incr2;
          repeatUpButton = millis();
          Serial.print("Counting up. New timer value: ");
          Serial.println(dur);
          tone(buzzerPin, upTone, upLength);
        }
        else {
          Serial.println("Value too high. Can't increase");
          tone(buzzerPin, errorTone, errorLength);
        }
      }
      
  if (upButtonReading != upButtonState) { // button has changed state
    upButtonState = upButtonReading; // set new state for button

    if (upButtonState == HIGH && setMode == HIGH) { // button is pressed and we're in set mode
      repeatUpButton = millis();

      if (newDur + incr1 < maxSeconds) { // we're under max allowed value
        newDur = newDur + incr1; // increase time
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
void downButtonAction() {
  if (downButtonState == HIGH && setMode == HIGH && millis() - repeatDownButton > repeatTime) {
        if (newDur - incr2 >  0) { // we're over min allowed value
          newDur = newDur + incr2;
          repeatDownButton = millis();
          Serial.print("Counting up. New timer value: ");
          Serial.println(dur);
          tone(buzzerPin, upTone, upLength);
        }
        else {
          Serial.println("Value too high. Can't increase");
          tone(buzzerPin, errorTone, errorLength);
        }
      }
      
  if (downButtonReading != downButtonState) {
    downButtonState = downButtonReading;

    if (downButtonState == HIGH && setMode == HIGH) {
      if (newDur - incr1  > 0) { // we're over min allowed value
        newDur = newDur - incr1;
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
