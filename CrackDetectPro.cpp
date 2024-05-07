#include "CrackDetectPro.h"

CrackDetectPro::CrackDetectPro(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CrackDetectProClass())
{   
    StreamVideo_D = nullptr;
    Video_D = nullptr;

    ui->setupUi(this);
    
}

CrackDetectPro::~CrackDetectPro()
{   
    delete StreamVideo_D;
    StreamVideo_D = nullptr;
    delete Video_D;
    Video_D = nullptr;
    delete ui;
}

void CrackDetectPro::Open_StreamVideo_Box_Slot() {

    if (StreamVideo_D == nullptr) {
        StreamVideo_D = new StreamVideo_Box();
        StreamVideo_D->show();
    }
    else
    {
        StreamVideo_D->show();
    }
}

void CrackDetectPro::Open_Video_Box_Slot() {

    if (Video_D == nullptr) {
        Video_D = new Video_Box();
        Video_D->show();
    }
    else
    {
        Video_D->show();
    }

}