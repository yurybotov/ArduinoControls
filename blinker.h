/*
	Объект Мигалка. Удобен при отладке и для визуального контроля работоспособности устройства.
    Может иметь несколько состояний:
    - постоянно потушен
    - мигает медленно меандром
    - мигает медленно короткими вспышками
    - мигает "средне" меандром
    - мигает быстро меандром
    - постоянно светится

	Подключается к одному цифровому выходу

	Создано 17.04.2019
	Юрий Ботов
	Изменено 17.04.2019
	Юрий Ботов

	http://github.com/yurybotov/ArduinoControls.git

*/
#ifndef __BLINKER_H__
#define __BLINKER_H__

#include "arduino.h"

enum BlinkerModes {NONE,SLOW,FLASH,MIDDLE,FAST,LIGHT};

class Blinker {
    public:
        inline Blinker(byte pin, BlinkerMode mode) { this->pin = pin; this->mode = this->previous = mode; pinMode(pin, OUTPUT); ledState = LOW; }
        inline Blinker(byte pin) { this->pin = pin; this->mode = this->previous = SLOW; pinMode(pin, OUTPUT); ledstate = LOW; }
        inline ~Blinker() {}
        inline void setMode(BlinkerMode mode) { this->mode = mode; }
        void update() {
            if( previous != mode && ( mode == NONE || mode == LIGHT)) { 
                if( mode == NONE) { ledState = LOW; digitalWrite( pin, LOW); }
                else { if( mode == LIGHT) { ledState = HIGH; digitalWrite( pin, HIGH); } }
            } else {
                switch( mode) {
                    case SLOW: blink(500,500); break;
                    case FLASH: blink(900,100); break;
                    case MIDDLE: blink(200,200); break;
                    case FAST: blink(50,50); break;
                    default: break;
                }
            }
            previous = mode;
        }
    private:
        byte pin;
        BlinkerModes mode;
        BlinkerModes previous;
        unsigned long prevtime;
        byte ledState;
        void blink(int dark, int light) {
            unsigned long current = millis();
            if(current - prevtime > ((ledState == LOW)?dark:light)) {
                prevtime = current;
                if (ledState == LOW) ledState = HIGH; else ledState = LOW;
                digitalWrite(pin, ledState);
            }
        }
};

#endif