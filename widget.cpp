#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QStyle>
#include <QTime>
#include <QTimer>
#include <windows.h>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("Stay Awake");

    sysTray = new QSystemTrayIcon(this);
    setAwake();
    sysTray->show();

    connect(sysTray, &QSystemTrayIcon::activated, this, [=](QSystemTrayIcon::ActivationReason reason) {
        if (reason == QSystemTrayIcon::DoubleClick)
            setAwake(!isAwake);
    });

//    QTimer* timer = new QTimer(this);
//    timer->setInterval(1000);
//    connect(timer, &QTimer::timeout, this, [=]() {
//        runSec++;
//        ui->label->setText(QString("%1 m %2 s").arg(runSec / 60).arg(runSec % 60));
//    });
//    timer->start();

    sysTray->showMessage("Caffeine", "Stay Awake ing\nDBClick sysTray to switch");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setAwake(bool awake)
{
    if (isAwake = awake)
        SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_AWAYMODE_REQUIRED); //stay awake
    else
        SetThreadExecutionState(ES_CONTINUOUS);
    if (sysTray) {
        //sysTray->setIcon(style()->standardIcon(isAwake ? QStyle::SP_FileDialogDetailedView : QStyle::SP_FileDialogListView));
        sysTray->setIcon(QIcon(isAwake ? ":/images/Sunny.ico" : ":/images/Night.ico"));
        sysTray->setToolTip(isAwake ? "Awake" : "Normal");
    }
    qDebug() << (isAwake ? "awake" : "normal");
}
