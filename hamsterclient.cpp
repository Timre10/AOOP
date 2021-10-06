#include <iostream>
using namespace std;

#include "hamsterclient.h"

HamsterClient::HamsterClient(HttpClient *http) : http(http) {}

void HamsterClient::start()
{
    connect(http, SIGNAL(responseAvailable(QString)), this, SLOT(nextStep(QString)));
    nextStep("start");
}

void HamsterClient::nextStep(QString previousResponse)
{
    cout << previousResponse.toStdString() << endl;
    QMap<QString, QString> params;
    params["fromUser"] = "testA21aoop";
    params["fromPassword"] = "4JNghHj6";
    params["toUser"] = "hamster21aoop";
    params["type"] = "txt";
    if (step == 0) params["txt"] = "init";
    if (step % 5 == 1) params["txt"] = "vor";
    if (step % 5 == 2) params["txt"] = "vor";
    if (step % 5 == 3) params["txt"] = "linksUm";
    if (step % 5 == 4) params["txt"] = "linksUm";
    if (step % 5 == 0 && step != 0) params["txt"] = "linksUm";
    cout << "Test " << endl;
    step++;
    http->post("http://turing.iem.thm.de/chatJava/sendTxt.php", params);
}


