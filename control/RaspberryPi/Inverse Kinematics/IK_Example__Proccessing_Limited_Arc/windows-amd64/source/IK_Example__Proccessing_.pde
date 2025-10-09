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
