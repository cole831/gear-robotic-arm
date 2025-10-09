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
