//
// Created by linux on 17-5-6.
//

#include <QtWidgets/QVBoxLayout>
#include "imageItem.h"
#include "../base/fileUtil.h"

imageItem::imageItem(QWidget *parent,  QString titleText,QString logoPath) :
        QPushButton(parent){
    this->setFixedSize(120, 120);

    QVBoxLayout *layout = new QVBoxLayout(this);

    logo = new QLabel(this);
    logo->setFixedSize(80, 80);
    if (!logoPath.isEmpty()){
        logo->setPixmap(QPixmap(logoPath).scaled(80,80,Qt::KeepAspectRatioByExpanding));
        logo->setAlignment(Qt::AlignCenter);
    }

    title = new QLabel(titleText, this);
    title->setStyleSheet("color:white");

    layout->addStretch();
    layout->addWidget(logo, 0, Qt::AlignCenter);
    layout->addSpacing(10);
    layout->addWidget(title, 0, Qt::AlignCenter);
    layout->addStretch();

    this->setStyleSheet(ReadFile(":/styles/imageItem.css"));
}