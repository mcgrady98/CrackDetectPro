#include "CrackDetectPro.h"
#include <QtWidgets/QApplication>
#include <opencv2/opencv.hpp>
#include "RestfulAPI.h"
extern "C"
{
#include "libavdevice/avdevice.h"
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "libavcodec/avcodec.h"
#include "libswresample/swresample.h" 
}
int main(int argc, char *argv[])
{   
    QApplication a(argc, argv);   
    CrackDetectPro w;
    w.show();
    return a.exec();
}
