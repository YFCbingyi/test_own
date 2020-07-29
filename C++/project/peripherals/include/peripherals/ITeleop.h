#ifndef _ITELEOP_H_
#define _ITELEOP_H_

class ITeleop {
	public:
	virtual ~ITeleop(){ }

	virtual void operate(const std::string& action) = 0;
};
#endif
