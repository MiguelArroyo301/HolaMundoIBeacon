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
  const int rssi;
  const int8_t txPower;

public:

  // .........................................................
  // .........................................................
  EmisoraBLE( const char * nombreEmisora_, const uint16_t fabricanteID_,
			  const int rssi_, const int8_t txPower_ ) 
	:
	nombreEmisora( nombreEmisora_ ) ,
	fabricanteID( fabricanteID_ ) ,
	rssi( rssi_ ) ,
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
	BLEBeacon elBeacon( beaconUUID, 45, 67,  (*this).rssi ); // OK

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
  // void emitirBeacon( uint8_t * beaconUUID, int major, int minor ) {

  // void emitirBeacon( uint8_t * beaconUUID, int16_t major, int16_t minor, int tiempoEmision = 0 ) {
  void emitirAnuncioIBeacon( uint8_t * beaconUUID, int16_t major, int16_t minor ) {

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
	// ? Bluefruit.autoConnLed( false );
	Bluefruit.setTxPower( (*this).txPower );
	Bluefruit.setName( (*this).nombreEmisora );
	elBeacon.setManufacturer( (*this).fabricanteID );
	// Bluefruit.ScanResponse.addName();

	//
	//
	//
	Bluefruit.Advertising.setBeacon( elBeacon );

	//
	//
	//
	Bluefruit.Advertising.start( 0 ); 
	
	// ? Bluefruit.Advertising.restartOnDisconnect( true );

	// habría que añadir parámetros para configurar estos valores
	/* ORIGINALMENTE 
	Bluefruit.Advertising.setInterval(160, 160);    // in unit of 0.625 ms
	Bluefruit.Advertising.setFastTimeout(15);      // number of seconds in fast mode
	Bluefruit.Advertising.start( 0  );
	*/

	// void setInterval  (uint16_t fast, uint16_t slow);
	// Bluefruit.Advertising.setInterval(3, 3);    // in unit of 0.625 ms

	// Bluefruit.Advertising.setFastTimeout(1);      // number of seconds in fast mode
	// Bluefruit.Advertising.start( 3 );
	// tiempoEmision
	// 0 = Don't stop advertising after n seconds, ver valor por defecto

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
