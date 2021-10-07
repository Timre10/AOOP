#include <iostream>

#include "hamsterclient.h"
#include <string.h>
#include <chrono>
#include <thread>
#include <QSignalSpy>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

HamsterClient::HamsterClient(HttpClient *http) : http(http) {}

void HamsterClient::start()
{
    connect(http, SIGNAL(responseAvailable(QString)), this, SLOT(hamsterInit(QString)));
    hamsterInit("Start");
}

void HamsterClient::hamsterInit(QString previousResponse) {
    char nutzdaten_string[1000];
    int nutzdaten_index;
    int size = previousResponse.size();
    int number_of_rows = 0;
    QChar c = '\n';
    QChar c_prev;
    int character_number_of_http_response = 3;
    QMap<QString, QString> params_messages;
    QMap<QString, QString> params_txt;
    params_messages["user"] = "kgmr29";
    params_messages["password"] = "q3chseNO";
    params_txt["fromUser"] = "kgmr29";
    params_txt["toUser"] = "hamster21aoop";
    params_txt["fromPassword"] = "q3chseNO";
    params_txt["type"] = "txt";
    params_txt["txt"] = "init";

    /* Request message ID */
    if (this->step == 0) {
        /* Send request */
        http->post("http://turing.iem.thm.de/chatJava/messages.php", params_messages);
        this->step++;
        return;
    }
    /* extract and save message ID, request hamster init */
    if (this->step == 1) {
        /* Run through the whole response */
        while (character_number_of_http_response < previousResponse.size() - 1) {
            /* Run through the first 5 parameters of a row */
            for (int i = 0; i < 5; i++) {
                if (i == 0) nutzdaten_index = 0;
                c = '0';
                while (c != '|') {
                    c_prev = previousResponse[character_number_of_http_response];
                    /* Extract the messageID when we are at the first parameter */
                    if (i == 0) {
                        nutzdaten_string[nutzdaten_index] = c_prev.toLatin1();
                        nutzdaten_index++;
                    }
                    character_number_of_http_response++;
                    c = previousResponse[character_number_of_http_response];
                }
                if (i == 0) nutzdaten_string[nutzdaten_index] = '\0';
            }
            /* Run through the 6th parameter of a row */
            while (c != '\n') {
                c_prev = previousResponse[character_number_of_http_response];
                character_number_of_http_response++;
                c = previousResponse[character_number_of_http_response];

                /* We are done with the response here */
                if (character_number_of_http_response == (size - 1))
                    break;
            }
        }

        /* Save messageID */
        this->messageID = atoi(nutzdaten_string);
        /* Send init request */
        http->post("http://turing.iem.thm.de/chatJava/sendTxt.php", params_txt);
        this->step++;
        return;
    } 

    /* Request messages for color and map */
    if (this->step == 2) {
        /* Set request parameter newerThan, using the saved messageID from step==1 */
        params_messages["newerThan"] = QString::number(this->messageID);

        /* Send request */
        http->post("http://turing.iem.thm.de/chatJava/messages.php", params_messages);
        this->step++;
        return;
    }

    /* Extract color and map, save color and map */
    if (this->step == 3) {
        /* Count the number of response rows */
        for (int j = 0; j < size; j++) {
            c = previousResponse[j];
            if (c == '\n') {
                  number_of_rows++;
              }
        }
        /* Resend request if the color and map aren't there yet */
        if (number_of_rows < 3) {
            params_messages["newerThan"] = QString::number(this->messageID);
            http->post("http://turing.iem.thm.de/chatJava/messages.php", params_messages);
            return;
        }
        /* Start extraction */
        else {
            /* Run through the whole response */
            while (character_number_of_http_response < previousResponse.size() - 1) {
                /* Run through the first 5 parameters of a row */
                for (int i = 0; i < 5; i++) {
                    c = '0';
                    while (c != '|') {
                        c_prev = previousResponse[character_number_of_http_response];
                        character_number_of_http_response++;
                        c = previousResponse[character_number_of_http_response];
                    }
                }
                nutzdaten_index = 0;
                /* Run through the 6th parameter of a row */
                while (c != '\n') {
                    c_prev = previousResponse[character_number_of_http_response];
                    character_number_of_http_response++;
                    c = previousResponse[character_number_of_http_response];
                    /* Extract color OR map OR other parameter */
                    nutzdaten_string[nutzdaten_index] = c.toLatin1();
                    if (nutzdaten_string[nutzdaten_index] == '\n') nutzdaten_string[nutzdaten_index] = '\0';
                    nutzdaten_index++;
                    /* We are done with the response here */
                    if (character_number_of_http_response == (size - 1))
                        break;
                }
                nutzdaten_string[nutzdaten_index] = '\0';
                //cout << nutzdaten_string << endl;

                /* Is the parameter the color? */
                if(strncmp(nutzdaten_string, "farbe: ", 6) == 0) {
                    /* Set hamster color and print it in console */
                    this->farbe = nutzdaten_string;
                    cout << nutzdaten_string << endl;
                }
                /* Is the parameter the map? */
                if(strncmp(nutzdaten_string, "territorium: ", 13) == 0) {
                    // todo hier Map initialisieren. Map ist in nutzdaten_string enthalten
                    cout << nutzdaten_string << endl;
                }
            }
        }
        this->step++;
        goToCorn();
    }
}

void HamsterClient::set_rotation(int end_rotation){
    QSignalSpy spy(http, SIGNAL(responseAvailable(QString)));
    QMap<QString, QString> params_txt;
    params_txt["fromUser"] = "kgmr29";
    params_txt["toUser"] = "hamster21aoop";
    params_txt["fromPassword"] = "q3chseNO";
    params_txt["type"] = "txt";
    params_txt["txt"] = "linksUm";
    int rotation = this->current_rotation;
    while(rotation != end_rotation){
        if(rotation < 3){
            rotation++;
        }
        else {
            rotation = 0;
        }
        http->post("http://turing.iem.thm.de/chatJava/sendTxt.php", params_txt);
        spy.wait();
    }
    this->current_rotation = rotation;
}

void HamsterClient::walk(int end_rotation){
    QSignalSpy spy(http, SIGNAL(responseAvailable(QString)));
    QMap<QString, QString> params_txt;
    params_txt["fromUser"] = "kgmr29";
    params_txt["toUser"] = "hamster21aoop";
    params_txt["fromPassword"] = "q3chseNO";
    params_txt["type"] = "txt";
    params_txt["txt"] = "vor";

    /* Send turn request(s) */
    set_rotation(end_rotation);

    /* Send step request */
    http->post("http://turing.iem.thm.de/chatJava/sendTxt.php", params_txt);
    spy.wait();

}

void HamsterClient::goToCorn(){
    string Laufstring = "";
    int laenge = Laufstring.length();
    for( int i = 0; i < laenge; i++){
        char zeichen = ((char)Laufstring[i]);
        switch(zeichen){
            case 'r': walk(1);
                break;
            case 'o': walk(2);
                break;
            case 'l': walk(3);
                break;
            case 'u': walk(0);
                break;
        }
    }
    corn++;
}
