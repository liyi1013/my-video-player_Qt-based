#ifndef VIDEODATAPLAYER_H
#define VIDEODATAPLAYER_H

#include <QtWidgets/QWidget>


class VideoDataPlayer : public QWidget
{
	Q_OBJECT

public:
	VideoDataPlayer(QWidget *parent = 0);
	~VideoDataPlayer();

private:
	//Ui::VideoDataPlayerClass ui;
};

#endif // VIDEODATAPLAYER_H
