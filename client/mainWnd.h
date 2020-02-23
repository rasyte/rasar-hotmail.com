#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainWnd.h"

class mainWnd : public QMainWindow
{
    Q_OBJECT

public:
    mainWnd(QWidget *parent = Q_NULLPTR);

private:
    Ui::mainWndClass ui;
};
