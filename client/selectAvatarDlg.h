#pragma once

#include <QDialog>
#include <QByteArray>


class QPushButton;
class QRadioButton;

class selectAvatarDlg : public QDialog
{
    Q_OBJECT

public:
    selectAvatarDlg(QWidget* parent, QByteArray);
    QByteArray  getAvatars(){ return m_qbaAvatars; }

public slots:
    void onDone();

private:
    void setupUI();

    QPushButton*             m_btnSelect;
    QVector<QRadioButton*>   m_vecPushButton;
    QByteArray               m_qbaAvatars;
};
