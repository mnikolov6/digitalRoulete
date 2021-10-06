#include<Adafruit_GFX.h>
#include<Adafruit_SSD1306.h>

#include<VL53L1X.h>
#include<Wire.h>

#define OLED_RESET 4

VL53L1X sensor;
Adafruit_SSD1306 display (OLED_RESET);

int button1 = 2, button2 = 3;
int state = 0;

void setup() {

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);

  sensor.setTimeout(500);
  if(!sensor.init()){
    Serial.println("Failed to detect and initialize sensor!");
    while(1);
  }
  sensor.setDistanceMode(VL53L1X::Long);
  sensor.setMeasurementTimingBudget(50000);
  sensor.startContinuous(50);

  pinMode(button1,INPUT);
  pinMode(button2,INPUT);
}

void loop() {
  distanceM();
   
}

void distanceMM(){
  sensor.read();
  display.clearDisplay();
  display.setCursor(25,0);
  display.print(sensor.ranging_data.range_mm);
  display.setCursor(85,0);
  display.print("mm");

  display.display();
  delay(1);
}

void distanceCM(){
  sensor.read();
  display.clearDisplay();
  display.setCursor(25,0);
  display.print((float)sensor.ranging_data.range_mm/10);
  display.setCursor(100,0);
  display.print("cm");

  display.display();
  delay(1);
}

void distanceM(){
  sensor.read();
  display.clearDisplay();
  display.setCursor(25,0);
  display.print((float)sensor.ranging_data.range_mm/1000);
  display.setCursor(80,0);
  display.print("m");

  display.display();
  delay(1);
}

void distanceInch(){
  sensor.read();
  display.clearDisplay();
  display.setCursor(25,0);
  display.print((float)sensor.ranging_data.range_mm*0.03937008);
  display.setCursor(100,0);
  display.print('"');

  display.display();
  delay(1);
}
