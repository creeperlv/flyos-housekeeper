//
// Created by linux on 17-3-24.
//

#ifndef FLYOS_HOUSEKEEPER_SUSPENSIONWIDGET_H
#define FLYOS_HOUSEKEEPER_SUSPENSIONWIDGET_H

#include <dwidget.h>
#include <QWidget>
#include <QtWidgets>
#include <DBlurEffectWidget>
#include <dcircleprogress.h>
#include <ddialog.h>

DWIDGET_USE_NAMESPACE

class SuspensionWidget : public DBlurEffectWidget{
Q_OBJECT
protected:
    virtual void enterEvent(QEvent *event);

    virtual void leaveEvent(QEvent *event);

    virtual void mouseDoubleClickEvent(QMouseEvent *event);

    virtual void mouseMoveEvent(QMouseEvent *event);

    virtual void mousePressEvent(QMouseEvent *event);

    virtual void mouseReleaseEvent(QMouseEvent *event);

    virtual void moveEvent(QMoveEvent *event);

private:

private:
public:
    SuspensionWidget(QWidget *parent=0);
    virtual ~SuspensionWidget();

private:
//    DBlurEffectWidget *blurtWidget;
    DCircleProgress *memorySize;
    QLabel *download;
    QLabel *upload;

    QPoint oldPoint;
public slots:
    void setMemSize(long Total,long Available);
    void setDownload(long downloadData);
    void setUpload(long uploadData);

};


#endif //FLYOS_HOUSEKEEPER_SUSPENSIONWIDGET_H
