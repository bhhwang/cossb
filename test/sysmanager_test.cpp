#include <gtest/gtest.h>

#include "../include/manager.hpp"

class system_manager_test : public ::testing::Test {

public:
	system_manager_test() { }
	virtual ~system_manager_test() { }

	/**
	 * @details	virtual void SetUp() will be called before each test is run
	 */
	void SetUp() {
		cossb_system_manager;
		manager = cossb_system_manager->instance();
	}

	/**
	 * @details	virtual void TearDown() will be called after each test is run.
	 */
	void TearDown() {
		cossb_system_manager->destroy();
	}

protected:
	cossb::manager::system_manager* manager = nullptr;

};

TEST_F(system_manager_test, system_manager_test1)
{
	EXPECT_NE(nullptr, cossb_system_manager);
}
