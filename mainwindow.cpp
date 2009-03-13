#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPalette>
#include <QVBoxLayout>
#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent)
    : /*QMainWindow(parent),*/ ui(new Ui::MainWindowClass)
{
    //ui->setupUi(this);
    desktop = QApplication::desktop();

    /* Init info data */
    strcpy((char*)sInfo.FW, "Beta 4.0");
    strcpy((char*)sInfo.IP, "Unknown");

    /* Connect to MsgD */
    StartMsgDConnection();

    QPixmap bg(":/jpg/background.jpg");
    setPixmap(bg);

    /* Hide cursor */
    //setCursor(QCursor(Qt::BlankCursor));
    //qApp->setOverrideCursor(QCursor(Qt::IBeamCursor));
    QCursor c;
    c.setPos(width(), height());
    setCursor(c);

    /* Set QPalette */
    QPalette p(palette());
    p.setColor(QPalette::WindowText, QColor(QString("white")));
    //p.setColor(QPalette::Window, QColor(QString("gray")));
    setPalette(p);

    /* change font size */
    QFont f(font());
    f.setPointSize(8);
    setFont(f);

    /* Layout widgets */
    infoL = new QLabel(this);
    infoL->setAlignment(Qt::AlignBottom);
    infoL->setText(QString("Initial...\n.."));
    //infoL->setFrameStyle(QFrame::Box);

    infoC = new QLabel(this);
    infoC->setAlignment(Qt::AlignBottom);
    infoC->clear();
    //infoC->setText(QString("Center Line 1\nCenter Line2"));
    //infoC->setFrameStyle(QFrame::Box);

    infoR = new QLabel(this);
    infoR->setAlignment(Qt::AlignBottom);
    infoR->setText(QString("FW: %1\nIP: %2").arg((char*)sInfo.FW).arg((char*)sInfo.IP));
    //infoR->setFrameStyle(QFrame::Box);


    QHBoxLayout *lay_bottom = new QHBoxLayout;
    lay_bottom->insertWidget(0, infoL, 0, Qt::AlignLeft);
    lay_bottom->insertWidget(1, infoC, 0, Qt::AlignHCenter);
    lay_bottom->insertWidget(2, infoR, 0, Qt::AlignRight);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addStretch(1);
    layout->addLayout(lay_bottom, 0);

    setLayout(layout);
    /* Set flags as splashscreen style */
    setWindowFlags(Qt::SplashScreen);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateInfoR()
{
    infoR->setText(QString("FW: %1\nIP: %2").arg((char*)sInfo.FW).arg((char*)sInfo.IP));
}

void MainWindow::dbgMsg(const QString &s)
{
    showMessage(s, Qt::AlignHCenter | Qt::AlignTop, QColor(Qt::red));
}

void MainWindow::Connect2MsgD()
{
    hdr.data_len = 0;
    tcpSocket->abort();


    tcpSocket->connectToHost(QString(MSGD_IP), MSGD_FE_PORT);
    /* Any errors will be fired through tcpSocket signal */

}

void MainWindow::displayMsgDErr(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        dbgMsg(QString("MsgD disconnected"));
        break;
    case QAbstractSocket::HostNotFoundError:
        dbgMsg(QString("The host was not found. Please check the \n"
                       "host name and port settings.\n"));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        dbgMsg(QString("The connection was refused by the peer. \n"
                       "Make sure the MsgD is running, \n"
                       "and check that the host name and port \n"
                       "settings are correct.\n"));
        break;
    default:
        dbgMsg(QString("The following error occurred: \n%1.")
                                 .arg(tcpSocket->errorString()));
    }

    /* BruceToDo */
}

void MainWindow::StartMsgDConnection()
{
    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readMsgD()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayMsgDErr(QAbstractSocket::SocketError)));

    Connect2MsgD();
}

void MainWindow::readMsgD()
{
    qint64 r = 0;

    QHostAddress addr = tcpSocket->localAddress();
    if ( ! (addr == QHostAddress::Null) ) {
        strcpy((char*)sInfo.IP,
               addr.toString().toAscii().data());

        updateInfoR();
    }


    if (hdr.data_len == 0) {

        if (tcpSocket->bytesAvailable() < (int)sizeof(struct info_hdr))
            return;

        r = tcpSocket->read((char*)&hdr, sizeof(struct info_hdr));
        if (r <= 0) {
            dbgMsg(tr("something wrong"));
            //BruceToDo.
            return;
        }

        if (hdr.type != INFOTYPE_RT && hdr.type != INFOTYPE_ST) {
            dbgMsg(tr("wrong type"));
            //BruceToDo.
        }
    }

    if (tcpSocket->bytesAvailable() < hdr.data_len)
        return;

    switch (hdr.type) {
    case INFOTYPE_RT:
        {
            QByteArray d(hdr.data_len, '\0');
            r = tcpSocket->read(d.data(), hdr.data_len);
            dbgMsg(QString(d.constData()));
        }
        break;
    case INFOTYPE_ST:
        r = tcpSocket->read((char*)&sInfo, hdr.data_len);
        dbgMsg(QString((char*)&sInfo));
        break;
    default:
        dbgMsg(tr("wrong type?!"));
    }

    if (r <= 0) {
        dbgMsg(tr("something wrong"));
        return;
    }


}




