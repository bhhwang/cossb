/*
 * uuid.hpp
 *
 *  Created on: 2015. 10. 13.
 *      Author: hwang
 */

#ifndef INCLUDE_UTIL_UUID_HPP_
#define INCLUDE_UTIL_UUID_HPP_

#include <uuid/uuid.h>
#include <string>

using namespace std;

namespace cossb {
namespace util {

typedef struct _uuid {

public:
	_uuid() {
		uuid_generate(code);
		memset(encoded, 0x00, sizeof(encoded));
		uuid_unparse_lower(code, encoded);
	}

	_uuid(string suuid) {
		std::transform(suuid.begin(), suuid.end(), suuid.begin(), ::tolower);
		if(suuid.size()==32) {
			for(int i=0;i<(int)sizeof(code);i++) {
				char t = suuid.at(i);
				if(t>96 && t<103)
					code[i] = t-86;
				else if(t>47 && t<58)
					code[i] = t-48;
				else {
					memset(code, 0x30, sizeof(code));
					break;
				}
			}

		}
		else
			memset(code, 0x30, sizeof(code));

		memset(encoded, 0x00, sizeof(encoded));
		uuid_unparse_lower(code, encoded);

	}

	const char* str() { return (const char*)encoded; }

	bool operator<(const _uuid& other) const {
		return (uuid_compare(this->code, other.code)<0)?true:false;
	}

	bool operator>(const _uuid& other) const {
		return (uuid_compare(this->code, other.code)>0)?true:false;
	}

	bool operator==(const _uuid& other) const {
		return (uuid_compare(this->code, other.code)==0)?true:false;
	}

	_uuid& operator=(const _uuid& other) {
		memcpy(this, &other, sizeof(_uuid));
		return *this;
	}

private:
	bool valid() { return true; }

private:
	unsigned char code[16];
	char encoded[64];
} uuid;

} /* namespace util */
} /* namespace cossb */



#endif /* INCLUDE_UTIL_UUID_HPP_ */
