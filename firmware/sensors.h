#ifndef SENSORS_H
#define SENSORS_H
//libreria HX711
#include "HX711.h"
 
//load cell 1
#define DOUT_PIN 20
#define SCK_PIN 21

//objeto celda
HX711 celda;
float tara = 0.0;
long load_cell_reading = 0.0;
float load_cell_value = 0.0;
void sensors_setup(void);
float read_load_cell(void);

#endif