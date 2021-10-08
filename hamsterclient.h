#ifndef HAMSTERCLIENT_H
#define HAMSTERCLIENT_H

#include <QObject>
#include <string>

#include "httpclient.h"

class Map;

using namespace std;

class HamsterClient : public QObject
{
    Q_OBJECT
public:
    HamsterClient(HttpClient *);
    void start();

private slots:
    void hamsterInit(QString);

private:
    HttpClient *http;
    int step = 0;
    int messageID = 0;
    QString farbe = "init";
    int current_rotation = 1;
    int corn = 0;

    void goToCorn(string);
    void walk(int);
    void set_rotation(int);



};

#endif // HAMSTERCLIENT_H
