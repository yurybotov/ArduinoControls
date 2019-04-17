#ifndef __COMPARATOR_H__
#define __COMPARATOR_H__

#include "meter.h"

class ComparatorSensor;
class Comparator;

class ComparatorSensor : public Meter {
  public:
    // обычный конструктор
    inline ComparatorSensor(String name/*имя сенсора*/, Comparator* comparator/*ссылка на вызывающий класс*/) : Meter( name) { parent = comparator; }
    // деструктор
    inline ~ComparatorSensor() {}
    // обработчик изменения - определен в comparator.cpp
    virtual void onChange(String name, int value);
  private:
    Comparator* parent; // добавочная ссылка на вызывающий объект
};

class Comparator {
  public:
    inline Comparator(String name, byte mainpin , byte referencepin) { 
      this->name = name; 
      work.setPin( mainpin);
      ref.setPin( referencepin);
      state = '?';
    }
    inline ~Comparator() {}
    inline void update(void) { work.update(); ref.update(); }
    inline void event(String name, int value) {;
      if( name == String("W")) { main = value; } else { if( name == String("R")) { reference = value; }}
      char current = (main > reference)?'>':((main < reference)?'<':'=');
      if(current != state && current == '>') { state = current; onMore(this->name); } 
      else { if(current != state && current == '<') { state = current; onLess(this->name); } 
             else { if(current != state && current == '=') { state = current; onEqual(this->name);} 
             }
      }  
    }
    inline char value(void) { return state; }
    virtual void onLess(String name);
    virtual void onEqual(String name);
    virtual void onMore(String name);
  private:
    String name;
    int main;
    int reference;
    char state;
    ComparatorSensor& work = *new ComparatorSensor(String("W"), this);
    ComparatorSensor& ref = *new ComparatorSensor(String("R"), this);
};

#endif
