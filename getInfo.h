//
// Created by linux on 17-3-24.
//

#ifndef FLYOS_HOUSEKEEPER_GETINFO_H
#define FLYOS_HOUSEKEEPER_GETINFO_H

#include <QThread>

class getInfo:public QThread {
Q_OBJECT
public:
    getInfo();

    void run() Q_DECL_OVERRIDE ;

private:
    long lastUploadData=0;
    long lastDownloadData=0;
signals:
    void setMemSize(long Total,long Available);
    void setDownload(long downloadData);
    void setUpload(long uploadData);

};


#endif //FLYOS_HOUSEKEEPER_GETINFO_H
