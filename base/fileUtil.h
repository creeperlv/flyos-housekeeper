//
// Created by linux on 17-3-31.
//

#ifndef FLYOS_INSTALL_FILEUTIL_H
#define FLYOS_INSTALL_FILEUTIL_H

#include <QString>
#include <QFile>
#include <QTextStream>

QString ReadFile(const QString& path);
qint64 getDirSize(QString dir);
#endif //FLYOS_INSTALL_FILEUTIL_H
