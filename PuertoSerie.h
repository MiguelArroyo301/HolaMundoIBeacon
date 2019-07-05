
// -*- mode: c++ -*-

#ifndef PUERTO_SERIE_H_INCLUIDO
#define PUERTO_SERIE_H_INCLUIDO

// ------------------------------------------------------
// ------------------------------------------------------
class PuertoSerie  {

public:
  // .........................................................
  // .........................................................
  PuertoSerie (long baudios) {
	Serial.begin(baudios);
	//	Serial1.begin(baudios);
  } // ()

  // .........................................................
  // .........................................................
  template<typename T>
  void escribir (T mensaje) {
	Serial.print( mensaje );
		//Serial1.print( mensaje );
  } // ()
  
}; // class PuertoSerie

// ------------------------------------------------------
// ------------------------------------------------------
#endif
