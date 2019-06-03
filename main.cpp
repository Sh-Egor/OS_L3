#include "touristbookmainwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TouristBookMainWindow w;

    //обрабытываем случай смены фокуса
    QObject::connect(&a, SIGNAL(focusChanged(QWidget*,QWidget*)), &w, SLOT(focusChanged(QWidget*,QWidget*)));

    w.show();

    return a.exec();
}
