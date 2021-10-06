#ifndef HAMSTERCLIENT_H
#define HAMSTERCLIENT_H

#include <QObject>

#include "httpclient.h"

class HamsterClient : public QObject
{
    Q_OBJECT
public:
    HamsterClient(HttpClient *);
    void start();

private slots:
    void nextStep(QString);

private:
    HttpClient *http;
    int step = 0;
};

#endif // HAMSTERCLIENT_H
