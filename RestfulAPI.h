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

	//向服务器发送拉流代理请求
	QString Request_PullStream(QString pulltype,int timeout);
	//关闭拉流代理
	QString Request_ClosePullStream(QString pulltype,int timeout);
	//解析服务器响应
	QString R_Reply(QNetworkReply* reply, int timeout);

private:
	QNetworkAccessManager* m_manager;

	QString m_recvData;
	//服务器地址
	QString addrs;
	//秘钥
	QString secret = "secret";
	QString key = "56yaXMl";
};

