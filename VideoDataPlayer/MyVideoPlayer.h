#pragma once

#include <QtWidgets\qwidget.h>

#include <QtGui/QMovie>

#include<QtMultimediaWidgets\qvideowidget.h>
#include<QtMultimedia\qmediaplayer.h>

class QSlider;
class QAbstractButton;
class QLabel;
class QComboBox;


// 视频播放器类, 用于视频的播放
// 拥有 控件：进度条，时间，播放按钮
// 对外提供 信号槽 ：下一秒，转到第几秒
class MyVideoPlayer : public QWidget
{
	Q_OBJECT

public:
	MyVideoPlayer(QWidget *parent=0);
	~MyVideoPlayer();

public slots:
	QString Open_File(const QString &filename);
	QString Open_File();
	
	void play();                         // 改变播放状态（暂停->播放，播放->暂停）

signals:

	void next_position();                // 信号，视频的下一时刻（秒）
	void goto_position_x(double x);      // 信号，转到视频的第x秒
	
//以上为对外接口
	
private slots:

	void mediaStateChanged(QMediaPlayer::State state);
	void mediapositionChanged(qint64 position);        // 视频改变  -》进度条改变
	void setPosition(int position);           // 进度条改变 -》视频改变
	
	void durationChanged(qint64 duration);
	void updateRate();
	
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

