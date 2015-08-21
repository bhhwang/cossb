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

typedef struct _mDNSHeader {
	unsigned short	id;		//transaction id
	unsigned short	flags;
	unsigned short	qdcount;
	unsigned short	ancount;
	unsigned short	nscount;
	unsigned short	arcount;

} mDNSHeader;

typedef struct _mDNSData {

} mDNSData;

typedef struct _mDNSFrame {
	mDNSHeader	header;
	mDNSData	data;
};

} /* namespace cossb */




#endif /* _COSSB_LIBCBMDNS_MDNS_COMMON_HPP_ */
