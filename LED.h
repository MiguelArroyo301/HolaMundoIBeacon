// -*- mode: c++ -*-

#ifndef LED_H_INCLUIDO
#define LED_H_INCLUIDO

// ------------------------------------------------------
// ------------------------------------------------------
void esperar (long tiempo) {
  delay (tiempo);
}

// ------------------------------------------------------
// ------------------------------------------------------
class LED {
private:
  int numeroLED;
  bool encendido;
public:

  // .........................................................
  // .........................................................
  LED (int numero)
	: numeroLED (numero), encendido(false)
  {
	pinMode(numeroLED, OUTPUT);
	apagar ();
  }

  // .........................................................
  // .........................................................
  void encender () {
	// digitalWrite(numeroLED, HIGH); 
	// encender en ESP8266 es al revés
	digitalWrite(numeroLED, LOW); 
	encendido = true;
  }

  // .........................................................
  // .........................................................
  void apagar () {
	// digitalWrite(numeroLED, LOW); // Turn off LED
	  digitalWrite(numeroLED, HIGH); // Turn off LED
	  encendido = false;
  }

  // .........................................................
  // .........................................................
  void alternar () {
	if (encendido) {
	  apagar();
	} else {
	  encender ();
	}
  } // ()

  // .........................................................
  // .........................................................
  void brillar (long tiempo) {
	encender ();
	esperar(tiempo); 
	apagar ();
  }
}; // class

// ------------------------------------------------------
// ------------------------------------------------------
#endif
