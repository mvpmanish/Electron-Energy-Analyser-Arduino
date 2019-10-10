#include "Arduino.h"
#include "MilliTimer.h"

MilliTimer::MilliTimer(){
  timeOut = 1000; // default time out is 1 second
  start = millis();
}

MilliTimer::MilliTimer(uint32_t t){
  timeOut = t;
  start = millis();
}

void MilliTimer::init(uint32_t t){
  timeOut = t;
  start = millis();
}

uint32_t MilliTimer::elapsed(){
  return millis() - start;
}

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

void MilliTimer::updateTimeOut(uint32_t t){
  timeOut = t;
}

void MilliTimer::reset(){
  start = millis();
}

uint32_t MilliTimer::getTimeOut(){
  return timeOut;
}