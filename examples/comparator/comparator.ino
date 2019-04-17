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

Blinker blink = Blink( LED, SLOW);
Comparator compensator = Comparator("Compensator", 400, 600 );

Comparator::onLess() { blink.setMode( SLOW); }
Comparator::onMore() { blink.setMode( FAST); }

void setup() {

}

void loop() {
    compensator.update();
    blink.update();
}
