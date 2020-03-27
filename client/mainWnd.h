#pragma once

#include <QMainWindow>
#include "../common/common.h"

class QTextEdit;
class QLabel;

class mainWnd : public QMainWindow
{
    Q_OBJECT

public:
    mainWnd(QString, QString, char* serverPort = nullptr, short sPort = -1, QWidget *parent = Q_NULLPTR);
    void keyPressEvent(QKeyEvent* pevt);

signals:
    void sendMsg(QByteArray);

private slots:
    void errorString(QString);
    void shutdown(QString);
    void heartBeat(QString);
    void gameBegin(QString);
    void selectAvatar(QString);

private:
    void setupUI();
    void createActions();
    void createMenus();
    void createWorker(char*, short);

    QTextEdit*       m_txtState;   
    QLabel*          m_map;
    QVector<QLabel*> m_qvecCards;

};
