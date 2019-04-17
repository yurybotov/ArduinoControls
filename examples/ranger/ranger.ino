/*
	Пример использования объекта Ranger влияющего на параметры Blinker

	Измеритель подключен к А0
    Вывод на встроенный LED

	Создан 17.04.2019
	Юрий Ботов
	Изменен 17.04.2019
	Юрий Ботов

	http://github.com/yurybotov/ArduinoControls.git

*/

#include "arduino.h"

#include "blinker.h"
#include "ranger.h"

Blinker blink = Blink( LED, SLOW);
Ranger termostat = Ranger("Termostat", 400, 600 );

Ranger::onLess() { blink.setMode( SLOW); }
Ranger::onMore() { blink.setMode( FAST); }
Ranger::onRange() { blink.setMode( LIGHT); }

void setup() {

}

void loop() {
    termostat.update();
    blink.update();
}

