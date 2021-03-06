/**
 * @file MosqConnect.cpp
 * @author Johan Simonsson
 * @brief Mosquitto interface
 */

/*
 * Copyright (C) 2014 Johan Simonsson
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstdio>
#include <cstring>

#include <QString>
#include <QDebug>
#include <QRegExp>
#include <QDateTime>
#include <QRegExp>

#include <mosquittopp.h>

#include "MosqConnect.h"
#include "targetvalues.h"
#include "tellstick.h"

MosqConnect::~MosqConnect()
{
}
MosqConnect::MosqConnect(
        const char *id,
        const char *host,
        int port,
        class targetvalues *tgt,
        class Tellstick *myiow
        ) : mosquittopp(id)
{
    int keepalive = 60;
    t= tgt;
    iow=myiow;
    // Connect immediately.
    connect(host, port, keepalive);
};

void MosqConnect::on_connect(int rc)
{
    if(rc == 0){
        // Only attempt to subscribe on a successful connect.
	subscribe(NULL,"/telldus/nexa/#");
    }
}

void MosqConnect::on_message(const struct mosquitto_message *message)
{
    /*
       struct mosquitto_message{
       int mid;
       char *topic;
       void *payload;
       int payloadlen;
       int qos;
       bool retain;
       };
       */

    //Move from "void* with payloadlen" to a QString.
    char* messData = (char*)malloc(sizeof(char)*(message->payloadlen+1));
    memcpy(messData, message->payload, message->payloadlen);
    messData[message->payloadlen] = '\0';

    //printf("Message %s - %s.\n", message->topic, messData);

    QString mess = QString(messData);
    free(messData);

    QString topic = QString(message->topic);

    //qDebug() << "New message:" << (QDateTime::currentDateTime()).toString("hh:mm:ss") << topic << mess;

                QRegExp rxCmd("(ON|OFF)");
                QRegExp rxAddr("/telldus/nexa/(.*)");
                if((rxAddr.indexIn(topic) != -1)&& (rxCmd.indexIn(mess) != -1))
                {
                    // qDebug() << "Force" << rxAddr.cap(1) << rxAddr.cap(2) << rxAddr.cap(2).toInt();
                    int mode=0;
                    if(0==rxCmd.cap(1).compare("ON")){
                        mode=1;
                    } else if(0==rxCmd.cap(1).compare("OFF")){
                        mode=-1;
                    }
                    // qDebug()<<rxAddr.cap(1)<<" Mode: "<<mode;
                    iow->txCMD(rxAddr.cap(1),mode);
                }
                else
                {
                }
}

void MosqConnect::on_subscribe(int mid, int qos_count, const int *granted_qos)
{
    printf("Subscription succeeded. mid=%d qos=%d granter_qos=%d\n", mid, qos_count, *granted_qos);
}

void MosqConnect::pub(QString topic, QString subject)
{
    publish(NULL, topic.toAscii(), subject.size(), subject.toAscii());
}
