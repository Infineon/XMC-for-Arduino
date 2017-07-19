//This example is designed for XMC example MagneticSensor3D -> spherical_fast

import processing.serial.*;
import java.util.Scanner;


final boolean vertical = false;
final float size1 = 30;
final float size2 = 30;

ComPortMenu portSelect;
String inString;

GeneralButton btnCalibrate;
GeneralButton btnReset;
GeneralButton btnDefault;
Slider slider;
SlideBar bar;


void setup()
{
  size(640, 480);
  background(0);
  textFont(createFont("Arial", 16, true));
  portSelect = new ComPortMenu();
  slider = new Slider(vertical, size1, size2);
  bar = new SlideBar(vertical, size1, size2);
  btnReset = new GeneralButton(480, 384, 128, 64, "Reset");
  btnDefault = new GeneralButton(256, 384, 128, 64, "Default");
  btnCalibrate = new GeneralButton(32, 384, 128, 64, "Calibrate");
  if(slider.getCalibrationMode()) {
    btnCalibrate.setActive();
  } else {
    btnCalibrate.setInActive();
  } 
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

  btnCalibrate.drawButton();
  btnReset.drawButton();
  btnDefault.drawButton();
  float position = 0;
  try {
    position = slider.getPosition(azimuth, polar);
    bar.drawBar(position);
  } catch(Exception e) {
    //ignore
  }
  text("Position: " + Float.valueOf(position).toString(), 320, 360);
}



void clickEventHandler() {
  if(btnCalibrate.mouseOverBtn())
  {
    slider.toggleCalibrationMode();
  }
  if(btnReset.mouseOverBtn())
  {
    slider.resetCalibration();
    slider.setCalibrationMode(true);
  }
  if(btnDefault.mouseOverBtn())
  {
    slider.setCalibration(1.46, -0.9, -0.8);
  }
  
  if(slider.getCalibrationMode()) {
    btnCalibrate.setActive();
  } else {
    btnCalibrate.setInActive();
  } 
}



class SlideBar {
  private boolean vertical;
  private int xPos;
  private int yPos;
  private int xSize;
  private int ySize;
  private float scaler;
  
  public SlideBar(boolean vertical, float size1, float size2) {
    this.vertical = vertical;
    if(vertical) {
      scaler = 256.0 / (size1+size2);
      xPos = 304;
      xSize = 32;
      yPos = 160 - (int)(scaler*size1);
      ySize = 288;
    } else {
      scaler = 256.0 / (size1+size2);
      xPos = 304 - (int)(scaler*size1);
      xSize = 288;
      yPos = 160;
      ySize = 32;
    }
  }
  
  public void drawBar(float position) {
    stroke(80);
    fill(80);
    rect(xPos, yPos, xSize, ySize, 16, 16, 16, 16);
    stroke(255);
    fill(255);
    if(vertical) {
      ellipse(320, 176+scaler*position, 32, 32);
    } else {
      ellipse(320+scaler*position, 176, 32, 32);
    }
  }
  
}




////////////////////////////////////////////////


class Slider {
  public static final int LEFT = 0;
  public static final int RIGHT = 1;
  public static final int UP = 0;
  public static final int DOWN = 1;
  
  // options
  private boolean mInvertField;
  private boolean mInvertDirection;
  // slider size 
  private boolean mVertical;
  private float mSize[];
  // calibration coefficients
  private float mPolarRef;
  private float mMultX;
  private float mMultY[];
  // measurement results for automatic calibration
  private float mMinPolar[];
  private float mMaxPolar;
  // behaviour
  private boolean mCalibMode;
  private float mModerationFactor;
  
  // Constructor
  // vertical: true for vertical sliders (read up instead of left and down instead of right), false otherwide
  // leftsize and rightsize: defines the range limits of the slider in any desired length unit
  // getPosition will return a value between -leftSize and +rightSize later. The position directly over (next to) the sensor is regarded as origin(0)
  // this way, you can also use define sliders where the sensor is not in the middle of the range. You could also define different scalings for left or right to the sensor. 
  public Slider(boolean vertical, float leftSize, float rightSize) {
    mVertical = vertical;
    mSize = new float[2];
    mSize[0] = leftSize;
    mSize[1] = rightSize;
    mInvertField = false;
    mInvertDirection = false;
    mMinPolar = new float[2];
    mMultY = new float[2];
    resetCalibration();
    mModerationFactor = 0.75;
    mCalibMode = true;
  }
  
