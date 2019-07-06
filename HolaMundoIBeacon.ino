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

  // Serial1 en el ejemplo de Curro creo que es la conexión placa-sensor 
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

  /*
  uint8_t beaconUUID[16] = { 
	'E', 'P', 'S', 'G', '-', 'G', 'T', 'I', 
	'-', 'P', 'R', 'O', 'Y', '-', '3', 'A'
	};
  */

  uint8_t beaconUUID[16+1] = "EPSG-GTI-PROY-3A"; 

  Globales::laEmisora.emitirBeacon( beaconUUID, // beacon UUID
									-16, // 0x12, // major
									1234	// 0x34 // minor
						  );
  
} // ()

// --------------------------------------------------------------
// Setup: inicializa BLE, crea semáforos y tareas, asigna funciones de callback
// --------------------------------------------------------------
void setup() {

  inicializarPlaquita();

  inicializarBluetooth();

  // Suspend Loop() to save power
  // suspendLoop();

  Globales::elPuerto.escribir( "---- setup(): fin ---- \n " );

} // setup ()

// --------------------------------------------------------------
// loop ()
// --------------------------------------------------------------
namespace Loop {
  int i = 0;
};

// ..............................................................
// ..............................................................
void loop() {

  using namespace Loop;

  Globales::elLED.brillar( 500 );
  esperar ( 500 );
  Globales::elLED.brillar( 500 );
  esperar ( 500 );
  Globales::elLED.brillar( 500 );

  esperar ( 1000 );

  i++;
  Globales::elPuerto.escribir( "---- loop(): fin " );
  Globales::elPuerto.escribir( i );
  Globales::elPuerto.escribir( "\n" );
  
} // loop ()
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
