#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QObject>

#include <QtCore>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class HttpClient : public QObject
{
Q_OBJECT
  QNetworkAccessManager *manager;

private slots:
  void replyFinished(QNetworkReply *);

public:
  void post(QString url, const QMap<QString, QString>& params);

signals:
  void responseAvailable(QString);
};

#endif // HTTPCLIENT_H
