// -*- mode: c++ -*-

#ifndef EMISORA_H_INCLUIDO
#define EMISORA_H_INCLUIDO

// fuente: https://www.instructables.com/id/Beaconeddystone-and-Adafruit-NRF52-Advertise-Your-/
// https://github.com/nkolban/ESP32_BLE_Arduino/blob/master/src/BLEBeacon.h

// ------------------------------------------------------
// ------------------------------------------------------
class EmisoraBLE {
private:

  const char * nombreEmisora;
  const uint16_t fabricanteID;
  const int8_t txPower;

public:

  // .........................................................
  // .........................................................
  EmisoraBLE( const char * nombreEmisora_, const uint16_t fabricanteID_,
			  const int8_t txPower_ ) 
	:
	nombreEmisora( nombreEmisora_ ) ,
	fabricanteID( fabricanteID_ ) ,
	txPower( txPower_ )
  {
  } // ()
	
  // .........................................................
  // .........................................................
  void encenderEmisora() {
	 Bluefruit.begin(); // parece que esto fastidia el asunto

  }

  // .........................................................
  // .........................................................
  void detenerAnuncio() {
	Bluefruit.Advertising.stop(); // OK
  } // 

  
  // .........................................................
  // .........................................................
  void pruebaEmision() {

	Globales::elPuerto.escribir( "     prueba emision \n"  );

	(*this).detenerAnuncio(); // OK

	uint8_t beaconUUID[16] = { 
	  'E', 'P', 'S', 'G', '-', 'G', 'T', 'I', 
	  '-', 'P', 'R', 'O', 'Y', '-', '3', 'A'
	};
	BLEBeacon elBeacon( beaconUUID, 45, 67,  1234 );

	// Bluefruit.begin(); // ???? 

	Bluefruit.setTxPower( (*this).txPower ); // OK
	Bluefruit.setName( (*this).nombreEmisora ); // OK
	elBeacon.setManufacturer( (*this).fabricanteID ); // OK
	Bluefruit.Advertising.setBeacon( elBeacon ); // OK

	Bluefruit.Advertising.start( 0 ); // ????
	Globales::elPuerto.escribir( "     prueba emision started \n"  );

	esperar( 3000 );

	detenerAnuncio ();
	Globales::elPuerto.escribir( "     prueba emision stoped \n"  );
  }

  // .........................................................
  // .........................................................
  void emitirAnuncioIBeacon( uint8_t * beaconUUID, int16_t major, int16_t minor, uint8_t rssi ) {

	//
	//
	//
	(*this).detenerAnuncio();
	
	//
	//
	//
	BLEBeacon elBeacon( beaconUUID, major, minor, rssi );

	elBeacon.setManufacturer( (*this).fabricanteID );

	Bluefruit.setTxPower( (*this).txPower );
	// Bluefruit.setName( (*this).nombreEmisora );
	Bluefruit.setName( "VAGO" );
	Bluefruit.ScanResponse.addName(); // para que envíe el nombre de emisora (?!)

	//
	//
	//
	Bluefruit.Advertising.setBeacon( elBeacon );


	//
	// ? qué valorers poner aquí
	//
	Bluefruit.Advertising.setInterval(100, 100);    // in unit of 0.625 ms

	//
	//
	//
	Bluefruit.Advertising.start( 0 ); 
	
  } // ()

  // .........................................................
  // .........................................................
  void emitirAnuncioIBeaconIntentandoPonerMasDatos( uint8_t * beaconUUID, int16_t major, int16_t minor, uint8_t rssi ) {

	//
	//
	//
	(*this).detenerAnuncio();
	
	Bluefruit.Advertising.clearData();
	Bluefruit.ScanResponse.clearData(); // add this



	
	Bluefruit.Advertising.addUuid( beaconUUID );

	int8_t datos[] = { 0x0A, 0x0B, 0x0C, 0xBD };
	Bluefruit.Advertising.addData( 0xFF, &datos[0], 4 );

	Bluefruit.setName( "fistro" );

	Bluefruit.Advertising.addName();
	Bluefruit.ScanResponse.addName(); // ?

	Bluefruit.Advertising.addAppearance( 0x1234 );

	uint8_t datos2[] = { 0x01, 0x0D, 0x02, 0x0E, 0x03, 0x0A };

	Bluefruit.Advertising.addManufacturerData( &datos2[0], 6 );

	Bluefruit.Advertising.setData( &datos2[0], 6 );

	/*
	Bluefruit.Advertising.addFlags( 0xCC );
	*/

	// Bluefruit.Advertising.setInterval(100, 100);    // in unit of 0.625 ms
	Bluefruit.Advertising.setInterval(160, 160);    // in unit of 0.625 ms

	//
	//
	//
	Bluefruit.Advertising.start( 0 ); 
	
  } // ()
  
  // .........................................................
  // .........................................................
  bool estaAnunciando() {
	return Bluefruit.Advertising.isRunning();
  } // ()

}; // class

// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------
#endif

/*
  // void emitirBeacon( uint8_t * beaconUUID, int16_t major, int16_t minor, int tiempoEmision = 0 ) {
  void emitirBeacon( uint8_t * beaconUUID, int16_t major, int16_t minor ) {

	//
	//
	//
	(*this).detenerAnuncio();
	
	//
	//
	//
	BLEBeacon elBeacon( beaconUUID, major, minor, (*this).rssi );
	  
	//
	//
	//
	Bluefruit.begin();
	  
	Bluefruit.autoConnLed( false );
	Bluefruit.setTxPower( (*this).txPower );
	Bluefruit.setName( (*this).nombreEmisora );
	elBeacon.setManufacturer( (*this).fabricanteID );
	Bluefruit.ScanResponse.addName();
	Bluefruit.Advertising.setBeacon( elBeacon );

	
	Bluefruit.Advertising.restartOnDisconnect( true );


	// habría que añadir parámetros para configurar estos valores
	 ORIGINALMENTE 
	Bluefruit.Advertising.setInterval(160, 160);    // in unit of 0.625 ms
	Bluefruit.Advertising.setFastTimeout(15);      // number of seconds in fast mode
	Bluefruit.Advertising.start( 0  );
	

	// void setInterval  (uint16_t fast, uint16_t slow);
	Bluefruit.Advertising.setInterval(3, 3);    // in unit of 0.625 ms

	Bluefruit.Advertising.setFastTimeout(1);      // number of seconds in fast mode
	Bluefruit.Advertising.start( 3 );
	// tiempoEmision
	// 0 = Don't stop advertising after n seconds, ver valor por defecto

	esperar( 1100 );

	Bluefruit.Advertising.stop();

  } // ()
  
*/
