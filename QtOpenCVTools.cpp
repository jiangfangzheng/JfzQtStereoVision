#include "QtOpenCVTools.h"
#include <QDebug>
using namespace cv;


cv::Mat QImageToMat(QImage image)
{
	cv::Mat mat;
	switch (image.format())
	{
	case QImage::Format_ARGB32:
	case QImage::Format_RGB32:
	case QImage::Format_ARGB32_Premultiplied:
		mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
		break;
	case QImage::Format_RGB888:
		mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
		cv::cvtColor(mat, mat, CV_BGR2RGB);
		break;
	case QImage::Format_Indexed8:
		mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
		break;
	}
	return mat;
}

QImage MatToQImage(const cv::Mat& mat)
{
	// 8-bits unsigned, NO. OF CHANNELS = 1
	if(mat.type() == CV_8UC1)
	{
		QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
		// Set the color table (used to translate colour indexes to qRgb values)
		image.setColorCount(256);
		for(int i = 0; i < 256; i++)
		{
			image.setColor(i, qRgb(i, i, i));
		}
		// Copy input Mat
		uchar *pSrc = mat.data;
		for(int row = 0; row < mat.rows; row ++)
		{
			uchar *pDest = image.scanLine(row);
			memcpy(pDest, pSrc, mat.cols);
			pSrc += mat.step;
		}
		return image;
	}
	// 8-bits unsigned, NO. OF CHANNELS = 3
	else if(mat.type() == CV_8UC3)
	{
		// Copy input Mat
		const uchar *pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	else if(mat.type() == CV_8UC4)
	{
		qDebug() << "CV_8UC4";
		// Copy input Mat
		const uchar *pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
		return image.copy();
	}
	else
	{
		qDebug() << "ERROR: Mat could not be converted to QImage.";
		return QImage();
	}
}


//左右摄像头载入编号，自己调一下
#define CAML 1
#define CAMR 2

//摄像头尺寸设置
#define WIDTH 352
#define HEIGHT 288

CvCapture *capture1 = NULL, *capture2 = NULL; //capture1为left, capture2为right
//Mat  imageLeft;
//Mat  imageRight;
IplImage* imageLeft;
IplImage* imageRight;

int cnt = 1;//拍照图片计数
char Leftname[25];//生成图像文件名
char Rightname[25];

bool JfzStereoImgGet(unsigned int cameraNum)
{
	if(cameraNum == 0)
		return true;
	if(cameraNum == 1)
	{
		VideoCapture capture(0);
		while (1)
		{
			Mat frame;
			capture >> frame;
			imshow("读取视频", frame);
			char c = cvWaitKey(30);
			if (c == 27)
			{
				break;
			}
		}
		//载入摄像头
//		capture1 = cvCaptureFromCAM(0);
//		cvCreateCameraCapture();
//		assert(capture1 != NULL);
//		//设置画面尺寸 WIDTH、HEIGHT在宏定义中改
//		cvSetCaptureProperty(capture1, CV_CAP_PROP_FRAME_WIDTH, WIDTH);
//		cvSetCaptureProperty(capture1, CV_CAP_PROP_FRAME_HEIGHT, HEIGHT);
//		qDebug() << "视频分辨率设置为：" << WIDTH << " x " << HEIGHT << endl;
		imageLeft = cvQueryFrame(capture1);
		qDebug() << "视频分辨率设置为：" << imageLeft->width << " x " << imageLeft->height << endl;
//		while (true)
//		{
//			imageLeft = cvQueryFrame(capture1);
//			imshow("Left", Mat(cvarrToMat(imageLeft)));
//			char c = waitKey(100);
//			if (c == '1') //按'g'保存照片
//			{
//				//			sprintf(Leftname, "stereoData\\Left%02d.jpg", cnt);
//				//			sprintf(Rightname, "stereoData\\Right%02d.jpg", cnt);
//				//			imwrite(Leftname, imageLeft);
//				//			imwrite(Rightname, imageRight);
//				cnt++;
//				qDebug() << Leftname <<" 和 "<<Rightname << " 保存成功！" << endl;
//			}
//			if (c == 27) //按ESC键退出
//				return true;
//		}
	}
	if(cameraNum == 2)
	{
		//载入摄像头
		capture1 = cvCaptureFromCAM(CAML);
		assert(capture1 != NULL);
		cvWaitKey(100);
		capture2 = cvCaptureFromCAM(CAMR);
		assert(capture2 != NULL);

		//设置画面尺寸 WIDTH、HEIGHT在宏定义中改
		cvSetCaptureProperty(capture1, CV_CAP_PROP_FRAME_WIDTH, WIDTH);
		cvSetCaptureProperty(capture1, CV_CAP_PROP_FRAME_HEIGHT, HEIGHT);
		cvSetCaptureProperty(capture2, CV_CAP_PROP_FRAME_WIDTH, WIDTH);
		cvSetCaptureProperty(capture2, CV_CAP_PROP_FRAME_HEIGHT, HEIGHT);

		qDebug() << "视频分辨率设置为：" << WIDTH << " x " << HEIGHT << endl;

		imageLeft = cvQueryFrame(capture1);
		imageRight = cvQueryFrame(capture2);

		while (true)
		{
			imageLeft = cvQueryFrame(capture1);
			imageRight = cvQueryFrame(capture2);
			imshow("Left", Mat(cvarrToMat(imageLeft)));
			imshow("Right", Mat(cvarrToMat(imageRight)));
			char c = waitKey(100);
			if (c == '1') //按'g'保存照片
			{
				//			sprintf(Leftname, "stereoData\\Left%02d.jpg", cnt);
				//			sprintf(Rightname, "stereoData\\Right%02d.jpg", cnt);
				//			imwrite(Leftname, imageLeft);
				//			imwrite(Rightname, imageRight);
				cnt++;
				qDebug() << Leftname <<" 和 "<<Rightname << " 保存成功！" << endl;
			}
		}
		char c = waitKey();
		if (c == 27) //按ESC键退出
			return true;
	}
}
