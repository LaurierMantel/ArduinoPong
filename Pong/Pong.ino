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


short distance;
short lastDistance = 0;

volatile int stopButton = LOW;
volatile int startButton = LOW;
volatile int pauseButton = LOW;

int testState = LOW;

char goal;
volatile short lives = 3;

void setup() {
Serial.begin(9600);

//buttons
pinMode(stopPin, INPUT);
pinMode(pausePin, INPUT);
pinMode(startPin, INPUT);

//communications with ultrasonic sensor
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);

pinMode(cinPin, OUTPUT);
pinMode(B1Pin, OUTPUT);
pinMode(B0Pin, OUTPUT);
pinMode(A1Pin, OUTPUT);
pinMode(A0Pin, OUTPUT);

attachInterrupt(0, buttonPressed, RISING);

//runs until applet responds and completes serial handshake
establishContact();
}

void loop() 
{

  if(Serial.available() > 0)
  {
    inByte = Serial.read(); //initial handshake
    if(inByte == 'B')
    {
      Serial.write('C');
      
    }
   else if(inByte == 'N') //default serial communication.  
   {
    Serial.write(distance); 
   }
   else if(inByte == 'G')//goal scored 
   {
    lives--;
    if(lives <= 0)
    {
      Serial.write('T');
      
    }
    else
    {
      Serial.write(distance);
    }
    
   }
  }

//we send single characters so that messages do not get cut off during interrupt
  
  //Getting data from sensor
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(trigPin, LOW);
  distance = pulseIn(echoPin, HIGH)/58.2;
  
  //Writing to serial port to have distance picked up for processing 
 // Serial.println(distance);

  
  delay(50); //allows time for serial communications from applet

if(lives == 3)
{
    digitalWrite(A0Pin, HIGH);
    digitalWrite(A1Pin, HIGH);
    digitalWrite(B0Pin, HIGH);
    digitalWrite(B1Pin, HIGH);
    digitalWrite(cinPin, HIGH);
}
else if(lives == 2)
{
    digitalWrite(A0Pin, HIGH);
    digitalWrite(A1Pin, HIGH);
    digitalWrite(B0Pin, HIGH);
    digitalWrite(B1Pin, HIGH);
    digitalWrite(cinPin, LOW);
}
else if(lives == 1)
{
    digitalWrite(A0Pin, HIGH);
    digitalWrite(A1Pin, LOW);
    digitalWrite(B0Pin, HIGH);
    digitalWrite(B1Pin, HIGH);
    digitalWrite(cinPin, LOW);
}


else
{
    digitalWrite(A0Pin, LOW);
    digitalWrite(A1Pin, LOW);
    digitalWrite(B0Pin, LOW);
    digitalWrite(B1Pin, LOW);
    digitalWrite(cinPin, LOW);

    for(int i = 0; i < 3; i++) //losing message (flash light 3 times)
    {
        delay(300);
    
        digitalWrite(A0Pin, HIGH);
        digitalWrite(A1Pin, HIGH);
        digitalWrite(B0Pin, HIGH);
        digitalWrite(B1Pin, HIGH);
        digitalWrite(cinPin, HIGH);
    
        delay(300);
    
        digitalWrite(A0Pin, LOW);
        digitalWrite(A1Pin, LOW);
        digitalWrite(B0Pin, LOW);
        digitalWrite(B1Pin, LOW);
        digitalWrite(cinPin, LOW);
      
    }

    

    delay(100);

    lives = 3;
}

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
  while (Serial.available() <= 0) // Serial.available() checks 
  {
    Serial.write('A');   // send a capital A, keeps writing until applet hears the capital A
    delay(300);
  }
}

