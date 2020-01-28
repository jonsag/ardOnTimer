
void countDown() {

  if (counting == LOW) {
    startMillis = millis();
    timeLeft = dur;
    counting = HIGH;
    Serial.print("Time left: ");
    Serial.println(timeLeft);
  }

  if (millis() - startMillis >= 1000) {
    timeLeft = timeLeft - 1;
    Serial.print("Time left: ");
    Serial.println(timeLeft);
    startMillis = millis();
  }

  if (timeLeft <= 0) {
    relayState = LOW;
    lcd.clear();
    counting = LOW;
    digitalWrite(relayPin, relayState);
    Serial.println("Timer finished");
    Serial.println();
    tone(buzzerPin, stopTone, stopLength);
  }
}
