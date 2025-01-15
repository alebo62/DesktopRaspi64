#include  "Udp.h"
#include  <QDebug>
void Udp::call_decoding(void)
{
	if (ba_udp_rcp.at(20) == 1)// voice RX
	{
		//sound_dir = FROM_DIG;
#ifdef DBG
		qDebug() << "rx_tim start";
#endif
		//sound_mic_init();
		//emit(sigcor(1));
		//mb_counter_in = mb_counter_out = 0;
		//snd_pcm_start(handle_mic);
		//rx_tim.start(20);
		if (ba_udp_rcp.at(22) == 1) {
			// group Call
			//sCallReport.callType = 1;
			qDebug() << "gr call init" << rcv_rcp << ((ba_udp_rcp.at(26) << 2) + (ba_udp_rcp.at(25) << 1) + ba_udp_rcp.at(24)) << 
				                       ((ba_udp_rcp.at(30) << 2) + (ba_udp_rcp.at(29) << 1) + ba_udp_rcp.at(28));
		}
		else if (ba_udp_rcp.at(22) == 0) {
			//PrivateCall
			//sCallReport.callType = 3;
			
			
		}
		else if (ba_udp_rcp.at(22) == 2) {
			// AllCall
			//sCallReport.callType = 5;
			
			
		}
		else if (ba_udp_rcp.at(22) == 3) {
			// Emerg Group Call
			//sCallReport.callType = 2;
		}
		else if (ba_udp_rcp.at(22) == 4) {
			// Remote Monitor Call

		}
		else if (ba_udp_rcp.at(22) == 5) {
			// Emerg Alarm

		}
		else if (ba_udp_rcp.at(22) == 9) {
			// Alert Call

		}
//		sCallReport.callState = eCallInit;
//		sCallReport.receivedId[1] = ba_udp_rcp.at(26);
//		sCallReport.receivedId[2] = ba_udp_rcp.at(25);
//		sCallReport.receivedId[3] = ba_udp_rcp.at(24);
//
//		sCallReport.calledId[1] = ba_udp_rcp.at(30);
//		sCallReport.calledId[2] = ba_udp_rcp.at(29);
//		sCallReport.calledId[3] = ba_udp_rcp.at(28);
//
//		if (tcp_srv.state() ==  QAbstractSocket::ConnectedState)
//		{
//			tcp_srv.write(reinterpret_cast<char*>(&sCallReport), sizeof(sCallReport));
//			tcp_srv.flush();
//		}

		//if (sound_dir == FROM_DIG)
		{
			checksum(messagesHm785->ptt_press_req);
			send_command[4] = send_req_id >> 8;
			send_command[5] = send_req_id & 0xFF;
			memcpy(send_command + 6, messagesHm785->ptt_press_req, messagesHm785->ptt_press_req[3] + 7);
			//udp_sock_rcp->writeDatagram((char*)send_command, messagesHm785->ptt_press_req[3] + 7 + 6, QHostAddress(reader->udp_ip[rcv_rcp]), reader->udp_port_rcp);
			// and wait 0x4180 ...
			send_req_id++;
		}
		//fp = popen(cmd, "r");
		//send_voice();

	}
	else if (ba_udp_rcp.at(20) == 2) // HangTime
	{
		
	    //rx_tim.stop();

		//emit(sigcor(0));
		//pclose(fp);
		//snd_pcm_close(handle_mic);
		//free(mic_buffer);
		//sound_mic_init();
//		sCallReport.receivedId[1] = ba_udp_rcp.at(26);
//		sCallReport.receivedId[2] = ba_udp_rcp.at(25);
//		sCallReport.receivedId[3] = ba_udp_rcp.at(24);

		if (ba_udp_rcp.at(22) == 1) {
			// group Call
			//sCallReport.callType = 1;
			qDebug() << "group call hang" ;
		}
		else if (ba_udp_rcp.at(22) == 0) {
			//PrivateCall
			//sCallReport.callType = 3;
		}
		else if (ba_udp_rcp.at(22) == 2) {
			// AllCall
			//sCallReport.callType = 5;

		}
		else if (ba_udp_rcp.at(22) == 3) {
			// Emerg Group Call
			//sCallReport.callType = 2;
		}
		else if (ba_udp_rcp.at(22) == 4) {
			// Remote Monitor Call
//			sCallReport.receivedId[1] = sRegMsgReport.radio_id[1];
//			sCallReport.receivedId[2] = sRegMsgReport.radio_id[2];
//			sCallReport.receivedId[3] = sRegMsgReport.radio_id[3];

		}
		else if (ba_udp_rcp.at(22) == 5) {
			// Emerg Alarm

		}
		else if (ba_udp_rcp.at(22) == 9) {
			// Alert Call

		}
		//if (sound_dir == FROM_DIG)
		{
			checksum(messagesHm785->dig_audio_rx);
			send_command[4] = send_req_id >> 8;
			send_command[5] = send_req_id & 0xFF;
			memcpy(send_command + 6, messagesHm785->dig_audio_rx, messagesHm785->dig_audio_rx[3] + 7);
			//udp_sock_rcp->writeDatagram((char*)send_command, messagesHm785->dig_audio_rx[3] + 7 + 6, QHostAddress(reader->udp_ip[rcv_rcp]), reader->udp_port_rcp);
			//udp_sock_rcp->flush();
			send_req_id++;
		}

//		sCallReport.callState = eCallHandTime;


//		sCallReport.calledId[1] = ba_udp_rcp.at(30);
//		sCallReport.calledId[2] = ba_udp_rcp.at(29);
//		sCallReport.calledId[3] = ba_udp_rcp.at(28);
//		if (tcp_srv.state() ==  QAbstractSocket::ConnectedState)
//		{
//			tcp_srv.write(reinterpret_cast<char*>(&sCallReport), sizeof(sCallReport));
//			tcp_srv.flush();
//		}

		checksum(messagesHm785->ptt_press_req);
		send_command[4] = send_req_id >> 8;
		send_command[5] = send_req_id & 0xFF;
		memcpy(send_command + 6, messagesHm785->ptt_release_req, messagesHm785->ptt_release_req[3] + 7);
		//udp_sock_rcp->writeDatagram((char*)send_command, messagesHm785->ptt_release_req[3] + 7 + 6, QHostAddress(reader->udp_ip[rcv_rcp]), reader->udp_port_rcp);
		// and wait 0x4180 ...
		send_req_id++;
	}
	else if (ba_udp_rcp.at(20) == 3) // CallEnd
	{
		qDebug() << "call end";

		checksum(messagesHm785->dig_audio_tx);
		send_command[4] = send_req_id >> 8;
		send_command[5] = send_req_id & 0xFF;
		memcpy(send_command + 6, messagesHm785->dig_audio_tx, messagesHm785->dig_audio_tx[3] + 7);
		//udp_sock_rcp->writeDatagram((char*)send_command, messagesHm785->dig_audio_tx[3] + 7 + 6, QHostAddress(reader->udp_ip[rcv_rcp]), reader->udp_port_rcp);
		//udp_sock_rcp->flush();
		send_req_id++;

		if (ba_udp_rcp.at(22) == 4)
		{
			// Remote Monitor Call
//			emit(sigcor(0));
//			sCallReport.callType = ePrivCall;
//			sCallReport.calledId[1] = ba_udp_rcp.at(30);
//			sCallReport.calledId[2] = ba_udp_rcp.at(29);
//			sCallReport.calledId[3] = ba_udp_rcp.at(28);
		}
//		if (sCallReport.callState == eCallInit)
//		{
			//emit(sigcor(0));
			//qDebug() << "emit";
//		}
//		sCallReport.callState = eCallEnded;
//		if (tcp_srv.state() ==  QAbstractSocket::ConnectedState)
//		{
//			tcp_srv.write(reinterpret_cast<char*>(&sCallReport), sizeof(sCallReport));
//			tcp_srv.flush();
//		}
	}
	else if (ba_udp_rcp.at(20) == 0 && ba_udp_rcp.at(22) == 5) // emergency alarm
	{
		
	    //32420020 000c8304 000002bd 04010102 (16)44b8 0c00 (20)0000 (22)0500 (24)01000000 (28)3c000000 e803
		//if (emgFlag == 0)
		{
			//emgFlag = 1;
//			emgReportStart[8] =  ba_udp_rcp.at(30);
//			emgReportStart[9]  = ba_udp_rcp.at(29);
//			emgReportStart[10] = ba_udp_rcp.at(28);
//			if (tcp_srv.state() ==  QAbstractSocket::ConnectedState)
//			{
//				tcp_srv.write(reinterpret_cast<char*>(emgReportStart), 11);
//				tcp_srv.flush();
//				qDebug() << "emergency alarm !!!";
//			}
		}
//		else
		{
//			emgFlag = 0;
//			emgReportFinish[8] =  ba_udp_rcp.at(30);
//			emgReportFinish[9]  = ba_udp_rcp.at(29);
//			emgReportFinish[10] = ba_udp_rcp.at(28);
//			if (tcp_srv.state() ==  QAbstractSocket::ConnectedState)
//			{
//				tcp_srv.write(reinterpret_cast<char*>(emgReportFinish), 11);
//				tcp_srv.flush();
//			}
		}
	}
	else  //  unnown call
	{
		qDebug() << "unnown call !!!";
	}
}