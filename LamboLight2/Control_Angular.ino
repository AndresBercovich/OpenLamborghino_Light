// Control_Angular.ino

// Función PID para control del robot
int errorAnterior = 0;
const int potenciaLimite = 250;

int PIDLambo(int posicionActual, float Kp, float Kd) {
  int error = posicionActual;
  int derivada = error - errorAnterior;
  errorAnterior = error;
  int potencia = (error * Kp) + (derivada * Kd);

  potencia = constrain(potencia, -potenciaLimite, potenciaLimite);
  return potencia;
}
