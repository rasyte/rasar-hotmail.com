#pragma once

#include <QObject>
#include <QString>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <time.h>


#include "logger.h"

class gameWorker : public QObject
{
    Q_OBJECT

public:
    gameWorker(char* serverIP, short sPort);
    ~gameWorker();

    //enum CMDS { CMD_HRT_BEAT = 0, CMD_UPDATE_STATE, CMD_SUGGEST, CMD_ACCUSE, CMD_INIT, CMD_PLAYER_JOIN, CMD_SHUTDOWN, CMD_HEARTBEAT};

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
    SOCKET   m_soc;               // socket we talk to the server on.


    bool   connectServer();
    void   disconnectServer();



};

// TODO : need to set m_bRun to false in finished handler