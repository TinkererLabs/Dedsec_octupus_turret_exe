/*

made by dedsec leader tinkerer to defaet his friend in moral damage by  nerf war
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⣏⠉⠩⠥⢄⡔⠉⢸⣦⠤⠄⢀⣀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⢹⢰⠀⢰⡟⠀⠰⠘⣟⣳⡉⠓⠒⠪⠴⣂⠄⡀⠀⠀
⠀⠀⠀⠀⠀⠈⡄⡆⣦⣿⣾⡻⣿⣾⡿⣃⠀⠀⠀⠀⠀⠈⠉⠲⠄
⠀⠀⠀⠀⠀⠀⠃⢀⡗⣿⡯⡛⢫⣽⣿⢿⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠸⠈⣷⣿⣿⣭⣤⣿⣃⣾⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⢠⠔⢘⣆⢻⣳⡻⣿⣿⡧⠉⠉⡸⠒⣢⡀⠀⠀⠀⠀⠀
⠀⠀⠀⣠⠿⠠⣼⣿⠜⣿⡚⢽⣿⣡⡪⣸⣣⠀⠈⢻⠀⠀⠀⠀⠀
⠀⠀⡔⣇⣤⣶⡟⠙⣧⢫⢚⣲⣿⣿⣗⢊⣤⡶⡄⢈⠇⠀⠀⠀⠀
⠀⢸⠰⢈⣿⣦⡔⣾⣿⣿⠏⢠⣽⠟⡡⠂⢹⣷⠇⢸⠇⠀⠀⠀⠀
⢠⢃⣥⣼⠋⡟⡉⠘⣿⡏⡿⠿⣿⣍⠠⣀⢹⢻⠂⡏⠰⠀⠀⠀⠀
⢸⠊⢉⠌⢸⠱⡴⣷⣾⣿⢰⣾⣀⣀⠨⢋⣿⠀⢴⡇⡄⠀⠀⠀⠀
⠈⠣⣻⠶⠷⠀⢠⠈⣇⢸⡚⣋⣩⠐⠁⣿⣩⣊⠌⢁⡇⠀⠀⠀⠀
⠀⠀⠀⠉⠉⣷⣶⣇⣿⣿⢧⢹⠫⡄⣠⣿⣟⠓⠋⡌⠇⠀⠀⠀⠀
⠀⠀⠀⠀⠀⢹⣹⣿⢿⣿⣿⡜⣽⡟⢸⠟⢠⣴⢢⣿⠀⠀⠀⠀⠀
Join us .............. dedsec in discord https://discord.gg/Pj85XHR4
to be a hacksor shadow arteficer like us
X_X
*/
//a little of help from zzzcode
//-------------------------------libaries
#include <Servo.h>
#include <SoftwareSerial.h>
//-----------setting up all uart connection0--------------------------------//
SoftwareSerial hc12(17,16);
//---------------------------all variables-------------------------//
Servo yaw;
int fireMotor = 3;
int trottleMotor = 5;
int servoPos;
bool fireState;
bool flywheelState;
//-------------------------code start with the 1 core----------------------------//
void setup() {
//-----------------------------all motor and transister connectis-----------/
yaw.attach(9);
pinMode(fireMotor,OUTPUT);
pinMode(trottleMotor,OUTPUT);

}
//----------------------second core start up-------------------------------------//
void setup1(){
//--------------------------beging uart----------------------------------------//
hc12.begin(9600);
}
//--------------------------------core one loob starting--------------------------//
void loop() {
if (rp2040.fifo.available() ==3){
//-------------------------------------fifo core one connection0------------------//
servoPos=int(rp2040.fifo.pop());
flywheelState=bool(rp2040.fifo.pop());
fireState = bool(rp2040.fifo.pop());
//------------------------------------motor set to the uart connection
yaw.write(servoPos);
digitalWrite(trottleMotor,flywheelState);
digitalWrite(fireMotor, fireState);
}
}
//-------------------core two loop-------------------------------------------------------//
void loop1(){
  if (hc12.available() > 0) {
  //-------------------------------reseaving data-----------------------------------------//
    String data = hc12.readStringUntil('\n'); // Read the incoming data until a newline character is encountered
    int servoPos = data.substring(0, data.indexOf(',')).toInt(); // Extract servo position
    bool flywheelState = data.substring(data.indexOf(',') + 1, data.lastIndexOf(',')).toInt(); // Extract flywheel state
    bool fireState = data.substring(data.lastIndexOf(',') + 1).toInt(); // Extract fire state
//-------------------------------------------pusing data by fifo--------------------------------//
    rp2040.fifo.push(servoPos);
    rp2040.fifo.push(flywheelState);
    rp2040.fifo.push(fireState);
    // Now you can use the parsed values (servoPos, flywheelState, fireState) for further processing
  }
}
