#include "Udp.h"

void Udp::press_ptt(void)
{
//	if (sound_dir == FROM_SRV)
//	{
//		sCallReply.requestResult = eSucces;
//		tcp_srv.write(reinterpret_cast<char*>(&sCallReply), sizeof(sCallReply));
//	}
//	// to Digital Radio
//	if (sound_dir == FROM_SRV || sound_dir == FROM_ANL)
//	{
//		checksum(ptt_press_req);
//		send_command[4] = send_req_id >> 8;
//		send_command[5] = send_req_id & 0xFF;
//		memcpy(send_command + 6, ptt_press_req, ptt_press_req[3] + 7);
//		udpRCP_3005.writeDatagram((char*)send_command, ptt_press_req[3] + 7 + 6, QHostAddress(radio_ip), RCP);
//		// and wait 0x4180 ...
//		send_req_id++;
//	}
//	if (sound_dir == FROM_SRV)
//	{
//		// to Analog Radio
//		checksum(ptt_press_req);
//		send_command[4] = send_req_id_an >> 8;
//		send_command[5] = send_req_id_an & 0xFF;
//		memcpy(send_command + 6, ptt_press_req, ptt_press_req[3] + 7);
//		udpAN_RCP.writeDatagram((char*)send_command, ptt_press_req[3] + 7 + 6, QHostAddress(radio_ip_an), AN_RCP);
//		// and wait 0x4180 ...
//		send_req_id_an++;
//	}
}