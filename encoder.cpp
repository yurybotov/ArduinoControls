 #include "encoder.h"
 
 // обработчики "нажатия" и "отпускания" датчиков энкодера - сообщают классу энкодера о произошедших событиях нажатия и отпускания
 void EncoderSensor::onPress(String name) { parent->event(name); }
 void EncoderSensor::onRelise(String name) { parent->event(name); }

// вызывается из обработчиков EncoderSensors, собственно декодер движения
void Encoder::event(String name) { 
  buf = buf + name; // накапливаем 4 символа полученных от датчиков (набор из "A" и "B")
  if( buf.length() == 4) // накопили ...
  {
    if(buf == String("ABAB")) { // это последовательность корректного поворота вправо
      position++; 
      if( mode) {
        if (position >= max+1) { position = min; onChange( name, position); buf = ""; return; }
      } else {
        if (position >= max+1) { position = max; buf = ""; return; }
      }
      onChange( name, position);
      } 
    else { if(buf == String("BABA")) {  // это влево, все остальные некорректны и игнорируются
        position--;
        if( mode) {
          if (position <= min-1) { position = max; onChange( name, position); buf = ""; return; }
        } else {
          if (position <= min-1) { position = min; buf = ""; return;}
        }
        onChange( name, position);
        }
      } 
    buf = "";
  }
}
