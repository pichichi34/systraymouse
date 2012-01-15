#include <QtGui>

#include "mainwindow.h"

//! [0]
MainWindow::MainWindow()
{
    createGroupBox();
    createActions();
    createTrayIcon();
    setIcon();
    connect(showIconCheckBox, SIGNAL(toggled(bool)),trayIcon, SLOT(setVisible(bool)));
    connect(programDeviceButton, SIGNAL(clicked()), this, SLOT(programDevice()));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(groupBox);

    setLayout(mainLayout);


    trayIcon->show();

    setWindowTitle(tr("Systraymouse"));
    setFixedSize(300,200);
}
//! [0]

//! [1]
void MainWindow::setVisible(bool visible)
{
    minimizeAction->setEnabled(visible);
    maximizeAction->setEnabled(!isMaximized());
    restoreAction->setEnabled(isMaximized() || !visible);
    QDialog::setVisible(visible);
}
//! [1]

//! [2]
void MainWindow::closeEvent(QCloseEvent *event)
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
void MainWindow::setIcon()
{
    QIcon icon(":/images/Computer_mouse.svg");
    trayIcon->setIcon(icon);
    setWindowIcon(icon);

    trayIcon->setToolTip("mouse");
}
//! [3]

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
        //showMessage();
        break;
    default:
        ;
    }
}
//! [5]
void MainWindow::programDevice()
{

}
//! [5]




void MainWindow::createGroupBox()
{
    groupBox = new QGroupBox(tr("Mouse performence"));

    QHBoxLayout *layout = new QHBoxLayout;

    QVBoxLayout *sensLayout = new QVBoxLayout;
    QLabel *sensLabel = new QLabel("sensivity");
    QSlider *sensSlider= new QSlider();
    sensLayout->addWidget(sensLabel);
    sensLayout->addWidget(sensSlider);
    layout->addLayout(sensLayout);

    QVBoxLayout *delayLayout = new QVBoxLayout;
    QLabel *delayLabel = new QLabel("delay");
    QSlider *delaySlider= new QSlider();
    delayLayout->addWidget(delayLabel);
    delayLayout->addWidget(delaySlider);
    layout->addLayout(delayLayout);

    QVBoxLayout *otherLayout = new QVBoxLayout;
    showIconCheckBox = new QCheckBox(tr("Show icon"));
    showIconCheckBox->setChecked(true);
    programDeviceButton= new QPushButton("&Go");
    otherLayout->addWidget(showIconCheckBox);
    otherLayout->addWidget(programDeviceButton);
    layout->addLayout(otherLayout);

    groupBox->setLayout(layout);

}


void MainWindow::createActions()
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

void MainWindow::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);


}

