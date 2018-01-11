#include "showpage.h"
#include "myserialport.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MySerialPort::getobject()->openSerial();

    ShowPage s;
    s.show();
    return a.exec();
}
