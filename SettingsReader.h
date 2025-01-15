#pragma once

#include <QFile>
#include <QObject>


class SettingsReader: public QObject
{
	Q_OBJECT
		
public: explicit SettingsReader(QObject* parent = nullptr);
	
	int udp_num;
	QString* udp_ip;
	ushort udp_port_rtp;
	ushort udp_port_rcp;	
	
};