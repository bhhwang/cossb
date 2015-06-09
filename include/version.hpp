/*
 * version.hpp
 *
 * Author : Byunghun Hwang<bhhwang@nsynapse.com>
 * Date : 2015. 6. 9
 */

#ifndef _COSSB_VERSION_HPP_
#define _COSSB_VERSION_HPP_

#define COSSB_VERSION_MAJOR	0
#define COSSB_VERSION_MINOR	0
#define COSSB_VERSION_REV	1

#define VERSION_STR(x) #x
#define COSSB_VERSION_SET(major, minor, rev)	VERSION_STR(major) "." VERSION_STR(minor) "." VERSION_STR(rev)
#define COSSB_VERSION	COSSB_VERSION_SET(COSSB_VERSION_MAJOR, COSSB_VERSION_MINOR, COSSB_VERSION_REV)


#endif /* _COSSB_VERSION_HPP_ */


