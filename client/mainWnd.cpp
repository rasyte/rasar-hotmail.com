
#include <QThread>
#include <QGroupBox>
#include <QCheckBox>
#include <QLabel>
#include <QApplication>
#include <QTextEdit>
#include <QMessageBox>
#include <QStatusBar>

#include "mainWnd.h"
#include "gameWorker.h"


const char* lpszSuspects[] = { "Col. Mustard","Prof. Plum","Mr. Green","Mrs. Peacock","Miss Scarlet", "Mrs. White" };
const char* lpszRooms[] = {"Hall", "Lounge", "Dining Room", "Kitchen", "Ball Room","Conservatory", "Billard Room", "Library", "Study"};
const char* lpszWeapons[] = {"Knife", "Candlestick", "Revolver", "Rope", "Lead Pipe", "Wrench"};


mainWnd::mainWnd(QString qstrUid, QString qstrPwd, char* serverIP, short sPort, QWidget *parent) : QMainWindow(parent)
{
    setupUI();
    createActions();
    createMenus();
    createWorker(serverIP,sPort);


    // TODO : check to see if we can chat to server...
    // TODO : pass uid/pwd to server....
    // TODO : check to see if we've logged in....
    // TODO : if we failed to log in, clean up and bail
    //        else show main GUI.

    // TODO : if successfully login in, start comms thread and show main UI


}


void mainWnd::setupUI() 
{
    QWidget*    centralWidget;   
    QFrame*     line1, * line2, * line3;
    QMenuBar*   menuBar;
    QMenu*      menuGame;
    QToolBar*   mainToolBar;
    QStatusBar* statusBar;
    QGroupBox*  grpBoxRooms;
    QGroupBox*  grpBoxSuspects;
    QGroupBox*  grpBoxWeapons;


    int cntSuspects = sizeof(lpszSuspects) / sizeof(lpszSuspects[0]);
    int cntRooms = sizeof(lpszRooms) / sizeof(lpszRooms[0]);
    int cntWeapons = sizeof(lpszWeapons) / sizeof(lpszWeapons[0]);

    QVector<QLabel*> qvecSuspects;
    QVector<QLabel*> qvecRooms;
    QVector<QLabel*> qvecWeapons;
    QVector<QLabel*> m_qvecCards;

    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("mainWndClass"));
    resize(1200, 919);//resize(887, 919);
    setWindowTitle("clue-less");

    // set up fonts that we will use
    QFont font;
    font.setFamily(QString::fromUtf8("Courier New"));
    font.setPointSize(14);

    QFont font1;
    font1.setFamily(QString::fromUtf8("AR BERKLEY"));
    font1.setPointSize(11);

    // set up central widget
    centralWidget = new QWidget(this);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    this->setCentralWidget(centralWidget);

    // build first note-book page.....
    // build suspects group box
    grpBoxSuspects = new QGroupBox(centralWidget);
    grpBoxSuspects->setObjectName(QString::fromUtf8("grpBoxSuspects"));
    grpBoxSuspects->setGeometry(QRect(10, 10, 191, 151));
    grpBoxSuspects->setTitle("Suspects");
    grpBoxSuspects->setFont(font);

    // build note-book entries...
    for (int ndx = 0; ndx < cntSuspects; ndx++)
    {
        QLabel* pTemp = new QLabel(grpBoxSuspects);
        pTemp->setObjectName(QString("suspect%1").arg(ndx));
        pTemp->setGeometry(QRect(10, 30 + 20 * ndx, 91, 16));
        pTemp->setText(lpszSuspects[ndx]);
        pTemp->setFont(font1);
        qvecSuspects.push_back(pTemp);

        // add in check boxes....
        for (int jdx = 0; jdx < 4; jdx++)
        {
            QCheckBox* pTemp1 = new QCheckBox(grpBoxSuspects);
            pTemp1->setObjectName(QString("chkBox%1%2").arg(ndx).arg(jdx));
            //setGeometry(QRect(x, y, width, heigth)
            pTemp1->setGeometry(QRect(110 + 20 * jdx, 30 + 20 * ndx, 16, 16));
        }
    }

    // add dividing line...
    line1 = new QFrame(grpBoxSuspects);
    line1->setObjectName(QString::fromUtf8("line1"));
    line1->setGeometry(QRect(90, 20, 20, 121));
    line1->setFrameShape(QFrame::VLine);
    line1->setFrameShadow(QFrame::Sunken);


    // build second note-book page...
    // build rooms group box
    grpBoxRooms = new QGroupBox(centralWidget);
    grpBoxRooms->setObjectName(QString::fromUtf8("grpBoxRooms"));
    grpBoxRooms->setGeometry(QRect(10, 160, 191, 221));
    grpBoxRooms->setTitle("Rooms");
    grpBoxRooms->setFont(font);

    // build note-book entries...
    for (int ndx = 0; ndx < cntRooms; ndx++)
    {
        QLabel* pTemp = new QLabel(grpBoxRooms);
        pTemp->setObjectName(QString("room%1").arg(ndx));
        pTemp->setGeometry(QRect(10, 30 + 20*ndx, 91, 16));
        pTemp->setText(lpszRooms[ndx]);
        pTemp->setFont(font1);
        qvecRooms.push_back(pTemp);

        // add in check boxes....
        for (int jdx = 0; jdx < 4; jdx++)
        {
            QCheckBox* pTemp1 = new QCheckBox(grpBoxRooms);
            pTemp1->setObjectName(QString("chkBox%1%2").arg(ndx).arg(jdx));
            //setGeometry(QRect(x, y, width, heigth)
            pTemp1->setGeometry(QRect(110 + 20 * jdx, 30 + 20 * ndx, 16, 16));
        }
    }

    // add dividing line ...
    line2 = new QFrame(grpBoxRooms);
    line2->setObjectName(QString::fromUtf8("line"));
    line2->setGeometry(QRect(90, 20, 20, 191));
    line2->setFrameShape(QFrame::VLine);
    line2->setFrameShadow(QFrame::Sunken);


    // build third note-book page...
    // build weapon group box
    grpBoxWeapons = new QGroupBox(centralWidget);
    grpBoxWeapons->setObjectName(QString::fromUtf8("grpBoxWeapon"));
    grpBoxWeapons->setGeometry(QRect(10, 380, 191, 161));
    grpBoxWeapons->setTitle("Weapons");
    grpBoxWeapons->setFont(font);

    // build note-book entries...
    for (int ndx = 0; ndx < cntWeapons; ndx++)
    {
        QLabel* pTemp = new QLabel(grpBoxWeapons);
        pTemp->setObjectName(QString("weapon%1").arg(ndx));
        pTemp->setGeometry(QRect(10, 30 + 20*ndx, 91, 16));
        pTemp->setText(lpszWeapons[ndx]);
        pTemp->setFont(font1);
        qvecWeapons.push_back(pTemp);

        // add in check boxes....
        for (int jdx = 0; jdx < 4; jdx++)
        {
            QCheckBox* pTemp1 = new QCheckBox(grpBoxWeapons);
            pTemp1->setObjectName(QString("chkBox%1%2").arg(ndx).arg(jdx));
            //setGeometry(QRect(x, y, width, heigth)
            pTemp1->setGeometry(QRect(110 + 20 * jdx, 30 + 20 * ndx, 16, 16));
        }
    }

    // add dividing line ...
    line2 = new QFrame(grpBoxWeapons);
    line2->setObjectName(QString::fromUtf8("line2"));
    line2->setGeometry(QRect(90, 20, 16, 131));
    line2->setFrameShape(QFrame::VLine);
    line2->setFrameShadow(QFrame::Sunken);

    // build state mangement window...
    m_txtState = new QTextEdit(centralWidget);
    m_txtState->setObjectName(QString::fromUtf8("m_txtState"));
    m_txtState->setGeometry(QRect(20, 620, 861, 241));

    // set up map...
    m_map = new QLabel(centralWidget);
    m_map->setObjectName(QString::fromUtf8("label"));
    m_map->setGeometry(QRect(210, 0, 681, 621));
    m_map->setPixmap(QPixmap(QString::fromUtf8("Resources/board.png")));
    m_map->setStyleSheet("border: 1px solid black");

    // setup card locations
    int cnt = 1;
    for (int row = 30; row < 501; row += 235)
    {
        for (int col = 900; col < 1064; col += 163)
        {
            QLabel* pTemp = new QLabel(centralWidget);
            pTemp->setObjectName(QString("card%1").arg(cnt));
            pTemp->setGeometry(QRect(col, row, 133, 205));
            pTemp->setPixmap(QPixmap(QString("Resources/card%1").arg(3*cnt + 2)));

            m_qvecCards.push_back(pTemp);
            ++cnt;
        }
    }
 
    // setup StatusBar
    QStatusBar* statusbar = new QStatusBar(this);
    statusbar->setObjectName(QStringLiteral("statusbar"));
    this->setStatusBar(statusbar);

    // setup menu
    //menubar = new QMenuBar(this);
    //menubar->setObjectName(QStringLiteral("menubar"));
    //menubar->setGeometry(QRect(0, 0, WIN_WIDTH, 21));
    //this->setMenuBar(menubar);

    QMetaObject::connectSlotsByName(this);
} 



