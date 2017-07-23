//
// Created by linux on 17-5-8.
//

#include <QtGui/QPainter>
#include <QtCore/QStorageInfo>
#include "rootWidget.h"
#include "../base/fileUtil.h"
#include <QDebug>
#include <QtCore/QDirIterator>

rootWidget::rootWidget(QWidget *parent) :
        QWidget(parent) {
    this->setFixedSize(260, 260);
    DCircleProgress *rootSize = new DCircleProgress(this);
    rootSize->setGeometry(calcPoint(240), calcPoint(240), 240, 240);
    rootSize->setLineWidth(5);
    rootSize->setBackgroundColor(QColor(150,150,150));
    rootSize->setChunkColor(QColor("#46B322"));
    rootSize->setStyleSheet("color:white");

    etcSize = new DCircleProgress(this);
    etcSize->setGeometry(calcPoint(225), calcPoint(225), 225, 225);
    etcSize->setLineWidth(5);
    etcSize->setBackgroundColor(QColor(150, 150, 150));
    etcSize->setChunkColor(QColor("#CA2BCE"));

    libSize = new DCircleProgress(this);
    libSize->setGeometry(calcPoint(210), calcPoint(210), 210, 210);
    libSize->setLineWidth(5);
    libSize->setBackgroundColor(QColor(150, 150, 150));
    libSize->setChunkColor(QColor("#0099FF"));

    optSize = new DCircleProgress(this);
    optSize->setGeometry(calcPoint(195), calcPoint(195), 195, 195);
    optSize->setLineWidth(5);
    optSize->setBackgroundColor(QColor(150, 150, 150));
    optSize->setChunkColor(QColor("#8754E1"));

    usrSize = new DCircleProgress(this);
    usrSize->setGeometry(calcPoint(180), calcPoint(180), 180, 180);
    usrSize->setLineWidth(5);
    usrSize->setBackgroundColor(QColor(150, 150, 150));
    usrSize->setChunkColor(QColor("#FF0000"));

    varSize = new DCircleProgress(this);
    varSize->setGeometry(calcPoint(165), calcPoint(165), 165, 165);
    varSize->setLineWidth(5);
    varSize->setBackgroundColor(QColor(150, 150, 150));
    varSize->setChunkColor(QColor("#ECDE4A"));

    QLabel *rootLabel = new QLabel("·/", this);
    QLabel *etcLabel = new QLabel("·/etc", this);
    QLabel *libLabel = new QLabel("·/lib", this);
    QLabel *optLabel = new QLabel("·/opt", this);
    QLabel *usrLabel = new QLabel("·/usr", this);
    QLabel *varLabel = new QLabel("·/var", this);

    rootLabel->setStyleSheet("color:#46B322");
    etcLabel->setStyleSheet("color:#CA2BCE");
    libLabel->setStyleSheet("color:#0099FF");
    optLabel->setStyleSheet("color:#8754E1");
    usrLabel->setStyleSheet("color:#FF0000");
    varLabel->setStyleSheet("color:#ECDE4A");

    rootLabel->move(230, 170);
    etcLabel->move(230, 185);
    libLabel->move(230, 200);
    optLabel->move(230, 215);
    usrLabel->move(230, 230);
    varLabel->move(230, 245);

    etcSize->setValue(0);
    libSize->setValue(0);
    optSize->setValue(0);
    usrSize->setValue(0);
    varSize->setValue(0);

    QStorageInfo root("/");
    qint64 yiYongSize = root.bytesTotal() - root.bytesFree();
    int size = ((float) yiYongSize / root.bytesTotal()) * 100;
    rootSize->setValue(size);
    rootSize->setText(QString("%1/%2 GB\n已用/总共").arg(yiYongSize / 1024 / 1024 / 1024).arg(
            root.bytesTotal() / 1024 / 1024 / 1024));

    rootWidgetThread *thread1 = new rootWidgetThread();
    connect(thread1, &rootWidgetThread::updata, this, &rootWidget::updata);
    thread1->start();
}

int rootWidget::calcPoint(int size) {
    return (120 - (size / 2));
}


void rootWidget::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
//    QPainter *painter = new QPainter(this);
//    QPen pen(QColor(QColor(200,200,200)));
//    pen.setWidth(10);
//    painter->setPen(pen);
//    painter->drawEllipse(50, 50, 300-100, 300-100);
//    painter->drawEllipse(60, 60, 300-120, 300-120);
//    painter->drawEllipse(70, 70, 300-140, 300-140);
//    pen.setColor(QColor(80, 100, 150));
//    painter->setPen(pen);
//    painter->drawArc(QRectF(50, 50, 300-100, 300-100), 90 *16 , -75 * 16);
//    painter->drawArc(QRectF(60, 60, 300-120, 300-120), 90 *16 , -45* 16);
//    painter->drawArc(QRectF(70, 70, 300-140, 300-140), 90 *16 , -10 *16);



}
void rootWidget::updata(int etc, int lib, int opt, int usr, int var) {
    etcSize->setValue(etc);
    libSize->setValue(lib);
    optSize->setValue(opt);
    usrSize->setValue(usr);
    varSize->setValue(var);
}

void rootWidgetThread::run() {
    QStorageInfo root("/");
    int etcSize = ((float) getDirSize("/etc") / root.bytesTotal()) * 100;

    int libSize = ((float)  getDirSize("/lib") / root.bytesTotal()) * 100;

    int optSize = ((float) getDirSize("/opt") / root.bytesTotal()) * 100;

    int usrSize = ((float) getDirSize("/usr") / root.bytesTotal()) * 100;

    int varSize = ((float) getDirSize("/var") / root.bytesTotal()) * 100;

    emit updata(etcSize, libSize, optSize, usrSize, varSize);

}

