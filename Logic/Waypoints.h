
#ifndef _CGD_WAYPOINTS_H_
#define _CGD_WAYPOINTS_H_

#include <Renderers/IRenderNode.h>
#include <Math/Vector.h>
#include <iostream>
#include <deque>

using namespace std;

using namespace OpenEngine::Renderers;
using namespace OpenEngine::Math;

class Waypoints : public IRenderNode {
private:
    class Waypoint {
    private:
        Vector<3,float> position;
    public:
        Waypoint(Vector<3,float> pos);
        ~Waypoint();
        Vector<3,float> GetWaypoint();
    };
    
    deque<Waypoint> waypoints;

public:

    Waypoints();
    ~Waypoints();
    void AddWaypoint(Vector<3,float> position);
    //deque<Waypoint>* GetWaypoints();
    Waypoint GetNextWaypoint();
    int GetCount();
    void PopWaypoint();
    void Save(ostream* out);
    void Load(istream* in);
    void Clear();
    void Apply(IRenderingView* view);
};

#endif // _CGD_WAYPOINTS_H_
