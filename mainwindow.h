#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSystemTrayIcon>
#include <QDialog>

QT_BEGIN_NAMESPACE
class QAction;
class QCheckBox;
class QGroupBox;
class QLabel;
class QMenu;
class QPushButton;
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

    QGroupBox *groupBox;
    QLabel *delayLabel;
    QLabel *sensitivityLabel;
    QPushButton *programDeviceButton;
    QCheckBox *showIconCheckBox;
    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
};
//! [0]

#endif
