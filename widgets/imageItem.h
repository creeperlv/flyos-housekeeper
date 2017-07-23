//
// Created by linux on 17-5-6.
//

#ifndef FLYOS_HOUSEKEEPER_IMAGEITEM_H
#define FLYOS_HOUSEKEEPER_IMAGEITEM_H


#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

class imageItem : public QPushButton{

public:
    imageItem(QWidget *parent=0,QString titleText="",QString logoPath="");

private:
    QLabel *logo;
    QLabel *title;


};


#endif //FLYOS_HOUSEKEEPER_IMAGEITEM_H
