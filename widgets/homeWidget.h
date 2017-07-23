//
// Created by linux on 17-5-8.
//

#ifndef FLYOS_HOUSEKEEPER_HOMEWIDGET_H
#define FLYOS_HOUSEKEEPER_HOMEWIDGET_H


#include <QtWidgets/QWidget>
#include <dcircleprogress.h>
#include <QThread>

DWIDGET_USE_NAMESPACE

class homeWidget : public QWidget{
Q_OBJECT
public:
    homeWidget(QWidget *parent=0);

public slots:
    void updata(int value,QString text);

private:
    int calcPoint(int size);

    DCircleProgress *homeSize;


};

class homeWidgetThread :public QThread{
Q_OBJECT
public:
    void run() Q_DECL_OVERRIDE ;

signals:
    void updata(int value,QString text);

};


#endif //FLYOS_HOUSEKEEPER_HOMEWIDGET_H
