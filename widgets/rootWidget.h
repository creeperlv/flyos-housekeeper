//
// Created by linux on 17-5-8.
//

#ifndef FLYOS_HOUSEKEEPER_ROOTWIDGET_H
#define FLYOS_HOUSEKEEPER_ROOTWIDGET_H


#include <QtWidgets/QWidget>
#include <dcircleprogress.h>
#include <QThread>

DWIDGET_USE_NAMESPACE

class rootWidget : public QWidget{
Q_OBJECT
public:
    rootWidget(QWidget *parent=0);

public slots:
    void updata(int etc,int lib,int opt,int usr,int var);

private:
    int calcPoint(int size);

    DCircleProgress *etcSize;
    DCircleProgress *libSize;
    DCircleProgress *optSize;
    DCircleProgress *usrSize;
    DCircleProgress *varSize;

protected:
    virtual void paintEvent(QPaintEvent *event);

};

class rootWidgetThread :public QThread{
Q_OBJECT
public:
    void run() Q_DECL_OVERRIDE ;

signals:
    void updata(int etc,int lib,int opt,int usr,int var);

};


#endif //FLYOS_HOUSEKEEPER_ROOTWIDGET_H
