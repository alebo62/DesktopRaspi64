#include "Udp.h"
#include <QDebug>



Udp::Udp(QObject *parent)
	: QObject(parent)
{
	messagesHm785 = new Messages_HM785();
	
	radioConn_tim = new QTimer();
	connect(radioConn_tim, SIGNAL(timeout()), this, SLOT(rad_conn_tim_slot()));
	radioConn_tim->setInterval(1000);
	
	udp_sock_rtp = new QUdpSocket();
	udp_sock_rtp->bind(QHostAddress("192.168.0.132"), reader->udp_port_rtp);
	//connect(udp_sock_rtp, SIGNAL(readyRead()), this, SLOT(readPendDgrmRtp()));
	
	udp_sock_rcp = new QUdpSocket();
	udp_sock_rcp->bind(QHostAddress("192.168.0.132"), reader->udp_port_rcp);
	connect(udp_sock_rcp, SIGNAL(readyRead()), this, SLOT(readPendDgrmRcp()));
}


QByteArray ba_udp_test = { "hello" };
void Udp::readPendDgrmRtp()
{
	int rcv_rtp;
	QHostAddress ha;
	ushort port;
	
	ba_udp_rtp.resize((int)udp_sock_rtp->pendingDatagramSize());
	udp_sock_rtp->readDatagram(ba_udp_rtp.data(), ba_udp_rtp.size(), &ha, &port);
	
	for (rcv_rtp = 0; rcv_rtp < reader->udp_num; rcv_rtp++)
		if (QHostAddress(reader->udp_ip[rcv_rtp]) == ha)
			break;
	
	
	if (ba_udp_rtp.at(3) ==  0x24) // connect request
	{
		qDebug() << "rtp connect";
		memcpy((char*)messagesHm785->ack_connect + 4, ba_udp_rtp.data() + 4, 13);
		messagesHm785->ack_connect[12] = 0x04;
		udp_sock_rtp->writeDatagram((char*) messagesHm785->ack_connect_rtp, 15, QHostAddress(reader->udp_ip[rcv_rtp]), reader->udp_port_rtp);
		udp_sock_rtp->flush();
	}
	else if (ba_udp_rtp.at(3) == 0x02) // heatbeat
	{
		qDebug() << "rtp heatbeat";
		udp_sock_rtp->writeDatagram((char*) messagesHm785->ack_heatbeat, 6, QHostAddress(reader->udp_ip[rcv_rtp]), reader->udp_port_rtp);
		udp_sock_rtp->flush();
	}
	else 
	{
		
//		if (udp_srv)
//		{
//		
//		}
		//sound_tim.start(); // 15msec timer
	}
	//udp_sock[rcv]->writeDatagram(ba_udp_test, QHostAddress(reader->udp_ip[rcv]), RTP_PORT);
	//udp_sock[rcv]->flush();

	//qDebug() << "udp rtp rx: " << rcv << ba_udp_rtp.size();
}


