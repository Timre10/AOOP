#include <QCoreApplication>
#include <iostream>

using namespace std;

#include "hamsterclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    HttpClient http;
    HamsterClient client(&http);
    client.start();

    return a.exec();
}
