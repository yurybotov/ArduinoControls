﻿## Библиотека элементов управления генерирующих события

#### Key
обработчик произвольного контактного датчика, например кнопки, с подавлением дребезга. Генерирует события onPress и onRelise.

#### Encoder 
обработчик двух-точечного энкодера вращения, например колесико механической мыши. Использует Key. Генерирует событие onChange. Настраиваются диапазон значений и режим работы - закольцованный или с упорами по краям.

#### Meter
обработчик произвольного аналогового датчика подключенного к АЦП. Генерирует событие onChange при изменении значения больше чем на значение "чувствительности" - которую можно задать. "Чувствительность" по умолчанию: 4. Диапазон значений 0...1024.

#### Ranger
обработчик значения аналогового датчика контролирующий выход значения параметра за фиксированные границы. Использует Meter. Например термостат, водокачка. Генерирует события onLess, onMore, onRange. Последнее удобно для индикации. 

#### Comparator
обработчик значений двух аналоговых датчиков. Использует Meter. Если значение одного датчика превышает значение другого на величину гистерезиса и более генерируются сообщение onLess или onMore.

#### Joystic
обработчик двух-координатного джойстика. Использует Meter. Диапазон значений на выходе маппируется в -255...0...255. Требуется калибровка в setup(). Генерируется событие onChange при переходе одной из координат через границу "чувствительности".

Немного в сторонке стоит
#### Blinker
он полезен при отладке, когда на устройстве с одним светодиодом можно отобразить 6 состояний: не горит, медленно мигает, медленно вспыхивает на короткое время, мигает часто или "средне" и светится постоянно.

### Использование
1. Подцепить соответствующий *.h файл
```
#include "key.h"
```
2. Создать соответствующие объекты
```
Key ok = Key("Ok" /*имя кнопки*/,2 /*нога Arduino*/,5 /*время дебаунсинга в миллисекундах*/);
Key cancel = Key("Cancel",4,5);
```
3. Написать обработчики событий
```
void Key::onPress(String name) {
  if(name == String("Ok")) {/*что то сделать*/} else { /*если Cancel то сделать что то другое*/}
};
void Key::onRelise(String name) {} // надо описать все обработчики, если они не используются - создайте пустые
```
Есть одна тонкость c virtual методами... Если вы используете Encoder, но не используете Key - добавьте пустые обработчики Key. И соответственно если вы используете Joystick, Ranger, Comparator но не используете Meter - добавьте пустой обработчик Meter.
Возможно, потом я это потом исправлю.
 
4. В setup() обычно ничего добавлять не надо, за исключением Joystick. Для экземпляров класса Joystick добавьте метод .calibrate()
5. В loop() добавить вызовы .update() для каждого из экземпляров.
```
void loop() {
  ok.update();
  cancel.update();
  // ... ваш прочий код
}
```
