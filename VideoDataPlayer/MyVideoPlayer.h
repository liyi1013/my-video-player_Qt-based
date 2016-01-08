#pragma once

#include "D:\Qt\Qt5.5.1\5.5\msvc2013\include\QtWidgets\qwidget.h"

#include <QtGui/QMovie>

#include<QtMultimediaWidgets\qvideowidget.h>
#include<QtMultimedia\qmediaplayer.h>

class QSlider;
class QAbstractButton;
class QLabel;
class QComboBox;


// 视频播放器类

class MyVideoPlayer : public QWidget
{
	Q_OBJECT

public:
	MyVideoPlayer(QWidget *parent);
	~MyVideoPlayer();

public:
	//bool Open_File(const QString &filename);
	bool Open_File();

public slots:

	void mediaStateChanged(QMediaPlayer::State state);
	void mediapositionChanged(qint64 position);  // 视频改变  -》进度条改变
	void setPosition(int position);              // 进度条改变 -》视频改变
	
	void durationChanged(qint64 duration);
	void updateRate();
	void play();
	
private:
	QMediaPlayer    _mediaPlayer;     // qt内置播放器
	QVideoWidget    *_videoWidget;    // 显示视频控件

	QAbstractButton *_playButton;     // 播放按钮
	QSlider         *_positionSlider; // 进度条
	QComboBox       *_rateBox;        // 播放速率选择

	QLabel *_currentTime_info;        // 当前已播放时长 label
	QLabel *_totalTime_info;          // 视频总时长 label

	void update_currentTime(qint64 currentInfo);
	void update_totalTime(qint64 duration);
};