void mainWnd::createActions() 
{
    //m_fileOpen = new QAction("&Open", this);
    //m_fileOpen->setShortcuts(QKeySequence::Open);
    //m_fileOpen->setStatusTip("opens existing configuration file");
    //connect(m_fileOpen, &QAction::triggered, this, &LanGen::onFileOpen);
}

void mainWnd::createMenus() 
{
    //m_fileMenu = menuBar()->addMenu("&File");
    //m_fileMenu->addAction(m_fileNew);
    //m_fileMenu->addAction(m_fileOpen)
}

void mainWnd::createWorker(char* sIP, short sPort) 
{
    QThread* pThread = new QThread;                 // build communication thread....
    gameWorker* pWorker = new gameWorker(sIP, sPort);
    pWorker->moveToThread(pThread);

    // set up signal/slot connections 
    connect(pWorker, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
    connect(pWorker, SIGNAL(serverShutdown(QString)), this, SLOT(shutdown(QString)));
    connect(pWorker, SIGNAL(hrtBeat(QString)), this, SLOT(heartBeat(QString)));
    connect(pWorker, SIGNAL(finished()), pWorker, SLOT(deleteLater()));
    connect(pWorker, SIGNAL(finished()), pThread, SLOT(quit()));
    connect(pThread, SIGNAL(started()), pWorker, SLOT(process()));
    connect(pThread, SIGNAL(finished()), pThread, SLOT(deleteLater()));


    pThread->start();                               // start the thread running

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// private slots:
void mainWnd::errorString(QString msg)
{
    QMessageBox::critical(this, "Error", msg);
}

void mainWnd::shutdown(QString msg)
{
    QString strHtml= QString("<font color=\"red\">%1</font>").arg(msg);
    m_txtState->insertHtml(strHtml);

}

void mainWnd::heartBeat(QString msg)
{
    QString strHtml = QString(msg);
    m_txtState->insertHtml(strHtml);
    statusBar()->showMessage(msg);
}
