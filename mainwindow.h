#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QDesktopWidget>
#include <QWidget>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QSplashScreen>
#include <QLabel>
#include <QtNetwork/QTcpSocket>

#include "msgd.h"


namespace Ui
{
    class MainWindowClass;
}

class MainWindow : public QSplashScreen
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void readMsgD();
    void displayMsgDErr(QAbstractSocket::SocketError socketError);

private:
    Ui::MainWindowClass *ui;

    QGraphicsScene *scene;
    QGraphicsView *view;
    QDesktopWidget *desktop;
    QSplashScreen *splash_screen;
    QLabel *infoL;
    QLabel *infoC;
    QLabel *infoR;

    void updateInfoR();

    struct static_info sInfo;
    struct runtime_info rInfo;

    unsigned int info_data_len;
    struct info_hdr hdr;

    QTcpSocket *tcpSocket;
    void StartMsgDConnection();
    void dbgMsg(const QString&);
    void Connect2MsgD();
};

#endif // MAINWINDOW_H
