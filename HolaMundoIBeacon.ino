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
namespace Globales {
  // Define hardware: LED and Button pins and states
  const int LED_PIN = 7;
  const int LED_OFF = LOW;
  const int LED_ON = HIGH;
  
  // Definicion de los pines UART
  const int  RX_PIN  = 15;
  const int  TX_PIN  = 17;
};

// --------------------------------------------------------------
// --------------------------------------------------------------
void inicializarPlaquita () {

  Serial.begin(9600); // Serial is the USB serial port
  Serial1.begin(9600); // Puerto serie hardware para comunicación con el sensor, 8 bit, o paority, 1 stop bit, 3.3V

  // Turn on-board blue LED on
  pinMode( Globales::LED_PIN, OUTPUT);
  digitalWrite(Globales::LED_PIN, Globales::LED_ON);

} // ()

// --------------------------------------------------------------
// --------------------------------------------------------------
void inicializarBluetooth () {

  // declaro un objeto beacon para publicitar
  // fuente: https://www.instructables.com/id/Beaconeddystone-and-Adafruit-NRF52-Advertise-Your-/

  // https://github.com/nkolban/ESP32_BLE_Arduino/blob/master/src/BLEBeacon.h

  char * NOMBRE_EMISORA = "GTI 3A";
  int MANUFACTURER_ID = 0x004C;  // Apple valid Manufacturer ID
  int Major=0x03;
  int Minor=0x06;
  int Beacon_RSSI=-73;
  int Tx_power=4;  
  // AirLocate UUID: B3D6F818-DA71-09ED-EA80-F3C45FB19A50
  /*
  uint8_t beaconUuid[16] = { 
	  0xB3, 0xD6, 0xF8, 0x18, 0xDA, 0x71, 0x09, 0xED, 
	  0xEA, 0x80, 0xF3, 0xC4, 0x5F, 0xB1, 0x9A, 0x50, 
	};
  */
  uint8_t beaconUuid[16] = { 
	'E', 'P', 'S', 'G', '-', 'G', 'T', 'I', 
	'-', 'P', 'R', 'O', 'Y', '-', '3', 'A'
	};

  BLEBeacon elBeacon(beaconUuid, Major, Minor, Beacon_RSSI);
  
  //
  //
  //
  Bluefruit.begin();
  
  Bluefruit.autoConnLed(false);
  Bluefruit.setTxPower(Tx_power);
  Bluefruit.setName( NOMBRE_EMISORA );
  elBeacon.setManufacturer(MANUFACTURER_ID);
  Bluefruit.ScanResponse.addName();
  Bluefruit.Advertising.setBeacon(elBeacon);
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(160, 160);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(15);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds  

} // ()

// --------------------------------------------------------------
// Setup: inicializa BLE, crea semáforos y tareas, asigna funciones de callback
// --------------------------------------------------------------
void setup() {

  inicializarPlaquita();

  inicializarBluetooth();

  // Suspend Loop() to save power
  suspendLoop();

} // setup ()

// --------------------------------------------------------------
// loop() : no hace nada
// --------------------------------------------------------------
void loop() { 

  
} // loop ()
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
