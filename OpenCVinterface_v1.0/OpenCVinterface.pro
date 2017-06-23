#-------------------------------------------------
#
# Project created by QtCreator 2017-03-31T16:12:23
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenCVinterface
TEMPLATE = app

INCLUDEPATH += /usr/include/opencv2
INCLUDEPATH += /home/cinae/caffe/include
INCLUDEPATH += /usr/local/cuda-8.0/include
#LIBS += -L/usr/local/lib -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_detection_based_tracker -lopencv_esm_panorama -lopencv_facedetect -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_imuvstab -lopencv_legacy -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_tegra -lopencv_ts -lopencv_video -lopencv_videostab -lopencv_vstab
#LIBS += -L/usr/local/lib -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab
LIBS += -L/usr/local/lib -lopencv_calib3d -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_videoio -lopencv_video -lopencv_videostab
LIBS += -lboost_system -lglog
LIBS += -L/home/cinae/caffe/build/lib -lcaffe

LIBS += -L/usr/local/lib \


SOURCES += main.cpp\
        mainwindow.cpp\
    classifier.cpp


HEADERS  += mainwindow.h \
    classifier.h

FORMS    += mainwindow.ui
