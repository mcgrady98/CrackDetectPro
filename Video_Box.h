#pragma once

#include <QWidget>
#include "ui_Video_Box.h"

class Video_Box : public QWidget
{
	Q_OBJECT

public:
	Video_Box(QWidget *parent = nullptr);
	~Video_Box();

private:
	Ui::Video_BoxClass ui;
};
