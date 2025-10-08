// IK movement library
// 9-22-2025 12:01 - 8:25
// 9-23-2025 4:45 - 5:55
// 
// Sebastian Van Deren
// Gavilan GEAR CLUB
// Robotic Arm Project - Arm Inverse Kinematics

//Terminology:
// Heading: The curent position of the motars rotation.
//   Defined with directly up being 0 and rotations ranging from -180 to 180 on the counter clockwise and clockwise directions respectively.
// CW = ClockWise
// Var = Variable / Vars = Variables
// IK = Inverse Kinematics

// Base code started from https://www.youtube.com/watch?v=GUF3Qr9C7eY

//C++ Adaptation Start

#include <iostream>
#include <cmath>
using namespace std;

//C++ Adaptation End

//IK EXAMPLE PROCCESSING
limb l1;

void setup(){
    println("0°:", degToRad(0));      // should be -1.570796 (up)
    println("-90°:", degToRad(-90));  // should be -3.14159 (left)
    println("90°:", degToRad(90));    // should be 0.0 (right)
    size(800,1000); //Drawing window
    l1 = new limb();
}

void draw(){
    background(200);
    l1.update();
    l1.display();
}


//SEGMENT

class segment {
  float angle;
  float len;
  float wid;
  float x;
  float y;
  float threshold = 0.0001;
  float minAngle;
  float maxAngle;

  // constructor now takes limits
  segment(float a, float l, float w, float nx, float ny,
          float minA, float maxA) {
    angle = a;
    len = l;
    wid = w;
    x = nx;
    y = ny;
    minAngle = minA;
    maxAngle = maxA;
  }

  void update(float endArmX, float endArmY, float targetX, float targetY) {
    float angleToEnd = atan2(endArmY - y, endArmX - x);
    float angleToTarget = atan2(targetY - y, targetX - x);
    float delta = angleToTarget - angleToEnd;

    // normalize delta to -PI..PI
    while (delta > PI)  delta -= TWO_PI;
    while (delta <= -PI) delta += TWO_PI;

    if (abs(delta) > threshold) {
      angle += delta;

      // **clamp** after updating
      if (angle < minAngle) angle = minAngle;
      if (angle > maxAngle) angle = maxAngle;
    }
  }

  void display() {
    pushMatrix();
    translate(x, y);
    rotate(angle);
    strokeWeight(wid);
    line(0, 0, len, 0);
    popMatrix();
  }
}

// LIMB
float degToRad(float deg) {
  // 0° = up, negative = CCW from up
  // so internal radians = - (deg + 90) * PI/180
  return radians(deg) - HALF_PI;
}

class limb {
  float x, y;
  float endX, endY;
  ArrayList<segment> segments;
  int numSegments;

  limb(){
    segments = new ArrayList<segment>();
    x = width * 0.5;
    y = height * 0.5;
    numSegments = 4;
    for (int i = 0; i < numSegments; i++){
      // angle, length, width, start x, start y
      float len = map(i, 0, max(1, numSegments-1), 50, 150);
      float wid = map(i, 0, max(1, numSegments-1), 20, 4);
      segments.add(new segment(0, len, wid, x, y,degToRad(-150),degToRad(150)));
    }
    // initialize forward positions
    segments.get(0).x = x;
    segments.get(0).y = y;
    for (int j = 1; j < segments.size(); j++){
      segment p = segments.get(j-1);
      segment c = segments.get(j);
      c.x = p.x + p.len * cos(p.angle);
      c.y = p.y + p.len * sin(p.angle);
    }
  }

  void display(){
    for (segment s : segments){
      s.display();
    }
  }

  void update(){
    // 1) forward pass to ensure positions are up-to-date (base anchored)
    segments.get(0).x = x;
    segments.get(0).y = y;
    for (int i = 1; i < segments.size(); i++){
      segment prev = segments.get(i-1);
      segment cur  = segments.get(i);
      cur.x = prev.x + prev.len * cos(prev.angle);
      cur.y = prev.y + prev.len * sin(prev.angle);
    }

    // 2) backward CCD pass
    for (int i = segments.size() - 1; i >= 0; i--){
      // recompute current tip (end effector) from current angles/positions
      segment tip = segments.get(segments.size() - 1);
      float tipX = tip.x + tip.len * cos(tip.angle);
      float tipY = tip.y + tip.len * sin(tip.angle);

      segment s = segments.get(i);
      // rotate this segment to bring tip closer to mouse
      s.update(tipX, tipY, mouseX, mouseY);

      // after changing this segment, forward-update all downstream children
      for (int j = i + 1; j < segments.size(); j++){
        segment prev = segments.get(j-1);
        segment cur  = segments.get(j);
        cur.x = prev.x + prev.len * cos(prev.angle);
        cur.y = prev.y + prev.len * sin(prev.angle);
      }
    }
  }
}