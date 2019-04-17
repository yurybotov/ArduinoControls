/*
	Обработчик двух-входового компаратора c возможностью гистерезиса

	Подключается к двум аналоговым входам

	При изменении взаимного состояния входов генерирует события:
  * onLess
  * onMore
  * onEqual

	Создано 3.02.2019
	Юрий Ботов
	Изменено 17.04.2019
	Юрий Ботов

	http://github.com/yurybotov/ArduinoControls.git

*/
#ifndef __COMPARATOR_H__
#define __COMPARATOR_H__

#include "meter.h"

class ComparatorSensor;
class Comparator;

class ComparatorSensor : public Meter {
  public:
    // обычный конструктор
    inline ComparatorSensor(String name/*имя сенсора*/, Comparator* comparator/*ссылка на вызывающий класс*/) : Meter( name) { parent = comparator;}
    // конструктор с гистерезисом
    inline ComparatorSensor(String name, Comparator* comparator, int hysteresis/*гистерезис компататора*/) : Meter( name) { parent = comparator; }
    // деструктор
    inline ~ComparatorSensor() {}
    // обработчик изменения - определен в comparator.cpp
    virtual void onChange(String name, int value);
  private:
    Comparator* parent; // добавочная ссылка на вызывающий объект
};

class Comparator {
  public:
    inline Comparator(String name, byte mainpin, byte referencepin, int hysteresis) { 
      this->name = name; 
      work.setPin( mainpin);
      ref.setPin( referencepin);
      state = '?';
      this->hysteresis = hysteresis;
    }
    inline Comparator(String name, byte mainpin , byte referencepin) { 
      this->name = name; 
      work.setPin( mainpin);
      ref.setPin( referencepin);
      state = '?';
      hysteresis = 0;
    }
    inline ~Comparator() {}
    inline void update(void) { work.update(); ref.update(); }
    inline void event(String name, int value) {;
      if( name == String("W")) { main = value; } else { if( name == String("R")) { reference = value; }}
      char current = (main - hysteresis > reference)?'>':((main < reference - hysteresis)?'<':'=');
      if(current != state && current == '>') { state = current; onMore(this->name); } 
      else { if(current != state && current == '<') { state = current; onLess(this->name); } 
             else { if(current != state && current == '=') { state = current;} 
             }
      }  
    }
    inline char value(void) { return state; }
    virtual void onLess(String name);
    virtual void onMore(String name);
  private:
    String name;
    int main;
    int reference;
    char state;
    int hysteresis;
    ComparatorSensor& work = *new ComparatorSensor(String("W"), this);
    ComparatorSensor& ref = *new ComparatorSensor(String("R"), this);
};

#endif
