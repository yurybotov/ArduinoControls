/*
	Обработчик контролирующий выход параметра за пределы верхней и нижней границы

	Подключается к аналоговому входу

	При переходах через границы генерирует события:
  * onLow
  * onNormal
  * onHigh

	Создано 3.02.2019
	Юрий Ботов
	Изменено 17.04.2019
	Юрий Ботов

	http://github.com/yurybotov/ArduinoControls.git

*/
#ifndef __RANGER_H__
#define __RANGER_H__

#include "arduino.h"
#include "meter.h"

class RangerSensor;
class Ranger;

class RangerSensor : public Meter {
  public:
    // обычный конструктор
    inline RangerSensor(String name/*имя сенсора*/, Ranger* ranger/*ссылка на вызывающий класс*/) : Meter( name) { parent = ranger; }
    // деструктор
    inline ~RangerSensor() {}
    // обработчик изменения - определен в ranger.cpp
    virtual void onChange(String name, int value);
  private:
    Ranger* parent; // добавочная ссылка на вызывающий объект
};
// проверка того факта, что что-то находится в пределах верхней и нижней границ
// при пересечении границ вызываются соответственно onHigh, onLow
// есть и onNormal, он полезен для индикации того, что все в норме
class Ranger {
  public:
    // штатный конструктор
    inline Ranger(String name/*имя*/, int lowrange/*значение нижней границы*/, int highrange/*значение верхней границы*/) 
      { this->name = name; this->lowrange = lowrange; this->highrange = highrange; state = '?'; sensor.setName( name);}
    // деструктор
    inline ~Ranger() {}
    // установка диапазона (если надо в процессе работы поменять)
    inline void setRange(int lowrange, int highrange) { this->lowrange = lowrange; this->highrange = highrange; }
    // обновляет состояние сенсора, должна быть вызвана из loop для каждого из экземпляров объекта
    inline void update(void) { sensor.update(); }
    // обработчик событий от датчика
    inline void event(String name, int value) {
      char current = (value > highrange)?'>':((value < lowrange)?'<':'=');
      if(current != state && current == '>') {state = current; onMore(this->name);} 
      else { if(current != state && current == '<') {state = current; onLess(this->name);} 
             else { if(current != state && current == '=') { state = current; onRange(this->name);} }
      }  
    }
    // возвращает последнее значение
    inline char value(void) { return state; }
    // события, обработчики которых должен написать пользователь, указав какие действия предпринять при их возникновении
    virtual void onLess(String name);
    virtual void onRange(String name);
    virtual void onMore(String name);
  private:
    String name; // имя датчика
    int lowrange; // нижняя граница, ниже ее вызывается onLow
    int highrange; // верхняя граница, выше ее вызывается onHigh
    char state; // последнее состояние
    RangerSensor& sensor = *new RangerSensor("", this); // объект датчика, имя ему присваивается сверху в конструкторе
};

#endif
