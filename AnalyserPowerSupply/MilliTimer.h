#ifndef MILLITIMER_H
#define MILLITIMER_H
#include <stdint.h> // Needed since Arduino IDE 1.8.10 otherwise get error about uint32_t not being named type.

// This class sets up a software timer which allows the caller to check how much time has elapsed since 
// it was last polled and report whether a minimum interval has been passed.
// This allows events to be setup to occur at minimum set intervals within a block of code.
// To use, ideally the timer must be polled often enough that timed events are not started late.
  

class MilliTimer
{ 
    volatile uint32_t start;
    volatile uint32_t timeOut;
  public:
    MilliTimer();
    MilliTimer(uint32_t t);
    void init(uint32_t t); //initialisation function to be used if the timer is created with the null constructor.
    uint32_t elapsed();// return the elapsed time.
    //bool timedOut();// function to check whether the timer has timed out. If it has, reports true and resets the timer
    bool timedOut(bool RESET = false);
    bool timedOutAndReset(); // equivalent to timedOut(true);
    void updateTimeOut(uint32_t t); //update the timeout variable without restarting the current time
    uint32_t getTimeOut();
    void reset(); // reset the timer.      
};


#endif 
