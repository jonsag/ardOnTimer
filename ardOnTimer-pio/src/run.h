
void countDown()
{

  if (counting == LOW) // low when timer starts
  {
    startMillis = millis();
    timeLeft = dur;
    counting = HIGH;
    Serial.print("Time left: ");
    Serial.print(timeLeft);
    Serial.println(" seconds");
  }

  if (millis() - startMillis >= 1000) // one second has elapsed
  {
    timeLeft = timeLeft - 1;
    Serial.print("Time left: ");
    Serial.print(timeLeft);
    Serial.println(" seconds");
    startMillis = millis();
  }

  if (timeLeft <= 0) // timer has run out
  {
    relayState = LOW;
    lcd.clear();
    counting = LOW;
    digitalWrite(relayPin, relayState);
    Serial.println("Timer finished");
    Serial.println();
    tone(buzzerPin, stopTone, stopLength);
  }
}
