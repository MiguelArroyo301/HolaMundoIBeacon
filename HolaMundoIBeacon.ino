// -*-c++-*-

// --------------------------------------------------------------
// --------------------------------------------------------------

// https://learn.sparkfun.com/tutorials/nrf52840-development-with-arduino-and-circuitpython

// https://stackoverflow.com/questions/29246805/can-an-ibeacon-have-a-data-payload

// --------------------------------------------------------------
// --------------------------------------------------------------
#include <bluefruit.h>

#include "LED.h"
#include "PuertoSerie.h"
#include "EmisoraBLE.h"

// --------------------------------------------------------------
// --------------------------------------------------------------
namespace Globales {
  
  LED elLED ( /* NUMERO DEL PIN LED = */ 7 );

  PuertoSerie elPuerto ( /* velocidad = */ 9600 ); // 115200

  // Nota no sé qué es Serial1 en el ejemplo de Curro */
};

// --------------------------------------------------------------
// --------------------------------------------------------------
void inicializarPlaquita () {

} // ()

// --------------------------------------------------------------
// --------------------------------------------------------------
namespace Globales {

  EmisoraBLE laEmisora(
					   "GTI 3A", // nombreEmisora
					   0x004c, // fabricanteID (Apple)
					   -73, // rssi
					   4 // txPower
					   );

}; // namespace

// --------------------------------------------------------------
// --------------------------------------------------------------
void inicializarBluetooth () {


  uint8_t beaconUUID[16] = { 
	'E', 'P', 'S', 'G', '-', 'G', 'T', 'I', 
	'-', 'P', 'R', 'O', 'Y', '-', '3', 'A'
	};

  Globales::laEmisora.emitirBeacon( beaconUUID, // beacon UUID
						  0x03, // major
						  0x04 // minor
						  );
  
} // ()

// --------------------------------------------------------------
// Setup: inicializa BLE, crea semáforos y tareas, asigna funciones de callback
// --------------------------------------------------------------
void setup() {

  Globales::elPuerto.escribir( " ---- setup () ---- \n " );

  inicializarPlaquita();

  inicializarBluetooth();

  // Suspend Loop() to save power
  // suspendLoop();

} // setup ()

// --------------------------------------------------------------
// loop() : no hace nada
// --------------------------------------------------------------
void loop() { 

  Globales::elLED.brillar( 200 );

  esperar ( 500 );

  
} // loop ()
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
