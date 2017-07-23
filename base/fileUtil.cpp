//
// Created by linux on 17-3-31.
//

#include "fileUtil.h"
#include <QDebug>
#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>

QString ReadFile(const QString& path) {
    QFile file(path);
    if (file.exists()) {
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "ReadFile() failed to open" << path;
            return "";
        }
        QTextStream text_stream(&file);
        QString str = text_stream.readAll();
        file.close();
        return str;
    } else {
        qWarning() << "ReadFileContent() file not found: " << path;
        return "";
    }
}

qint64 getDirSize(QString dir) {
    qint64 total = 0;
    QFileInfo targetInfo(dir);
    if (targetInfo.exists()){
        if (targetInfo.isDir()){
            QDir d(dir);
            QFileInfoList entryInfoList = d.entryInfoList(QDir::AllEntries | QDir::System
                                                          | QDir::NoDotAndDotDot | QDir::NoSymLinks
                                                          | QDir::Hidden);
                    foreach (QFileInfo file, entryInfoList) {
                    if (file.isFile()){
                        total += file.size();
                    }
                    else {
                        QDirIterator it(file.absoluteFilePath(), QDir::AllEntries | QDir::System
                                                                 | QDir::NoDotAndDotDot | QDir::NoSymLinks
                                                                 | QDir::Hidden, QDirIterator::Subdirectories);
                        while (it.hasNext()) {
                            it.next();
                            total += it.fileInfo().size();
                        }
                    }
                }
        }else{
            total += targetInfo.size();
        }
    }
    return total;
}