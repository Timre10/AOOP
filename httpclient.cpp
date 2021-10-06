#include <QTextCodec>
#include "httpclient.h"

void HttpClient::replyFinished(QNetworkReply *reply)
{
    QString dataAsString = QTextCodec::codecForMib(106)->toUnicode(reply->readAll());
    emit responseAvailable(dataAsString);
}

void HttpClient::post(QString url, const QMap<QString, QString>& params)
{
  manager = new QNetworkAccessManager(this);
  connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

  QUrlQuery postData;
  for (auto it = params.begin(); it != params.end(); it++) {
      postData.addQueryItem(it.key(), it.value());
  }

  QNetworkRequest request(url);
  request.setHeader(QNetworkRequest::ContentTypeHeader,
      "application/x-www-form-urlencoded");
  manager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());
}
