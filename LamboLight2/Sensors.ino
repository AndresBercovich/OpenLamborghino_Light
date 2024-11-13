// Sensors.ino

#define PIN_SENSOR_ON 11
#define PIN_BUZZER 10

const int numSensores = 6;
int v_s_min[numSensores];
int v_s_max[numSensores];
int s_p[numSensores];
bool online = false;

int posicionAnterior = 0;

void Sensors_init() {
  pinMode(PIN_SENSOR_ON, OUTPUT);
  for (int i = 0; i < numSensores; i++) {
    v_s_min[i] = 1023;
    v_s_max[i] = 0;
  }
}

void calibracion() {

  pixels.setPixelColor(0, pixels.Color(50, 0, 0));
  pixels.show();
  int v_s[numSensores];

  for (int j = 0; j < 100; j++) {
    delay(30);
    for (int i = 0; i < numSensores; i++) {
      v_s[i] = analogRead(A6 - i);
    }
    for (int i = 0; i < numSensores; i++) {
      Serial.print(v_s[i]);
      Serial.print("\t");
      if (v_s[i] < v_s_min[i]) {
        v_s_min[i] = v_s[i];
      }
      if (v_s[i] > v_s_max[i]) {
        v_s_max[i] = v_s[i];
      }
    }
    Serial.println();
  }

  beep();
  beep();

  Serial.println("\nMínimos:");
  for (int i = 0; i < numSensores; i++) {
    Serial.print(v_s_min[i]);
    Serial.print("\t");
  }
  Serial.println();

  Serial.println("Máximos:");
  for (int i = 0; i < numSensores; i++) {
    Serial.print(v_s_max[i]);
    Serial.print("\t");
  }
  Serial.println();


  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}

void readSensors() {


  int s[numSensores];
  int suma = 0;

  for (int i = 0; i < numSensores; i++) {
    s[i] = analogRead(A6 - i);
    s[i] = constrain(s[i], v_s_min[i], v_s_max[i]);
    s_p[i] = map(s[i], v_s_min[i], v_s_max[i], 100, 0);
    suma += s_p[i];
  }

  online = (suma > 100);

}

int GetPosicion() {
  readSensors();
  int prom = 0;
  int suma = 0;
  int pesos[numSensores] = { -25, -15, -5, 5, 15, 25 }; // Pesos escalados

  for (int i = 0; i < numSensores; i++) {
    prom += pesos[i] * s_p[i];
    suma += s_p[i];
  }

  int posicion;
  if (online) {
    posicion = prom / suma;
  } else {
    posicion = (posicionAnterior < 0) ? -255 : 255;
  }
  posicionAnterior = posicion;
  return posicion;
}
