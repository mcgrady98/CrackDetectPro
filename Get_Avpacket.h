#pragma once
#include <queue>
#include <mutex>
#include <QDebug>
#include <QThread>

extern "C"
{
    //avcodec:编解码(最重要的库)
#include <libavcodec/avcodec.h>
    //avformat:封装格式处理
#include <libavformat/avformat.h>
    //swscale:视频像素数据格式转换
#include <libswscale/swscale.h>
    //avdevice:各种设备的输入输出
#include <libavdevice/avdevice.h>
    //avutil:工具库（大部分库都需要这个库的支持）
#include <libavutil/avutil.h>
}
class Get_Avpacket
{
public:

    Get_Avpacket(int videoIndex);
    ~Get_Avpacket();

public:

    //将包放入队列
    bool Push_Pkt(AVPacket& AVpkt);
    //从包里解码数据,注意释放资源
    AVPacket Get_Pkt();
    //清除队列数据
    bool Clear_Pktque();
    
    
private:

    //包队列
    std::queue <AVPacket> pkt;
    //互斥锁
    std::mutex pkt_mutex;
    //流索引
    int g_videoIndex;
    //停止
    bool g_stop;

public slots:

    //获取包
    void Get_AVpkt(AVFormatContext* FormatCtx);

signals:
    //打印信息到控制台信号
    void Print_Message(QString msg);
    void finished();
};

