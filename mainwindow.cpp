#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPalette>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : /*QMainWindow(parent),*/ ui(new Ui::MainWindowClass)
{
    //ui->setupUi(this);
    desktop = QApplication::desktop();

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
    infoR->setText(QString("FW: %1\nIP: %2").arg("Unknown").arg("Unknown"));
    //infoR->setFrameStyle(QFrame::Box);


    QHBoxLayout *lay_bottom = new QHBoxLayout;
    lay_bottom->insertWidget(0, infoL, 0, Qt::AlignLeft);
    lay_bottom->insertWidget(1, infoC, 0, Qt::AlignHCenter);
    lay_bottom->insertWidget(2, infoR, 0, Qt::AlignRight);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addStretch(1);
    layout->addLayout(lay_bottom, 0);

    setLayout(layout);
    setWindowFlags(Qt::SplashScreen);
}

MainWindow::~MainWindow()
{
    delete ui;
}
