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

namespace cossb {
namespace db {

class sqlite {
public:
	sqlite();
	virtual ~sqlite();
};

} /* naemspace db */
} /* namespace cossb */

#endif /* _COSSB_DB_SQLITE_HPP_ */
