/**
 * @file		message.hpp
 * @brief		Message class using JSON
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 6
 * @details	component message class
 */

#ifndef _COSSB_MESSAGE_HPP_
#define _COSSB_MESSAGE_HPP_

#include <string>
#include <vector>
#include "ext/json.hpp"

using namespace std;

namespace cossb {
namespace broker { class component_broker; }
namespace driver { class component_driver; }
namespace interface { class icomponent; }
namespace message {

enum class msg_type : char {
		DATA = 0x01,
		ERROR,
		ALERT,
		EVENT,
		REQUEST,	//request only should responsible
		RESPONSE
};

enum class msg_target : int {
	ANY = 1,
	ONE
};

/**
 * @brief	serialized message frame
 */
typedef struct _msgframe {
	msg_target target;
	msg_type	type;
	vector<char> encoded_data;
	string pub_topic;
	string from;
} msgframe;


/**
 * @brief	message interface class with json
 */
class message {
	using json = nlohmann::json;

	friend class cossb::broker::component_broker;
	friend class cossb::driver::component_driver;

public:
	message(interface::icomponent* component, msg_type type = msg_type::DATA, msg_target target = msg_target::ANY);
	virtual ~message() { }

	inline json::reference operator[] (const char* k) {
		return this->data[k];
	}

	inline json::const_reference operator[] (const char* k) const {
		return this->data[k];
	}

	string show() {
		return this->data.dump(4);
	}

	void set_topic(const char* topic) { this->frame.pub_topic = topic; }
	void set_type(msg_type type) { this->frame.type = type; }
	cossb::message::msgframe* get_frame() { return &frame; }
	const char* get_topic() { return this->frame.pub_topic.c_str(); }
	const char* get_from() { return this->frame.from.c_str(); }

protected:
	/**
	 * @brief	serialize the json data
	 */
	void serialize() {
		string encode = data.dump();
		std::copy(encode.begin(), encode.end(), std::back_inserter(this->frame.encoded_data));
	}

public:
	json data;

protected:
	cossb::message::msgframe frame;
};

} /* namespace message */
} /* namespace cossb */


#endif /* _COSSB_MESSAGE_HPP_ */
