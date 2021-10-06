#ifndef HAMSTERCLIENT_H
#define HAMSTERCLIENT_H

#include <QObject>
#include <string>

#include "httpclient.h"

using namespace std;

class HamsterClient : public QObject
{
    Q_OBJECT
public:
    HamsterClient(HttpClient *);
    void start(void);
    void goToCorn(void);

private slots:
    void nextStep(QString);

private:
    HttpClient *http;
    int step = 0;
    int pos_x = 0;
    int poy_y = 0;
    int corn = 0;
    int current_rotation = 3;
    string colour = "";

    void set_rotation(int number_turns);

    void walk(int end_rotation);
};

#endif // HAMSTERCLIENT_H
