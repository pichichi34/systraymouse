#include <QtGui>

#include "mainwindow.h"

//! [0]
Window::Window()
{

    createMessageGroupBox();


    createActions();
    createTrayIcon();

    connect(programDeviceButton, SIGNAL(clicked()), this, SLOT(programDevice()));
    connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(messageClicked()));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(messageGroupBox);
    setLayout(mainLayout);

    trayIcon->show();

    setWindowTitle(tr("Systraymouse"));
    resize(400, 300);
}
//! [0]

//! [1]
void Window::setVisible(bool visible)
{
    minimizeAction->setEnabled(visible);
    maximizeAction->setEnabled(!isMaximized());
    restoreAction->setEnabled(isMaximized() || !visible);
    QDialog::setVisible(visible);
}
//! [1]

//! [2]
void Window::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible()) {
        QMessageBox::information(this, tr("Systraymouse"),
                                 tr("The program will keep running in the "
                                    "system tray. To terminate the program, "
                                    "choose <b>Quit</b> in the context menu "
                                    "of the system tray entry."));
        hide();
        event->ignore();
    }
}
//! [2]

//! [3]
void Window::setIcon(int index)
{
    QIcon icon("bad.svg");
    trayIcon->setIcon(icon);
    setWindowIcon(icon);
}
//! [3]

//! [4]
void Window::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::MiddleClick:
        showMessage();
        break;
    default:
        ;
    }
}
//! [4]

//! [5]
void Window::showMessage()
{
    QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(
            typeComboBox->itemData(typeComboBox->currentIndex()).toInt());
    trayIcon->showMessage(titleEdit->text(), bodyEdit->toPlainText(), icon,
                          durationSpinBox->value() * 1000);
}
//! [5]

//! [6]
void Window::messageClicked()
{
    QMessageBox::information(0, tr("Systray"),
                             tr("Sorry, I already gave what help I could.\n"
                                "Maybe you should try asking a human?"));
}
//! [6]

void Window::createIconGroupBox()
{
    iconGroupBox = new QGroupBox(tr("Tray Icon"));


    iconComboBox = new QComboBox;
    iconComboBox->addItem(QIcon(":/images/bad.svg"), tr("Bad"));
    showIconCheckBox = new QCheckBox(tr("Show icon"));
    showIconCheckBox->setChecked(true);

#if defined(Q_WS_X11)
    jitToolTipCheckBox = new QCheckBox(tr("Just In Time Tooltip"));
#endif

    QHBoxLayout *iconLayout = new QHBoxLayout;
    iconLayout->addWidget(iconLabel);
    iconLayout->addWidget(iconComboBox);
    iconLayout->addStretch();
    iconLayout->addWidget(showIconCheckBox);
#if defined(Q_WS_X11)
    iconLayout->addWidget(jitToolTipCheckBox);
#endif
    iconGroupBox->setLayout(iconLayout);
}


void Window::createActions()
{
    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

    maximizeAction = new QAction(tr("Ma&ximize"), this);
    connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void Window::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    QByteArray category = qgetenv("SNI_CATEGORY");
    if (!category.isEmpty()) {
        trayIcon->setProperty("_qt_sni_category", QString::fromLocal8Bit(category));
    }
    trayIcon->setContextMenu(trayIconMenu);

#if defined(Q_WS_X11)
    trayIcon->installEventFilter(this);
#endif
}

#if defined(Q_WS_X11)
bool Window::eventFilter(QObject *, QEvent *event)
{
    switch(event->type()) {
    case QEvent::ToolTip:
        if (jitToolTipCheckBox->isChecked()) {
            QString timeString = QTime::currentTime().toString();
            trayIcon->setToolTip(tr("Current Time: %1").arg(timeString));
        }
        break;
    case QEvent::Wheel: {
        QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);
        int delta = wheelEvent->delta() > 0 ? 1 : -1;
        int index = (iconComboBox->currentIndex() + delta) % iconComboBox->count();
        iconComboBox->setCurrentIndex(index);
        break;
    }
    default:
        break;
    }
    return false;
}
#endif
