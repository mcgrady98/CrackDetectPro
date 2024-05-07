#pragma once
#include <queue>
#include <mutex>
#include <QDebug>
#include <QThread>

extern "C"
{
    //avcodec:�����(����Ҫ�Ŀ�)
#include <libavcodec/avcodec.h>
    //avformat:��װ��ʽ����
#include <libavformat/avformat.h>
    //swscale:��Ƶ�������ݸ�ʽת��
#include <libswscale/swscale.h>
    //avdevice:�����豸���������
#include <libavdevice/avdevice.h>
    //avutil:���߿⣨�󲿷ֿⶼ��Ҫ������֧�֣�
#include <libavutil/avutil.h>
}
class Get_Avpacket
{
public:

    Get_Avpacket(int videoIndex);
    ~Get_Avpacket();

public:

    //�����������
    bool Push_Pkt(AVPacket& AVpkt);
    //�Ӱ����������,ע���ͷ���Դ
    AVPacket Get_Pkt();
    //�����������
    bool Clear_Pktque();
    
    
private:

    //������
    std::queue <AVPacket> pkt;
    //������
    std::mutex pkt_mutex;
    //������
    int g_videoIndex;
    //ֹͣ
    bool g_stop;

public slots:

    //��ȡ��
    void Get_AVpkt(AVFormatContext* FormatCtx);

signals:
    //��ӡ��Ϣ������̨�ź�
    void Print_Message(QString msg);
    void finished();
};

