#include "Get_Avpacket.h"

Get_Avpacket::Get_Avpacket(int videoIndex):g_stop(true)
{
    g_videoIndex = videoIndex;
}
Get_Avpacket::~Get_Avpacket()
{

}

void Get_Avpacket::Get_AVpkt(AVFormatContext* FormatCtx) {
	AVPacket avp;

	while (true)
	{
		if (g_stop == true) {

			QString stop_msg("stop get Avpkt");
			emit Print_Message(stop_msg);
			break;
		}
		
        if (av_read_frame(FormatCtx, &avp) < 0) {

            QString readfail_msg = QString("clearAVpkt fail,AVpkt stream_index:%1").arg(avp.stream_index);
            emit Print_Message(readfail_msg);

        }
        
        if (avp.stream_index == g_videoIndex) {
            if (Push_Pkt(avp) != true) {

                QString pushfail_msg = QString("push AVpkt to queue fail,AVpkt stream_index:%1").arg(avp.stream_index);
                emit Print_Message(pushfail_msg); 

            }
        }
        
        if (pkt.size() > 500) {

            //防止一次性读取过多包，到一定数量线程休眠3s
            QThread::msleep(3000);
            continue;
        }
    }
    emit finished();
	
}


bool Get_Avpacket::Push_Pkt(AVPacket& AVpkt)
{   
    //av_packet_make_refcounted 函数用于确保 AVPacket 结构的引用计数被正确设置
    if (av_packet_make_refcounted((AVPacket*)&AVpkt) < 0) {
        qDebug() << "av_packet_make_refcounted fail";
        return false;
    }

    pkt_mutex.lock();
    pkt.push(AVpkt);
    pkt_mutex.unlock();

    return true;
	
}

AVPacket Get_Avpacket::Get_Pkt()
{   
    if (!pkt.empty()) {

        pkt_mutex.lock();
        AVPacket avp = pkt.front();
        pkt.pop();
        pkt_mutex.unlock();

        return avp;
    }

    emit Print_Message("Avpktqueue is unll!");
	return AVPacket();
}

bool Get_Avpacket::Clear_Pktque()
{
    pkt_mutex.lock();

    for (int i=0; i < pkt.size(); ++i) {

        AVPacket avp = pkt.front();
        av_packet_unref(&avp);
        pkt.pop();

    }

    pkt_mutex.unlock();
    return true;
}

void Get_Avpacket::finished()
{
    qDebug() << "finished signal emit";
}

void Get_Avpacket::Print_Message(QString msg) {

    qDebug() << "emit Print_Message:"<<msg;

}
