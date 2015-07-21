//Pong2

import processing.serial.*; //library for serial communications

Serial port; //declares Serial object with name "port"

PImage claire;
void setup()
{
  size(500, 500);
  noStroke();
  claire = loadImage("CH.jpg");
  String portName = Serial.list()[2];
  println(Serial.list());
  
  port = new Serial(this, portName, 9600); 
  

}
Boolean firstContact = false;


float yDirection = random(3, 7)/10;
float xDirection = -1*sqrt(1-yDirection*yDirection);

float imagePosX = 400;
float imagePosY = 400;
float imageDim = 35;

float rectanglePosX = 4;
float rectanglePosY = 0;
float rectangleHeight = 100;
float rectangleWidth = 5;


int fiveDisplay = 0;

float speedLimit = 5.5;
Boolean limitReached = false;

Boolean analytics = true;
float oldPos = 0;
int newPos = 0;

Boolean goalScored = false;
Boolean stopped = true;
Boolean started = false;

void draw()
{
  
  background(0, 0, 0);
    
  if(!started)
  {
    textAlign(CENTER);
    if(stopped)
    {
      text("Press Green Button To Start",(width/2), height/2); //occurs in the case of a stop button
    }
    else
    {
      text("PAUSED",width/2, height/2);
    } 
  }
  else
  {
    if (fiveDisplay > 0)
    {
      text("Speed Increase 5 %", imagePosX-20, imagePosY-20); 
      fiveDisplay--;
    }
    fill(0, 255, 255);
    rect(rectanglePosX, rectanglePosY, rectangleWidth, rectangleHeight);
  
    if (abs(xDirection) + abs(yDirection) > speedLimit )
    {
      limitReached = true;
    }
  
    image(claire, imagePosX, imagePosY, imageDim, imageDim);
  
    if (imagePosX - abs(xDirection)<= rectanglePosX + rectangleWidth && imagePosX >= rectanglePosX && imagePosY + imageDim/2 >= rectanglePosY && imagePosY + imageDim/2 <= rectanglePosY + rectangleHeight)//checks for ball contacting rectangle
    {
  
      if (limitReached)
      {
        xDirection *= -1;
      } else
      {
        xDirection *= -1.05;
        yDirection *= 1.01;
        fiveDisplay = 100;
      }
    } 
    else if ((imagePosX-abs(xDirection) <= 0))
    {
      yDirection = random(3, 7)/10;
      xDirection = -1*sqrt(1-yDirection*yDirection);
      imagePosX = 400;
      imagePosY = 400;

      goalScored = true;
      
   
      
      limitReached = false;
    }
    
  
  
    if (imagePosY - 1 <= 0 || imagePosY + imageDim + 1 >= height)
    {
      if (limitReached)
      {
        yDirection *= -1;
      } else
      {
        yDirection *= -1.05;
        fiveDisplay = 100;
      }
    }
  
    if (imagePosX + imageDim + 1 >= width)
    {
      if (limitReached)
      {
        xDirection *= -1;
      } else
      {
        xDirection *= -1.05;
        yDirection *= 1.01;
        fiveDisplay = 100;
      }
    }
    imagePosX += xDirection;   
    imagePosY += yDirection;
    
    
  }
  

    
      
    
    
    
}

void serialEvent(Serial port)
{
  println("Serial port event");
  int inByte = port.read();
  
  println(inByte);
  if(firstContact == false)
  {
    if(inByte == 'A')
    {
      port.clear();
      //firstContact = true;
      port.write('B');
      println('B');
    }
    else if(inByte == 'C')
    {
     firstContact = true; 
     port.write('N');
     println('N');
    }
  }
  else
  {
    if(inByte == 'S')
    {
      started = true;
      stopped = false; 
      println("Start Button");
      port.write('N');
    }
    else if(inByte == 'P')
    {
      started = false;
      println("Pause Button");
      port.write('N');
    }
    else if(inByte == 'T')
    {
     started = false;
     stopped = true; 
     println("Stop Button");
     port.write('N');
    }
    else if(goalScored)
    {
      started = false;
      goalScored = false;
      port.write('G');
      println('G');
    }
    else
    {
       if(inByte > 2 && inByte < 8)
       {
         rectanglePosY = (inByte-3)*100;
       }
       
       else
       rectanglePosY = oldPos;
       port.write('N');
       println('N');
       oldPos = rectanglePosY;
    }
   
    
  }
  
}


void keyPressed()
{
  if (key == CODED )
  {
    if (keyCode == UP && rectanglePosY > -15)
    {
      rectanglePosY-=15;
    } else if (keyCode == DOWN && rectanglePosY + rectangleHeight < height + 15)
    {
      rectanglePosY += 15;
    }
  }
}


