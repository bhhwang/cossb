/**
 * @file		mdns_common.hpp
 * @brief		mDNS common header file
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 20
 * @details	Common header file for mDNS
 */

#ifndef _COSSB_LIBCBMDNS_MDNS_COMMON_HPP_
#define _COSSB_LIBCBMDNS_MDNS_COMMON_HPP_

namespace cossb {

/**
 * @brief	mDNS flags
 */
//QR (1 bit) - Query(0), Response(1)
//OPCODE (4 bits) - kind of query
//AA (1 bit) - Authoritative Answer
//TC (1 bit) - TrunCation
//RD (1 bit) - Recursion Desired : this bit directs the name server to pursue the query recursively
//RA (1 bit) - Recursion Available
//Z (3 bits) - Reserved for future use (must be set 0)
//RCODE (4 bits) - Response code : 0(No error), 1(Format error), 2(Server failure), 3(Name Error), 4(Not implemented), 5(Refused)

typedef struct _mDNSHeader {
	unsigned short	id;		//transaction id
	unsigned short	flags;
	unsigned short	qdcount;	//number of entries in the question section
	unsigned short	ancount;	//number of resource records in the answer section
	unsigned short	nscount;	//number of resource records in the authority section
	unsigned short	arcount;	//number of resource records in the additional records section

} mDNSHeader;

typedef struct _mDNSData {

} mDNSData;

typedef struct _mDNSQuestion {

} mDNSQuestion;

typedef struct _mDNSAnswer {

} mDNSAnswer;

typedef struct _mDNSFrame {
	mDNSHeader		header;
	mDNSQuestion	question;
	mDNSAnswer		answer;
	mDNSData		data;
};

} /* namespace cossb */




#endif /* _COSSB_LIBCBMDNS_MDNS_COMMON_HPP_ */
