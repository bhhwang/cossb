/**
 * @file		libserial.hpp
 * @brief		Serial Communication library
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 25
 * @details	Serial Communication library
 */

#ifndef SUPPORT_COMPSERIAL_LIBSERIAL_HPP_
#define SUPPORT_COMPSERIAL_LIBSERIAL_HPP_

#include <sys/types.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

class libserial {
public:
	libserial();
	virtual ~libserial();

	/**
	 * @brief	open serial port
	 */
	bool open(const char* port, int baudrate);

	/**
	 * @brief	close port
	 */
	void close();

	/**
	 * @brief	write data to opened port
	 * @return	written bytes
	 */
	int write(const char* data, int size);
	int write(const unsigned char* data, int size);

	/**
	 * @brief	read data from the port
	 */
	int read(unsigned char* pdata, int size);

private:
	int _com;
	struct termios _tio;
};


#endif /* SUPPORT_COMPSERIAL_LIBSERIAL_HPP_ */
