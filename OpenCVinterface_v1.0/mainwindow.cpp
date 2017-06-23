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

string model_file   = "/var/lib/digits/jobs/20170530-120046-fe55/deploy.prototxt";
string trained_file = "/var/lib/digits/jobs/20170530-120046-fe55/snapshot_iter_8450.caffemodel";
string mean_file    = "/var/lib/digits/jobs/20170522-095838-df96/mean.binaryproto";
string label_file   = "/var/lib/digits/jobs/20170522-095838-df96/labels.txt";

Classifier classifier(model_file, trained_file, mean_file, label_file);


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Update text+
    ui->txtpath->appendPlainText(QString("-"));


}


MainWindow::~MainWindow()
{


    delete ui;
}



void MainWindow::on_ButtonOpenImage_clicked()
{
    //Open file dialog
    QString fileName =  QFileDialog::getOpenFileName(this,"Open image","/home","All files (*.*);;JPEG (*.jpg *.jpeg);;TIFF (*.tif);;PNG files (*.png)");
    //Load image into object
    QImage *imageObject = new QImage();
    imageObject->load(fileName);

    if (imageObject->isNull())
    {
            QMessageBox::information(this, "ERROR",tr("Cannot load %1").arg(QDir::toNativeSeparators(fileName)));
    }else
    {
       int w = ui->lblimage->width();
       int h = ui->lblimage->height();
       //Write filepath
       ui->txtpath->clear();
       ui->txtpath->appendPlainText(fileName);
       //Plot image
       ui->lblimage->setPixmap(QPixmap::fromImage(*imageObject).scaled(w,h,Qt::KeepAspectRatio));
       //CategoriesPlot();

       img = cv::imread(fileName.toStdString(), -1);
       CHECK(!img.empty()) << "Unable to decode image " << fileName.toStdString();


   /* image classification */
       std::vector<Prediction> predictions = classifier.Classify(img);

       /* Print the top N predictions. */
       ui->cat1label->setText(QString::fromStdString(predictions[0].first));
       std::ostringstream ss;
       ss << predictions[0].second;
       ui->cat1but->setText(QString::fromStdString(ss.str()));
       ui->cat1but->setStyleSheet("background-color: black");
       ui->cat2label->setText(QString::fromStdString(predictions[1].first));
       ss.str(std::string());
       ss << predictions[1].second;
       ui->cat2but->setText(QString::fromStdString(ss.str()));
       ui->cat2but->setStyleSheet("background-color: black");
       ui->cat3label->setText(QString::fromStdString(predictions[2].first));
       ss.str(std::string());
       ss << predictions[2].second;
       ui->cat3but->setText(QString::fromStdString(ss.str()));
       ui->cat3but->setStyleSheet("background-color: black");
       ui->cat4label->setText(QString::fromStdString(predictions[3].first));
       ss.str(std::string());
       ss << predictions[3].second;
       ui->cat4but->setText(QString::fromStdString(ss.str()));
       ui->cat4but->setStyleSheet("background-color: black");
       ui->cat5label->setText(QString::fromStdString(predictions[4].first));
       ss.str(std::string());
       ss << predictions[4].second;
       ui->cat5but->setText(QString::fromStdString(ss.str()));
       ui->cat5but->setStyleSheet("background-color: black");


    }



}

