#include "RestfulAPI.h"

RestfulAPI::RestfulAPI(QString R_adr, QString R_port)
{
    m_manager = new QNetworkAccessManager();
    addrs = R_adr + ":" + R_port;
}

RestfulAPI::~RestfulAPI()
{
    delete m_manager;
    m_manager = nullptr;
}

QString RestfulAPI::Request_PullStream(QString pulltype, int timeout)
{   
    QNetworkRequest request;
    QString scheme = "http://";
    QString requestHeader = scheme + addrs + "/index/api";
    //��������
    QString fullrquest;

    //������������
    if (pulltype == "Normal") {
        QString fullrquest = QString(requestHeader + "/addStreamProxy" + 
            "?%1=%2&"
            "vhost=__defaultVhost__&app=proxy&stream=0&url=/dev/video0")
            .arg(secret).arg(key);
    }
    //FFmpeg��������keyΪcmd1
    if (pulltype == "FFmpeg") {
        QString fullrquest = QString(requestHeader + "/addFFmpegSource" +
            "?%1=%2&"
            "src_url=/dev/video0&dst_url=rtsp://127.0.0.1/live/test&timeout_ms=10000&ffmpeg_cmd_key=%3")
            .arg(secret).arg(key).arg("ffmpeg.cmd1");
    }
    QString ss = QString("http://192.168.10.106/index/api/getApiList?%1=%2&").arg(secret).arg(key);
    request.setUrl(QUrl(ss));
    
    return R_Reply(m_manager->get(request), timeout);
}

QString RestfulAPI::Request_ClosePullStream(QString pulltype, int timeout)
{
    QNetworkRequest request;
    QString scheme = "http://";
    QString requestHeader = scheme + addrs + "/index/api";
    //��������
    QString fullrquest;

    //�ر���ͨ��������
    if (pulltype == "Normal") {
        QString fullrquest = QString(requestHeader +
            "/delStreamProxy?%1=%2&").arg(secret).arg(key);
    }
    //�ر�FFmpeg��������keyΪcmd1
    if (pulltype == "FFmpeg") {
        QString fullrquest = QString(requestHeader + "/delFFmpegSource" +
            "?%1=%2&").arg(secret).arg(key).arg("ffmpeg.cmd1");
    }

    return R_Reply(m_manager->get(request), timeout);
}

QString RestfulAPI::R_Reply(QNetworkReply* reply, int timeout)
{   
    //�¼�ѭ��
    QEventLoop loop;
    QTimer time;

    connect(&time, &QTimer::timeout, &loop, &QEventLoop::quit);
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    time.start(timeout);
    loop.exec();

    //��ȡ״̬��Ӧ��
    QVariant status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    //��ȡ����
    const QByteArray bytes = reply->readAll();
    //��ȡһ��UTF-8����������pCodec
    QTextCodec* pCodec = QTextCodec::codecForName("UTF-8");
    //���ֽ�����ת��ΪUnicode�ַ���
    QString r_recvUnicode = pCodec->toUnicode(bytes);

    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "httpͨ�ŷ��ش���" << reply->url() << status_code;
    }
    //���� reply ���������¼�ѭ���д����ģ������Ҫ���� deleteLater() ��������ȫ��ɾ������
    // �Ա���Ǳ�ڵ��ڴ�й©
    reply->deleteLater();
    qInfo() << r_recvUnicode;
    return r_recvUnicode;
}
