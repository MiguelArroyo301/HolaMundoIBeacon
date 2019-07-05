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
  const int fabricanteID;
  const int rssi;
  const int txPower;

public:

  // .........................................................
  // .........................................................
  EmisoraBLE( const char * nombreEmisora_, const int fabricanteID_,
			  const int rssi_, const int txPower_ ) 
	:
	nombreEmisora( nombreEmisora_ ) ,
	fabricanteID( fabricanteID_ ) ,
	rssi( rssi_ ) ,
	txPower( txPower_ )
  {
	
  } // ()
	
  // .........................................................
  // .........................................................
  void emitirBeacon( uint8_t * beaconUUID, int major, int minor ) {

	//
	//
	//
	(*this).detenerEmision();
	
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
	Bluefruit.Advertising.setInterval(160, 160);    // in unit of 0.625 ms
	Bluefruit.Advertising.setFastTimeout(15);      // number of seconds in fast mode
	Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds  

  } // ()
  
  // .........................................................
  // .........................................................
  void detenerEmision() {
	// no encuentro el método para parar la emisión
	// Bluefruit.stop()  ;
  } // ()

}; // class

// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------
#endif
