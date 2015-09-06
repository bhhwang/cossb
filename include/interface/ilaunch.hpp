/**
 * @file		ilaunch.cpp
 * @brief		utility library launch interface
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 9. 6
 * @details	Launch interface for utility, it is not necessary for only cossb.
 */

#ifndef _COSSB_ILAUNCH_HPP_
#define _COSSB_ILAUNCH_HPP_


namespace cossb {
namespace interface {

class ilaunch {
public:
	ilaunch() { }
	virtual ~ilaunch() {
	}

	/**
	 * @brief	launch interface function
	 * @details	pass all arguments to launch interface, inherited class should control the arguments
	 */
	virtual bool launch(const char* target_util, int argc, char* argv[]) = 0;
};


} /* namespace interfce */
} /* namespace ossb */



#endif /* _COSSB_ILAUNCH_HPP_ */
