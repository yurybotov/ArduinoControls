/*
	Пример простейшего BLINK

	Использует встроенный LED

	Создан 17.04.2019
	Юрий Ботов
	Изменен 17.04.2019
	Юрий Ботов

	http://github.com/yurybotov/ArduinoControls.git

*/

#include "arduino.h"

#include "blinker.h"

Blinker blink = Blink(LED);

void setup() {

}

void loop() {

  blink.update();

}

