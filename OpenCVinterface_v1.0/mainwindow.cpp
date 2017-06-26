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
#include <classifier.h>
//#include <glog/logging.h>

//using namespace std;
using namespace cv;
using namespace caffe;

//google::InitGoogleLogging("main");

/* model_file is the deploy prototxt file */
string model_file   = "/var/lib/digits/jobs/20170530-120046-fe55/deploy.prototxt";
/* trained_file is the trained model *.caffemodel file */
string trained_file = "/var/lib/digits/jobs/20170530-120046-fe55/snapshot_iter_8450.caffemodel";
/* mean_file mean image file */
string mean_file    = "/var/lib/digits/jobs/20170522-095838-df96/mean.binaryproto";
/* label_file is a text file containing the categories adn its labels */
string label_file   = "/var/lib/digits/jobs/20170522-095838-df96/labels.txt";

/* create the classifier */
Classifier classifier(model_file, trained_file, mean_file, label_file);


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Update text */
    ui->tePath->appendPlainText(QString("-"));


}


MainWindow::~MainWindow()
{


    delete ui;
}



void MainWindow::on_bOpenImage_clicked()
{
    /* Open file dialog */
    QString fileName =  QFileDialog::getOpenFileName(this,"Open image","/home","All files (*.*);;JPEG (*.jpg *.jpeg);;TIFF (*.tif);;PNG files (*.png)");
    /* Load image into object */
    QImage *imageObject = new QImage();
    imageObject->load(fileName);

    if (imageObject->isNull())
    {
            QMessageBox::information(this, "ERROR",tr("Cannot load %1").arg(QDir::toNativeSeparators(fileName)));
    }else
    {
       int w = ui->qlImage->width();
       int h = ui->qlImage->height();
       /* Write filepath */
       ui->tePath->clear();
       ui->tePath->appendPlainText(fileName);
       /* Resize the image according the size of the object in the GUI and plot it */
       ui->qlImage->setPixmap(QPixmap::fromImage(*imageObject).scaled(w,h,Qt::KeepAspectRatio));

       /* load the image as an OpenCV mat type */
       img = cv::imread(fileName.toStdString(), -1);
       CHECK(!img.empty()) << "Unable to decode image " << fileName.toStdString();


   /* image classification */
       std::vector<Prediction> predictions = classifier.Classify(img);

       /* Print the top N predictions in the buttons. */
       ui->lCat1->setText(QString::fromStdString(predictions[0].first));
       std::ostringstream ss;
       ss << predictions[0].second;
       ui->bCat1->setText(QString::fromStdString(ss.str()));
       ui->bCat1->setStyleSheet("background-color: black");
       ui->lCat2->setText(QString::fromStdString(predictions[1].first));
       ss.str(std::string());
       ss << predictions[1].second;
       ui->bCat2->setText(QString::fromStdString(ss.str()));
       ui->bCat2->setStyleSheet("background-color: black");
       ui->lCat3->setText(QString::fromStdString(predictions[2].first));
       ss.str(std::string());
       ss << predictions[2].second;
       ui->bCat3->setText(QString::fromStdString(ss.str()));
       ui->bCat3->setStyleSheet("background-color: black");
       ui->lCat4->setText(QString::fromStdString(predictions[3].first));
       ss.str(std::string());
       ss << predictions[3].second;
       ui->bCat4->setText(QString::fromStdString(ss.str()));
       ui->bCat4->setStyleSheet("background-color: black");
       ui->lCat5->setText(QString::fromStdString(predictions[4].first));
       ss.str(std::string());
       ss << predictions[4].second;
       ui->bCat5->setText(QString::fromStdString(ss.str()));
       ui->bCat5->setStyleSheet("background-color: black");


    }



}

