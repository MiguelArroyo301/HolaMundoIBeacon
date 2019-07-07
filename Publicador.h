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
  EmisoraBLE laEmisora{ 
						  "GTI-3A",
						  0x004c, // fabricanteID (Apple)
						  4 // txPower
							};

  const int RSSI = -53;

  // .........................................................
  // .........................................................
public:

  // .........................................................
  // .........................................................
  enum MedicionesID  {
	CO2 = 11,
	TEMPERATURA = 12,
	RUIDO = 13
  };


  // .........................................................
  // .........................................................
  Publicador( ) {
	// ATENCION: no hacerlo aquí. (*this).laEmisora.encenderEmisora();
	// Pondremos un método para llamarlo desde el setup
  } // ()

  // .........................................................
  // .........................................................
  void encenderEmisora() {
	(*this).laEmisora.encenderEmisora();
  } // ()

  // .........................................................
  // .........................................................
  void publicarCO2( int16_t valorCO2, uint8_t contador, long tiempoEspera ) {

	uint16_t major = (MedicionesID::CO2 << 8) + contador;
	(*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID, 
											major,
											valorCO2, // minor
											(*this).RSSI // rssi
									);

	Globales::elPuerto.escribir( "   publicarCO2(): valor=" );
	Globales::elPuerto.escribir( valorCO2 );
	Globales::elPuerto.escribir( "   contador=" );
	Globales::elPuerto.escribir( contador );
	Globales::elPuerto.escribir( "   todo="  );
	Globales::elPuerto.escribir( major );
	Globales::elPuerto.escribir( "\n" );
	esperar( tiempoEspera );

	(*this).laEmisora.detenerAnuncio();
  } // ()

  // .........................................................
  // .........................................................
  void publicarTemperatura( int16_t valorTemperatura, uint8_t contador, long tiempoEspera ) {

	(*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID, 
											(MedicionesID::TEMPERATURA << 8) + contador, // major
											valorTemperatura, // minor
											(*this).RSSI // rssi
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
