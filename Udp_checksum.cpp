#include "Udp.h"

void Udp::checksum(unsigned char *ip)
{
	unsigned char sum_pep = 0;
	unsigned char cnt_pep = 0;
	unsigned char i_pep;// = ip->pep.num_of_bytes[0];

	//int sum = 0; /* assume 32 bit long, 16 bit short */
	//unsigned char* ips = ip;
	int len;// = ip[9];

	//  ip[10] = ip[11] = 0;
	//  if(len == 19)
	//  {
	//    ip[17] = ~(ip[13] + ip[14] + ip[15] + ip[16]) + 0x33;
	//  }
	//  else if(len > 19)
	//  {
	if (ip[0] == 2) // RCP little endian
		i_pep = ip[3];
	else  					// LP TMP big endian
		i_pep = ip[4];
	len = i_pep + 7;
	sum_pep = ip[1] + ip[2] + ip[3] + ip[4];
	while (cnt_pep < i_pep)
		sum_pep += ip[5 + (cnt_pep++)];
	ip[len - 2] = ~sum_pep + 0x33;

	//  }
	//  while( len > 1 )
	//  {
	//    sum += *(reinterpret_cast<unsigned short*>(ip));
	//    ip +=2;
	//    if (sum >>16) /* if high-order bit set, fold */
	//      sum = (sum & 0xFFFF) + (sum>> 16) ;
	//    len -= 2;
	//  }
	//  if ( len ) /* take care of left over byte */
	//  {
	//    unsigned char end[2];
	//    end[0] = * (static_cast<unsigned char*> (ip));
	//    end[1] = 0;
	//    sum += * (reinterpret_cast<unsigned short*>(end));
	//  }
	//  while ( sum >> 16)
	//    sum =(sum & 0xFFFF) + (sum>> 16);
	//  sum = ~sum;
	//  ips[10] = sum & 0xFF;
	//  ips[11] = (sum >> 8) & 0xFF;
}

//Checksum = ~ ( Opcode + # of bytes + Payload ) + 0x33
void Udp::crc(quint8* p, int len)
{
	quint8 sum = 0;
	for (int i = 1; i < (len - 2); i++)
	{
		sum += p[i];
	}
	p[len - 2] = (~sum) + 0x33;
}
