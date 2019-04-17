/*
	Обработчик произвольного измерителя значения аналогового сигнала

	Подключается к одному аналоговому входу

	При изменении состояния генерирует события:
  * onChange

  Диапазон значений: 0...1024

  Можно настроить шаг при изменении свыше которого генерируется событие

	Создано 3.02.2019
	Юрий Ботов
	Изменено 17.04.2019
	Юрий Ботов

	http://github.com/yurybotov/ArduinoControls.git

*/

#ifndef __METER_H__
#define __METER_H__
#include "arduino.h"

// произвольный аналоговый сенсор - измеритель напряжения на входе АЦП
// значение аналогового сенсора в диапазоне: 0-1023
// точность по умолчанию: 4 , при увеличении точности (уменьшении этого значения) сказывается шум в 2х младших разрядах
class Meter {
  public:
    // полный конструктор
    inline Meter(String name, byte pin, byte reftype, int selectivity) { current = 32767; this->name = name; this->pin = pin; this->selectivity = selectivity; analogReference(reftype); }
    // конструктор без задания селективности
    inline Meter(String name, byte pin, byte reftype) { current = 32767; this->name = name; this->pin = pin; this->selectivity = 4; analogReference(reftype); }
    // конструктор с ref по умолчанию - 1024 отсчета на полное напряжение питания
    inline Meter(String name, byte pin, int selectivity) { current = 32767; this->name = name; this->pin = pin; this->selectivity = selectivity; analogReference(DEFAULT); }
    // конструктор с селективностью и ref по умолчанию 
    inline Meter(String name, byte pin) { current = 32767; this->name = name; this->pin = pin; this->selectivity = 4; analogReference(DEFAULT); }
    // конструктор для наследуемых объектов - после него обязательно нужно выполнить setPin
    inline Meter(String name) { current = 32767; this->name = name; this->pin = 255; this->selectivity = 4; analogReference(DEFAULT); }
    // деструктор
    inline ~Meter() {}
    // установка номера вывода в наследуемых классах
    inline void setPin(byte pin) { this->pin = pin; }
    // установка имени (иногда бывает нужно...)
    inline void setName(String name) { this->name = name; }
    // возвращает последнее сохраненное состояние
    inline int value(void) { return current; }
    // обновляет состояние сенсора, должна быть вызвана из loop для каждого из экземпляров объекта
    inline void update(void) { int value = analogRead(pin); if( abs( abs(value) - abs(current)) > selectivity ) { current = value; onChange(name, current); }}
    // обработчик изменения значения - частота его срабатывания обратно пропорциональна selectivity. При малых значениях selectivity шум вызывает постоянное срабатывание
    virtual void onChange(String name, int value);
  private:
    int selectivity; // "чувствительность" датчика - при изменении последнего состояния более чем на эту величину, вызывается onChange
    int current; // последнее сохраненное значение
    String name; // имя датчика
    byte pin; // аналоговый вывод датчика A0...A5..A7
};

#endif
