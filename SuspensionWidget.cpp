//
// Created by linux on 17-3-24.
//

#include "SuspensionWidget.h"
#include "getInfo.h"
#include <QDebug>
#include <zconf.h>

SuspensionWidget::SuspensionWidget(QWidget *parent) :
        DBlurEffectWidget(parent) {
    this->setFixedSize(160, 58);
    QRect rect = QApplication::desktop()->geometry();
//    move(rect.width() - 58, rect.height() - 58);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setMaskColor(Qt::black);
    setBlurRectXRadius(29);
    setBlurRectYRadius(29);

    memorySize = new DCircleProgress(this);
//    memorySize->move(40, 32);
    memorySize->resize(58, 58);
    memorySize->setValue(0);
    memorySize->setStyleSheet("color:white");

    upload = new QLabel(this);
    upload->setMinimumWidth(110);
    upload->move(65, 9);
    upload->setStyleSheet("color:white");

    download = new QLabel(this);
    download->setMinimumWidth(110);
    download->move(65, 31);
    download->setStyleSheet("color:white");

    getInfo *infoThread = new getInfo();
    connect(infoThread, &getInfo::setMemSize, this, &SuspensionWidget::setMemSize);
    connect(infoThread, &getInfo::setDownload, this, &SuspensionWidget::setDownload);
    connect(infoThread, &getInfo::setUpload, this, &SuspensionWidget::setUpload);
    infoThread->start();

}

SuspensionWidget::~SuspensionWidget() {
    auto configPath = QStandardPaths::standardLocations(QStandardPaths::ConfigLocation).first();
    configPath = configPath
                 + "/" + QApplication::organizationName()
                 + "/" + QApplication::applicationName()
                 + "/" + QApplication::applicationName() + ".conf";
    QSettings config(configPath, QSettings::IniFormat);

    config.setValue("Suspension/xPoint", x());
    config.setValue("Suspension/yPoint", y());
}

//bool isMove = false;

void SuspensionWidget::mouseReleaseEvent(QMouseEvent *event) {
    QWidget::mouseReleaseEvent(event);
//    if (isMove = true) {
//        if (event->button() == Qt::LeftButton) {
//            isMove = false;
//            setCursor(Qt::ArrowCursor);
//        }
//
//    }

    setCursor(Qt::PointingHandCursor);
}

void SuspensionWidget::moveEvent(QMoveEvent *event) {
    DBlurEffectWidget::moveEvent(event);
        if (this->x() <= 0) {
            this->setFixedSize(58, 58);
            this->move(0, this->y());
        } else if (this->x() >= QApplication::desktop()->width() - 159) {
            this->setFixedSize(58, 58);
            this->move(QApplication::desktop()->width() - 58, this->y());
        } else {
            this->setFixedSize(160, 58);
        }
}

void SuspensionWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
//        isMove = true;
        oldPoint = event->globalPos() - this->pos();
//        setCursor(Qt::ClosedHandCursor);
        event->accept();
    } else {
        QWidget::mousePressEvent(event);
    }
}

void SuspensionWidget::mouseMoveEvent(QMouseEvent *event) {
//    if (isMove = true) {
        QWidget::mouseMoveEvent(event);
        move(event->globalPos() - oldPoint);
        event->accept();
//    }
}

void SuspensionWidget::mouseDoubleClickEvent(QMouseEvent *event) {
    QProcess::startDetached("gnome-system-monitor");
}

void SuspensionWidget::enterEvent(QEvent *event) {
    QWidget::enterEvent(event);
//    QRect rect=QApplication::desktop()->geometry();
//    if (x() +58 >=rect.width()){
//
//        while (this->width() < 160) {
//
////            qDebug() << x();
//            move(x() - 1, y());
//            resize(width() + 1, height());
//            usleep(1000);
//        }
//        qDebug() <<this-> width();
//    }
}

void SuspensionWidget::leaveEvent(QEvent *event) {
    QWidget::leaveEvent(event);
    QRect rect=QApplication::desktop()->geometry();
//    if (x() +58 >=rect.width()) {
//        while (width() > 58) {
//            move(x() + 1, y());
//            resize(width() - 1, height());
//            usleep(1000);
//        }
//    }
    auto configPath = QStandardPaths::standardLocations(QStandardPaths::ConfigLocation).first();
    configPath = configPath
                 + "/" + QApplication::organizationName()
                 + "/" + QApplication::applicationName()
                 + "/" + QApplication::applicationName() + ".conf";
    QSettings config(configPath, QSettings::IniFormat);

    config.setValue("Suspension/xPoint", x());
    config.setValue("Suspension/yPoint", y());
}


void SuspensionWidget::setMemSize(long Total, long Available) {
    int mem = (float) Available / Total * 100;
    memorySize->setValue(mem);
    QString tmp = QString("%1%").arg(mem);
    memorySize->setText(tmp);
}

void SuspensionWidget::setDownload(long downloadData) {
    char danwei = 'b';
    float tmp;
    if (downloadData >= 1024 * 1024) {
        danwei = 'm';
        tmp = (float) downloadData / 1024 / 1024;
    } else if (downloadData >= 1024) {
        danwei = 'k';
        tmp = (float) downloadData / 1024;
    }
    QString str = QString("⇩：%1 %2/s").arg(tmp, 0, 'f', 2).arg(danwei);
    download->setText(str);
}

void SuspensionWidget::setUpload(long uoloadData) {
    char danwei = 'b';
    float tmp;
    if (uoloadData >= 1024 * 1024) {
        tmp = (float) uoloadData / 1024 / 1024;
        danwei = 'm';
    } else if (uoloadData >= 1024) {
        tmp = (float) uoloadData / 1024;
        danwei = 'k';
    }
    QString str = QString("⇧：%1 %2/s").arg(tmp, 0, 'f', 2).arg(danwei);
    upload->setText(str);
}



