// intervalTimer 2022 by Erik Dorstel
// published 2022 under GNU GENERAL PUBLIC LICENSE Version 3
// https://github.com/ErikDorstel/intervalTimer
//
// This library defines a C++ class which makes it possible to control the call of code parts
// within functions or functions at timed intervals. The Arduino function millis() is required.
//
// Five attributes are used for parameterization:
//
// * uint32_t time - The time between two intervals in milliseconds. (default value 1000)
// * bool active - Activates and deactivates the interval timer. (default value false)
// * uint32_t start - The time after which the first interval starts. (default value 1000)
// * int count - The number of cycles. itInfinite for infinite operation. (default value itInfinite)
// * void call - A function pointer to call a specific function. (default nullptr)
//
// The following methods are supported:
//
// * constructor(time,active,start,count,call)
// * enable() - Set active to true.
// * disable() - Set active to false.
// * reset() - The interval time and the cycle counter are set to the start values.
// * restart() - The interval time and the cycle counter are set to the start values. (Starts with the first interval.)
// * set(time,active,start,count,call)
// * check() - Checks whether the next interval has been reached. Returns true or false. Calls a function if call not nullptr.

#ifndef INTERVAL_TIMER_H
#define INTERVAL_TIMER_H

#define itInfinite -1

class intervalTimer {
  public:
    uint32_t timer;
    uint32_t time=1000;
    bool active=false;
    uint32_t start=1000;
    int counter=itInfinite;
    int count=itInfinite;
    void (*call)(void)=nullptr;

    intervalTimer(uint32_t value1=1000,bool value2=false,uint32_t value3=1000,int value4=itInfinite,void (*value5)(void)=nullptr) {
      time=value1; active=value2; start=value3; timer=millis()+value3; counter=value4; count=value4; call=value5; }

    void set(uint32_t value1=1000,bool value2=false,uint32_t value3=1000,int value4=itInfinite,void (*value5)(void)=nullptr) {
      time=value1; active=value2; start=value3; timer=millis()+value3; counter=value4; count=value4; call=value5; }

    void enable() { active=true; }
    void disable() { active=false; }

    void reset() { active=true; timer=millis()+time; counter=count; }
    void restart() { active=true; timer=millis()+start; counter=count; }

    bool check() {
      if (millis()>=timer) {
        if (active && counter!=0) {
          if (count>0 && counter>0) { counter--; }
          timer=millis()+time; if (call!=nullptr) { call(); } return true; }
        else { return false; } }
      else { return false; } } };

#endif
