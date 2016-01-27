#ifndef DATAPLOT_WIDGET_H
#define DATAPLOT_WIDGET_H

#pragma execution_character_set("utf-8")

#include<fstream>

#include <qstring.h>
#include <QtCore\qdebug.h>
#include <QtCore\qvector.h>
#include <QtWidgets\QWidget>
#include <QtWidgets\qpushbutton.h>

#include"qcustomplot.h"

// 这个类与视频显示的类一起用，用于视频帧对应的数据的显示    
// 主要用于观看回放回放视频的整体曲线
// 读取一个数据文件，
// 将数据以曲线图的形式显示出来（蓝色）
// 提供红色的曲线，表示实时绘制
class DataPlot_Widget : public QWidget
{
	Q_OBJECT

 public:
	 DataPlot_Widget(QWidget *parent = 0);
	 ~DataPlot_Widget();

public:

	void openfile();                 // 打开文件
	bool openfile(QString filename); // 打开文件
	
	void timeouttodo();              // 每一秒执行：绘制秒的数据，由外部驱动

	void goto_x(double positon_x);   // 绘制数据到positon_x

//以上为对外接口

 private:

	int length;           //数据长度
	int _current_position;//当前数据位置

	std::ifstream _datafile; //文件名（.txt）

	QVector<double> x;       //x坐标

	QVector<double> qspeed;
	QVector<double> qwp;
	
	QCustomPlot* ui_qcustomplot;

	QPen pen;
	QPushButton *button;
};

#endif // DataPlot_Widget
