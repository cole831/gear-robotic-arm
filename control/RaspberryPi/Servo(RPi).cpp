// Servo movement library
// 9-15-2025 20:47 - 23:54
// 9-16-2025 10:00 - 1:18
// Sebastian Van Deren
// Gavilan GEAR CLUB
// Robotic Arm Project - Servo Control

//Terminology:
// Heading: The curent position of the motars rotation.
//   Defined with directly up being 0 and rotations ranging from -180 to 180 on the counter clockwise and clockwise directions respectively.
// CW = ClockWise
// Var = Variable / Vars = Variables

//Music: https://www.youtube.com/watch?v=oIGPyAgKgBM https://www.youtube.com/watch?v=A02vT-I4Dds https://www.youtube.com/watch?v=9RHFFeQ2tu4
#include <iostream>
using namespace std;

int motorCount = 0; //global variable to keep track of how many variables there are.

float servo_mesure(int id) { // Actual call to specific servo to aquire current rotation, important in-case that torque moves it while not in use. 
    return -20;
    // Cant do until servo motor is selected
}
bool servo_move(int id, float pos) { // Actual call to specific servo to send signals and move it.
    return false;
    // Cant do until servo motor is selected
}

bool servos_reset() {
    cout << "motorCount:" << motorCount << endl; //how many motors are there to cycle through
    int success = 0; 
    for (int i = 1; i < motorCount; i++) {
        if (servo_move(i,0)) // if servo moves add a count to success var
            success += 1;
    }
    if (success == motorCount) { // if success var is equal to # of motors it was successful
        return true;
    } 
    else {
        return false;
    }
}

// use a struct or class for each motor with all these same functions and folwing vars. (Variables)
class ServoMotor {
    public: // Publicly avalible Atributes
        ServoMotor(int num, int CW,int _CW) { // Constructor
            //_ = - in this case and _CW means -CW or Counter Clockwise
            motorIdentifier = num;
            bounds_counterCW = _CW;
            bounds_CW = CW;
            motorCount += 1;
        }
        
        bool allowedAngle(float angle) {
            if ((bounds_counterCW == 360) && (bounds_CW == 360)) {
                return true; // Override (All angle's allowed if both are set to 360)
            }
            if ((bounds_counterCW <= angle) && (angle <= bounds_CW)) { // Check requested angle is in bounds
                //if not (bounds_counterCW > target > bounds_CW){ // If.. I think I got very confused. Was trying to make sure that the bounds were not entered backwards
                //cout << bounds_counterCW << " <= " << angle; // DEBUG
                //cout << " " << angle << " <= " << bounds_CW << " = "; // DEBUG
                return true; 
            }
            return false;
        }
        
        bool movePreciseSafe(float target) { //Move to exact heading and avoids passing into restricted bounds but takes paths avoiding -180/180 degrees (folding in on its self)
            if (allowedAngle(target)) { // EX: target:179 CurHeading:-20 dist:199 allowed:1
                float CurHeading = servo_mesure(motorIdentifier); //Read encoder to aquire curent heading        UNFINISHED
                float dist = target - CurHeading;   // raw difference  
                cout << "target:" << target << " CurHeading:" << CurHeading << " dist:" << dist << " allowed:"; // DEBUG
                //servo_move(motorIdentifier,dist); //                                 UNFINISHED
                return true; // 0 (Unless servo fails somehow) //This is for int returns and error codes, ignore
            }
            else
                return false; // 1 Illegal movement
        }
        
        bool movePrecise(float target) { //Move to exact heading using shortest path and avoids passing into restricted bounds
            if (allowedAngle(target)) { // EX: target:179 CurHeading:-20 dist:-161 allowed:1
                float CurHeading = servo_mesure(motorIdentifier); //Read encoder to aquire curent heading        UNFINISHED
                float dist = target - CurHeading;   // raw difference  
                if (dist > 180) // if over 180 go other way
                    dist -= 360;
                if (dist < -180) // if under -180 go other way
                    dist += 360;
                cout << "target:" << target << " CurHeading:" << CurHeading << " dist:" << dist << " allowed:"; // DEBUG
                //servo_move(motorIdentifier,dist); //                                 UNFINISHED
                return true; // 0 (Unless servo fails somehow) //This is for int returns and error codes, ignore
            }
            else
                return false; // 1 Illegal movement
        }
    
    private: // Individual Atributes
        int motorIdentifier; // Used as an easier way to identfy what motor we are trying to move (Will be numbered bottom to top)
        int bounds_counterCW; // bounds left
        int bounds_CW; // bounds right
};

int main() { 
    ServoMotor motor1(1,180,-180);
    ServoMotor motor2(2,180,-180);
    ServoMotor motor3(3,180,-180);
    ServoMotor motor4(4,180,-180);

    cout << servos_reset();
    /*cout << "movePreciseSafe" << endl;
    cout << motor1.movePreciseSafe(20) << endl;
    cout << motor1.movePreciseSafe(-20) << endl;
    cout << motor1.movePreciseSafe(-90) << endl;
    cout << motor1.movePreciseSafe(90) << endl;
    cout << motor1.movePreciseSafe(270) << endl;
    cout << motor1.movePreciseSafe(360) << endl;
    cout << motor1.movePreciseSafe(91) << endl;
    cout << motor1.movePreciseSafe(179) << endl;
    cout << "movePrecise" << endl;
    cout << motor1.movePrecise(20) << endl;
    cout << motor1.movePrecise(-20) << endl;
    cout << motor1.movePrecise(-90) << endl;
    cout << motor1.movePrecise(90) << endl;
    cout << motor1.movePrecise(270) << endl;
    cout << motor1.movePrecise(360) << endl;
    cout << motor1.movePrecise(91) << endl;
    cout << motor1.movePrecise(179) << endl; */

}
