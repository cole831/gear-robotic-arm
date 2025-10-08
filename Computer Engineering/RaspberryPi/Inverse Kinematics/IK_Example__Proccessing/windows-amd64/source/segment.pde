class segment{ // A segment of the robotic arm. 
  float angle; 
  float len; 
  float wid; 
  float x; 
  float y; 
  float threshold = 0.001; 
  
  segment(float a, float l, float w, float nx, float ny) { 
    angle = a; 
    len = l; 
    wid = w; 
    x = nx; 
    y = ny; 
  } 
  
  void update(float endArmX, float endArmY, float targetX, float targetY){ 
    float angleToEnd = atan2(endArmY-y,endArmX-x); 
    float angleToTarget = atan2(targetY-y,targetX-x); 
    float delta = angleToTarget-angleToEnd; 
    if (delta >= threshold); //If not 
    angle += delta; 
  } 
  
  void display(){ 
    pushMatrix(); 
    translate(x,y); 
    rotate(angle); 
    strokeWeight(wid); 
    line(0,0,len,0); 
    popMatrix(); 
  } 
}
