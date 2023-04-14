#ifndef __TASKBASE_H__
#define __TASKBASE_H__

/*
	@desc	:	Abstract base class of Callable, actually a functor
*/

namespace nsThreadPool
{
	class Callable
	{
		public:
			virtual void operator() () = 0;
	};
}

#endif //#ifndef __TASKBASE_H__