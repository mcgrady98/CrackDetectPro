#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CrackDetectPro.h"
#include "StreamVideo_Box.h"
#include "Video_Box.h"
QT_BEGIN_NAMESPACE
namespace Ui { class CrackDetectProClass; };
QT_END_NAMESPACE

class CrackDetectPro : public QMainWindow
{
    Q_OBJECT

public:
    CrackDetectPro(QWidget *parent = nullptr);
    ~CrackDetectPro();

    //视频流检测类界面指针
    StreamVideo_Box* StreamVideo_D;
    //本地视频测类界面指针
    Video_Box* Video_D;

private:
    Ui::CrackDetectProClass *ui;

public slots:

    //打开视频流检测界面槽函数
    void Open_StreamVideo_Box_Slot();
    //打开本地视频检测界面槽函数
    void Open_Video_Box_Slot();
};
