#include "key.h"
#include "meter.h"
#include "comparator.h"
#include "encoder.h"

Key encoderkey = Key("encoderkey",7,5);
Comparator compare = Comparator("compare",A0,A0);
Encoder encoder = Encoder("encoder",2,4,0,8,0,CYCLIC);

void Key::onPress(String name) {Serial.println("press "+name);}
void Key::onRelise(String name) {}
void Meter::onChange(String name, int value) {}
void Comparator::onLess(String name) {Serial.println("compare <");}
void Comparator::onMore(String name) {Serial.println("compare >");}
void Comparator::onEqual(String name) {Serial.println("compare =");}
void Encoder::onChange(String name,int value) {Serial.println("encoder "+name+" is "+value);}

void setup() {
  Serial.begin(9600);
}

void loop() {
  encoderkey.update();
  compare.update();
  encoder.update();
}
