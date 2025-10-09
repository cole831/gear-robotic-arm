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
