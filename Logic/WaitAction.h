// Task that encapsulates an behavior tree of tasks.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _WAIT_ACTION_H_
#define _WAIT_ACTION_H_

#include <Logic/Task.h>
#include <Utils/Timer.h>

using namespace OpenEngine::Utils;

namespace OpenEngine {
namespace Logic {

  /**
   *
   */
  class WaitAction : public Task {
  protected:
    bool running;
    double waitTime;
    double waitedTime;
    double lastTime;

  public:
	  WaitAction(double wait) {
		waitTime = wait;
        waitedTime = 0.0;
        lastTime = 0.0;
        running = false;
	  }

	  virtual ~WaitAction() {}

	  virtual TaskStatus Execute() {
        if (!running) {
          waitedTime = 0.0;
          lastTime = Timer::GetTime().AsInt64() / 1000.0;
          running = true;
        }
        double time = Timer::GetTime().AsInt64() / 1000.0;
		waitedTime += time - lastTime;
        lastTime = time;
        if (waitedTime >= waitTime * 1000) {
          running = false;
          return TASK_SUCCESS;
        }
        
        return TASK_RUNNING;
	  }
  };

}
}

#endif // _WAIT_ACTION_H_
