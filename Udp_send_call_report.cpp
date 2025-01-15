#include "Udp.h"

void Udp::send_call_report(void)
{
	if (ba_udp_rcp.at(28) == 1)// press ptt
	{
		checksum(messagesHm785->dig_audio_tx);
		send_command[4] = send_req_id >> 8;
		send_command[5] = send_req_id & 0xFF;
		memcpy(send_command + 6, messagesHm785->dig_audio_tx, messagesHm785->dig_audio_tx[3] + 7);
		udp_sock_rcp->writeDatagram((char*)send_command, messagesHm785->dig_audio_tx[3] + 7 + 6, QHostAddress(reader->udp_ip[rcv_rcp]), reader->udp_port_rcp);
		//udp_sock_rcp->flush();
		send_req_id++;

//		memcpy(sCallReport.calledId, sRegMsgReport.radio_id, 4);// its my id
//		sCallReport.callState = eCallInit;
		//if(tcp_srv.state() ==  QAbstractSocket::ConnectedState)
		{
//		tcp_srv.write(reinterpret_cast<char*>(&sCallReport), sizeof(sCallReport));
//			tcp_srv.flush();
#ifdef DBG
			qDebug() << "callled id" << sCallReport.calledId[3];
			qDebug() << "received id" << sCallReport.receivedId[3];
			qDebug() << "call type" << sCallReport.callType;
			qDebug() << "sendCallRepport";
#endif
		}
//		start_sound = 1;
	}
	else // release ptt
	{
		//sCallStopReply.replyResult = eSucces;
//		if (tcp_srv.state() ==  QAbstractSocket::ConnectedState)
//		{
//			tcp_srv.write(reinterpret_cast<char*>(&sCallStopReply), sizeof(sCallStopReply));
//			tcp_srv.flush();
//		}
	}
}

