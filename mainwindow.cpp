#include <QtGui>
#include "mainwindow.h"

MainWindow::MainWindow()
{
    createGroupBox();
    createActions();
    createTrayIcon();
    setIcon();

    connect(programDeviceButton, SIGNAL(clicked()), this, SLOT(programDevice()));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(groupBox);
    setLayout(mainLayout);
    trayIcon->show();

    setWindowTitle(tr("Systraymouse"));
    setFixedSize(250,200);

    stm32=new Device();
}

void MainWindow::setVisible(bool visible)
{
    minimizeAction->setEnabled(visible);
    //maximizeAction->setEnabled(!isMaximized());
    restoreAction->setEnabled(isMaximized() || !visible);
    QDialog::setVisible(visible);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible()) {
        QMessageBox::information(this, tr("Systraymouse"),
                                 tr("Program zostaje zminimalizowany do  "
                                    "system tray'a. Aby zakończyć program, "
                                    "wybierz <b>Quit</b> z menu kontektowego "
                                    "aplikacji w tray'u."));
        hide();
        event->ignore();
    }
}

void MainWindow::setIcon()
{
    QIcon icon(":/images/Computer_mouse.svg");
    trayIcon->setIcon(icon);
    setWindowIcon(icon);

    trayIcon->setToolTip("Systraymouse");
}


void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:{
        if(!isVisible()){
        showNormal();
        }else
        hide();
        break;
    }
    case QSystemTrayIcon::DoubleClick:
        break;
    case QSystemTrayIcon::MiddleClick:
        break;
    default:
        ;
    }
}

void MainWindow::programDevice()
{

    int sens=sensSlider->value();
    int delay=delaySlider->value();
    stm32->program(sens,delay);
}

void MainWindow::createGroupBox()
{
    groupBox = new QGroupBox(tr("Mouse performence"));

    QHBoxLayout *layout = new QHBoxLayout;

    QVBoxLayout *sensLayout = new QVBoxLayout;
    QLabel *sensLabel = new QLabel("sensivity");
    sensSlider= new QSlider();
    sensLayout->addWidget(sensLabel);
    sensLayout->addWidget(sensSlider);
    layout->addLayout(sensLayout);

    QVBoxLayout *delayLayout = new QVBoxLayout;
    QLabel *delayLabel = new QLabel("delay");
    delaySlider= new QSlider();
    delayLayout->addWidget(delayLabel);
    delayLayout->addWidget(delaySlider);
    layout->addLayout(delayLayout);

    QVBoxLayout *otherLayout = new QVBoxLayout;
    programDeviceButton= new QPushButton("&Go");

    otherLayout->addWidget(programDeviceButton);
    layout->addLayout(otherLayout);

    groupBox->setLayout(layout);
}

void MainWindow::createActions()
{
    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
}

