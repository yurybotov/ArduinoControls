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

Blinker blink = Blinker( LED_BUILTIN, SLOW);
Ranger termostat = Ranger("Termostat", 400, 600 );

void Ranger::onLess(String name) { blink.setMode( SLOW); }
void Ranger::onMore(String name) { blink.setMode( FAST); }
void Ranger::onRange(String name) { blink.setMode( LIGHT); }
void Meter::onChange(String name, int value) {}

void setup() {

}

void loop() {
    termostat.update();
    blink.update();
}

