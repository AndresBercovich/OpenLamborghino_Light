
int fin = 0;

int l_geo, ll_geo, lll_geo;

int geo = 0;

int HL, HR = 0;

void Read_hits() {

  HL = analogRead(A0);
  HR = analogRead(A7);

  if (HL > umbral) {
    HL = 0;
  } else {
    HL = 1;
  }

  if (HR > umbral) {
    HR = 0;
  } else {
    HR = 1;
  }
}

void detectGeo() {

  Read_hits();


  if ((HL == 0) && (HR == 0)) {
    geo = 0;
  }

  if ((HL == 1) && (HR == 0)) {
    geo = 1;
  }

  if ((HL == 0) && (HR == 1)) {
    geo = 2;
  }

  if ((HL == 1) && (HR == 1)) {
    geo = 3;
  }

  if (l_geo != geo) {




    if (geo == 0 && l_geo == 2 && ll_geo == 0) {

      funcion_HL();
    }
    if (geo == 0 && l_geo == 1 && ll_geo == 0) {

      funcion_HR();
    }

    if (geo == 0 && ((l_geo == 3) || (ll_geo == 3) || (lll_geo == 3))) {

      funcion_Cruce();
    }
    lll_geo = ll_geo;
    ll_geo = l_geo;
    l_geo = geo;
  }
}

void funcion_HL() {

  tone(PIN_BUZZER, 2000, 50);
}

void funcion_HR() {

  tone(PIN_BUZZER, 1500, 50);
  fin++;

  switch (fin) {
    case 1:
      Serial.println("Hit 1");
      break;
    case 2:
      digitalWrite(PIN_DRON, 0);
      delay(50);
      Serial.println("Hit 2");

      Motores(0, 0);

      pixels.setPixelColor(0, pixels.Color(0, 50, 0));
      pixels.show();

      while (!digitalRead(PIN_BOTON)) {
        change_Speed();
      }
      tone(PIN_BUZZER, 2000, 100);
      delay(300);

      pixels.setPixelColor(0, pixels.Color(0, 0, 50));
      pixels.show();


      while (!digitalRead(PIN_BOTON)) {
        change_Dron();
      }
      pixels.setPixelColor(0, pixels.Color(50, 0, 0));
      pixels.show();
      tone(PIN_BUZZER, 2000, 100);
      delay(2000);
      fin = 0;
      break;


    default:
      // if nothing else matches, do the default
      // default is optional
      break;

  }
}

void funcion_Cruce() {

  tone(PIN_BUZZER, 2500, 50);
}
