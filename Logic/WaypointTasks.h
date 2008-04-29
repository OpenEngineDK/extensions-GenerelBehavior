// Task that encapsulates an behavior tree of tasks.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _WAYPOINT_TASKS_H_
#define _WAYPOINT_TASKS_H_

#include <Logic/Task.h>
#include <Utils/Timer.h>

using namespace OpenEngine::Utils;

namespace OpenEngine {
namespace Logic {

  /**
   *
   */
  class MoveToNextWaypointAction : public Task {
  protected:
    Waypoints* waypoints;
	TransformationNode* transNode;

	Vector<3,float> nextWaypoint;
	Vector<3,float> previousWaypoint;

	Vector<3,float> waypointDiff;
	float waypointDist;

	float waypointDt;
    
    double lastTime;
    
    bool running;

  public:
	  MoveToNextWaypointAction(TransformationNode* trans, Waypoints* waypoints) { // TODO: Time is unhandled
		transNode = trans;
		this->waypoints = waypoints;
		//transNode->AddNode(waypoints);
		waypointDt = 0.0;
        lastTime = 0.0;
        running = false;

		if (waypoints->GetCount() > 0) {
			previousWaypoint = transNode->GetPosition();
			nextWaypoint = waypoints->GetNextWaypoint().GetWaypoint();

			waypointDiff =  nextWaypoint - previousWaypoint;
			waypointDist = previousWaypoint.Distance(nextWaypoint);
		}
	  }

	  virtual ~MoveToNextWaypointAction() {}

	  virtual TaskStatus Execute() {
        if (!running) {
          running = true;
          lastTime = Timer::GetTime();
        }
        
		Vector<3,float> position(transNode->GetPosition());
		if (waypointDt < 1.0) {
			MoveTowardsWaypoint();
			return Task::TASK_RUNNING;
		} else {
			waypointDt = 0.0;
			if (waypoints->GetCount() > 1) {
				previousWaypoint = nextWaypoint;
				waypoints->PopWaypoint();
				nextWaypoint = waypoints->GetNextWaypoint().GetWaypoint();

				waypointDiff =  nextWaypoint - previousWaypoint;
				waypointDist = previousWaypoint.Distance(nextWaypoint);
			} else {
				return Task::TASK_FAIL;
			}
            running = false;
			return Task::TASK_SUCCESS;
		}

	  }
	  
	  void MoveTowardsWaypoint() {
        double time = Timer::GetTime();
        double timeDiff = time - lastTime;
        lastTime = time;
		waypointDt += timeDiff * 0.05 / waypointDist;

		transNode->SetPosition(previousWaypoint + waypointDt * waypointDiff);
	  }

  };

  class MoveForwardAction : public Task {
  protected:
    RigidBox* box;

  public:
	  MoveForwardAction(RigidBox* box) {
		this->box = box;
	  }

	  virtual ~MoveForwardAction() {}

	  virtual TaskStatus Execute() {
		Matrix<3,3,float> m = box->GetRotationMatrix(); //orientation
		Vector<3,float> dir = m.GetRow(0) * 10.0;
		box->AddForce(dir, 1);
		box->AddForce(dir, 2);
		box->AddForce(dir, 3);
		box->AddForce(dir, 4);

		return Task::TASK_SUCCESS;
	  }
  };

  class TurnLeftAction : public Task {
  protected:
    RigidBox* box;

  public:
	  TurnLeftAction(RigidBox* box) {
		this->box = box;
	  }

	  virtual ~TurnLeftAction() {}

	  virtual TaskStatus Execute() {
		Matrix<3,3,float> m = box->GetRotationMatrix(); //orientation
		Vector<3,float> dir = -m.GetRow(2) * 5.0;
		box->AddForce(dir, 2);
		box->AddForce(dir, 4);

		return Task::TASK_SUCCESS;
	  }
  };

  class TurnRightAction : public Task {
  protected:
    RigidBox* box;

  public:
	  TurnRightAction(RigidBox* box) {
		this->box = box;
	  }

	  virtual ~TurnRightAction() {}

	  virtual TaskStatus Execute() {
		Matrix<3,3,float> m = box->GetRotationMatrix(); //orientation
		Vector<3,float> dir = m.GetRow(2) * 5.0;
		box->AddForce(dir, 1);
		box->AddForce(dir, 3);

		return Task::TASK_SUCCESS;
	  }
  };

}
}

#endif // _WAYPOINT_TASKS_H_
