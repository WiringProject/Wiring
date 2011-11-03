/**
 * Sparkfun RBG LED Matrix backpack
 * by Vanessa Carpenter, Mads Høbye, Daniel Brynolf, Jonas Eriksson,
 * Nicolas Padfield and BARRAGAN.
 * 
 * Demonstrates how to use the Sparkfun RBG LED Matrix backpack showing a small
 * animation made frame by frame.
 * Two types of animation are handled: slide and frame replace.
 */

int bits[8] =
{
  128, 64, 32, 16, 8, 4, 2, 1
};

int clock = 16;  // pin SCK del display
int data = 18;   // pin DI del display
int cs = 19;     // pin CS del display

byte bitmaps[10][8][8];     // Space for 10 frames of 8x8 pixels
byte displayPicture[8][8];  // What is currently ON display.
int currentBitmap = 0;      // current displayed bitmap, per display
int targetBitmap = 1;       // Desired image, for the animation to strive for, per display
int step;                   // animation step, usually from 0 to 8, per screen
int stepDelay = 19;         // the wait time between each animation frame
unsigned int delayCounter;           // holder for the delay, as to not hog to processor, per screen
int animationStyle = 0;     // different types of animation 0 = slide 1 = frame replace
unsigned long lastTime;     // display refresh time

