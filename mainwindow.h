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

struct info_hdr {
    unsigned int type;
    unsigned int data_len;
    unsigned char data[];
};

struct static_info {
    unsigned char IP[16];
    unsigned char FW[16];
};

struct runtime_info {
    unsigned int type;
    unsigned int str_len;
    unsigned char str[];
};

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

private:
    Ui::MainWindowClass *ui;

    QGraphicsScene *scene;
    QGraphicsView *view;
    QDesktopWidget *desktop;
    QSplashScreen *splash_screen;
    QLabel *infoL;
    QLabel *infoC;
    QLabel *infoR;

    struct static_info sInfo;
    struct runtime_info rInfo;
};

#endif // MAINWINDOW_H
