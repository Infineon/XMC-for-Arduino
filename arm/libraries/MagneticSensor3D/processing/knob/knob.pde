//This example is designed for XMC example MagneticSensor3D -> spherical_fast

import processing.serial.*;
import java.util.Scanner;



ComPortMenu portSelect;
String inString;


void setup()
{
  size(640, 480);
  background(0);
  textFont(createFont("Arial", 16, true));
  portSelect = new ComPortMenu();
}


void draw()
{
  background(0);
  portSelect.drawMenu();
  Serial comPort = portSelect.getComPort();
  if(comPort != null)
  {
    try
    {
      comPort.bufferUntil('\n');
      Scanner comInput = new Scanner(inString);
      comInput.useLocale(java.util.Locale.US);
      while(!comInput.hasNextFloat())
        comInput.next();
      float amount  = comInput.nextFloat();
      while(!comInput.hasNextFloat())
        comInput.next();
      float azimuth = comInput.nextFloat();
      while(!comInput.hasNextFloat())
        comInput.next();
      float polar   = comInput.nextFloat();
      comInput.close();
      visualize(amount, azimuth, polar);
    }
    catch(Exception e)
    {
      System.err.print("Invalid COM input: ");
      System.err.println(inString);
      System.err.print("Original message: ");
      System.err.println(e.getMessage());
    }
  } 
}


void visualize(float amount, float azimuth, float polar)
{
  float average = 45.0;
  float sensibility = 5.0;
  float red = 128 + sensibility * (amount-average);
  if(red<0) red = 0;
  if(red>255) red = 255;
  float green = 128 - sensibility * (amount-average);
  if(green<0) green = 0;
  if(green>255) green = 255;
  stroke(red, green, 0);
  fill(red, green, 0);
  ellipse(320, 320, 300, 300);
  stroke(255);
  fill(255);
  triangle(320-130*sin(azimuth), 320-130*cos(azimuth), 
           320-100*sin(azimuth+0.1), 320-100*cos(azimuth+0.1), 
           320-100*sin(azimuth-0.1), 320-100*cos(azimuth-0.1));
}



////////////////////////////////////////////////


Serial createSerial(String name)
{
  try
  {
    return new Serial(this, name, 9600);
  }
  catch(Exception e)
  {
    System.err.print(e.getMessage());
    return null;
  }
}

void serialEvent(Serial port)
{
  inString = port.readString();
}


void mousePressed()
{
  portSelect.clickHandler();
}


class ComPortMenuButton
{
  private int mX;
  private int mY;
  private int mWidth;
  private int mHeight;
  private String mName;
  private boolean mIsActive;
  
  public ComPortMenuButton(int btnX, int btnY, int btnWidth, int btnHeight, String btnName)
  {
    mX = btnX;
    mY = btnY;
    mWidth = btnWidth;
    mHeight = btnHeight;
    mName = btnName;
    mIsActive = false;
  }
  
  boolean mouseOverBtn()
  {
    return (mouseX>mX && mouseX<mX+mWidth && mouseY>mY && mouseY<mY+mHeight);
  }
  
  public void drawButton()
  {
    fill(70);
    if(mIsActive)
    {
      fill(120,80,0);
    }
    if(mouseOverBtn())
    {
      fill(180,120,0);
    }
    rect(mX, mY, mWidth, mHeight);
    fill(255);
    textAlign(CENTER);
    text(mName, mX+mWidth/2,mY+mHeight/2+8);
  }
  
  void setInActive()
  {
    mIsActive = false;
  }
  
  Serial setActive()
  {
    mIsActive = true;
    return createSerial(this.mName);  
  }
   
}


class ComPortMenu
{
  private ArrayList<ComPortMenuButton> mButtons;
  private ComPortMenuButton mActiveBtn = null;
  private Serial mComPort = null;
  
  public ComPortMenu()
  {
    int i = 0;
    mButtons = new ArrayList();
    for(String current : Serial.list())
    {
      int x = i % 5;
      int y = i / 5;
      mButtons.add(new ComPortMenuButton(100*x+5, 50*y+5, 90, 40, current));
      i++;
    }
    
  }
  
  public void drawMenu()
  {
    for(ComPortMenuButton current : mButtons)
    {
      current.drawButton();
    }
  }
  
  public void clickHandler()
  {
    for(ComPortMenuButton current : mButtons)
    {
      if(current.mouseOverBtn())
      {
        if(mActiveBtn != null)
          mActiveBtn.setInActive();
        mActiveBtn = current;
        mComPort = current.setActive();
      }
    }
  }
  
  public Serial getComPort()
  {
    return mComPort;
  }
  
}