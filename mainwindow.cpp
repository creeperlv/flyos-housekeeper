//
// Created by linux on 17-3-23.
//

#include <dwindowoptionbutton.h>
#include <dswitchbutton.h>
#include "mainwindow.h"
#include "SuspensionWidget.h"
#include "widgets/imageItem.h"
#include "widgets/rootWidget.h"
#include "widgets/homeWidget.h"
#include <DTitlebar>

mainwindow::mainwindow(QWidget *parent) :
        DMainWindow(parent) {

    configPath = QStandardPaths::standardLocations(QStandardPaths::ConfigLocation).first();
    configPath = configPath
                 + "/" + QApplication::organizationName()
                 + "/" + QApplication::applicationName()
                 + "/" + QApplication::applicationName() + ".conf";
    config = new QSettings(configPath, QSettings::IniFormat);

    if (this->titlebar()) {
        QMenu *menu = new QMenu(this);
        QAction *setting;
        if (config->value("Suspension/enable", true).toBool())
            setting = new QAction("关闭悬浮球", this);
        else
            setting = new QAction("开启悬浮球", this);

        connect(setting, &QAction::triggered, this, [=] {

            if (setting->text().contains("关闭悬浮球")) {

                setting->setText("开启悬浮球");
                config->setValue("Suspension/enable", false);
                suspensionWidget->close();
            } else {
                setting->setText("关闭悬浮球");
                config->setValue("Suspension/enable", true);
                    QRect rect = QApplication::desktop()->geometry();
                    suspensionWidget = new SuspensionWidget();
                    suspensionWidget->move(config->value("Suspension/xPoint", rect.width() - 58).toInt(),
                                           config->value("Suspension/yPoint", rect.height() - 58).toInt());
                suspensionWidget->show();

            }
        });
        menu->addAction(setting);
        this->titlebar()->setMenu(menu);
    }

    blurtWidget = new DBlurEffectWidget(this);
    blurtWidget->setBlendMode(DBlurEffectWidget::BehindWindowBlend);
    blurtWidget->setMaskColor(Qt::black);
    blurtWidget->move(0, 38);

    rootWidget *rootSize = new rootWidget(this);
    rootSize->move(30, 70);

    QLabel *rootLabel = new QLabel("根分区使用情况", this);
    rootLabel->move(110, 40);
    rootLabel->setStyleSheet("color:white");

    homeWidget *homeSize = new homeWidget(this);
    homeSize->move(30, 370);

    QLabel *homeLabel = new QLabel("主分区使用情况", this);
    homeLabel->move(110, 330);
    homeLabel->setStyleSheet("color:white");

    QLabel *logo = new QLabel(this);
    logo->setPixmap(QPixmap(":/images/logo.png"));
    logo->setGeometry(400, 80, 200, 200);

    QLabel *systemOs = new QLabel("发行版：FlyOS",this);
    systemOs->setStyleSheet("color:white");
    systemOs->move(650, 100);

    QLabel *kernelVersion = new QLabel(this);
    QProcess process;
    process.start("uname", QStringList() << "-r");
    process.waitForFinished(-1);
    kernelVersion->setText(tr("内核版本: %1").arg(tr(process.readAll())));
    kernelVersion->setStyleSheet("color:white");
    kernelVersion->move(650, 130);
    kernelVersion->resize(300, 16);

    upTime = new QLabel(this);
    process.start("/bin/bash", QStringList() << "-c" << "pacman -Qq | wc -l");
    process.waitForFinished(-1);
    upTime->setText(tr("已运行: 0"));
    upTime->setStyleSheet("color:white");
    upTime->setGeometry(650, 160, 500, 16);

    QLabel *packageNum = new QLabel(this);
    process.start("/bin/bash", QStringList() << "-c" << "pacman -Qq | wc -l");
    process.waitForFinished(-1);
    packageNum->setText(tr("软件包数: %1").arg(tr(process.readAll())));
    packageNum->setStyleSheet("color:white");
    packageNum->move(650, 190);

    QFrame *itemFrame = new QFrame(this);
    QGridLayout *itemLayout = new QGridLayout(this);
    itemLayout->setColumnStretch(3, 1);
//    itemLayout->setSpacing(20);
    itemLayout->setHorizontalSpacing(20);
    itemLayout->setVerticalSpacing(20);
    itemFrame->setLayout(itemLayout);
    itemFrame->setStyleSheet("color:transparent");
    itemFrame->setFixedSize(130 * 4, 130 * 2);
    itemFrame->move(350, 320);

    imageItem *packageItem = new imageItem(this, "包管理器", ":/images/flyos-package-manager.png");
    imageItem *partedItem = new imageItem(this, "磁盘管理器", ":/images/backup.png");
    imageItem *systemdItem = new imageItem(this, "systemd管理器", ":/images/environment.png");
    imageItem *lanmpItem = new imageItem(this, "LANMP管理器", ":/images/environment.png");
    imageItem *environmentItem = new imageItem(this, "环境变量管理", ":/images/environment.png");
    imageItem *systemItem = new imageItem(this, "系统监视器", ":/images/deepin-system-monitor.svg");
    imageItem *snapshotSettingItem = new imageItem(this, "快照管理器", ":/images/flyos-snapper-manager.png");
    imageItem *backupSettingItem = new imageItem(this, "系统备份", ":/images/backup.png");

    QButtonGroup *itemGroup = new QButtonGroup(this);
    itemGroup->addButton(packageItem, 0);
    itemGroup->addButton(partedItem, 1);
    itemGroup->addButton(systemdItem, 2);
    itemGroup->addButton(lanmpItem, 3);
    itemGroup->addButton(environmentItem, 4);
    itemGroup->addButton(systemItem, 5);
    itemGroup->addButton(snapshotSettingItem, 6);
    itemGroup->addButton(backupSettingItem, 7);

    itemLayout->addWidget(packageItem);
    itemLayout->addWidget(partedItem);
    itemLayout->addWidget(systemdItem);
    itemLayout->addWidget(lanmpItem);
    itemLayout->addWidget(environmentItem);
    itemLayout->addWidget(systemItem);
    itemLayout->addWidget(snapshotSettingItem);
    itemLayout->addWidget(backupSettingItem);

    if (config->value("Suspension/enable", true).toBool()) {
        QRect rect = QApplication::desktop()->geometry();

        suspensionWidget = new SuspensionWidget();
        suspensionWidget->show();
        suspensionWidget->move(config->value("Suspension/xPoint", rect.width() - 58).toInt(),
                               config->value("Suspension/yPoint", rect.height() - 58).toInt());
    }

    startTimer(1000);

    connect(itemGroup, SIGNAL(buttonClicked(int)), this, SLOT(onItemClick(int)));

}

