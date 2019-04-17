/*
	Обработчик двух-координатного джойстика

	Подключается к двум аналоговым входам

	При изменении состояния генерирует события:
  * onChange

  Диапазон значений по каждой из координат: -255...0...255

  До использования нуждается в калибровке (.calibrate())

	Создано 3.02.2019
	Юрий Ботов
	Изменено 17.04.2019
	Юрий Ботов

	http://github.com/yurybotov/ArduinoControls.git

*/
#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#include "arduino.h"
#include "meter.h"

class JoystickSensor;
class Joystick;

class JoystickSensor : public Meter {
  public:
    // обычный конструктор
    inline JoystickSensor(String name/*имя сенсора*/, Joystick* joystick/*ссылка на вызывающий класс*/) : Meter( name) { parent = joystick; }
    // деструктор
    inline ~JoystickSensor() {}
    // обработчик изменения - определен в joystick.cpp
    virtual void onChange(String name, int value);
  private:
    Joystick* parent; // добавочная ссылка на вызывающий объект
};

// аналоговый джойстик
// значение джойстика -255...0...255 по каждому из направлений
class Joystick {
  public:
    // штатный конструктор
    inline Joystick(String name/*имя сенсора*/, byte pinx/*пин X координаты*/, byte piny/*пин Y координаты*/) { 
      this->name = name;
      sensorX.setPin( pinx);
      sensorY.setPin( piny);
      x = y = x0 = y0 = 0; 
    }
    // деструктор
    inline ~Joystick() {}
    // обновляет состояние сенсора, должна быть вызвана из loop для каждого из экземпляров объекта
    inline void update(void) { sensorX.update(); sensorY.update();}
    // вызываемый датчиками обработчик
    inline void event(String name, int value) {
      if( name == String("X")) {
        x = value;
      } else {
        if( name == String("Y")) {
          y = value;
        }
      }
      // приведение к диапазону -255...255
      onChange(this->name, ((x < x0)? (map(x,0,x0,-255,0)): (map(x,x0,1023,0,255))), ((y < y0)? (map(y,0,y0,-255,0)): (map(y,y0,1023,0,255))));
    }
    // калибровка джойстика (обязательно разместите ее в setup)
    void calibrate(byte pinx, byte piny) {
      for(byte i = 0; i < 8; i++) {
        x0 += analogRead(pinx);
        y0 += analogRead(piny);
      }
      x0 = x0 >> 3;
      y0 = y0 >> 3;
    }
    // текущие значения
    inline int valuex(void) {return x;}
    inline int valuey(void) {return y;}
    // обработчик изменения - его необходимо создать
    virtual void onChange(String name, int x, int y);
  private:
    String name; // имя джойстика
    int x; // последнее значение по X
    int y; // последнее значение по Y
    int x0; // откалиброванный центр по x
    int y0; // откалиброванный центр по y
    JoystickSensor& sensorX = *new JoystickSensor( String("X"), this);
    JoystickSensor& sensorY = *new JoystickSensor( String("Y"), this);
};

#endif
