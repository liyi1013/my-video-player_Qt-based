#include "videodataplayer.h"
#include <QtWidgets/QApplication>

#include"MyVideoPlayer.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//VideoDataPlayer w;
	//w.show();

	MyVideoPlayer V(0);
	V.show();
	return a.exec();
}
