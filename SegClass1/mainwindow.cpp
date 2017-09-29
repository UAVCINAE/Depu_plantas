/** @file Video file segmentation interface
 * @brief : This small app lets the user select a video file, segments each frame at a time and shows the result
 * Developed under Qt Creator.
 * @date : June 2017
 * @author : Martin Bueno
 * @version : 1.0
 * */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <string>
#include <bitset>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <caffe/caffe.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <algorithm>
#include <iosfwd>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "segclassifier.h"

//using namespace std;
using namespace cv;
using namespace caffe;

/** ModelFile is the deploy prototxt file */
//string ModelFile = "/home/cinae/ENet/prototxts/enet_deploy_final.prototxt";
/** TrainedFile is the *.caffemodel file with the weights */
//string TrainedFile = "/home/cinae/ENet/enet_weights_zoo/cityscapes_weights.caffemodel";
string ModelFile = "/var/lib/digits/jobs/20170627-110413-b391/deploy.prototxt";
string TrainedFile = "/var/lib/digits/jobs/20170627-110413-b391/snapshot_iter_14640.caffemodel";
/** create the classifier */
SegClassifier classifier(ModelFile, TrainedFile);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bOpen_clicked()
{

    /* Open file dialog */
    QString fileName =  QFileDialog::getOpenFileName(this,"Open video file","/home","All files (*.*);;MPG4 (*.mp4);;AVI (*.avi)");
    VideoCapture VideoFile(fileName.toStdString()); // open the video file for reading

    if ( !VideoFile.isOpened() )  // if not success, exit program
    {
        std::cout << "Cannot open the video file" << std::endl;
    }

    double fps = VideoFile.get(CV_CAP_PROP_FPS); //get the frames per seconds of the video

    std::cout << "Frame per seconds : " << fps << std::endl;

    /* Get the size of the image in the GUI to resize the input and output accordingly */
    int w = ui->lSegmentedImage->width();
    int h = ui->lSegmentedImage->height();

    /** image containing the frame to be processed*/
    Mat VideoFrame;
    bool bSuccess = VideoFile.read(VideoFrame); // read a new frame from video

    /* While there is frames in the video file */
    while(bSuccess)
    {

        /** segmented frame */
        Mat SegImage;

        /** perform the segmentation of the frame */
        //classifier.Predict(VideoFrame, "/home/cinae/ENet/scripts/cityscapes19.png", SegImage);
        classifier.Predict(VideoFrame, "/home/cinae/ENet/scripts/pascal20.png", SegImage);

        /* OpenCV works with image in BGR format, convert the images to BGR to be able to display them */
        cv::cvtColor(VideoFrame, VideoFrame, CV_BGR2RGB);
        cv::cvtColor(SegImage, SegImage, CV_BGR2RGB);

        /* resize the images to the widget size*/
        Size NewSize(w,h);
        cv::resize(SegImage,SegImage,NewSize);
        cv::resize(VideoFrame,VideoFrame,NewSize);
        /* Load original frame into object */
        QImage qImgOriginal((const uchar*) VideoFrame.data,VideoFrame.cols,VideoFrame.rows,VideoFrame.step,QImage::Format_RGB888); // for color images
        ui->lSourceImage->setPixmap(QPixmap::fromImage(qImgOriginal).scaled(w,h,Qt::KeepAspectRatio));

        /* Load segmented image into object */
        QImage qSegImg((const uchar*) SegImage.data,SegImage.cols,SegImage.rows,SegImage.step,QImage::Format_RGB888); // for color images
        ui->lSegmentedImage->setPixmap(QPixmap::fromImage(qSegImg).scaled(w,h,Qt::KeepAspectRatio));

        /* blended image containing the original frame and the segmentation */
        Mat BlendedImage;
        /* set the alpha value for the original frame, the segmented image will have 1 - alpha value */
        double alpha = 0.4;
        /* mix the images */
        addWeighted(VideoFrame, alpha, SegImage, 1-alpha, 0.0, BlendedImage);
        QImage qImgSeg((const uchar*) BlendedImage.data,BlendedImage.cols,BlendedImage.rows,BlendedImage.step,QImage::Format_RGB888); // for color images
        ui->lMixedImage->setPixmap(QPixmap::fromImage(qImgSeg).scaled(w,h,Qt::KeepAspectRatio));

        /* force the GUI to display the images */
        qApp->processEvents();

        /* read the next frame */
        bSuccess = VideoFile.read(VideoFrame);

    }

}
