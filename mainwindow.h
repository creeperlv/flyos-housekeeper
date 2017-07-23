//
// Created by linux on 17-3-23.
//

#ifndef FLYOS_HOUSEKEEPER_MAINWINDOW_H
#define FLYOS_HOUSEKEEPER_MAINWINDOW_H

#include <DMainWindow>
#include <DBlurEffectWidget>
#include <QtWidgets>
#include "SuspensionWidget.h"

DWIDGET_USE_NAMESPACE

class mainwindow: public DMainWindow {
Q_OBJECT
public:
    mainwindow(QWidget *parent = 0);

private:
    DBlurEffectWidget *blurtWidget;
    QVBoxLayout *layout;
    QLabel *upTime;

    SuspensionWidget *suspensionWidget;

    QString configPath;
    QSettings *config;

private slots:
    void onItemClick(int id);

protected:
    void resizeEvent(QResizeEvent *event) override;

    virtual void paintEvent(QPaintEvent *event);

    virtual void timerEvent(QTimerEvent *event);
};


#endif //FLYOS_HOUSEKEEPER_MAINWINDOW_H
