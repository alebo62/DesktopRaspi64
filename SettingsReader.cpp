#include "SettingsReader.h"
#include <QDebug>

SettingsReader::SettingsReader(QObject* parent)
	: QObject(parent)
{
	udp_num = 2;
	
	udp_ip = new QString[udp_num];
	udp_ip[0] = "192.168.0.140";
	udp_ip[1] = "192.168.0.238";
	
	//udp_port_rtp = new ushort[udp_num];
	udp_port_rtp = 3010;
	udp_port_rcp = 3005;
	
}
	
