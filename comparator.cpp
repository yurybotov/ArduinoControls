#include "comparator.h"

void ComparatorSensor::onChange(String name, int value) { parent->event( name, value); }
