#include <DApplication>
#include <DTitlebar>
#include <dutility.h>

#include "mainwindow.h"


DWIDGET_USE_NAMESPACE

int main(int argc,char **argv){
    DApplication::loadDXcbPlugin();
    DApplication app(argc, argv);

    if (app.setSingleInstance("flyos-housekeeper")) {
        app.loadTranslator();
        app.setOrganizationName("flyos");
        app.setApplicationName("flyos-housekeeper");
        app.setApplicationVersion("0.1");
        app.setOrganizationDomain("fly-os.xyz");
        app.setApplicationDescription(DApplication::translate("MainWindow", "FlyOS管家") + "\n");
        app.setApplicationDisplayName("FlyOS管家");

        app.setTheme("light");

        mainwindow w;
        DTitlebar *titlebar=w.titlebar();
        titlebar->setTitle("FlyOS管家");
        w.setFixedSize(900, 650);
        DUtility::moveToCenter(&w);
        w.show();

        return app.exec();
    }

    return 0;

}