// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _TIMED_TASK_H_
#define _TIMED_TASK_H_

#include <Logic/Task.h>
#include <Utils/Timer.h>

using namespace OpenEngine::Utils;

namespace OpenEngine {
namespace Logic {

  /**
   *
   */
  class TimedTask : public Task {
  protected:
    bool running;
    double lastTime;
    double totalTime;

  public:
	  TimedTask() : Task() {
        lastTime  = 0.0;
        totalTime = 0.0;
        running   = false;
	  }

	  virtual ~TimedTask() {}

	  virtual TaskStatus Execute() {
        if (!running) {
          totalTime = 0.0;
          lastTime  = Timer::GetTime().AsInt64() / 1000.0;
          running   = true;
          Start();
        }
        
        double time   = Timer::GetTime().AsInt64() / 1000.0;
		double timeDt = time - lastTime;
		totalTime    += timeDt;
        lastTime      = time;
       
        TaskStatus status = Execute(timeDt, totalTime);
        
        if (status != TASK_RUNNING) {
			running = false;
			End();
		}
		
		return status;
	  }
	  
	  virtual TaskStatus Execute(double timeDt, double totalTime) = 0;
	  virtual void Start() {};
	  virtual void End() {};
  };

}
}

#endif // _TIMED_TASK_H_
