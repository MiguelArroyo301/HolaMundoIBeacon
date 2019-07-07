// -*- mode: c++ -*-

// ----------------------------------------------------------
// Jordi Bataller i Mascarell
// 2019-07-07
// ----------------------------------------------------------
#ifndef EMISORA_H_INCLUIDO
#define EMISORA_H_INCLUIDO

// fuente: https://www.instructables.com/id/Beaconeddystone-and-Adafruit-NRF52-Advertise-Your-/
// https://github.com/nkolban/ESP32_BLE_Arduino/blob/master/src/BLEBeacon.h

// https://os.mbed.com/blog/entry/BLE-Beacons-URIBeacon-AltBeacons-iBeacon/
// https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/bleadvertising

// ----------------------------------------------------------
// ----------------------------------------------------------
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
	 Bluefruit.begin(); 
  } // ()

  // .........................................................
  // .........................................................
  void detenerAnuncio() {
	Bluefruit.Advertising.stop(); 
  }  // ()
  
  // .........................................................
  // .........................................................
  bool estaAnunciando() {
	return Bluefruit.Advertising.isRunning();
  } // ()

  // .........................................................
  // .........................................................
  void emitirAnuncioIBeacon( uint8_t * beaconUUID, int16_t major, int16_t minor, uint8_t rssi ) {

	//
	//
	//
	(*this).detenerAnuncio();
	
	//
	// creo el beacon 
	//
	BLEBeacon elBeacon( beaconUUID, major, minor, rssi );
	elBeacon.setManufacturer( (*this).fabricanteID );

	//
	// parece que esto debe ponerse todo aquí
	//

	Bluefruit.setTxPower( (*this).txPower );
	Bluefruit.setName( (*this).nombreEmisora );
	Bluefruit.ScanResponse.addName(); // para que envíe el nombre de emisora (?!)

	//
	// pongo el beacon
	//
	Bluefruit.Advertising.setBeacon( elBeacon );

	//
	// ? qué valorers poner aquí
	//
	Bluefruit.Advertising.restartOnDisconnect(true); // no hace falta, pero lo pongo
	Bluefruit.Advertising.setInterval(100, 100);    // in unit of 0.625 ms

	//
	// empieza el anuncio, 0 = tiempo indefinido (ya lo pararán)
	//
	Bluefruit.Advertising.start( 0 ); 
	
  } // ()

  // .........................................................
  //
  // Ejemplo de Beacon (31 bytes)
  //
  // https://os.mbed.com/blog/entry/BLE-Beacons-URIBeacon-AltBeacons-iBeacon/
  //
  // The iBeacon Prefix contains the hex data : 0x0201061AFF004C0215. This breaks down as follows:
  //
  // 0x020106 defines the advertising packet as BLE General Discoverable and BR/EDR high-speed incompatible.
  // Effectively it says this is only broadcasting, not connecting.
  //
  // 0x1AFF says the following data is 26 bytes long and is Manufacturer Specific Data.
  //
  // 0x004C is Apple’s Bluetooth Sig ID and is the part of this spec that makes it Apple-dependent.
  //
  // 0x02 is a secondary ID that denotes a proximity beacon, which is used by all iBeacons.
  //
  // 0x15 defines the remaining length to be 21 bytes (16+2+2+1).
  //
  // Por ejemmplo:
  //
  // 1. prefijo: 9bytes
  //       0x02, 0x01, 0x06,       // advFlags 3bytes
  //       0x1a, 0xff,             // advHeader 2 (0x1a = 26 = 25(lenght de 0x4c a 0xca)+1)   0xFF -> BLE_GAP_AD_TYPE_MANUFACTURER_SPECIFIC_DATA
  //       0x4c, 0x00,             // companyID 2bytes
  //       0x02,                   // ibeacon type 1 byte
  //       0x15,                   // ibeacon length 1 byte (dec=21 lo que va a continuación: desde  la 'f' hasta 0x01)
  // 
  // 2. uuid: 16bytes
  // 'f', 'i', 's', 't', 'r', 'o', 'f', 'i', 's', 't', 'r', 'o', 0xa7, 0x10, 0x96, 0xe0
  // 
  // 2 major: 2bytes
  // 0x04, 0xd2,
  // 
  // minor: 2bytes
  // 0x10, 0xe1,
  // 
  // 0xca, // tx power : 1bytes
  //
  // 0x01, // este es el byte 31 = BLE_GAP_ADV_SET_DATA_SIZE_MAX, parece que sobra
  //
  // .........................................................
  void emitirAnuncioIBeaconLibre( const char * carga, const uint8_t tamanyoCarga ) {

	(*this).detenerAnuncio(); 

	Bluefruit.Advertising.clearData();
	Bluefruit.ScanResponse.clearData();

	// Bluefruit.setTxPower( (*this).txPower );
	Bluefruit.setName( (*this).nombreEmisora );
	Bluefruit.ScanResponse.addName();

	Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);

	// hasta ahora habrá, supongo, ya puestos los 5 primeros bytes

	uint8_t restoPrefijoYCarga[4+21] = {
	  0x4c, 0x00, // companyID 2
	  0x02, // ibeacon type 1byte
	  21, // ibeacon length 1byte (dec=21)  longitud del resto // 0x15 // ibeacon length 1byte (dec=21)  longitud del resto
	  '-', '-', '-', '-', 
	  '-', '-', '-', '-', 
	  '-', '-', '-', '-', 
	  '-', '-', '-', '-', 
	  '-', '-', '-', '-', 
	  '-'
	};

	memcpy( &restoPrefijoYCarga[4], &carga[0], ( tamanyoCarga > 21 ? 21 : tamanyoCarga ) ); 

	Bluefruit.Advertising.addData( BLE_GAP_AD_TYPE_MANUFACTURER_SPECIFIC_DATA,
								   &restoPrefijoYCarga[0],
								   4+21 );

	//
	// ? qué valores poner aquí
	//
	Bluefruit.Advertising.restartOnDisconnect(true);
	Bluefruit.Advertising.setInterval(100, 100);    // in unit of 0.625 ms

	Bluefruit.Advertising.setFastTimeout( 1 );      // number of seconds in fast mode
	//
	// empieza el anuncio, 0 = tiempo indefinido (ya lo pararán)
	//
	Bluefruit.Advertising.start( 0 ); 
  } // ()

  /*
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
  */

}; // class
// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
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
