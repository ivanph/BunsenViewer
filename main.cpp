#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include "wmain.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    WMain wMain;
    wMain.setOrientation(WMain::ScreenOrientationAuto);
    wMain.show();

    return app.exec();

    /*QScopedPointer<QApplication> app(createApplication(argc, argv));
    QScopedPointer<QmlApplicationViewer> viewer(QmlApplicationViewer::create());

    viewer->setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer->setMainQmlFile(QLatin1String("qml/bunsenviewer/main.qml"));
    viewer->showExpanded();

    return app->exec();*/
}
