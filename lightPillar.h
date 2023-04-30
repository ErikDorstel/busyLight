#include "buttonTimer.h"
#include "intervalTimer.h"

#define greenOut 32
#define yellowOut 25
#define redOut 26
#define beepOut 27
#define greenIn 19
#define yellowIn 18
#define redIn 17

int defaultUnit=1000*60*10; int beepUnit=100; int alarmUnit=200;

buttonTimer greenButton(greenIn,nullptr,normClosed);
buttonTimer yellowButton(yellowIn,nullptr,normOpen);
buttonTimer redButton(redIn,nullptr,normOpen);
intervalTimer timerOne; intervalTimer timerTwo; intervalTimer timerThree;
int activeIn=0; bool alarmIn=false; bool overMax=false;

void beepOn() {
  if (alarmIn==true) {
    if (activeIn==0 || activeIn==redIn) { activeIn=greenIn; digitalWrite(redOut,LOW); digitalWrite(greenOut,HIGH); }
    else if (activeIn==greenIn) { activeIn=yellowIn; digitalWrite(greenOut,LOW); digitalWrite(yellowOut,HIGH); }
    else if (activeIn==yellowIn) { activeIn=redIn; digitalWrite(yellowOut,LOW); digitalWrite(redOut,HIGH); } }
  digitalWrite(beepOut,HIGH); timerTwo.restart();
  if (debug && alarmIn==false) { Serial.println("Beep"); } }

void beepOff() { digitalWrite(beepOut,LOW); timerTwo.disable(); }

void allOff() {
  if (activeIn!=0 || alarmIn==true) {
    timerOne.disable(); timerThree.disable(); activeIn=0; alarmIn=false; beepOn();
    digitalWrite(greenOut,LOW); digitalWrite(yellowOut,LOW); digitalWrite(redOut,LOW);
    if (debug) { Serial.println("All off"); } } }

void alarmOn() { allOff(); alarmIn=true; timerThree.restart(); if (debug) { Serial.println("Alarm"); } }

void buttonChanged(uint8_t gpio,uint32_t duration) {
  if (debug) { Serial.print("GPIO: "); Serial.print(gpio); Serial.print(" for "); Serial.print(duration); Serial.println(" ms"); }
  if (duration>1900) { allOff(); overMax=true; return; }
  if (duration>0 && overMax==false) {
    if (gpio==activeIn) { timerOne.timer+=defaultUnit; if (debug) { Serial.println("Timer: +" + String(defaultUnit/1000) + " seconds"); } return; }
    if (gpio==greenIn) { allOff(); digitalWrite(greenOut,HIGH); activeIn=gpio; timerOne.restart(); if (debug) { Serial.println("Green on"); } }
    if (gpio==yellowIn) { allOff(); digitalWrite(yellowOut,HIGH); activeIn=gpio; timerOne.restart(); if (debug) { Serial.println("Yellow on"); } }
    if (gpio==redIn) { allOff(); digitalWrite(redOut,HIGH); activeIn=gpio; timerOne.restart(); if (debug) { Serial.println("Red on"); } } }
  overMax=false; }

void initPillar() {
  pinMode(greenOut,OUTPUT); pinMode(yellowOut,OUTPUT); pinMode(redOut,OUTPUT); pinMode(beepOut,OUTPUT); allOff();
  greenButton.set(greenIn,buttonChanged,normClosed,activeLow,100,2000,true);
  yellowButton.set(yellowIn,buttonChanged,normOpen,activeLow,100,2000,true);
  redButton.set(redIn,buttonChanged,normOpen,activeLow,100,2000,true);
  timerOne.set(defaultUnit,false,defaultUnit,1,allOff);
  timerTwo.set(beepUnit,false,beepUnit,1,beepOff);
  timerThree.set(alarmUnit,false,0,itInfinite,beepOn); }

void pillarWorker() { greenButton.worker(); yellowButton.worker(); redButton.worker(); timerOne.check(); timerTwo.check(); timerThree.check(); }
