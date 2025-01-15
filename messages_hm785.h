#pragma once

#include <QObject>

class Messages_HM785 : public QObject
{
	Q_OBJECT
public:	
	Messages_HM785(QObject* parent = nullptr);
	
	unsigned char ack_connect[17] {0x32, 0x42, 0, 0x25}
	;
	unsigned char ack_connect_rtp[17] {0x32, 0x42, 0, 0x05, 0, 0 }
	;
	quint8 ack_heatbeat[6] { 0x32, 0x42, 0, 2, 0, 0 };
	quint8 ack[32] = { 0x32, 0x42, 0x00, 0x21 };
	quint8 disconn[6] = { 0x32, 0x42, 0x00, 0x08, 0x00, 0x00 };
//	quint8 send_command[256] = { 0x32, 0x42, 0, 0, 0, 0 };	
	quint8 conn[12] { 0x7e, 4, 0, 0xfe, 0x20, 0x10, 0, 0, 0, 0x0c, 0x60, 0xe1 };
	// 0x41 0x80 reply
	quint8 ptt_press_req[9] { 2, 0x41, 0, 2, 0, 0x2B, 1, 0, 3 };
	// 41 80
	quint8 ptt_release_req[9] { 2, 0x41, 0, 2, 0, 0x2B, 0, 0, 3 };
	// C4 80 reply
	quint8 zone_ch[12] { 2, 0xC4, 0, 5, 0, 1, 1, 0, 1, 0, 0, 3 };
	// 0x01 0x82 reply
	quint8 radio_info_req[8] { 2, 1, 2, 1, 0, 2, 0, 3 };
	// 52 84
	quint8 radio_id[8] { 2, 0x52, 4, 1, 0, 0, 0, 3 };
	// E4 80
	quint8 key_notific[14] { 2, 0xE4, 0x10, 7, 0, 3, 3, 2, 0x18, 1, 0x19, 1, 0, 3 };
	// 47 88
	quint8 bc_txt_notific[15] { 2, 0x47, 0x18, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 };
	// 19 84
	quint8 rtp_pld[12] { 2, 0x19, 4, 5, 0, 8, 0, 0, 0, 0, 0, 3 };
	// DF 80
	quint8 dig_audio_rx[9] { 2, 0xDF, 0, 2, 0, 1, 1, 0, 3 };
	//DF 8020
	quint8 dig_audio_tx[9]  { 2, 0xDF, 0, 2, 0, 0, 1, 0, 3 };
	// E7 80
	quint8 chan_status[9]    { 2, 0xE7, 0, 2, 0, 7, 0, 0, 3 };
	// broadcast 0xc9 0x80 reply
	quint8 broadcast_req[12]  { 2, 0xc9, 0x10, 5, 0, 2, 0, 1, 1, 1, 0, 3 };

	quint8 status_change_req[14] { 2, 0xc7, 0x10, 7, 0, 3, 1, 1, 5, 1, 6, 1, 0, 3 };

	quint8 analog_broadcast_req[10] { 2, 0x00, 0x1A, 3, 0, 1, 0, 1, 0, 3 };

	quint8 call_req[12] { 2, 0x41, 0x08, 5, 0, 0, 0, 0, 0, 0, 0, 3 };

	quint8 analog_audio_rx[8] { 2, 0xD6, 0, 1, 0, 1, 0, 3 };
	quint8 analog_audio_pgain[10] { 2, 0xDC, 0, 4, 0, 0, 0, 0, 0, 3 };
	quint8 analog_audio_route[10] { 2, 0x10, 0x04, 3, 0, 1, 1, 1, 0, 3 };
	
		
};