//
// Created by linux on 17-5-8.
//

#include <QtGui/QPainter>
#include <QtCore/QStorageInfo>
#include "homeWidget.h"
#include "../base/fileUtil.h"
#include <QDebug>
#include <QtCore/QDirIterator>

homeWidget::homeWidget(QWidget *parent) :
        QWidget(parent) {
    this->setFixedSize(240, 240);
    homeSize = new DCircleProgress(this);
    homeSize->setGeometry(calcPoint(240), calcPoint(240), 240, 240);
    homeSize->setLineWidth(5);
    homeSize->setBackgroundColor(QColor(150, 150, 150));
    homeSize->setStyleSheet("color:white");
    homeSize->setValue(0);

    homeWidgetThread *thread1=new homeWidgetThread();
    connect(thread1,&homeWidgetThread::updata,this,&homeWidget::updata);
    thread1->start();
}

int homeWidget::calcPoint(int size) {
    return (120 - (size / 2));
}

void homeWidget::updata(int value,QString text) {
    homeSize->setValue(value);
    homeSize->setText(text);
}

void homeWidgetThread::run() {

    QStorageInfo home("/home");
    qint64 size=0;
    qint64 yiYongSize;
    if(home.isValid()){

        yiYongSize = home.bytesTotal() - home.bytesFree();
        size = ((float) yiYongSize / home.bytesTotal()) * 100;
    }else{
        QStorageInfo root("/");
        size = getDirSize("/home");
        yiYongSize= root.bytesTotal() - root.bytesFree();
    }
    emit updata(size,QString("%1/%2 GB\n已用/总共").arg(yiYongSize / 1024 / 1024 / 1024).arg(
            home.bytesTotal() / 1024 / 1024 / 1024));
}
