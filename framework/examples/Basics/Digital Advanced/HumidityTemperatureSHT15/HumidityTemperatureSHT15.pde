/**
 * sensirion SHT15 humidity/temperature sensor (sparkfun breakout)
 * 
 * Demonstrates how to read temperature / humidity using the sensirion
 * SHT15 sensor. The sensor communicates using a 2-wire serial protocol. Based on Maurice Ribble example.
 */

int temperatureCommand  = B00000011;  // command used to read temperature
int humidityCommand = B00000101;  // command used to read humidity

int clockPin = 8;  // pin used for clock
int dataPin  = 9;  // pin used for data
int ack;  // track acknowledgment for errors
int val;
float temperature;
float humidity;

void setup()
{
  Serial.begin(9600); // open serial at 9600 bps
}

void loop()
{
  // read the temperature and convert it to centigrades
  sendCommandSHT(temperatureCommand, dataPin, clockPin);
  waitForResultSHT(dataPin);
  val = getData16SHT(dataPin, clockPin);
  skipCrcSHT(dataPin, clockPin);
  temperature = (float)val * 0.01 - 40;
  Serial.print("temperature: ");
  Serial.print(temperature);
  // read the humidity
  sendCommandSHT(humidityCommand, dataPin, clockPin);
  waitForResultSHT(dataPin);
  val = getData16SHT(dataPin, clockPin);
  skipCrcSHT(dataPin, clockPin);
  humidity = -4.0 + 0.0405 * val + -0.0000028 * val * val;
  Serial.print(" humidity: ");
  Serial.println(humidity);
  delay(200); // wait for 200 milliseconds for next reading
}

// commands for reading/sending data to a SHTx sensor

// send a command to the SHTx sensor
void sendCommandSHT(int command, int dataPin, int clockPin)
{
  int ack;

  // transmission start
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  digitalWrite(dataPin, HIGH);
  digitalWrite(clockPin, HIGH);
  digitalWrite(dataPin, LOW);
  digitalWrite(clockPin, LOW);
  digitalWrite(clockPin, HIGH);
  digitalWrite(dataPin, HIGH);
  digitalWrite(clockPin, LOW);

  // shift out the command (the 3 MSB are address and must be 000, the last 5 bits are the command)
  shiftOut(dataPin, clockPin, MSBFIRST, command);

  // verify we get the right ACK
  digitalWrite(clockPin, HIGH);
  pinMode(dataPin, INPUT);
  ack = digitalRead(dataPin);
  if (ack != LOW)
    Serial.println("ACK error 0");
  digitalWrite(clockPin, LOW);
  ack = digitalRead(dataPin);
  if (ack != HIGH)
    Serial.println("ACK error 1");
}

// wait for the SHTx answer
void waitForResultSHT(int dataPin)
{
  int ack;

  pinMode(dataPin, INPUT);
  for (int i = 0; i < 100; ++i)
  {
    delay(20);
    ack = digitalRead(dataPin);
    if (ack == LOW)
      break;
  }
  if (ack == HIGH)
    Serial.println("ACK error 2");
}

// get data from the SHTx sensor
int getData16SHT(int dataPin, int clockPin)
{
  int val;

  // get the MSB (most significant bits)
  pinMode(dataPin, INPUT);
  pinMode(clockPin, OUTPUT);
  val = shiftIn(dataPin, clockPin, MSBFIRST, 8, 3);
  val *= 256; // this is equivalent to val << 8;

  // send the required ACK
  pinMode(dataPin, OUTPUT);
  digitalWrite(dataPin, HIGH);
  digitalWrite(dataPin, LOW);
  digitalWrite(clockPin, HIGH);
  digitalWrite(clockPin, LOW);

  // get the LSB (less significant bits)
  pinMode(dataPin, INPUT);
  val |= shiftIn(dataPin, clockPin, MSBFIRST, 8, 3);
  return val;
}

// skip CRC data from the SHTx sensor
void skipCrcSHT(int dataPin, int clockPin)
{
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  digitalWrite(dataPin, HIGH);
  digitalWrite(clockPin, HIGH);
  digitalWrite(clockPin, LOW);
}

