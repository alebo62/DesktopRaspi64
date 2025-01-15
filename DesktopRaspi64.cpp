#include "MainWindow.h"
#include <QApplication>
#include <QObject>
#include <QThread>

#include <QDebug>
#include <hidapi/hidapi.h>
#include "Sound.h"
#include "Udp.h"
#include "DataBase.h"
#include "SettingsReader.h"

MainWindow* w;
Sound* sound;
Udp* udp;
DataBase* dbase;
SettingsReader* reader; 

class MyThread : public QThread {
	Q_OBJECT

	public :
	    unsigned char buffer[1];
	void run()
	{

		while (1)
		{
			QThread::msleep(100);
			//hid_read(w->handle, buffer, 1);
			//emit ptt(buffer[0]);
			//qDebug() << buffer[0];
		}
	}

signals:
	void pttKey(int);
};


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	reader = new SettingsReader();
	dbase = new DataBase();
	sound = new Sound();
	udp = new Udp();
	w = new MainWindow;
	MyThread     thread;
	thread.start();
	w->show();
	
	QObject::connect(&thread, SIGNAL(pttKey(int)),
						   w, SLOT(pttKeySlot(int)));
	
	return a.exec();
}

#include "DesktopRaspi64.moc"