void mainwindow::timerEvent(QTimerEvent *event) {
    QProcess process;
    process.start("/bin/bash", QStringList() << "-c"
                                             << "cat /proc/uptime| awk -F. '{run_days=$1 / 86400;run_hour=($1 % 86400)/3600;run_minute=($1 % 3600)/60;run_second=$1 % 60;printf(\"系统已运行：%d天%d时%d分%d秒\",run_days,run_hour,run_minute,run_second)}'");
    process.waitForFinished(-1);
    upTime->setText(process.readAll());
}

void mainwindow::paintEvent(QPaintEvent *event) {

}

void mainwindow::resizeEvent(QResizeEvent *event) {
    blurtWidget->resize(event->size());
}

void mainwindow::onItemClick(int id) {
    QProcess q;
    switch (id) {
        case 0:
            qDebug() << "open 包管理器";
            break;
        case 1:
            qDebug() << "open 磁盘管理器";
            break;
        case 2:
            qDebug() << "open systemd管理器";
            break;
        case 3:
            qDebug() << "open LANMP管理器";
            break;
        case 4:
            qDebug() << "open 环境变量管理";
            break;
        case 5:
            qDebug() << "open 系统监视器";
            q.startDetached("deepin-system-monitor");
            break;
        case 6:
            qDebug() << "open 快照管理器";
            break;
        case 7:
            qDebug() << "open 系统备份";
            break;
    }
}
