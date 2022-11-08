#ifndef INC_TIMERTASK_H_
#define INC_TIMERTASK_H_


class TimerTask
{
public:
	virtual ~TimerTask(){}

	virtual void timerFunc() = 0;
};



#endif /* INC_TIMERTASK_H_ */
