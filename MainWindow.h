#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <hidapi/hidapi.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	QTimer* hid_timer;
	hid_device *handle;


protected slots:
    void ButtonClicked();

private:
    Ui::MainWindow *ui;
	
	public slots :
		void pttKeySlot(int );
};

#endif // MAINWINDOW_H