void setup()
{
  Serial.begin(115200);  // used for debug

  matrixInit();
  int bitmap = 0;

  // black color for buildings 0
  // sky rotating color 1-7

  // bitmap 0
  addLineTobitmap(bitmap, 0, 1, 1, 1, 1, 0, 1, 1, 1);
  addLineTobitmap(bitmap, 1, 1, 1, 1, 1, 0, 0, 1, 1);
  addLineTobitmap(bitmap, 2, 1, 1, 1, 1, 0, 0, 1, 1);
  addLineTobitmap(bitmap, 3, 1, 1, 1, 1, 0, 0, 1, 0);
  addLineTobitmap(bitmap, 4, 1, 0, 1, 0, 0, 0, 1, 0);
  addLineTobitmap(bitmap, 5, 1, 0, 0, 0, 0, 0, 0, 0);
  addLineTobitmap(bitmap, 6, 0, 0, 0, 0, 0, 0, 0, 0);
  addLineTobitmap(bitmap, 7, 0, 0, 0, 0, 0, 0, 0, 0);

  // bitmap 1
  bitmap++;
  addLineTobitmap(bitmap, 0, 2, 2, 2, 2, 0, 2, 2, 2);
  addLineTobitmap(bitmap, 1, 2, 2, 2, 2, 0, 0, 2, 2);
  addLineTobitmap(bitmap, 2, 2, 2, 2, 2, 0, 0, 2, 2);
  addLineTobitmap(bitmap, 3, 2, 2, 2, 2, 0, 0, 2, 0);
  addLineTobitmap(bitmap, 4, 2, 0, 2, 0, 0, 0, 2, 0);
  addLineTobitmap(bitmap, 5, 2, 0, 0, 0, 0, 0, 0, 0);
  addLineTobitmap(bitmap, 6, 0, 0, 0, 0, 0, 0, 0, 0);
  addLineTobitmap(bitmap, 7, 0, 0, 0, 0, 0, 0, 0, 0);

  // bitmap 2
  bitmap++;
  addLineTobitmap(bitmap, 0, 3, 3, 3, 3, 0, 3, 3, 3);
  addLineTobitmap(bitmap, 1, 3, 3, 3, 3, 0, 0, 3, 3);
  addLineTobitmap(bitmap, 2, 3, 3, 3, 3, 0, 0, 3, 3);
  addLineTobitmap(bitmap, 3, 3, 3, 3, 3, 0, 0, 3, 0);
  addLineTobitmap(bitmap, 4, 3, 0, 3, 0, 0, 0, 3, 0);
  addLineTobitmap(bitmap, 5, 3, 0, 0, 0, 0, 0, 0, 0);
  addLineTobitmap(bitmap, 6, 0, 0, 0, 0, 0, 0, 0, 0);
  addLineTobitmap(bitmap, 7, 0, 0, 0, 0, 0, 0, 0, 0);

  // bitmap 3
  bitmap++;
  addLineTobitmap(bitmap, 0, 4, 4, 4, 4, 0, 4, 4, 4);
  addLineTobitmap(bitmap, 1, 4, 4, 4, 4, 0, 0, 4, 4);
  addLineTobitmap(bitmap, 2, 4, 4, 4, 4, 0, 0, 4, 4);
  addLineTobitmap(bitmap, 3, 4, 4, 4, 4, 0, 0, 4, 0);
  addLineTobitmap(bitmap, 4, 4, 0, 4, 0, 0, 0, 4, 0);
  addLineTobitmap(bitmap, 5, 4, 0, 0, 0, 0, 0, 0, 0);
  addLineTobitmap(bitmap, 6, 0, 0, 0, 0, 0, 0, 0, 0);
  addLineTobitmap(bitmap, 7, 0, 0, 0, 0, 0, 0, 0, 0);

  // bitmap 4
  bitmap++;
  addLineTobitmap(bitmap, 0, 5, 5, 5, 5, 0, 5, 5, 5);
  addLineTobitmap(bitmap, 1, 5, 5, 5, 5, 0, 0, 5, 5);
  addLineTobitmap(bitmap, 2, 5, 5, 5, 5, 0, 0, 5, 5);
  addLineTobitmap(bitmap, 3, 5, 5, 5, 5, 0, 0, 5, 0);
  addLineTobitmap(bitmap, 4, 5, 0, 5, 0, 0, 0, 5, 0);
  addLineTobitmap(bitmap, 5, 5, 0, 0, 0, 0, 0, 0, 0);
  addLineTobitmap(bitmap, 6, 0, 0, 0, 0, 0, 0, 0, 0);
  addLineTobitmap(bitmap, 7, 0, 0, 0, 0, 0, 0, 0, 0);

  // bitmap 5
  bitmap++;
  addLineTobitmap(bitmap, 0, 6, 6, 6, 6, 0, 6, 6, 6);
  addLineTobitmap(bitmap, 1, 6, 6, 6, 6, 0, 0, 6, 6);
  addLineTobitmap(bitmap, 2, 6, 6, 6, 6, 0, 0, 6, 6);
  addLineTobitmap(bitmap, 3, 6, 6, 6, 6, 0, 0, 6, 0);
  addLineTobitmap(bitmap, 4, 6, 0, 6, 0, 0, 0, 6, 0);
  addLineTobitmap(bitmap, 5, 6, 0, 0, 0, 0, 0, 0, 0);
  addLineTobitmap(bitmap, 6, 0, 0, 0, 0, 0, 0, 0, 0);
  addLineTobitmap(bitmap, 7, 0, 0, 0, 0, 0, 0, 0, 0);

  // bitmap 6
  bitmap++;
  addLineTobitmap(bitmap, 0, 7, 7, 7, 7, 0, 7, 7, 7);
  addLineTobitmap(bitmap, 1, 7, 7, 7, 7, 0, 0, 7, 7);
  addLineTobitmap(bitmap, 2, 7, 7, 7, 7, 0, 0, 7, 7);
  addLineTobitmap(bitmap, 3, 7, 7, 7, 7, 0, 0, 7, 0);
  addLineTobitmap(bitmap, 4, 7, 0, 7, 0, 0, 0, 7, 0);
  addLineTobitmap(bitmap, 5, 7, 0, 0, 0, 0, 0, 0, 0);
  addLineTobitmap(bitmap, 6, 0, 0, 0, 0, 0, 0, 0, 0);
  addLineTobitmap(bitmap, 7, 0, 0, 0, 0, 0, 0, 0, 0);

  // bitmap 7
  bitmap++;
  addLineTobitmap(bitmap, 0, 1, 1, 1, 1, 0, 1, 1, 1);
  addLineTobitmap(bitmap, 1, 1, 1, 1, 1, 0, 0, 1, 1);
  addLineTobitmap(bitmap, 2, 1, 1, 1, 1, 0, 0, 1, 1);
  addLineTobitmap(bitmap, 3, 1, 1, 1, 1, 0, 0, 1, 0);
  addLineTobitmap(bitmap, 4, 1, 0, 1, 0, 0, 0, 1, 0);
  addLineTobitmap(bitmap, 5, 1, 0, 0, 0, 0, 0, 0, 0);
  addLineTobitmap(bitmap, 6, 0, 0, 0, 0, 0, 0, 0, 0);
  addLineTobitmap(bitmap, 7, 0, 0, 0, 0, 0, 0, 0, 0);

  currentBitmap = 7;
  targetBitmap = 7;
  lastTime = millis();
}

