// SO.ino

#define PIN_BUZZER 10
#define PIN_BOTON 2
#define PIN_DRON 3

extern int baseSpeed; // Declaramos 'baseSpeed' como externa
extern const int umbralDedo; // Indicamos que 'umbralDedo' está definida en otro lugar

int cont_Speed = 0;
int cont_Dron = 0;
unsigned long tiempoInicio = 0;
bool flagR = false;

void change_Speed() {
  digitalWrite(PIN_DRON, LOW);
  pixels.setPixelColor(0, pixels.Color(0, 50, 0));
  pixels.show();

  if (analogRead(A0) < umbralDedo) {
    tiempoInicio = millis();
    flagR = true;

    while (analogRead(A0) < (umbralDedo + 40)) {
      if ((millis() - tiempoInicio) > 2000) {
        setDron();
        setSpeed();
        Serial.println("Set velocidad:");
        Serial.println(baseSpeed);

        if (baseSpeed == 0) {
          tone(PIN_BUZZER, 1300, 50);
          delay(100);
          tone(PIN_BUZZER, 1300, 50);
          delay(100);
        }

        for (int i = 1; i <= cont_Speed; i++) {

          tone(PIN_BUZZER, 4000, 50);
          pixels.setPixelColor(0, pixels.Color(0, 50, 0));
          pixels.show();
          delay(100);

          pixels.setPixelColor(0, pixels.Color(0, 0, 0));
          pixels.show();
          delay(300);
        }
        delay(1000);
        flagR = false;
        return;
      }
    }
  }

  if ((analogRead(A0) > umbralDedo) && flagR) {
    flagR = false;
    cont_Speed++;
    tone(PIN_BUZZER, 3500, 50);
    pixels.setPixelColor(0, pixels.Color(0, 50, 0));
    pixels.show();
    delay(100);
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    pixels.show();
    delay(300);
    Serial.println(cont_Speed);
  }

  if (analogRead(A7) < umbralDedo) {
    cont_Speed--;
    tone(PIN_BUZZER, 3000, 50);
    pixels.setPixelColor(0, pixels.Color(0, 50, 0));
    pixels.show();
    delay(100);
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    pixels.show();
    delay(300);
    Serial.println(cont_Speed);
  }
}




void change_Dron() {
  digitalWrite(PIN_DRON, LOW);
  pixels.setPixelColor(0, pixels.Color(0, 0, 50));
  pixels.show();

  if (analogRead(A0) < umbralDedo) {
    tiempoInicio = millis();
    flagR = true;

    while (analogRead(A0) < (umbralDedo + 40)) {
      if ((millis() - tiempoInicio) > 2000) {
        setDron();
        setSpeed();
        Serial.println("Set DronSpeed:");
        Serial.println(baseDron);

        if (baseDron == 0) {
          tone(PIN_BUZZER, 1300, 50);
          delay(150);
          tone(PIN_BUZZER, 1300, 50);
          delay(150);
        }

        for (int i = 1; i <= cont_Dron; i++) {


          tone(PIN_BUZZER, 4000, 50);
          pixels.setPixelColor(0, pixels.Color(0, 0, 50));
          pixels.show();
          delay(100);

          pixels.setPixelColor(0, pixels.Color(0, 0, 0));
          pixels.show();
          delay(300);
        }
        delay(1000);
        flagR = false;
        return;
      }
    }
  }

  if ((analogRead(A0) > umbralDedo) && flagR) {
    flagR = false;
    cont_Dron++;
    tone(PIN_BUZZER, 3500, 50);
    pixels.setPixelColor(0, pixels.Color(0, 0, 50));
    pixels.show();
    delay(100);
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    pixels.show();
    delay(300);
    Serial.println(cont_Dron);
  }

  if (analogRead(A7) < umbralDedo) {
    cont_Dron--;
    tone(PIN_BUZZER, 3000, 50);
    pixels.setPixelColor(0, pixels.Color(0, 0, 50));
    pixels.show();
    delay(100);
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    pixels.show();
    delay(300);
    Serial.println(cont_Dron);
  }
}

void setSpeed() {
  baseSpeed = cont_Speed * 10;
}

void setDron() {
  baseDron = cont_Dron * 10;
}
