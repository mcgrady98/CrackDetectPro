#pragma once

#include <QWidget>
#include "ui_StreamVideo_Box.h"

class StreamVideo_Box : public QWidget
{
	Q_OBJECT

public:
	StreamVideo_Box(QWidget *parent = nullptr);
	~StreamVideo_Box();

private:
	Ui::StreamVideo_BoxClass ui;
};
