#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QtOpenCVTools.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_pushButton_clicked();
	void updateImage();

private:
	VideoCapture capture;
	bool cameraUse;
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
