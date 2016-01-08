/********************************************************************************
** Form generated from reading UI file 'videodataplayer.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEODATAPLAYER_H
#define UI_VIDEODATAPLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VideoDataPlayerClass
{
public:

    void setupUi(QWidget *VideoDataPlayerClass)
    {
        if (VideoDataPlayerClass->objectName().isEmpty())
            VideoDataPlayerClass->setObjectName(QStringLiteral("VideoDataPlayerClass"));
        VideoDataPlayerClass->resize(600, 400);

        retranslateUi(VideoDataPlayerClass);

        QMetaObject::connectSlotsByName(VideoDataPlayerClass);
    } // setupUi

    void retranslateUi(QWidget *VideoDataPlayerClass)
    {
        VideoDataPlayerClass->setWindowTitle(QApplication::translate("VideoDataPlayerClass", "VideoDataPlayer", 0));
    } // retranslateUi

};

namespace Ui {
    class VideoDataPlayerClass: public Ui_VideoDataPlayerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEODATAPLAYER_H
