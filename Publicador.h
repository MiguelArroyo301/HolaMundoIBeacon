// -*- mode: c++ -*-

#ifndef PUBLICADOR_H_INCLUIDO
#define PUBLICADOR_H_INCLUIDO

// ------------------------------------------------------
// ------------------------------------------------------
class Publicador {

  // .........................................................
  // .........................................................
private:

  uint8_t beaconUUID[16] = { 
	'E', 'P', 'S', 'G', '-', 'G', 'T', 'I', 
	'-', 'P', 'R', 'O', 'Y', '-', '3', 'A'
	};


  // .........................................................
  // .........................................................
public:
  EmisoraBLE laEmisora{ 
						  "GTI-3A",
						  0x004c, // fabricanteID (Apple)
						  -79, // rssi
						  4 // txPower
							};

  // .........................................................
  // .........................................................
public:

  // .........................................................
  // .........................................................
  enum MedicionesID  {
	CO2 = 101,
	TEMPERATURA = 102,
	RUIDO = 103
  };


  // .........................................................
  // .........................................................
  Publicador( ) {
	
  } // ()

  // .........................................................
  // .........................................................
  void publicarCO2( int valorCO2, long tiempoEspera ) {

	(*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID, 
									MedicionesID::CO2, // major
									valorCO2 // minor
									);

	esperar( tiempoEspera );

	(*this).laEmisora.detenerAnuncio();
  } // ()

  // .........................................................
  // .........................................................
  void publicarTemperatura( int valorTemperatura, long tiempoEspera ) {

	(*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID, 
									MedicionesID::TEMPERATURA, // major
									valorTemperatura // minor
									);
	esperar( tiempoEspera );

	(*this).laEmisora.detenerAnuncio();
  } // ()
	
}; // class

// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------
#endif