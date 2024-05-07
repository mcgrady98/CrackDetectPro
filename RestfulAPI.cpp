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
    //完整请求
    QString fullrquest;

    //设置拉流代理
    if (pulltype == "Normal") {
        QString fullrquest = QString(requestHeader + "/addStreamProxy" + 
            "?%1=%2&"
            "vhost=__defaultVhost__&app=proxy&stream=0&url=/dev/video0")
            .arg(secret).arg(key);
    }
    //FFmpeg拉流代理，key为cmd1
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
    //完整请求
    QString fullrquest;

    //关闭普通拉流代理
    if (pulltype == "Normal") {
        QString fullrquest = QString(requestHeader +
            "/delStreamProxy?%1=%2&").arg(secret).arg(key);
    }
    //关闭FFmpeg拉流代理，key为cmd1
    if (pulltype == "FFmpeg") {
        QString fullrquest = QString(requestHeader + "/delFFmpegSource" +
            "?%1=%2&").arg(secret).arg(key).arg("ffmpeg.cmd1");
    }

    return R_Reply(m_manager->get(request), timeout);
}

QString RestfulAPI::R_Reply(QNetworkReply* reply, int timeout)
{   
    //事件循环
    QEventLoop loop;
    QTimer time;

    connect(&time, &QTimer::timeout, &loop, &QEventLoop::quit);
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    time.start(timeout);
    loop.exec();

    //获取状态响应码
    QVariant status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    //读取数据
    const QByteArray bytes = reply->readAll();
    //获取一个UTF-8编码器对象pCodec
    QTextCodec* pCodec = QTextCodec::codecForName("UTF-8");
    //将字节数组转换为Unicode字符集
    QString r_recvUnicode = pCodec->toUnicode(bytes);

    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "http通信返回错误" << reply->url() << status_code;
    }
    //由于 reply 对象是在事件循环中创建的，因此需要调用 deleteLater() 函数来安全地删除它，
    // 以避免潜在的内存泄漏
    reply->deleteLater();
    qInfo() << r_recvUnicode;
    return r_recvUnicode;
}
