// -*-c++-*-

// --------------------------------------------------------------
// --------------------------------------------------------------

// https://learn.sparkfun.com/tutorials/nrf52840-development-with-arduino-and-circuitpython

// https://stackoverflow.com/questions/29246805/can-an-ibeacon-have-a-data-payload

// --------------------------------------------------------------
// --------------------------------------------------------------
#include <bluefruit.h>

// --------------------------------------------------------------
// --------------------------------------------------------------
#include "LED.h"
#include "PuertoSerie.h"

// --------------------------------------------------------------
// --------------------------------------------------------------
namespace Globales {
  
  LED elLED ( /* NUMERO DEL PIN LED = */ 7 );

  PuertoSerie elPuerto ( /* velocidad = */ 9600 ); // 115200

  // Serial1 en el ejemplo de Curro creo que es la conexión placa-sensor 
};

// --------------------------------------------------------------
// --------------------------------------------------------------
#include "EmisoraBLE.h"
#include "Publicador.h"

// --------------------------------------------------------------
// --------------------------------------------------------------
void inicializarPlaquita () {

  // de momento nada

} // ()

// --------------------------------------------------------------
// --------------------------------------------------------------
namespace Globales {

  Publicador elPublicador;

}; // namespace


// --------------------------------------------------------------
// Setup: inicializa BLE, crea semáforos y tareas, asigna funciones de callback
// --------------------------------------------------------------
void setup() {

  esperar( 1000 );

  inicializarPlaquita();

  // Suspend Loop() to save power
  // suspendLoop();

  // 
  // 
  // 
  Globales::elPublicador.encenderEmisora();
  

  // Globales::elPublicador.laEmisora.pruebaEmision();


  esperar( 1000 );

  Globales::elPuerto.escribir( "---- setup(): fin ---- \n " );

} // setup ()

// --------------------------------------------------------------
// --------------------------------------------------------------
void lucecitas() {
  Globales::elLED.brillar( 100 ); // 100 encendido
  esperar ( 400 ); //  100 apagado
  Globales::elLED.brillar( 100 ); // 100 encendido
  esperar ( 400 ); //  100 apagado
  Globales::elLED.brillar( 100 ); // 100 encendido
  esperar ( 400 ); //  100 apagado
  Globales::elLED.brillar( 1000 ); // 1000 encendido
  esperar ( 1000 ); //  100 apagado
} // ()

// --------------------------------------------------------------
// loop ()
// --------------------------------------------------------------
namespace Loop {
  uint8_t cont = 0;
};

// ..............................................................
// ..............................................................
void loop () {

  using namespace Loop;

  cont++;

  Globales::elPuerto.escribir( "\n---- loop(): empieza " );
  Globales::elPuerto.escribir( cont );
  Globales::elPuerto.escribir( "\n" );

  lucecitas();

  // 
  // 
  // 
  int valorCO2 = 234; // medirlo verdaderamente !
  
  Globales::elPublicador.publicarCO2( valorCO2,
									  cont,
									  1000 // intervalo de emisión
									  );
  
  // 
  // 
  // 
  int valorTemperatura = -15; // medirlo verdaderamente !
  
  Globales::elPublicador.publicarTemperatura( valorTemperatura, 
											  cont,
											  1000 // intervalo de emisión
											  );
  
  
  Globales::elPuerto.escribir( "---- loop(): acaba **** " );
  Globales::elPuerto.escribir( cont );
  Globales::elPuerto.escribir( "\n" );
  
} // loop ()
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
