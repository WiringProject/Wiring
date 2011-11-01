/**
 * Wiring and "C" style code
 * by BARRAGAN http://barraganstudio.com
 * 
 * Demonstrates how to mix "C" syntax code within a Wiring program.
 * All C code should be enclosed in an extern "C" { } section
 */

extern "C" {

  typedef int STEPPER_COORD;

  typedef struct _stepper_xy
  {
    STEPPER_COORD x;
    STEPPER_COORD y;
  }
  STEPPER_POINT;

  void test(STEPPER_POINT *a)
  {
    a->x = 50;
    a->y = 20;
  }

}

STEPPER_POINT myPt;

void setup()
{
  Serial.begin(9600);
  myPt.x = 100;  // access the x and y components of
  myPt.y = 100;  // a variable type STEPPER_POINT
  Serial.print("myPt is: ");
  Serial.print(myPt.x, DEC);
  Serial.print(", ");
  Serial.println(myPt.y, DEC);
  test(&myPt);
  Serial.print("now myPt is: ");
  Serial.print(myPt.x, DEC);
  Serial.print(", ");
  Serial.println(myPt.y, DEC);
}

void loop()
{

}

