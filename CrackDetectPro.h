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

    //��Ƶ����������ָ��
    StreamVideo_Box* StreamVideo_D;
    //������Ƶ�������ָ��
    Video_Box* Video_D;

private:
    Ui::CrackDetectProClass *ui;

public slots:

    //����Ƶ��������ۺ���
    void Open_StreamVideo_Box_Slot();
    //�򿪱�����Ƶ������ۺ���
    void Open_Video_Box_Slot();
};
