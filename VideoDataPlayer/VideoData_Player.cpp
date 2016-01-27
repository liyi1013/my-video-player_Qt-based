#include "VideoData_Player.h"

VideoDataPlayer::VideoDataPlayer(QWidget *parent)
	: QWidget(parent)
{
	this->setupUI(4);

	connect(ui_videoplayer, &MyVideoPlayer::next_position, ui_plotdata_1, &DataPlot_Widget::timeouttodo);
	connect(ui_videoplayer, &MyVideoPlayer::goto_position_x, ui_plotdata_1, &DataPlot_Widget::goto_x);


	// 下面是个例子，实际中用外部的时间调用下面两个函数
	this->openfile("E:","20160107171952");
	this->ui_videoplayer->play();

	set_title("20160107171952", "20160107171952", "20160107171952", "20160107171952");

	//
}

VideoDataPlayer::~VideoDataPlayer()
{

}

void VideoDataPlayer::setupUI(int num_fish)
{
	// [0]
	QVBoxLayout *vLayout_main = new QVBoxLayout(this);
	// [1]
	ui_title = new QLabel(this);
	ui_title->setText(tr("监测编号：01201506061059； 视频编号：201506061100； 起始时间2015-06-06 9：00，结束时间2015-06-06 11：00"));

	// [2]
	QHBoxLayout *hLayout_main = new QHBoxLayout(this);

	// [2][1]
	QVBoxLayout *vLayout_data_Widgets = new QVBoxLayout(this);

	// [2][1][1]
	QTabWidget *tabWidget = new QTabWidget(this);

	if (num_fish == 1)
	{
		ui_plotdata_1 = new DataPlot_Widget(this);
		ui_plotdata_2 = new DataPlot_Widget(this);
		tabWidget->addTab(ui_plotdata_1, tr("速度"));
		tabWidget->addTab(ui_plotdata_2, tr("尾频"));
	}
	else if (num_fish > 1)
	{
		ui_plotdata_1 = new DataPlot_Widget(this);
		ui_plotdata_2 = new DataPlot_Widget(this);
		tabWidget->addTab(ui_plotdata_1, tr("R"));
		tabWidget->addTab(ui_plotdata_2, tr("out of cricle"));
	}

	tabWidget->setFixedHeight(280);

	// [2][1][2]
	QHBoxLayout *hLayout_3 = new QHBoxLayout(this);
	QComboBox* _datastep_comboBox = new QComboBox(this);
	_datastep_comboBox->addItem("1秒");
	_datastep_comboBox->addItem("1分钟");
	_datastep_comboBox->addItem("30分钟");

	hLayout_3->addWidget(new QLabel("间隔单位:"));
	hLayout_3->addWidget(_datastep_comboBox);
	hLayout_3->addSpacing(340);

	// [2][1][add]
	vLayout_data_Widgets->addWidget(tabWidget);
	vLayout_data_Widgets->addLayout(hLayout_3);

	// [2][2]
	QVBoxLayout *vLayout_video_Widgets = new QVBoxLayout(this);
	ui_videoplayer = new MyVideoPlayer(this);
	AddPlotDataWidget(ui_plotdata_1);
	AddPlotDataWidget(ui_plotdata_2);

	vLayout_video_Widgets->addSpacing(20);
	vLayout_video_Widgets->addWidget(ui_videoplayer);

	// [2][add]
	hLayout_main->addLayout(vLayout_data_Widgets);
	hLayout_main->addLayout(vLayout_video_Widgets);

	// [0][add]
	vLayout_main->addWidget(ui_title);
	vLayout_main->addLayout(hLayout_main);
	
	this->setLayout(vLayout_main);
	//this->setFixedSize(880, 380);
	this->setWindowTitle("视频数据查看");
}

//数据和视频所在的路径，根据id找到数据文件和视频文件
void VideoDataPlayer::openfile(std::string path, std::string id){
	QString video_name = QString::fromStdString(path+"\\"+id+".avi");
	ui_videoplayer->Open_File(video_name);
	QString data_name1 = QString::fromStdString(path + "\\" + id + "_3.txt");
	ui_plotdata_1->openfile(data_name1);
}

void VideoDataPlayer::set_title(QString monitorID, QString videoID, QString time_begin, QString time_end){
	if (ui_title){
		QString title(tr("监测编号:%1,视频编号: %2,起始时间:%3,结束时间:%4")
			.arg(monitorID)
			.arg(videoID)
			.arg(time_begin)
			.arg(time_end));
			ui_title->setText(title);
	}
}