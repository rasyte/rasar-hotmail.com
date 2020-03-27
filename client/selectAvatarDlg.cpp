#include "../common/common.h"
#include "selectAvatarDlg.h"

#include <QRadioButton>
#include <QPushButton>
#include <QByteArray>
#include <QMessageBox>

selectAvatarDlg::selectAvatarDlg(QWidget* parent, QByteArray qba) : QDialog(parent), m_qbaAvatars(qba)
{
    setupUI();
}

void selectAvatarDlg::setupUI()
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("selectAvatarDlg"));
    resize(175, 182);
    setContextMenuPolicy(Qt::NoContextMenu);
    setWindowTitle("Select Avatar");

    QFont font;
    font.setFamily(QString::fromUtf8("AR BERKLEY"));
    font.setPointSize(16);

    for (int ndx = 0; ndx < NBR_SUSPECTS; ndx++)
    {
        QRadioButton* pTemp = new QRadioButton(this);
        pTemp->setObjectName(QString("btnAvatar%1").arg(ndx));
        pTemp->setGeometry(QRect(10, 10 + 20*ndx, 82, 17));
        pTemp->setText(lpszSuspects[ndx]);
        pTemp->setFont(font);
        if (0xFF == m_qbaAvatars.at(ndx))
        {
            pTemp->setEnabled(false);           // avatar has already been selected
            pTemp->setChecked(true);            // show it as selected
        }

        m_vecPushButton.push_back(pTemp);
    }

    m_btnSelect = new QPushButton(this);
    m_btnSelect->setObjectName(QString::fromUtf8("m_btnSelect"));
    m_btnSelect->setGeometry(QRect(10, 130, 75, 23));
    m_btnSelect->setText("Select");
    m_btnSelect->setFont(font);

    connect(this, SIGNAL(selected()), this, SLOT(onDone()));
}


void selectAvatarDlg::onDone()
{
    QByteArray   trial;

    // get current state of the Dialog...
    for (int ndx = 0; ndx < NBR_SUSPECTS; ndx++)
    {
        if (m_vecPushButton.at(ndx)->isChecked())
            trial.append(0xFF);
        else
            trial.append((char)0x00);
    }

    // compare the trial to the original, if the same user had not selected..
    if (m_qbaAvatars.compare(trial) == 0)   
    {
        QMessageBox::critical(this, "error", "you must select an avatar");
    }
    else                                        // accept the current selection
    {
        m_qbaAvatars = trial;
        QDialog::accept();
    }
}
