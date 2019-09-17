#include "Arduino.h"
#include "MilliTimer.h"

MilliTimer::MilliTimer(){
  timeOut=1000000;
  start=millis();
}

MilliTimer::MilliTimer(unsigned long t){
  timeOut=t;
  start=millis();
}

void MilliTimer::init(unsigned long t){
  timeOut=t;
  start=millis();
}

unsigned long MilliTimer::elapsed(){
  return millis() - start;
}

// bool MilliTimer::timedOut(){
//   if(elapsed() >= timeOut){
//     return true;
//   }
//   else{
//     return false;
//   }
// }

bool MilliTimer::timedOut(bool RESET){
  if(elapsed() >= timeOut){
    if(RESET) reset();
    return true;
  }
	else{
    return false;
  }
}

bool MilliTimer::timedOutAndReset(){
  return timedOut(true);
}

void MilliTimer::updateTimeOut(unsigned long t){
  timeOut=t;
}

void MilliTimer::reset(){
  start=millis();
}

unsigned long MilliTimer::getTimeOut(){
  return timeOut;
}