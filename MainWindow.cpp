#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "QtOpenCVTools.h"
#include <QDebug>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	cameraUse = false;
	ui->setupUi(this);
	QTimer *timer = new QTimer();
	connect(timer, &QTimer::timeout, this, &MainWindow::updateImage);
	timer->start(1);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_pushButton_clicked()
{
	capture.open(0);
	cameraUse = true;
//	JfzStereoImgGet(1);
//	Mat img = imread("E:\\我的坚果云\\头像\\异想家poi(310x310)无手-透明.png");
//	if(img.empty())
//	{
//		qDebug() << "error";
//	}
//	else
//	{
//		//		imshow("bridge", img);
//		qDebug() << "ok";
//		QImage image = MatToQImage(img);
//		ui->label->setGeometry(10, 10, image.width(), image.height());
//		ui->label->setPixmap(QPixmap::fromImage(image));
////		ui->label->setScaledContents(true);
//		//		waitKey();
//	}
}

void MainWindow::updateImage()
{
	if(cameraUse)
	{
		static uint aaa = 0;
		qDebug() << aaa++;
		Mat frame;
		capture >> frame;
		if(frame.data)
		{
			QImage image = MatToQImage(frame);
			ui->label->setGeometry(10, 10, image.width(), image.height());
			ui->label->setPixmap(QPixmap::fromImage(image));
			this->update();  //发送刷新消息
		}
	}
}
