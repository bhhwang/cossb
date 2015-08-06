/**
 * @file		sqlite.hpp
 * @brief		database class using sqlite
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 7. 29
 * @details	Sqlite database
 */


#ifndef _COSSB_DB_SQLITE_HPP_
#define _COSSB_DB_SQLITE_HPP_

#include <sqlite3.h>
#include "../interface/isql.hpp"

namespace cossb {
namespace db {

class sqlite : public interface::iSQL {
public:
	sqlite();
	virtual ~sqlite();
};

} /* naemspace db */
} /* namespace cossb */

#endif /* _COSSB_DB_SQLITE_HPP_ */
