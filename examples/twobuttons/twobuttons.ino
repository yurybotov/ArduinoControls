/*
	Пример использования двух кнопок влияющих на параметры Blinker

	Кнопки подключены к 2 и 4 выводам.
    Вывод на встроенный LED

	Создан 17.04.2019
	Юрий Ботов
	Изменен 17.04.2019
	Юрий Ботов

	http://github.com/yurybotov/ArduinoControls.git

*/

#include "arduino.h"

#include "blinker.h"
#include "key.h"

Blinker blink = Blink(LED,SLOW);
Key slow = Key("Slow",2,5);
Key fast = Key("Fast",4,5);

void Key::onPress(String name) { if(name == String("Slow")) { blink.setMode(SLOW); } else { blink.setMode(FAST); } }
void Key::onRelise(String name) {}

void setup() {

}

void loop() {
    slow.update();
    fast.update();
    blink.update();
}
