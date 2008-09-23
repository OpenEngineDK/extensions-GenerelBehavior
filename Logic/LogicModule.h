// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _LOGIC_MODULE_H_
#define _LOGIC_MODULE_H_

#include <Logic/BehaviorTree.h>

namespace OpenEngine {
namespace Logic {

  /**
   *
   */
  class LogicModule : public IModule {
  protected:
	BehaviorTree* behave;

  public:
	  LogicModule(BehaviorTree* behavior) { behave = behavior; }
	  virtual ~LogicModule() {}

	  virtual void Handle(InitializeEventArg arg) {}
	  virtual void Handle(ProcessEventArg arg) {
          behave->Execute();
      }

	  virtual void Handle(DeinitializeEventArg arg) {}
  };

}
}

#endif // _LOGIC_MODULE_H_
