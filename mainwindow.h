#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSystemTrayIcon>
#include <QDialog>

QT_BEGIN_NAMESPACE
class QAction;
class QCheckBox;
class QComboBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QPushButton;
class QSpinBox;
class QTextEdit;
QT_END_NAMESPACE

//! [0]
class Window : public QDialog
{
    Q_OBJECT

public:
    Window();

    void setVisible(bool visible);

protected:
    void closeEvent(QCloseEvent *event);
#if defined(Q_WS_X11)
    bool eventFilter(QObject *object, QEvent *event);
#endif

private slots:
    void setIcon(int index);
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void showMessage();
    void messageClicked();

private:
    void createIconGroupBox();
    void createMessageGroupBox();
    void createActions();
    void createTrayIcon();

#if defined(Q_WS_X11)
    QCheckBox *jitToolTipCheckBox;
#endif

    QGroupBox *messageGroupBox;
    QLabel *delayLabel;
    QLabel *sensitivityLabel;
    QPushButton *programDeviceButton;

    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
};
//! [0]

#endif
