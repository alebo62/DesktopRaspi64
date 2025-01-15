#include "Udp.h"
#include "SettingsReader.h"

extern SettingsReader* reader;

uint32_t route_cnt = 0;

void Udp::rad_conn_tim_slot()
{
	udp_sock_rcp->writeDatagram((char*)messagesHm785->conn, 12, QHostAddress(reader->udp_ip[rcv_rcp]), reader->udp_port_rcp);
	//udpAN_RCP.writeDatagram((char*)conn, 12, QHostAddress(host), AN_RCP);
	
}

void Udp::radio_init(void)
{
	if (ba_udp_rcp.at(16) == (char)0xC4 && ba_udp_rcp.at(17) == (char)0x80)
	{
#ifdef DBG_RCP
		qDebug() << "zonechan";
#endif
		checksum(messagesHm785->radio_info_req);
		send_command[4] = send_req_id >> 8;
		send_command[5] = send_req_id & 0xFF;
		memcpy(send_command + 6, messagesHm785->radio_info_req, messagesHm785->radio_info_req[3] + 7);
		udp_sock_rcp->writeDatagram((char*)send_command, messagesHm785->radio_info_req[3] + 7 + 6, QHostAddress(reader->udp_ip[rcv_rcp]), reader->udp_port_rcp);
		send_req_id++;
	}
	else if (ba_udp_rcp.at(16) == 0x01 && ba_udp_rcp.at(17) == (char)0x82)
	{
#ifdef DBG_RCP
		qDebug() << "serial num";
#endif \
		    // memcpy(sRegMsgReport.ser_num, "8972HPT115", 10);
//		sRegMsgReport.ser_num[9] = (uint8_t)ba_udp_rcp.at(28);
//		sRegMsgReport.ser_num[8] = (uint8_t)ba_udp_rcp.at(30);
//		sRegMsgReport.ser_num[7] = (uint8_t)ba_udp_rcp.at(32);
//		sRegMsgReport.ser_num[6] = (uint8_t)ba_udp_rcp.at(34);
//		sRegMsgReport.ser_num[5] = (uint8_t)ba_udp_rcp.at(36);
//		sRegMsgReport.ser_num[4] = (uint8_t)ba_udp_rcp.at(38);
//		sRegMsgReport.ser_num[3] = (uint8_t)ba_udp_rcp.at(40);
//		sRegMsgReport.ser_num[2] = (uint8_t)ba_udp_rcp.at(42);
//		sRegMsgReport.ser_num[1] = (uint8_t)ba_udp_rcp.at(44);
//		sRegMsgReport.ser_num[0] = (uint8_t)ba_udp_rcp.at(46);
		checksum(messagesHm785->radio_id);
		send_command[4] = send_req_id >> 8;
		send_command[5] = send_req_id & 0xFF;
		memcpy(send_command + 6, messagesHm785->radio_id, messagesHm785->radio_id[3] + 7);
		udp_sock_rcp->writeDatagram((char*)send_command, messagesHm785->radio_id[3] + 7 + 6, QHostAddress(reader->udp_ip[rcv_rcp]), reader->udp_port_rcp);
		send_req_id++;
	}
	else if (ba_udp_rcp.at(16) == 0x52 && ba_udp_rcp.at(17) == (char)0x84)
	{
#ifdef DBG_RCP
		qDebug() << "radio id";
#endif
//		sRegMsgReport.radio_id[0] = ba_udp_rcp.at(25);
//		sRegMsgReport.radio_id[1] = ba_udp_rcp.at(24);
//		sRegMsgReport.radio_id[2] = ba_udp_rcp.at(23);
//		sRegMsgReport.radio_id[3] = ba_udp_rcp.at(22);
		checksum(messagesHm785->key_notific);
		send_command[4] = send_req_id >> 8;
		send_command[5] = send_req_id & 0xFF;
		memcpy(send_command + 6, messagesHm785->key_notific, messagesHm785->key_notific[3] + 7);
		udp_sock_rcp->writeDatagram((char*)send_command, messagesHm785->key_notific[3] + 7 + 6, QHostAddress(reader->udp_ip[rcv_rcp]), reader->udp_port_rcp);
		send_req_id++;
	}
	else if (ba_udp_rcp.at(16) == (char)0xE4 && ba_udp_rcp.at(17) == (char)0x80)
	{
#ifdef DBG_RCP
		qDebug() << "key notific";
#endif
		checksum(messagesHm785->chan_status);
		send_command[4] = send_req_id >> 8;
		send_command[5] = send_req_id & 0xFF;
		memcpy(send_command + 6, messagesHm785->chan_status, messagesHm785->chan_status[3] + 7);
		udp_sock_rcp->writeDatagram((char*)send_command, messagesHm785->chan_status[3] + 7 + 6, QHostAddress(reader->udp_ip[rcv_rcp]), reader->udp_port_rcp);
		send_req_id++;
	}
	// *************************************************************************************
	else if (ba_udp_rcp.at(16) == (char)0xE7 && ba_udp_rcp.at(17) == (char)0x80) // отсюда начиналось
	{
		//0: conventional digital
		//1: conventional analog
		//                //2: repeater digital
		//                //3: repeater analog
		//                //4: trunking digital
		//                //5: trunking analog
#ifdef DBG_RCP
		qDebug() << "channel status";
#endif
//		if (ba_udp_rcp.at(23) == 1 || ba_udp_rcp.at(23) == 3 || ba_udp_rcp.at(23) == 5)
//			sRegMsgReport.signal_mode = 0;
//		else
//			sRegMsgReport.signal_mode = 1;
		checksum(messagesHm785->broadcast_req);
		send_command[4] = send_req_id >> 8;
		send_command[5] = send_req_id & 0xFF;
		memcpy(send_command + 6, messagesHm785->broadcast_req, messagesHm785->broadcast_req[3] + 7);
		udp_sock_rcp->writeDatagram((char*)send_command, messagesHm785->broadcast_req[3] + 7 + 6, QHostAddress(reader->udp_ip[rcv_rcp]), reader->udp_port_rcp);
		send_req_id++;
	}
	else if (ba_udp_rcp.at(16) == (char)0xC9 && ba_udp_rcp.at(17) == (char)0x80)
	{
#ifdef DBG_RCP
		qDebug() << "broadcast";
#endif
		checksum(messagesHm785->rtp_pld);
		send_command[4] = send_req_id >> 8;
		send_command[5] = send_req_id & 0xFF;
		memcpy(send_command + 6, messagesHm785->rtp_pld, messagesHm785->rtp_pld[3] + 7);
		udp_sock_rcp->writeDatagram((char*)send_command, messagesHm785->rtp_pld[3] + 7 + 6, QHostAddress(reader->udp_ip[rcv_rcp]), reader->udp_port_rcp);
		send_req_id++;

	}
	else if (ba_udp_rcp.at(16) == 0x19 && ba_udp_rcp.at(17) == (char)0x84)
	{
#ifdef DBG_RCP
		qDebug() << "rtp payload";
#endif
		checksum(messagesHm785->dig_audio_rx);
		send_command[4] = send_req_id >> 8;
		send_command[5] = send_req_id & 0xFF;
		//dig_audio_rx[6] = 0;
		memcpy(send_command + 6, messagesHm785->dig_audio_rx, messagesHm785->dig_audio_rx[3] + 7);
		udp_sock_rcp->writeDatagram((char*)send_command, messagesHm785->dig_audio_rx[3] + 7 + 6, QHostAddress(reader->udp_ip[rcv_rcp]), reader->udp_port_rcp);
		send_req_id++;
		//dig_audio_rx[6] = 1;
		//radioInit = true;
		//tcp_conn_tim.start();
		route_cnt = 1;
		//snd_route_timer.start(500);
	}
	else if (ba_udp_rcp.at(16) == (char)0xDF && ba_udp_rcp.at(17) == (char)0x80 && (route_cnt == 1))
	{
		qDebug() << "rx route";
		route_cnt = 2;
		checksum(messagesHm785->dig_audio_tx);
		send_command[4] = send_req_id >> 8;
		send_command[5] = send_req_id & 0xFF;
		//dig_audio_tx[6] = 0;
		memcpy(send_command + 6, messagesHm785->dig_audio_tx, messagesHm785->dig_audio_tx[3] + 7);
		udp_sock_rcp->writeDatagram((char*)send_command, messagesHm785->dig_audio_tx[3] + 7 + 6, QHostAddress(reader->udp_ip[rcv_rcp]), reader->udp_port_rcp);
		send_req_id++;
		//dig_audio_rx[6] = 1;
		//radioInit = true;

	}
	else if (ba_udp_rcp.at(16) == (char)0xDF && ba_udp_rcp.at(17) == (char)0x80 && (route_cnt == 2))
	{

		qDebug() << "tx route";
		route_cnt = 0;

	}
}