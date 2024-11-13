// Lambolight.ino

#include <Adafruit_NeoPixel.h>

// Definición de pines y constantes globales
#define PIN_BUZZER 10
#define PIN_BOTON 2
#define PIN_LED 13
#define PIN_DRON 3    // Cambiado de 3 a 12 para liberar el pin 3
#define PIN_SENSOR_ON 11

#define LED_PIN 12      // Pin conectado al LED WS2812B
#define NUMPIXELS 1    // Número de LEDs NeoPixel

const int umbral = 830; // Definición única del umbral
const int umbralDedo = 876; // Definición única del umbral



// Variables y constantes
int posicion_ideal = 0;
int baseSpeed = 0;
int baseDron = 0;

float Kprop = 2.0;
float Kderiv = 25.0;


int error_pasado = 0;

// Declaración de funciones externas
void Peripherals_init();
void TB6612FNG_init();
void Sensors_init();
void WaitBoton();
void calibracion();
void Motores(int izquierda, int derecha);
void change_Speed();
void detectGeo();
int GetPosicion();
int PIDLambo(int posicionActual, float Kp, float Kd);




// Inicialización del NeoPixel
Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  Peripherals_init();
  TB6612FNG_init();
  Sensors_init();

  pinMode(PIN_DRON, OUTPUT);
  digitalWrite(PIN_LED, LOW);
  digitalWrite(PIN_DRON, LOW);
  delay(500);

  pixels.begin();
  pixels.show(); // Inicializa todos los pixeles a 'apagado'

  Motores(0, 0);

  Serial.println("Programa Básico");

  delay(500);

  // Mostrar lecturas de los sensores de impacto en el LED antes de presionar el botón
  while (digitalRead(PIN_BOTON) == LOW) {
    // Leer valores analógicos
    int analogA7 = analogRead(A7); // Sensor de impacto derecho (HR)
    int analogA0 = analogRead(A0); // Sensor de impacto izquierdo (HL)

    Serial.print(analogA7);
    Serial.print("\t");
    Serial.println(analogA0);


    // Mapear lecturas analógicas a intensidades (inversamente proporcionales)
    int redIntensity = map(analogA7, 0, 1023, 255, 0);
    int blueIntensity = map(analogA0, 0, 1023, 255, 0);

    // Asegurar que las intensidades estén dentro del rango 0-255
    redIntensity = constrain(redIntensity, 0, 255);
    blueIntensity = constrain(blueIntensity, 0, 255);

    // Establecer el color del pixel
    pixels.setPixelColor(0, pixels.Color(redIntensity, 0, blueIntensity));
    pixels.show();
    delay(10);
  }

  tone(PIN_BUZZER, 2000, 100);
  pixels.setPixelColor(0, pixels.Color(50, 0, 0));
  pixels.show();
  // WaitBoton();
  calibracion();

  pixels.setPixelColor(0, pixels.Color(0, 50, 0));
  pixels.show();

  while (!digitalRead(PIN_BOTON)) {
    change_Speed();
  }
  tone(PIN_BUZZER, 2000, 100);
  pixels.setPixelColor(0, pixels.Color(0, 0, 50));
  pixels.show();
  delay(1000);

  while (!digitalRead(PIN_BOTON)) {
    change_Dron();
  }
  tone(PIN_BUZZER, 2000, 100);
  pixels.setPixelColor(0, pixels.Color(50, 0, 0));
  pixels.show();
  delay(2000);
  analogWrite(PIN_DRON, baseDron);


}




void loop() {
  int p = GetPosicion();
  detectGeo();

  int error = p - posicion_ideal;
  int d_error = error - error_pasado;
  int correction_power = int(Kprop * error) + int(Kderiv * (d_error));


  if (correction_power > 255) {
    correction_power = 255;
  }

  else if (correction_power < -255) {
    correction_power = -255;
  }

  Motores(baseSpeed + correction_power, baseSpeed + -correction_power);
  error_pasado = error;
}
