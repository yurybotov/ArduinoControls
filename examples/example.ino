/*
	Пример использования энкодера с кнопкой и аналогового компаратора

	Компаратор подключается к двум аналоговым входам A0 и A1
  Энкодер подключается: CLK - 2, DT - 4, кнопка энкодера - 7

	Результаты отображаются через Serial

	Создано 3.02.2019
	Юрий Ботов
	Изменено 17.04.2019
	Юрий Ботов

	http://github.com/yurybotov/ArduinoControls.git

*/

#include "arduino.h"

#include "key.h"
#include "meter.h"
#include "comparator.h"
#include "encoder.h"

// Кнопка энкодера. 7 - номер вывода, 5 - время дебаунсинга в миллисекундах
Key encoderkey = Key("encoderkey", 7, 5);
// Компаратор. A0 и A1 - подключаемые выводы CLK (A) и DT (B)
Comparator compare = Comparator("compare", A0, A1);
// Энкодер. 2 и 4 - номера выводов, 0 и 8 - минимальное и максимальное значения, 0 - стартовое значение, CYCLIC - при выходе значения за пределы оно зацикливается
Encoder encoder = Encoder("encoder",2,4,0,8,0,CYCLIC);

void Key::onPress(String name) {Serial.println("pressed "+name);}
void Key::onRelise(String name) {} // обработчик нужен даже если мы не хотим его использовать, просто делаем пустой обработчик
void Meter::onChange(String name, int value) {} // для "родительских" классов надо добавить пустые обработчики
void Comparator::onLess(String name) {Serial.println("compare <");}
void Comparator::onMore(String name) {Serial.println("compare >");}
void Comparator::onEqual(String name) {Serial.println("compare =");}
void Encoder::onChange(String name,int value) {Serial.println("encoder "+name+" is "+value);}

void setup() {
  Serial.begin(9600);
}

void loop() {
  // вызываем для каждого экземпляра команду update
  encoderkey.update();
  compare.update();
  encoder.update();
  // а тут все остальное... 

}
