/*
	Пример использования объекта Encoder влияющего на параметры Blinker

	Вход CLK подключен к 2, BT к 4
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
Encoder encoder = Encoder("Encoder", 2, 4, 0, 6, 0, CYCLIC );
Key encoderkey = Key("EncoderKey", 2, 5);

Encoder::onChange(String name, int value) { 
    BlinkerModes mode = NONE;
    switch( value) {
        case 0: mode = NONE; break;
        case 1: mode = SLOW; break;
        case 2: mode = FLASH; break;
        case 3: mode = MIDDLE; break;
        case 4: mode = FAST; break;
        case 5: mode = LIGHT;break;
        default: mode = NONE; break;
    }
    blink.setMode( mode); 
}
Key::onPress(String name) { blink.setMode(LIGHT); }
Key::onRelise(String name) { blink.setMode(NONE); }

void setup() {

}

void loop() {
    compensator.update();
    blink.update();
}

