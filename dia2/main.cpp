#include "mainwindow.h"
#include <QApplication>
#include <QSurface>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat format = QSurfaceFormat::defaultFormat();
    format.setMinorVersion(3);
    format.setMajorVersion(3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    format.setRedBufferSize(8);
    format.setGreenBufferSize(8);
    format.setBlueBufferSize(8);
    format.setAlphaBufferSize(8);
    format.setSwapBehavior(QSurfaceFormat::SwapBehavior::DoubleBuffer);
    QSurfaceFormat::setDefaultFormat(format);

    MainWindow w;
    w.show();

    return a.exec();
}