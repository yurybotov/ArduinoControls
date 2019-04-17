#include "joystick.h"

// переопределение события onChange датчика, перенаправление его на обработчик
void JoystickSensor::onChange(String name, int value) { parent->event(name,value); }
