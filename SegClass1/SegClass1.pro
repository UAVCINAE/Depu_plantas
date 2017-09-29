#-------------------------------------------------
#
# Project created by QtCreator 2017-06-27T15:58:06
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SegClass
TEMPLATE = app

INCLUDEPATH += /usr/include/opencv2
INCLUDEPATH += /home/cinae/ENet/caffe-enet/include
INCLUDEPATH += /usr/local/cuda-8.0/include
LIBS += -L/usr/local/lib -lopencv_calib3d -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_videoio -lopencv_video -lopencv_videostab
LIBS += -lboost_system -lglog
LIBS += -L/home/cinae/ENet/caffe-enet/build/lib -lcaffe

LIBS += -L/usr/local/lib \


SOURCES += main.cpp\
        mainwindow.cpp\
        segclassifier.cpp


HEADERS  += mainwindow.h \
    classifier.h \
    segclassifier.h

FORMS    += mainwindow.ui