void loop()
{
  if (currentBitmap == targetBitmap)
  {
    targetBitmap++;
    targetBitmap %= 8; // there are 8 frames, from 0 to 7
  }

  if ((millis() - lastTime) > 70)
  {
    handleAnimations();
    lastTime = millis();
    Serial.print("currentBitmap: ");
    Serial.print(currentBitmap);
    Serial.print(" targetBitmap: ");
    Serial.println(targetBitmap);
  }
  drawFrame(displayPicture);
}

void drawFrame(byte frame[8][8])
{
  digitalWrite(clock, LOW);  //sets the clock for each display, running through 0 then 1
  digitalWrite(data, LOW);   //ditto for data.
  delayMicroseconds(10);
  digitalWrite(cs, LOW);     //ditto for cs.
  delayMicroseconds(10);
  for (int x = 0; x < 8; x++)
  {
    for (int y = 0; y < 8; y++)
    {
      //Drawing the grid. x across then down to next y then x across.
      writeByte(frame[x][y]);
      delayMicroseconds(10);
    }
  }
  delayMicroseconds(10);
  digitalWrite(cs, HIGH);
}

// prints out bytes. Each colour is printed out.
void writeByte(byte myByte)
{
  for (int b = 0; b < 8; b++)    // converting it to binary from colour code.
  {
    digitalWrite(clock, LOW);
    if ((myByte & bits[b])  > 0)
    {
      digitalWrite(data, HIGH);
    }
    else
    {
      digitalWrite(data, LOW);
    }
    digitalWrite(clock, HIGH);
    delayMicroseconds(10);
    digitalWrite(clock, LOW);
  }
}

void matrixInit()
{
  pinMode(clock, OUTPUT); // sets the digital pin as output
  pinMode(data, OUTPUT);
  pinMode(cs, OUTPUT);
}

void handleAnimations()
{
  if (currentBitmap != targetBitmap)
  {
    // the function takes 3 variables
    drawAnimationToDisplay(currentBitmap, targetBitmap, step);
    delayCounter++;
    if (delayCounter > stepDelay)
    {
      step--;
    }
    if (step < 0)
    {
      step = 7;
      currentBitmap = targetBitmap;
    }
  }
  else
  {
    drawBitmapToDisplay(currentBitmap);
  }
}

void drawBitmapToDisplay(int bitmap)
{
  for (int x = 0; x < 8; x++)
  {
    for (int y = 0 ; y < 8; y++)
    {
      //copies the bitmap to be displayed ( in memory )
      displayPicture[x][y] = bitmaps[bitmap][x][y];
    }
  }
}

void drawAnimationToDisplay(int bitmap, int targetBitmap, int step)
{
  switch (animationStyle)
  {
  case 0:   // slide transition
    for (int x = 0; x < 8 - step; x++)
    {
      for (int y = 0 ; y < 8; y++)
      {
        displayPicture[x][y] = bitmaps[targetBitmap][x + step][y];
      }
    }
    for (int x = 0; x < step ; x++)
    {
      for (int y = 0 ; y < 8; y++)
      {
        displayPicture[8 - step + x][y] = bitmaps[bitmap][x][y];
      }
    }
    break;
  case 1:  // frame by frame
    for (int x = 0; x < 8; x++)
    {
      for (int y = 0 ; y < 8; y++)
      {
        displayPicture[x][y] = bitmaps[bitmap][x][y];
      }
    }
    break;
  }
}

void addLineTobitmap(int bitmap, int line, byte a, byte b, byte c, byte d, byte e, byte f, byte g, byte h)
{
  bitmaps[bitmap][7][line] = a;
  bitmaps[bitmap][6][line] = b;
  bitmaps[bitmap][5][line] = c;
  bitmaps[bitmap][4][line] = d;
  bitmaps[bitmap][3][line] = e;
  bitmaps[bitmap][2][line] = f;
  bitmaps[bitmap][1][line] = g;
  bitmaps[bitmap][0][line] = h;
}

