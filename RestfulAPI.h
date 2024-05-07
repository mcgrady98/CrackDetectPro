#pragma once
#include <QObject>
#include <QString.h>
#include <QNetworkAccessManager>
#include <qnetworkrequest.h>
#include <QNetworkReply>
#include <QtCore5Compat/QTextCodec>
#include <QEventLoop>
#include <QTimer>
#include <Qurl>
class RestfulAPI:public QObject
{
	Q_OBJECT

public:
	RestfulAPI(QString R_adr, QString R_port);
	~RestfulAPI();

	//�����������������������
	QString Request_PullStream(QString pulltype,int timeout);
	//�ر���������
	QString Request_ClosePullStream(QString pulltype,int timeout);
	//������������Ӧ
	QString R_Reply(QNetworkReply* reply, int timeout);

private:
	QNetworkAccessManager* m_manager;

	QString m_recvData;
	//��������ַ
	QString addrs;
	//��Կ
	QString secret = "secret";
	QString key = "56yaXMl";
};

