/**
 * @file		imessage.hpp
 * @brief		Message Interface class
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 6
 * @details	component message interface class
 */

#ifndef _COSSB_INTERFACE_IMESSAGE_HPP_
#define _COSSB_INTERFACE_IMESSAGE_HPP_

#include <msgpack.hpp>
#include <string>
#include <vector>

using namespace std;

namespace cossb {
namespace message {

typedef std::vector<char>	message;

template<typename msgType>
inline void pack(message* msg, const msgType& data)
{
	msgpack::sbuffer _buffer;
	msgpack::pack(_buffer, data);
	msg->clear();
	msg->assign(_buffer.data(), _buffer.data()+_buffer.size());
}

template<typename msgType>
inline bool unpack(msgType* data, const message& msg)
{
	try {
		msgpack::sbuffer _buffer;
		msgpack::unpacked _unpack_msg;

		msgpack::unpack(&_unpack_msg, msg.data(), msg.size());
		msgpack::object obj = _unpack_msg.get();
		obj.convert(data);
	}
	catch(std::exception& e) {

	}
	return false;
}

} /* namespace message */

namespace interface {

class imessage {
public:
	virtual ~imessage() { }

};

} /* namespace interface */
} /* namespace cossb */


#endif /* _COSSB_INTERFACE_IMESSAGE_HPP_ */
