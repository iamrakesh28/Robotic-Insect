#include <Servo.h> 

void forward_transition();
void servoWrite();
void dist_fun();
void forward_initial(int);
void rotate();

const int ANGLE_mid_Shaft = 1450;
const int ANGLE_mid_Fleft =1550;
const int ANGLE_mid_Fright =1550;//1570;
const int ANGLE_mid_Bleft = 1450;
const int ANGLE_mid_Bright = 1450;
const int trigPin = 4;
const int echoPin = 5;  
int distance;
long duration;
int count =0;

const int ANGLE_sweep = 200;//250;  //need to be reduced

Servo Servo_Fleft;
Servo Servo_Fright;
Servo Servo_Bleft;
Servo Servo_Bright;
Servo Servo_Shaft;

int ANGLE_Shaft = ANGLE_mid_Shaft;
int ANGLE_Fleft = ANGLE_mid_Fleft;
int ANGLE_Fright = ANGLE_mid_Fright;
int ANGLE_Bleft = ANGLE_mid_Bleft;
int ANGLE_Bright = ANGLE_mid_Bright;

const int ANGLE_max_Shaft = ANGLE_mid_Shaft + ANGLE_sweep/2;
const int ANGLE_min_Shaft = ANGLE_mid_Shaft - ANGLE_sweep/2;
const int wait = 350; //wait for 60*15 microseconds


void setup()
{
  Servo_Fleft.attach(8);
  Servo_Fright.attach(9);
  Servo_Bleft.attach(10);
  Servo_Bright.attach(11);
  Servo_Shaft.attach(6);

  Servo_Fleft.writeMicroseconds(ANGLE_mid_Fleft);
  Servo_Fright.writeMicroseconds(ANGLE_mid_Fright);
  Servo_Bleft.writeMicroseconds(ANGLE_mid_Bleft);
  Servo_Bright.writeMicroseconds(ANGLE_mid_Bright);
  Servo_Shaft.writeMicroseconds(ANGLE_mid_Shaft);
 // pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  delay(wait);
    //dist_fun();
}

void loop()
{
      //dist_fun();
      distance = digitalRead(echoPin);
      if(distance==HIGH)
        {
        
            forward_transition();
            forward_transition();
        }
       else
       {
          rotate();
          servoWrite();
          delay(wait);
          for(int i =0; i<4;++i)
          {
            forward_transition(); 
          }
           rotate();
          servoWrite();
          delay(wait);
        }
}

void dist_fun()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin,HIGH);
  distance = (duration*0.034)/2;
}

void forward_one()
{
  if(ANGLE_Fleft<ANGLE_mid_Fleft)
  {
    ANGLE_Fleft = ANGLE_mid_Fleft + ANGLE_sweep;
  }
  else
  {
     ANGLE_Fleft = ANGLE_mid_Fleft - ANGLE_sweep;
  }
  if(ANGLE_Bright>ANGLE_mid_Bright)
  {
    ANGLE_Bright = ANGLE_mid_Bright - ANGLE_sweep;
  }
  else
  {
    ANGLE_Bright = ANGLE_mid_Bright + ANGLE_sweep;
  }
  if(ANGLE_Bleft>ANGLE_mid_Bleft)
  {
    ANGLE_Bleft = ANGLE_mid_Bleft - ANGLE_sweep;
  }
  else
  {
    ANGLE_Bleft = ANGLE_mid_Bleft + ANGLE_sweep;
  }
  if(ANGLE_Fright<ANGLE_mid_Fright)
  {
    ANGLE_Fright = ANGLE_mid_Fright + ANGLE_sweep;
  }
  else
  {
    ANGLE_Fright = ANGLE_mid_Fright - ANGLE_sweep;
  }
  servoWrite();
}
void rotate()
{
      if(ANGLE_Shaft>ANGLE_mid_Shaft)
      ANGLE_Shaft = ANGLE_min_Shaft ;
      else
      ANGLE_Shaft = ANGLE_max_Shaft;
      if(ANGLE_Bright>ANGLE_mid_Bright)
      {
            ANGLE_Bright = ANGLE_mid_Bright - ANGLE_sweep;
      }
      else
      {
           ANGLE_Bright = ANGLE_mid_Bright + ANGLE_sweep;
      }
      if(ANGLE_Bleft>ANGLE_mid_Bleft)
      {
          ANGLE_Bleft = ANGLE_mid_Bleft - ANGLE_sweep;
      }
      else
     {
         ANGLE_Bleft = ANGLE_mid_Bleft + ANGLE_sweep;
     }
}


void forward_initial()
{
   ANGLE_Fright = ANGLE_mid_Fright - ANGLE_sweep;
   ANGLE_Fleft = ANGLE_mid_Fleft - ANGLE_sweep;
  ANGLE_Bleft = ANGLE_mid_Bleft + ANGLE_sweep;
  ANGLE_Bright = ANGLE_mid_Bright + ANGLE_sweep;
  servoWrite();
}

void forward_transition()
{
  if(ANGLE_Fleft==ANGLE_mid_Fleft)
  {
      ANGLE_Shaft = ANGLE_mid_Shaft;
      forward_initial();
  }
  else
  {
      if(ANGLE_Shaft>ANGLE_mid_Shaft)
        ANGLE_Shaft = ANGLE_min_Shaft;
      else
        ANGLE_Shaft = ANGLE_max_Shaft;
        forward_one();
  }
  delay(wait);
}

void servoWrite()
{
  Servo_Fleft.writeMicroseconds(ANGLE_Fleft);
  Servo_Fright.writeMicroseconds(ANGLE_Fright);
  Servo_Bleft.writeMicroseconds(ANGLE_Bleft);
  Servo_Bright.writeMicroseconds(ANGLE_Bright);
  Servo_Shaft.writeMicroseconds(ANGLE_Shaft);
}


