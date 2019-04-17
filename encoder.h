#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "arduino.h"
#include "key.h"

// обход forward definition
class EncoderSensor;
class Encoder;

// вспомогательный класс обработчик датчика энкодера. Используется классом RotaryEncoder
// наследуется от класса кнопки с подавлением дребезга
class EncoderSensor : public Key {
  public:
    // обычный конструктор
    inline EncoderSensor(String name/*имя датчика*/, Encoder* encoder/*ссылка на вызывающий класс*/) 
    : Key( name, 2 /*для энкодера время дебаунсинга меньше, иначе пропускает изменения*/) { parent = encoder; }
    // деструктор
    inline ~EncoderSensor() {}
    // обработчик нажатия - определен в rotaryencoder.cpp
    virtual void onPress(String name);
    // обработчик отпускания - определен в rotaryencoder.cpp
    virtual void onRelise(String name);
  private:
    Encoder* parent; // добавочная ссылка на вызывающий объект
};

// режимы работы энкодера: CYCLIC - по достижению максимального значения переходит к минимальному
// NOCYCLIC - при достижении максимального значения останавливается на нем, с минимальными аналогично
enum  EncoderMode {CYCLIC = true, NOCYCLIC = false};

// класс обработчик двухточечного вращающегося энкодера (мышиное колесо)
class Encoder {
  public:
    inline Encoder(String name, byte A_or_CLK/*номер пина вывода clock(A)*/, byte B_or_DT/*номер пина вывода data(B)*/, 
                        int min/*минимальное значение на выходе*/, int max/*максимальное значение на выходе*/, 
                        int start/*состояние на момент старта*/, enum EncoderMode mode/*режим работы: циклический или нет*/) { 
      this->name = name;
      clkPin.setPin( A_or_CLK); 
      dataPin.setPin( B_or_DT); 
      position = start;
      buf = "";
      this->min = min;
      this->max = max;
      this->mode = mode;
    }
    // по умолчанию начальное состояние - 0
    inline Encoder(String name, byte A_or_CLK/*номер пина вывода clock(A)*/, byte B_or_DT/*номер пина вывода data(B)*/, 
                        int min/*минимальное значение на выходе*/, int max/*максимальное значение на выходе*/,
                        enum EncoderMode encodermode/*режим работы: циклический или нет*/) { 
      this->name = name;
      clkPin.setPin( A_or_CLK); 
      dataPin.setPin( B_or_DT); 
      position = 0;
      buf = "";
      this->min = min;
      this->max = max;
      this->mode = mode;
    }
    // по умолчанию режим работы циклический
    inline Encoder(String name, byte A_or_CLK/*номер пина вывода clock(A)*/, byte B_or_DT/*номер пина вывода data(B)*/, 
                        int min/*минимальное значение на выходе*/, int max/*максимальное значение на выходе*/, 
                        int start/*состояние на момент старта*/) { 
      this->name = name;
      clkPin.setPin( A_or_CLK); 
      dataPin.setPin( B_or_DT); 
      position = start;
      buf = "";
      this->min = min;
      this->max = max;
      mode = CYCLIC;
    }   
    // обычный конструктор - режим циклический, максимальное и минимальное значения -255...255
    inline Encoder(String name, byte A_or_CLK/*номер пина вывода clock(A)*/, byte B_or_DT/*номер пина вывода data(B)*/) { 
      this->name = name;
      clkPin.setPin( A_or_CLK); 
      dataPin.setPin( B_or_DT); 
      position = 0;
      buf = "";
      this->min = -255;
      this->max = 255;
      mode = CYCLIC;
    }
    // деструктор
    inline ~Encoder(void) {}
    // обновляет состояние энкодера, должна быть вызвана из loop для каждого из экземпляров объекта
    inline void update(void) { clkPin.update(); dataPin.update(); }
    // вызывается из обработчиков EncoderSensors, собственно декодер движения
    void event(String name); 
    // возвращает текущее стабильное значение положения энкодера
    inline int value(void) { return position; }
    // позволяет программно менять текущее положение энкодера
    inline void setValue(int value) { position = value; }
    // обработчик изменения значения положения энкодера - необходимо создать
    virtual void onChange(String name, int value);
  private:
    String name; // произвольное имя
    String buf; // буфер в котором копится 4 символа в соответствии с порядком этих символов принимается решение о направлении
    int position; // текущее положение энкодера
    EncoderSensor& clkPin = *new EncoderSensor( String("A"), this); // датчик clock энкодера
    EncoderSensor& dataPin = *new EncoderSensor( String("B"), this); // датчик дата энкодера
    int min; // минимальное значение на выходе
    int max; // максимальное значение на выходе
    boolean mode; // режим работы циклический или нециклический (с упорами сверху и снизу)
};

#endif
