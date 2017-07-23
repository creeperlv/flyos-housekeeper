//
// Created by linux on 17-3-24.
//

#include "getInfo.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

getInfo::getInfo() {

}

void getInfo::run() {
    while (true) {
        QFile meminfo("/proc/meminfo");
        if (meminfo.open(QIODevice::ReadOnly)) {
            QTextStream in(&meminfo);
            QString tmp;
            QList<long> list;
            while ((tmp = in.readLine()) != NULL) {
                QStringList info;
                tmp = tmp.simplified();
                info = tmp.split(":");
                info[1] = info[1].split("kB")[0];
                if (info[0] == "MemTotal") {
                    list << info[1].toLong();
                } else if (info[0] == "MemAvailable") {
                    list << info[1].toLong();
                }
            }
            emit setMemSize(list[0], list[0] - list[1]);
            meminfo.close();
        }
        QFile netdev("/proc/net/dev");
        if (netdev.open(QIODevice::ReadOnly)) {
            QTextStream in(&netdev);
            QString tmp;
            QList<long> list;
            in.readLine();
            in.readLine();
            long tmp1 = 0;
            long tmp2 = 0;
            while ((tmp = in.readLine()) != NULL) {
                QStringList list = tmp.split(":");
                list[0]= list[0].trimmed();
                if (list[0] != "lo") {
                    QTextStream text(&list[1]);
                    long tmp3;
                    text >> tmp3;
                    tmp1+=tmp3;
                    text >> tmp3;
                    text >> tmp3;
                    text >> tmp3;
                    text >> tmp3;
                    text >> tmp3;
                    text >> tmp3;
                    text >> tmp3;
                    text >> tmp3;
                    tmp2+=tmp3;
                }

            }
            emit setDownload(tmp1 - lastDownloadData);
            emit setUpload(tmp2 - lastUploadData);
            lastDownloadData =tmp1;
            lastUploadData =tmp2;

        }

        sleep(1);
    }
}

