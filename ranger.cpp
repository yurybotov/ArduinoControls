#include "ranger.h"

// переопределение события onChange датчика, перенаправление его на обработчик
void RangerSensor::onChange(String name, int value) { parent->event( name, value); }
