#include "tellstick.h"
#include "targetvalues.h"
#include <QMutex>
#include <QDebug>
#include <telldus-core.h>


Tellstick::Tellstick(class targetvalues *tgt){
    t=tgt;
    dutycycle=0;
}
Tellstick::~Tellstick(){
}

void Tellstick::txCMD(QString addr,int mode){
    QByteArray nexaaddr=addr.toLatin1(); 
    tdInit();
    int intNumberOfDevices = tdGetNumberOfDevices();
    for (int i = 0; i < intNumberOfDevices; i++) {
       int id = tdGetDeviceId( i );
       char *name = tdGetName( id );
       if(0==strcmp(nexaaddr,name)){
    //      printf("Found %d\t%s\n", id, name);
          if(mode==1){
            tdTurnOn(id);
          }
          if(mode==-1){
            tdTurnOff(id);
          }
       }
       tdReleaseString(name);
    }
    tdClose();
}
