/*
	Пример использования объекта Comparator влияющего на параметры Blinker

	Основной вход подключен к А0, ref к A1
    Вывод на встроенный LED

	Создан 17.04.2019
	Юрий Ботов
	Изменен 17.04.2019
	Юрий Ботов

	http://github.com/yurybotov/ArduinoControls.git

*/

#include "arduino.h"

#include "blinker.h"
#include "comparator.h"

Blinker blink = Blinker( LED_BUILTIN, SLOW);
Comparator compensator = Comparator("Compensator", A0, A1 );

void Comparator::onLess(String name) { blink.setMode( SLOW); }
void Comparator::onMore(String name) { blink.setMode( FAST); }
void Meter::onChange(String name, int value) {}

void setup() {

}

void loop() {
    compensator.update();
    blink.update();
}
