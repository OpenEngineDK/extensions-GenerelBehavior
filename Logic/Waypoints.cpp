
#include "Waypoints.h"
#include <stdio.h>
#include <Meta/OpenGL.h>

using namespace std;

Waypoints::Waypoints() {

}

Waypoints::~Waypoints() {

}

void Waypoints::AddWaypoint(Vector<3,float> position) {
  waypoints.push_back(Waypoint(position));
}

void Waypoints::Save(ostream* out) {
  *out << "# Waypoint file" << endl;
  for (unsigned int i = 0; i < waypoints.size(); i++) {
    Vector<3,float> waypoint = waypoints[i].GetWaypoint();
    *out << "w " << waypoint[0] << " " << waypoint[1] << " " << waypoint[2];
    if (i < (waypoints.size() - 1)) *out << endl;
  }
}

void Waypoints::Load(istream* in) {
  Clear(); // Clear old data

  if (in->fail()) {
	  cout << "Error accessing waypoint steam!" << endl;
	  return;
  }

  char buf[255];
  int line = 0;

  // for each line in the waypoints file...
  while (!in->eof()) {
    line++;
    in->getline(buf,255);
    if (string(buf,2) == "w ") {
      float x,y,z;
      if (sscanf(buf, "w %f %f %f\n",&x ,&y, &z) != 3) {
        cout << "Error loading waypoints! Line " << line << endl;
      } else {
        AddWaypoint(Vector<3,float>(x,y,z));
      }
    }
  }
}

int Waypoints::GetCount() {
  return waypoints.size();
}


void Waypoints::Clear() {
  waypoints.clear();
}
/*
deque<Waypoint>* Waypoints::GetWaypoints() {
  return &waypoints;
}
*/

Waypoints::Waypoint Waypoints::GetNextWaypoint() {
  return waypoints.front();
}

void Waypoints::PopWaypoint() {
  waypoints.pop_front();
}

void Waypoints::Apply(IRenderingView* view) {
  GLboolean t = glIsEnabled(GL_TEXTURE_2D);
  GLboolean l = glIsEnabled(GL_LIGHTING);
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_LIGHTING);

  glLineWidth(2.0);
  glPointSize(10.0);

  glBegin(GL_LINE_STRIP);
  {
    for(unsigned int i = 0; i < waypoints.size(); i++) {
      glColor3f(1.0, 0.0, (float)(i % 2));
	  float a[3];
	  waypoints[i].GetWaypoint().ToArray(a);
	  glVertex3fv(a);
    }
  }
  glEnd();

  glColor3f(0.0, 0.0, 1.0);
  glBegin(GL_POINTS);
  {
    for(unsigned int i = 0; i < waypoints.size(); i++) {
	  float a[3];
	  waypoints[i].GetWaypoint().ToArray(a);
	  glVertex3fv(a);
    }
  }
  glEnd();

  // reset state
  glColor3f(0.0,0.0,0.0);
  glLineWidth(1.0);
  glPointSize(1.0);

  if (t) glEnable(GL_TEXTURE_2D);
  if (l) glEnable(GL_LIGHTING);
}


Waypoints::Waypoint::Waypoint(Vector<3,float> pos) {
  position = pos;
}

Waypoints::Waypoint::~Waypoint() {

}

Vector<3,float> Waypoints::Waypoint::GetWaypoint() {
  return position;
}


