#include <LiquidCrystal.h>
#include <stdio.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  

int minutes = 0;   
int seconds = 0; 
int countdown = 0;       
int button1 = A0;           // start
int button2 = A1;           // seconds
int button3 = A2;           // minutes
int button4 = A3;           // clear
int lightBoardPin = 9;
int buzzerPin = 8;
int ledPin = 13;             
boolean startCountdown = false;
int logic1, logic2, logic3, logic4;

void setup()
{ 
  pinMode(ledPin, OUTPUT);
  pinMode(lightBoardPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  lcd.begin(16, 2); 
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("-Exposure Time-"); 
  lcd.setCursor(0, 1);
  lcd.print("- Press SETUP -");
  digitalWrite(lightBoardPin, LOW);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);
}

void splashscreen()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Exposure Time"); 
    lcd.setCursor(0, 1);
    lcd.print("* Press SETUP *"); 
}

void buzzer()
{
  for(int x = 0; x <= 3; x++)
  {
   tone(buzzerPin, 1500, 100);
   delay(200);
   tone(buzzerPin, 1500, 100);
   delay(200);
   tone(buzzerPin, 1500, 100);
   delay(200);
   tone(buzzerPin, 1500, 100);
   delay(200);
  }
}

void uberTime()
{
  countdown = ((minutes * 60) + seconds);
  digitalWrite(lightBoardPin, HIGH);
  digitalWrite(ledPin, HIGH);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Exposing Board");
  lcd.setCursor(0, 1);
  lcd.print("Time:");
  lcd.setCursor(11, 1);
  lcd.print(" Secs");
  for (int timer = countdown; timer >= 0; timer --)
  {
    char buffer[6]; 
    
    sprintf(buffer, "%4d", countdown);
    lcd.setCursor(7, 1);
    lcd.print(buffer);
    delay(1000);
    countdown = countdown - 1;
  }
  
  digitalWrite(lightBoardPin, LOW);
  digitalWrite(ledPin, LOW);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" ** ALL DONE **");
  lcd.setCursor(0, 1);
  lcd.print("  Press START");
  buzzer();
  
  logic1 = analogRead(button1);
  while(logic1 != 0)
  {
    logic1 = analogRead(button1);
  }
  
  startCountdown = false;
  minutes = 0;
  seconds = 0;
  countdown = 0;
}

void setupTimer()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  - Set Time -  "); 
  lcd.setCursor(0, 1);
  lcd.print("Then Press Start");
  delay(3000);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Set Expose Time"); 
  lcd.setCursor(0, 1);
  lcd.print("Min: ");
  lcd.setCursor(9, 1);
  lcd.print("Sec: ");
  
  while(startCountdown == false) 
  { 
    logic2 = analogRead(button2);   
    if (logic2 == 0)                  // SECONDS ADJUST
    { 
      seconds ++;
      delay(300);
      
       if (seconds >= 60)
       {
         seconds = 0;
         minutes ++;
       }   
    }
   char buffer[3];
   sprintf(buffer, "%2d", seconds); 
   lcd.setCursor(14, 1);
   lcd.print(buffer);
  
   logic3 = analogRead(button3);
   if (logic3 == 0)                  // MINUTES ADJUST
   {
     minutes ++;
     delay(500);
   }
   
   lcd.setCursor(6, 1);
   lcd.print(minutes);
   
   logic4 = analogRead(button4);
   if(logic4 == 0)                   // clear timer
   {
     seconds = 0;
     minutes = 0;
   }
   
   logic1 = analogRead(button1);
   if (logic1 == 0)                  // START             
   {
     startCountdown = true;
   }
  }
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Exposure Start"); 
  lcd.setCursor(0, 1);
  lcd.print("Timer = "); 
  lcd.setCursor(8, 1);
  lcd.print(countdown);
  lcd.setCursor(12, 1);
  lcd.print("Secs");
  
  buzzer();
  uberTime();
}

void loop()
{
  splashscreen();
  logic1 = analogRead(button1);
  logic2 = analogRead(button2);
  logic3 = analogRead(button3);
  
  if (logic1 == 0)                 // SETUP & START BUTTON
  {
    setupTimer();
  }

    Serial.print("button1 = ");
    Serial.print(analogRead(button1));
    Serial.print("   button2 = ");
    Serial.print(analogRead(button2));
    Serial.print("   button3 = ");
    Serial.println(analogRead(button3));
    delay(100);
}
