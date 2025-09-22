#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int buzzer = 8;
int stopButton = 7;

int hours = 0, minutes = 0, seconds = 55;

int alarmHour = 0;    
int alarmMinute = 1;  
bool alarmOn = true;

unsigned long prevMillis = 0;

void setup() {
  lcd.begin(16, 2);
  pinMode(buzzer, OUTPUT);
  pinMode(stopButton, INPUT_PULLUP);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - prevMillis >= 1000) {
    prevMillis = currentMillis;
    seconds++;
    if (seconds == 60) { seconds = 0; minutes++; }
    if (minutes == 60) { minutes = 0; hours++; }
    if (hours == 24) { hours = 0; }
  }

  lcd.setCursor(0,0);
  lcd.print("Time: ");
  lcd.print(hours < 10 ? "0" : ""); lcd.print(hours);
  lcd.print(":");
  lcd.print(minutes < 10 ? "0" : ""); lcd.print(minutes);

  lcd.setCursor(0,1);
  lcd.print("Alarm: ");
  if (alarmOn) {
    lcd.print(alarmHour < 10 ? "0" : ""); lcd.print(alarmHour);
    lcd.print(":");
    lcd.print(alarmMinute < 10 ? "0" : ""); lcd.print(alarmMinute);
  } else {
    lcd.print("OFF ");
  }

  if (alarmOn && hours == alarmHour && minutes == alarmMinute && seconds < 5) {
    tone(buzzer, 1000);
    if (digitalRead(stopButton) == LOW) {
      alarmOn = false;
      noTone(buzzer);
      lcd.setCursor(0,1);
      lcd.print("Alarm: OFF      ");
      delay(200);
    }
  } else {
    noTone(buzzer);
  }
}
