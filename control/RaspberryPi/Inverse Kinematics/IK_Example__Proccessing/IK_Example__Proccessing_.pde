limb l1;

void setup(){
    size(800,1000); //Drawing window
    l1 = new limb();
}

void draw(){
    background(200);
    l1.update();
    l1.display();
}
