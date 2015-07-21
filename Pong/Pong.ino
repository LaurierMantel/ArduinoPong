#define stopPin 4
#define pausePin 5
#define startPin 6
#define echoPin 7
#define trigPin 8
#define cinPin 9
#define B1Pin 10
#define B0Pin 11
#define A1Pin 12
#define A0Pin 13



int inByte;

boolean ledState = false;
//char serialVal;

short distance;
short lastDistance = 0;

volatile int stopButton = LOW;
volatile int startButton = LOW;
volatile int pauseButton = LOW;

int testState = LOW;

char goal;
volatile short lives = 3;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(stopPin, INPUT);
pinMode(pausePin, INPUT);
pinMode(startPin, INPUT);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);

pinMode(cinPin, OUTPUT);
pinMode(B1Pin, OUTPUT);
pinMode(B0Pin, OUTPUT);
pinMode(A1Pin, OUTPUT);
pinMode(A0Pin, OUTPUT);



attachInterrupt(0, buttonPressed, HIGH);
establishContact();
}

void loop() 
{

  if(Serial.available() > 0)
  {
    inByte = Serial.read();
    if(inByte == 'B')
    {
      Serial.write('C');
      
    }
   else if(inByte == 'N')
   {
    Serial.write(distance); 
   }
   else if(inByte == 'G')//goal scored 
   {
    lives--;
    ledState = true;
    Serial.write(distance);
   }
  }

  
  if(ledState)
  {
    digitalWrite(A0Pin, HIGH);
  }
  
  //Getting data from sensor
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(trigPin, LOW);
  distance = pulseIn(echoPin, HIGH)/58.2;
  
  //Writing to serial port to have distance picked up for processing 
 // Serial.println(distance);

  
  delay(50);

//  if(lives > 0)
//  {
//    digitalWrite(A0Pin, HIGH);
//    
//    digitalWrite(B0Pin, HIGH);
//    digitalWrite(B1Pin, HIGH);
//    if(lives == 3)
//    {
//      digitalWrite(cinPin, HIGH);
//      digitalWrite(A1Pin, HIGH);
//    }
//    else if(lives == 2)
//    {
//      digitalWrite(cinPin, LOW);
//      digitalWrite(A1Pin, HIGH);
//    }
//    else
//    {
//      digitalWrite(cinPin, LOW);
//      digitalWrite(A1Pin, LOW);
//    }
//    
//  }
//  else
//  {
//    for(int i = 9; i < 14; i++)
//    {
//      digitalWrite(i, LOW);
//    }
//  }
  
  
  

}

void buttonPressed()
{
  do
  {
    
    pauseButton = digitalRead(pausePin);
    startButton = digitalRead(startPin);
    stopButton = digitalRead(stopPin);

    if(stopButton == HIGH)
    {
      Serial.write('T');
      lives = 3;
      
    }
    else if(pauseButton == HIGH)
    {
      Serial.write('P');
    }
    else if(startButton == HIGH)
    {
      Serial.write('S');
    }
    
  } while(stopButton == LOW && pauseButton == LOW && startButton == LOW);
  
  
  
}


void establishContact() 
{
  while (Serial.available() <= 0) 
  {
    Serial.write('A');   // send a capital A
    delay(300);
  }
}

