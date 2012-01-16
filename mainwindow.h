#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSystemTrayIcon>
#include <QDialog>

#include <device.h>

QT_BEGIN_NAMESPACE
class QAction;
class QCheckBox;
class QGroupBox;
class QLabel;
class QMenu;
class QPushButton;
class QSlider;
QT_END_NAMESPACE

//! [0]
class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow();

    void setVisible(bool visible);

protected:
    void closeEvent(QCloseEvent *event);
    void setIcon();

private slots:
    void programDevice();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
private:
    void createGroupBox();
    void createActions();
    void createTrayIcon();

#if defined(Q_WS_X11)
    QCheckBox *jitToolTipCheckBox;
#endif
    QSlider *sensSlider;
    QSlider *delaySlider;
    QGroupBox *groupBox;
    QLabel *delayLabel;
    QLabel *sensitivityLabel;
    QPushButton *programDeviceButton;
    QCheckBox *showIconCheckBox;
    QAction *minimizeAction;
    //QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    Device* stm32;
};
//! [0]

#endif
