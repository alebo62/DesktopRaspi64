#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	
	int res = hid_init();
	
	handle = hid_open(0x1962, 0x1809, NULL);
	if (!handle)
		qDebug() << "unable open";
	else
		qDebug() << "open";

	//hid_close(handle);

	//hid_timer->start(200);

	//res = hid_read(handle, buffer, 1);
	//hid_write(handle, buffer, 1);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ButtonClicked()
{
//    QMessageBox msgBox;
//    msgBox.setText("Hello, World!");
//    msgBox.setWindowTitle("VisualGDB Qt Demo");
//    msgBox.exec();
}


void MainWindow::pttKeySlot(int i)
{
}
