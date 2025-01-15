#pragma once

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include "messages_hm785.h"
#include "SettingsReader.h"

extern SettingsReader* reader;

class Udp : public QObject
{
	Q_OBJECT
	
		Messages_HM785* messagesHm785;
//	qint8 ack_connect_rtp[17] = { 0x32, 0x42, 0, 0x05, 0, 0 };
//	qint8 ack_heatbeat[6] = { 0x32, 0x42, 0, 2, 0, 0 };
//	qint8 ack[32] = { 0x32, 0x42, 0x00, 0x21 };
	quint8 send_command[256] = { 0x32, 0x42, 0, 0, 0, 0 };	
	quint8 conn[12] { 0x7e, 4, 0, 0xfe, 0x20, 0x10, 0, 0, 0, 0x0c, 0x60, 0xe1 };
	QTimer* radioConn_tim;
	quint32 rcv_rcp;
	quint32 rcv_rtp;
	QByteArray ba_udp_rtp;
	QByteArray ba_udp_rcp;
	uint16_t send_req_id = 0;
	uint16_t rcp_req_id = 0;
	uint32_t connection;
	void checksum(unsigned char *ip);
	void crc(quint8* p, int len);
	void radio_init();	
	void send_reply(int req_type);
	void press_ptt();
	void call_decoding();
	
	void send_call_report();
		
public:
	explicit Udp(QObject *parent = nullptr);
	
	//  До четырех направлений
	//QUdpSocket* udp_sock[4];
	QUdpSocket* udp_sock_rtp;
	QUdpSocket* udp_sock_rcp;
	
	private slots :
		void readPendDgrmRtp();
		void readPendDgrmRcp();
	void rad_conn_tim_slot();
	
	
};