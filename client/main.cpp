
#include <QtWidgets/QApplication>
#include <QDialog>
#include <QDebug>
#include <QSettings>

#ifdef __WIN
#include "XGetopt.h"
#endif

#include "mainWnd.h"
#include "loginDlg.h"
#include "logger.h"

const char* defLogFile = ".\\client_exec.log";

void allocConsole();

// issues
// (1) modifying network setting are not persisited to the registry
// (2) gear-icon is not displayed on the log-in dialog, settings button

int main(int argc, char *argv[])
{
    int   nRet = 0;                                   // return value from main.
    char  c;
    char* logFile = nullptr;

    allocConsole();                                   // get a console up and running....
    
    QApplication a(argc, argv);
    QSettings  setting("JHUProj", "clue-less");       // getting settings, can be overridden by cmd line
                                                      // found at: HKEY_USERS\<user>\Software\JHUProj\clue-less
    // process command line arguments...
    while ((c = getopt(argc, argv, "dl:hv")) != EOF)
    {
        switch (c)
        {
            case 'd':                                 // setting debug level
                break;
            case 'l':                                 // setting custom log location
                break;
            case 'h':                                 // displaying help and exiting
                break;
            case 'v':                                 // displaying version and information
                break;
            case '?':                                 // unknown switch or error
            default:                                  // fall-through is expected

        }
    }

    if (nullptr == logFile) logFile = const_cast<char*>(defLogFile);
    CLogger::getInstance(logFile);                    // get logging up and running .....
    CLogger::getInstance()->LogMessage("Client starting up");

    loginDlg  dlg(nullptr, &setting);
    if (QDialog::Accepted == dlg.exec())                 // display login dialog
    {
        QString qstrUid = dlg.getUid();
        QString qstrPwd = dlg.getPwd();

        // TODO : build communication thread....
        // TODO : check to see if we can chat to server...
        // TODO : pass uid/pwd to server....
        // TODO : check to see if we've logged in....
        // TODO : if we railed to log in, clean up and bail
        //        else show main GUI.

        // TODO : if successfully login in, start comms thread and show main UI
        mainWnd w;
        w.show();
        nRet =  a.exec();
    }
    else
    {
        CLogger::getInstance()->LogMessage("User cancelled, exitting\n");
    }

    CLogger::delInstance();

    return nRet;
}



// printing debugging information, status information is common and helpful...
// except if you are brain-dead idiots from Microsoft who disable this stuff
// So, lets fix this.  (taken from Adding Console I/O to a Win32 GUI App,
// Windows Developer Journal, Dec 1997; and updated from 
// https://smacdo.com/programming/redirecting-standard-output-to-console-in-windows/)

#include <windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>



void allocConsole()
{
    // Create the console window and set the window title.
    if (AllocConsole() == 0)
    {
        // Handle error here. Use ::GetLastError() to get the error.
    }

    // Redirect CRT standard input, output and error handles to the console window.
    FILE * pNewStdout = nullptr;
    FILE * pNewStderr = nullptr;
    FILE * pNewStdin = nullptr;

    ::freopen_s(&pNewStdout, "CONOUT$", "w", stdout);
    ::freopen_s(&pNewStderr, "CONOUT$", "w", stderr);
    ::freopen_s(&pNewStdin, "CONIN$", "r", stdin);

    // Clear the error state for all of the C++ standard streams. Attempting to accessing the streams before they refer
    // to a valid target causes the stream to enter an error state. Clearing the error state will fix this problem,
    // which seems to occur in newer version of Visual Studio even when the console has not been read from or written
    // to yet.

    std::cout.clear();
    std::cerr.clear();
    std::cin.clear();

    std::wcout.clear();
    std::wcerr.clear();
    std::wcin.clear();
}
