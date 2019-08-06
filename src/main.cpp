#include <Arduino.h>

#define PEDAL_PIN 9
#define RELAY_PIN 13
#define MODE_PIN 7
#define RED_PIN 4
#define BLUE_PIN 12
#define DEBOUNCE 20
#define BLINK 250

int ledState = LOW;
int modeLed = LOW;
int buttonState;
int lastButtonState = LOW;
int modeState = LOW;

unsigned long lastDebounceTime = 0;
unsigned long lastBlink = 0;

void setup() {

  pinMode(MODE_PIN, INPUT);
  pinMode(PEDAL_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, ledState);
}

void loop() {
  

  int reading = digitalRead(PEDAL_PIN);

  modeState = digitalRead(MODE_PIN);

  if(modeState == HIGH){

    if (reading != lastButtonState) {
      lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > DEBOUNCE) {
      if (reading != buttonState) {
        buttonState = reading;
        if (buttonState == HIGH) {
          ledState = !ledState;
        }
      }
    }

    if(millis() - lastBlink > BLINK){
      lastBlink = millis();
      modeLed = modeLed == HIGH ? LOW : HIGH;
    }
  
  } else  {
    modeLed = LOW;
    ledState = reading;
  }
  


  digitalWrite(RELAY_PIN, ledState);
  digitalWrite(RED_PIN, ledState);
  digitalWrite(BLUE_PIN, modeLed);

  lastButtonState = reading;
}