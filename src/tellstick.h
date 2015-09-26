#include "targetvalues.h"
#include <QDebug>
#include <QString>
#include <QDate>
#include <QTime>
#include <QThread>
#include <QMutex>


#ifndef  __TELLSTICK_H
#define  __TELLSTICK_H

class Tellstick
{
    class targetvalues *t;
    class targetvalues *internal;

public:
    Tellstick(class targetvalues *tgt);
    ~Tellstick();
    void txCMD(QString,int);
private:
    int dutycycle;
    QMutex mutex;
    void run();
};

#endif
