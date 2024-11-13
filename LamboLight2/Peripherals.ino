// Peripherals.ino

#define PIN_BUZZER 10
#define PIN_BOTON 2
#define PIN_LED 13

void Peripherals_init() {
  // Configuración de pines
  pinMode(PIN_BOTON, INPUT);     // El pin del botón se configura como entrada
  pinMode(PIN_BUZZER, OUTPUT);   // El pin del buzzer se configura como salida
  pinMode(PIN_LED, OUTPUT);      // El pin del LED se configura como salida
}

void WaitBoton() {
  // Espera hasta que se presione el botón
  while (!digitalRead(PIN_BOTON));
  beep();
}

void beep() {
  tone(PIN_BUZZER, 2000, 100); // Emite un tono de 2000 Hz durante 100 ms
  delay(200); // Espera 200 ms antes de continuar
}
