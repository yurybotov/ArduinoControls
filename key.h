#ifndef __KEY_H__
#define __KEY_H__
#include "arduino.h"

// класс обработчика произвольной кнопки и т.п. с удалением дребезга
// при нажатии и отпускании запускает обработчики onPress и onRelise
// можно использовать в качестве базового класса для более сложных устройств (энкодер например)
class Key {
  public:
    // основной конструктор
    inline Key(String name /*Имя датчика*/, byte pin/*номер вывода*/, byte debounce/*задержка для борьбы с дребезгом, миллисекунды*/) { 
      this->name = name; 
      this->debounce = debounce; 
      pinMode( pin, INPUT_PULLUP); 
      this->pin = pin; 
      last = current = digitalRead( pin);
    }
    // конструкторы для объявления в других классах (обязательно используйте в конструкторе класса setPin для установки номера вывода)
    inline Key(String name, byte debounce) { this->name = name; this->debounce = debounce; this->pin = 255; last = current = 1; }
    inline Key(String name) { this->name = name; this->debounce = 5; this->pin = 255; last = current = 1; }
    // деструктор
    inline ~Key() {}
    // установка номера вывода для существующего объекта, применяется при определении других классов
    inline void setPin(byte pin) { pinMode( pin, INPUT_PULLUP); this->pin = pin; last = current = digitalRead( pin); }
    // возвращает текущее значение
    inline boolean value(void) { return last; }
    // обновляет состояние кнопки, должна быть вызвана из loop для каждого из экземпляров объекта
    inline void update(void) {
      current = digitalRead( pin);
      if( last != current) {
        delay( debounce);
        current = digitalRead( pin);
        if( last != current) {
          last = current;
          if( current == 0) { onPress( name); } else { onRelise( name);}
        }
      }
    }
    // обработчик нажатия - необходимо обязательно написать его реализацию
    virtual void onPress(String name);
    // обработчик отпускания - необходимо обязательно написать его реализацию
    virtual void onRelise(String name);
  private:
    String name; // имя экземпляра
    boolean current; // текущее состояние
    boolean last; // последнее стабильное состояние
    byte pin; // номер вывода
    byte debounce; // задержка в миллисекундах
};

#endif
