#include <qfiledialog.h>
#include "DataPlot_Widget.h"


DataPlot_Widget::DataPlot_Widget(QWidget *parent) : QWidget(parent)
{
	_current_position = 0;

	ui_qcustomplot = new QCustomPlot(this);

	QVBoxLayout * ui_layout_main = new QVBoxLayout(this);

	ui_layout_main->setMargin(0);

	ui_layout_main->addWidget(ui_qcustomplot);
}

DataPlot_Widget::~DataPlot_Widget()
{

}

void DataPlot_Widget::timeouttodo()
{
	if (_current_position < length)
	{
		ui_qcustomplot->graph(1)->addData(_current_position, qspeed[_current_position - 1]);
		ui_qcustomplot->replot();
		++_current_position;
	} else {
		//t.stop();
	}
}

void DataPlot_Widget::goto_x(double positon_x)
{
	if (positon_x < length)
	{
		ui_qcustomplot->graph(1)->clearData();
		_current_position = 0;
		while (++_current_position <= positon_x)
		{
			ui_qcustomplot->graph(1)->addData(_current_position, qspeed[_current_position - 1]);
		}
	}
	ui_qcustomplot->replot();
}

bool DataPlot_Widget::openfile(QString filename)
{
	_datafile.open(filename.toStdString());
	if (_datafile.is_open())
	{
		qspeed.clear();
		   qwp.clear();
		     x.clear();
		
	    double s, w;
		while (_datafile >> s)
		{
			qspeed.push_back(s);
			x.push_back(++_current_position);
		}

		int maxval = 0;
		for (qreal i : qspeed)
		{
			if (i > maxval)
			{
				maxval = i;
			}
		}

		ui_qcustomplot->addGraph();

		ui_qcustomplot->graph(0)->setData(x, qspeed);

		ui_qcustomplot->xAxis->setRange(-1, x.size());

		ui_qcustomplot->yAxis->setRange(0, maxval);
		ui_qcustomplot->xAxis->setLabel(tr("时间 秒"));

		ui_qcustomplot->xAxis->setTickStep(60*5);
		ui_qcustomplot->xAxis->setSubTickCount(60);

		_current_position = 1;
		length = x.size();

		{
			ui_qcustomplot->addGraph();
			pen.setColor(Qt::red);
			pen.setWidth(2);
			ui_qcustomplot->graph(1)->setPen(pen);
		}
		ui_qcustomplot->replot();
		return true;
	} else {
#ifdef _DEBUG
		qDebug() << "open file fail!" << endl;
#endif
		return false;
	}
}

void DataPlot_Widget::openfile()
{
	QString path = QFileDialog::getOpenFileName(this, tr("打开视频文件"), ".", tr("(*.txt)"));
	if (path.isEmpty()){
		//QMessageBox::information(this, tr("Information"), tr("Can Not Open The File !"));
		return  ;
	}
	if (this->openfile(path)){
#ifdef _DEBUG
	qDebug() << "file path & name: " << path<<  endl;
#endif // DEBUG
	}
}