QByteArray ba_udp_tst = { "hello" };
void Udp::readPendDgrmRcp()
{
	
	QHostAddress ha;
	ushort port;
	
	ba_udp_rcp.resize((int)udp_sock_rcp->pendingDatagramSize());
	udp_sock_rcp->readDatagram(ba_udp_rcp.data(), ba_udp_rcp.size(), &ha, &port);
	
	for (rcv_rcp = 0; rcv_rcp < reader->udp_num; rcv_rcp++)
		if (QHostAddress(reader->udp_ip[rcv_rcp]) == ha)
			break;
	
	if (ba_udp_rcp.at(3) == 0x02) // heatbeat
	{
		if (connection == 2)
		{
			udp_sock_rcp->writeDatagram((char*) messagesHm785->ack_heatbeat, 6, QHostAddress(reader->udp_ip[rcv_rcp]), reader->udp_port_rcp);
			//radioConn_tim.start();
		}
		else if (connection == 1)
		{
			connection = 2;
			checksum(messagesHm785->zone_ch);
			send_command[4] = send_req_id >> 8;
			send_command[5] = send_req_id & 0xFF;
			memcpy(send_command + 6, messagesHm785->zone_ch, messagesHm785->zone_ch[3] + 7);
			udp_sock_rcp->writeDatagram((char*)send_command, messagesHm785->zone_ch[3] + 7 + 6, QHostAddress(reader->udp_ip[rcv_rcp]), reader->udp_port_rcp);
			send_req_id++;
		}
		else if (connection == 0)
		{
			udp_sock_rcp->writeDatagram((char*)messagesHm785->disconn, 6, QHostAddress(reader->udp_ip[rcv_rcp]), reader->udp_port_rcp);
		}
	}
	else if (ba_udp_rcp.at(3) & 0x01)// its ack
	{
		rcp_req_id = ((quint16)ba_udp_rcp.at(4) << 8) + (quint16)ba_udp_rcp.at(5);
	}
	else if (ba_udp_rcp.at(3) == 0x20 || ba_udp_rcp.at(3) == 0x00)
	{
		if (ba_udp_rcp.at(3) == 0x20)
		{
			if (ba_udp_rcp.at(6) == (char)0x83 && ba_udp_rcp.at(7) == 0x04 && ba_udp_rcp.at(12) == 0x04 && ba_udp_rcp.at(13) == 0x01)
			{
				memcpy((char*)messagesHm785->ack, ba_udp_rcp.data(), 15);
				messagesHm785->ack[3] = 0x21;
				udp_sock_rcp->writeDatagram((char*)messagesHm785->ack, 15, QHostAddress(reader->udp_ip[rcv_rcp]), reader->udp_port_rcp);
				udp_sock_rcp->flush();
				// receive
				if (ba_udp_rcp.at(16) == 0x44 && ba_udp_rcp.at(17) == (char)0xB8) {
					//                    checksum(dig_audio_rx);
					//                    send_command[4] = send_req_id >> 8;
					//                    send_command[5] = send_req_id & 0xFF;
					//                    memcpy(send_command + 6, dig_audio_rx, dig_audio_rx[3] + 7);
					//                    udp_sock_rcp->writeDatagram((char*)send_command, dig_audio_rx[3] + 7 + 6, QHostAddress(radio_ip), RCP);
					//                    udp_sock_rcp->flush();
					//                    send_req_id++;
					call_decoding();
				}
				// server initiated call
				else if ((ba_udp_rcp.at(16) == 0x41) && (ba_udp_rcp.at(17) == (char)0x88))
					press_ptt();
				else if ((ba_udp_rcp.at(16) == 0x41) && (ba_udp_rcp.at(17) == (char)0x80))
					send_call_report();
				else if ((ba_udp_rcp.at(16) == 0x43) && (ba_udp_rcp.at(17) == (char)0xB8))
				{
					if (ba_udp_rcp.at(20) == 2)
					{
						//qDebug() << "ptt reply";
//						sCallReport.callType = CallsDecoder[static_cast<uint>(ba_udp_rcp.at(24))];
//						sCallReport.callState = eCallHandTime;
//						memcpy(&sCallReport.calledId, &sRegMsgReport.radio_id, 4);
//						sCallReport.receivedId[3] = ba_udp_rcp.at(26);
//						sCallReport.receivedId[2] = ba_udp_rcp.at(27);
//						sCallReport.receivedId[1] = ba_udp_rcp.at(28);
//						if (tcp_srv.state() ==  QAbstractSocket::ConnectedState)
//						{
//							tcp_srv.write(reinterpret_cast<char*>(&sCallReport), sizeof(sCallReport));
//							tcp_srv.flush();
//						}
						//Radio_Reg_State = WAIT_STOP_CALL_ENDED;
//#ifdef DBG
//						qDebug() << "WAIT_STOP_CALL_HANGIN";
//#endif
					}
					else if (ba_udp_rcp.at(20) == 3)
					{
//						sCallReport.callType = CallsDecoder[static_cast<uint>(ba_udp_rcp.at(24))];
//						sCallReport.callState = eCallEnded;
//						memcpy(sCallReport.calledId, sRegMsgReport.radio_id, 4);
//						sCallReport.receivedId[3] = ba_udp_rcp.at(26);
//						sCallReport.receivedId[2] = ba_udp_rcp.at(27);
//						sCallReport.receivedId[1] = ba_udp_rcp.at(28);
//						if (tcp_srv.state() ==  QAbstractSocket::ConnectedState)
//						{
//							tcp_srv.write(reinterpret_cast<char*>(&sCallReport), sizeof(sCallReport));
//							tcp_srv.flush();
//						}
						//Radio_Reg_State = READY;
#ifdef DBG
						qDebug() << "WAIT_STOP_CALL_ENDED";
#endif
					}
				}
				else if ((ba_udp_rcp.at(16) == 0x49) && (ba_udp_rcp.at(17) == (char)0x88)) // replay radio disable
				{
					// result [20]          // ip[24-21]
					send_reply(1);
				}
				else if ((ba_udp_rcp.at(16) == 0x4A) && (ba_udp_rcp.at(17) == (char)0x88)) // replay radio enblbe
				{
					// result [20]                    // ip[24-21]
					send_reply(2);
				}
				else if ((ba_udp_rcp.at(16) == 0x33) && (ba_udp_rcp.at(17) == (char)0x88)) // replay check radio
				{
					// result [20]                    // ip[24-21]
					send_reply(0);

				}
				else if ((ba_udp_rcp.at(16) == 0x34) && (ba_udp_rcp.at(17) == (char)0x88)) // replay monitor
				{
					// result [20]                    // ip[24-21]
					send_reply(3);
				}
				else
				{
					radio_init();
				}
			}
			else 
			{
				qDebug() << "Length wrong!!!! " << ba_udp_rcp.toHex();
			}
		}
		else 
		{
			memcpy((char*)messagesHm785->ack, ba_udp_rcp.data(), 6);
			messagesHm785->ack[3] |= 0x01;
			udp_sock_rcp->writeDatagram((char*) messagesHm785->ack, 6, QHostAddress(reader->udp_ip[rcv_rcp]), reader->udp_port_rcp);
			udp_sock_rcp->flush();
		}		
	}
	else if (ba_udp_rcp.at(3) ==  0x24) // connect request
	{
		qDebug() << "rcp conn req";
		memcpy((char*)messagesHm785->ack_connect + 4, ba_udp_rcp.data() + 4, 11);
		udp_sock_rcp->writeDatagram((char*) messagesHm785->ack_connect, 15, QHostAddress(reader->udp_ip[rcv_rcp]), reader->udp_port_rcp);
	}
	else if(ba_udp_rcp.at(3) ==  0x28) // disconnect request
	{
		memcpy((char*)messagesHm785->ack_connect + 4, ba_udp_rcp.data() + 4, 11);
		udp_sock_rcp->writeDatagram((char*) messagesHm785->ack_connect, 15, QHostAddress(reader->udp_ip[rcv_rcp]), reader->udp_port_rcp);
		connection = 0;
	}
	//qDebug() << "udp rx: " << rcv << ba_udp_rcp.size();
}

void Udp::send_reply(int req_type)
{
//	sCtrlReply.result = ba_3005.at(20);
//	sCtrlReply.radio_id[3] = ba_3005.at(21);
//	sCtrlReply.radio_id[2] = ba_3005.at(22);
//	sCtrlReply.radio_id[1] = ba_3005.at(23);
//	sCtrlReply.req_type = req_type;//
//	if (tcp_srv.state() ==  QAbstractSocket::ConnectedState)
//	{
//		tcp_srv.write(reinterpret_cast<char*>(&sCtrlReply), sizeof(sCtrlReply));
//		tcp_srv.flush();
//	}
}