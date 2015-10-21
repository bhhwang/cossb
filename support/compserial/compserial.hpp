/**
 * @file		compserial.hpp
 * @brief		Serial Communication Component
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 25
 * @details	Serial Communication Component for COSSB
 */

#ifndef _COSSB_SUPPORT_COMPONENT_COMPSERIAL_HPP_
#define _COSSB_SUPPORT_COMPONENT_COMPSERIAL_HPP_

#include "../../include/interface.hpp"
#include "libserial.hpp"

using namespace cossb;

class compserial : public interface::icomponent {
public:
	compserial();
	virtual ~compserial();

	bool setup();
	bool run();
	bool stop();
	void request(cossb::message::message* msg) const;

private:
	/**
	 * @brief	receive task process
	 */
	void read_task_proc();

	/**
	 * @brief	received data print
	 */
	void print_hex(unsigned char* data, int len);

private:
	/**
	 * @brief	read task function for incoming data from the opened serial port
	 */
	base::task _read_task;

	/**
	 * @brief	serial communication library instance
	 */
	libserial* _serial = nullptr;
};

COMPONENT_EXPORT

#endif /* _COSSB_SUPPORT_COMPONENT_COMPSERIAL_HPP_ */

