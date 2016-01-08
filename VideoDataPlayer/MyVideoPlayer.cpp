#include "MyVideoPlayer.h"

#include <QtWidgets\qslider.h>
#include <QtWidgets\qpushbutton.h>
#include <QtWidgets\qstyle.h>
#include<QtWidgets\qlayout.h>
#include<QtWidgets\qlabel.h>
#include<QtWidgets\QComboBox.h>

#include<QtCore\qtime>

#include<QtWidgets\QFileDialog>
#include<QtCore\qdir.h>


#include<QtCore\qdebug.h>


MyVideoPlayer::MyVideoPlayer(QWidget *parent) 
	: QWidget(parent), 
	 _mediaPlayer(0, QMediaPlayer::VideoSurface), 
	 _playButton(0), 
	 _positionSlider(0)
{
	_videoWidget = new QVideoWidget;
	_videoWidget->setMinimumSize(320, 240);

	QPushButton *openButton = new QPushButton(tr("Open..."));

	connect(openButton, &QPushButton::clicked, this, &MyVideoPlayer::Open_File);

	_playButton = new QPushButton;
	_playButton->setEnabled(false);

	_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

	connect(_playButton, SIGNAL(clicked()),this, SLOT(play()));

	_positionSlider = new QSlider(Qt::Horizontal);
	_positionSlider->setRange(0, 0);

	connect(_positionSlider, SIGNAL(sliderMoved(int)),this, SLOT(setPosition(int)));

	//errorLabel = new QLabel;
	//errorLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

	_rateBox = new QComboBox(this);
	_rateBox->addItem("1", QVariant(1.0));
	_rateBox->addItem("2", QVariant(2.0));
	_rateBox->addItem("3", QVariant(3.0));
	_rateBox->setCurrentIndex(0);
	
	QBoxLayout *controlLayout = new QHBoxLayout;
	controlLayout->setMargin(0);
	controlLayout->addWidget(openButton);
	controlLayout->addWidget(_playButton);
	//controlLayout->addWidget(_positionSlider);
	controlLayout->addWidget(new QLabel("speed"));
	controlLayout->addWidget(_rateBox);

	connect(_rateBox, SIGNAL(activated(int)), SLOT(updateRate()));

	QBoxLayout *InfoLayout = new QHBoxLayout;
	InfoLayout->addWidget(_positionSlider);

	_currentTime_info = new QLabel("0000");
	_totalTime_info = new QLabel("0000");
	InfoLayout->addWidget(_currentTime_info);
	InfoLayout->addWidget(new QLabel("/"));
	InfoLayout->addWidget(_totalTime_info);
	

	QBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(_videoWidget);
	layout->addLayout(controlLayout);
	layout->addLayout(InfoLayout);
	//layout->addWidget(InfoLayout);

	_mediaPlayer.setVideoOutput(_videoWidget);
	
	connect(&_mediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(mediapositionChanged(qint64)));
	connect(&_mediaPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
	//connect(&_mediaPlayer, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(handleError()));

	this->setLayout(layout);
}

MyVideoPlayer::~MyVideoPlayer()
{
}
/*
bool MyVideoPlayer::Open_File(const QString &filename)
{
	if (!filename.isEmpty()) {
		_mediaPlayer.setMedia(QUrl::fromLocalFile(filename));
		_playButton->setEnabled(true);

		_positionSlider->setRange(0, _mediaPlayer.duration());

		return true;
	}
	return false;
}
*/

bool MyVideoPlayer::Open_File()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Open Movie"), QDir::homePath());
	if (!filename.isEmpty()) {

		_mediaPlayer.setMedia(QUrl::fromLocalFile(filename));

		_playButton->setEnabled(true);

		this->play();

		return true;
	}
	return false;
}


// 进度条改变 -》视频改变
void MyVideoPlayer::setPosition(int position)
{
	_mediaPlayer.setPosition(position);
}

// 视频改变 -》进度条改变
void MyVideoPlayer::mediapositionChanged(qint64 position)
{
	_positionSlider->setValue(position);
	update_currentTime(position / 1000);
}


// 已将mediaStateChanged的功能合并到play()中
void MyVideoPlayer::mediaStateChanged(QMediaPlayer::State state)
{
	switch (state) {
	case QMediaPlayer::PlayingState:
		_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
		break;
	default:
		_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
		break;
	}
}

void MyVideoPlayer::play()
{
	switch (_mediaPlayer.state()) {
	case QMediaPlayer::PlayingState:
		_mediaPlayer.pause();
		_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
		break;
	default:
		_mediaPlayer.play();
		_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
		break;
	}
}

void MyVideoPlayer::durationChanged(qint64 duration)
{
	_positionSlider->setRange(0, duration);
	update_totalTime(duration/1000);

#ifdef _DEBUG
	qDebug() <<"total: " << duration << " ms"<< endl;
#endif // DEBUG
}


void MyVideoPlayer::update_currentTime(qint64 currentInfo){
	QString tStr;
	if (currentInfo ) {
		QTime currentTime((currentInfo / 3600) % 60, (currentInfo / 60) % 60, currentInfo % 60, (currentInfo * 1000) % 1000);
		QString format = "hh:mm:ss";
		tStr = currentTime.toString(format) ;
	}
	_currentTime_info->setText(tStr);
}

void MyVideoPlayer::update_totalTime(qint64 duration){
	QString tStr;
	if (duration) {
		QTime totalTime((duration / 3600) % 60, (duration / 60) % 60, duration % 60, (duration * 1000) % 1000);
		QString format = "hh:mm:ss";
		tStr = totalTime.toString(format);
	}
	_totalTime_info->setText(tStr);
}

void MyVideoPlayer::updateRate(){
	double qreal =_rateBox->itemData(_rateBox->currentIndex()).toDouble();
	_mediaPlayer.setPlaybackRate(qreal);
}
