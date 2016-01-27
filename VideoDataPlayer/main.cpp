#include "VideoData_Player.h"
#include <QtWidgets/QApplication>

#include"MyVideoPlayer.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	VideoDataPlayer w;
	w.show();

	return a.exec();
}
