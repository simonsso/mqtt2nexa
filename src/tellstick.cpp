#include "tellstick.h"
#include "targetvalues.h"
#include <QMutex>
#include <QDebug>

Tellstick::Tellstick(class targetvalues *tgt){
    t=tgt;
    dutycycle=0;
}
Tellstick::~Tellstick(){
}
// Set dutycycle raw - TODO: caller should not need to know internal max
void Tellstick::setDutyCycle(int dc){
   mutex.lock();
   dutycycle=dc;
   mutex.unlock();
}

void Tellstick::run(){
    //TODO use targetvalue as increment give maxint to force on now.

    //loop forever
    while(1){
        mutex.lock();
        int sleeptimer=t->getDiv();
        dutycycle+=t->getT();
        if(dutycycle <0 ){
            dutycycle=0; //Zero
        }else if (dutycycle >8192){
            dutycycle=8192;
        }

        mutex.unlock();
        usleep(50000*sleeptimer);
    }
}
