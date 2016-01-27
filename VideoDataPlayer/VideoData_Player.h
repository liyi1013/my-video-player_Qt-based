#ifndef VIDEODATAPLAYER_H
#define VIDEODATAPLAYER_H

#include<string>

#include <QtWidgets/QWidget>
#include "MyVideoPlayer.h"
#include "DataPlot_Widget.h"


class VideoDataPlayer : public QWidget
{
	Q_OBJECT

public:
	VideoDataPlayer(QWidget *parent = 0);
	~VideoDataPlayer();

	void openfile(std::string path,std::string id);  //数据和视频所在的路径，根据id找到数据文件和视频文件
	
private:
	void setupUI(int num_fish);
	
	void AddPlotDataWidget(DataPlot_Widget* plotdata)
	{
		dataCruves.push_back(plotdata);
	}
	std::vector<DataPlot_Widget*> dataCruves;  
	
	MyVideoPlayer*   ui_videoplayer;         // 视频播放控件
	DataPlot_Widget* ui_plotdata_1;          // 数据显示控件
	DataPlot_Widget* ui_plotdata_2;

	QLabel* ui_currentData;
	QLabel* ui_title;

	void set_title(QString monitorID, QString videoID, QString time_begin, QString time_end);

	int num_fish;
	
	QString _file_name;
};

#endif // VIDEODATAPLAYER_H
