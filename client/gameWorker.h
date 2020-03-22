#pragma once

#include <QObject>
#include <QString>

//#include <winsock2.h>
//#include <ws2tcpip.h>
//#include <time.h>


#include "logger.h"

class gameWorker : public QObject
{
    Q_OBJECT

public:
    gameWorker(char* serverIP, short sPort);
    ~gameWorker();

public slots:
    void process();

signals:
    void finished();
    void error(QString err);
    void hrtBeat(QString time);
    void serverShutdown(QString msg);

private:
    bool     m_bRun;
    char*    m_sIP;
    short    m_sPort;
    int /*SOCKET*/   m_soc;               // socket we talk to the server on.


    bool   connectServer();
    void   disconnectServer();



};

// TODO : need to set m_bRun to false in finished handler