  // call this to clear the calibration
  // note: you should activate auto-calibration after calling this function
  // you need this reset if you had some external influences during auto-configuration (which increased the range limits)
  public void resetCalibration() {
    // This configuration is completely wrong, but this way we can be sure it will defenitely be updated during configuration
    mMinPolar[0] = PI/2;
    mMinPolar[1] = PI/2;
    mMaxPolar = -(PI/2);
    updateCalibration();
  }
  
  //the polar angles when the slider is directly over the sensor, at the left and at the right end of the slide
  public void setCalibration(float maxPolar, float minPolar1, float minPolar2) {
    mMaxPolar = maxPolar;
    mMinPolar[0] = minPolar1;
    mMinPolar[1] = minPolar2;
    updateCalibration();
    mCalibMode = false;
  }
  
  //this value is used for auto calibration
  public void setModerationFactor(float modFact) {
    mModerationFactor = modFact;
  }
  
  // call this once if magnetic poles (N and S) are swapped
  public void invertField() {
    mInvertField = !mInvertField;
  }
  
  // call this once if left and right (up and down) are swapped
  public void invertDirection() {
    mInvertDirection = !mInvertDirection;
  }
  
  // auto-calibration mode: 
  // when auto-calibration is on, our programs keeps the smallest and the highest elevation angles of the magnetic field vector through the sensor in mind
  // the highest angle will be remembered as the origin of our scale and the lowest angle (for each direction) will be saved as the range limit of our slider. 
  public boolean getCalibrationMode() {
    return mCalibMode;
  }
  
  public void setCalibrationMode(boolean calibMode) {
    mCalibMode = calibMode;
  }
  
  public void toggleCalibrationMode() {
    mCalibMode = !mCalibMode;
  }
  
  // calculates the slider position for a measured field vector direction
  // auto-calibration happens here if enabled
  public float getPosition(float azimuth, float polar) {
    // invert vector direction if magnetic field is inverted
    if(mInvertField) {
      azimuth = invertAngle(azimuth);
      polar = -polar;
    }
    // get direction
    int direction = getDirection(azimuth);
    // update calibration if in calibration mode
    if(mCalibMode) {
      if(polar > mMaxPolar) {
        mMaxPolar = polar;
        updateCalibration();
      }
      if(polar*mModerationFactor < mMinPolar[direction]) {
        mMinPolar[direction] = polar*mModerationFactor;
        updateCalibration();
      }
    }
    if(polar < mMinPolar[direction]) {
      polar = mMinPolar[direction];
    }
    // calculate distance from sensor
    float distance = mMultY[direction] * tan(mMultX * (mPolarRef-polar));
    if(abs(distance) > mSize[direction]) {
      distance = mSize[direction];
    }
    // invert direction if desired by user
    if(mInvertDirection) {
      distance = -distance;
    }
    // sign indicates direction
    if(direction == LEFT) {
      return -distance;
    } else {
      return distance;
    }
  }
  
  private float invertAngle(float angle)
  {
    if(angle > 0) {
      return angle - PI;
    } else {
      return angle + PI;
    }
  }
  
  private int getDirection(float azimuth) {
    if(mVertical) {
      if((azimuth>PI/2) || (azimuth<-PI/2)  ) {
        return UP;
      } else {
        return DOWN;
      }
    } else {
      if(azimuth > 0) {
        return RIGHT;
      } else {
        return LEFT;
      }
    }
  }
  
  private void updateCalibration() {
    mPolarRef = mMaxPolar;
    mMultX = PI / (2*mPolarRef + PI);
    for(int i=0; i<2; i++) {
      mMultY[i] = mSize[i] / tan(mMultX * (mPolarRef-mMinPolar[i]));
    }
  }

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
  clickEventHandler();
}



class GeneralButton
{
  private int mX;
  private int mY;
  private int mWidth;
  private int mHeight;
  private String mName;
  private boolean mIsActive;
  
  public GeneralButton(int btnX, int btnY, int btnWidth, int btnHeight, String btnName)
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
  
  public void setInActive()
  {
    mIsActive = false;
  }
  
  public void setActive()
  {
    mIsActive = true;
  }
  
  public boolean isActive()
  {
    return mIsActive;
  }
   
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