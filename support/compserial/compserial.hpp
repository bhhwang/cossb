/**
 * @file		compserial.hpp
 * @brief		Serial Communication Component
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 25
 * @details	Serial Communication Component for COSSB
 */

#ifndef SUPPORT_COMPSERIAL_COMPSERIAL_HPP_
#define SUPPORT_COMPSERIAL_COMPSERIAL_HPP_

#include "../../include/interface.hpp"
#include "../../include/base/task.hpp"
#include "libserial.hpp"

using namespace cossb;

class compserial : public interface::icomponent {
public:
	compserial();
	virtual ~compserial();

	bool setup();
	bool run();
	bool stop();
	void request(cossb::interface::imessage* msg);

private:
	void read_task_proc();

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

#endif /* SUPPORT_COMPSERIAL_COMPSERIAL_HPP_ */

