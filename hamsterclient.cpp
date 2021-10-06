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
    step++;
    http->post("http://turing.iem.thm.de/chatJava/sendTxt.php", params);
}

void HamsterClient::set_rotation(int end_rotation){
    int rotation = this->current_rotation;
    int i = this->current_rotation;
    while(i != end_rotation){
        //HTTP-Anfrage hier rein für 90° Drehung anzeigen
        if(rotation < 3){
            rotation++;
        }
        else{
            rotation = 0;
        }
        i++;
    }
    this->current_rotation = rotation;
}

void HamsterClient::walk(int end_rotation){
    set_rotation(end_rotation);
    //HTTP Aanfrage einfügen für grade aus laufen
}

void HamsterClient::goToCorn(){
    string Laufstring = "rrruu";
    int länge = Laufstring.length();

    for( int i = 0; i < länge; i++){
        char zeichen = ((char)Laufstring[i]);
        switch(zeichen){
            case 'r': walk(1);
                break;
            case 'u': walk(2);
                break;
            case 'l': walk(3);
                break;
            case 'o': walk(0);
                break;
        }
    }
    corn++;
}
