
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH    (128)
#define SCREEN_HEIGHT   (64)
#define SCREEN_ADDRESS  (0x3C)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

bool isSW1_pushed;
bool isSW2_pushed;
struct repeating_timer st_tm10ms;

int blinktim;
int g_disp_blink; // 0 or 1

void init_hardware() {
  Serial.begin(115200);

  // SW1,2
  pinMode(10,INPUT_PULLUP); // Button SW1
  pinMode(11,INPUT_PULLUP); // Button SW2
  isSW1_pushed = false;
  isSW1_pushed = false;
  //Setup SSD1306
	if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
  	Serial.println(F("SSD1306 can not allocate memory!"));
	} else {
    //Clear display.
    display.clearDisplay();

    display.setTextSize(4);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print("PowerUP");
    display.display();
  }
  // PWM
  analogWriteFreq(2000);
  //analogWriteRange(111); range is defalut as 255 max

//analogWrite(16, 100);

  // timer int
  add_repeating_timer_us(10000, tm10ms, NULL, &st_tm10ms);

  blinktim = 100; // init value
}

// BZ
void bz_proc() {
  if ( bzon > 0 ) {
    bzon--;
    if (bzon==0) {
      bz_off();
    }
  }
}
void bz(int m) {
  bzon=m;
  analogWrite(16, 100); // BZ is GP16
}
void bz_off() {
  analogWrite(16, 0); // BZ is GP16
}

// LCD関係
void disp_adj() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(analogRead(A0)); // sensor
  display.println(analogRead(A1)); // ref dial
  display.display();
}

void disp_laptime(int lap) {
  display.clearDisplay();
  display.setCursor(0, 0);
  if (is_finish==true) {
    if (g_disp_blink!=0) {
      display.println("YOUR");
    } else {
      display.println("TIME:");
    }
  } else {
    if (g_disp_blink!=0) {
      display.println("RUN:");
    } else {
      display.println("    ");
    }    
  }
  display.print(lap/100);
  display.print(":");
  display.print(lap%100);
  display.display();
}
// 
void disp_ready() {
  display.clearDisplay();
  display.setCursor(0, 0);
  if (g_disp_blink!=0) {
    display.println("RDY?");
  } else {
    display.println("R U ");
  }
  display.print("00:00");
  display.display();
}
void disp_start(int lap) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("START");
  display.print(lap/100);
  display.print(":");
  display.print(lap%100);
  display.display();
}
void disp_refad(int ad) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("REFAD");
  display.print(ad);
  display.display();
}



/*
 50カウントでON、50カウントでOFFのg_変数を作る
*/
void blinkdisp() {
  if (blinktim>0) {
    blinktim--;
    if (blinktim==0) {
      blinktim=100;
      // now detect
      if (g_disp_blink==0) {
        g_disp_blink=1;
      } else {
        g_disp_blink=0;
      }
    }
  }
}

// adjmodeでnoneZeroを返す
int is_adjmode() {
  int ret = 0;
  int mode1 = 0;
  int mode2 = 0;
  int i;
  for(i=0;i<4;i++) {
    if (digitalRead(10)==0) { // low detect
      mode1++;
    }
    if (digitalRead(11)==0) { // low detect
      mode2++;
    }
    delay(1000);
  }
  if ((mode1>0)&&(mode2>0)) {
    ret++;
  }
  return ret;
}

// SW関係のルーチン（最速で回す
void btn_proc() {
  if (digitalRead(10)==0) { // low detect
    isSW1_pushed = true;
  }
  if (digitalRead(11)==0) {
    isSW2_pushed = true;
  }
}
// if pushed return noneZero
int is_sw1_pushed() {
  int ret=0;
  if (isSW1_pushed==true) {
    ret = 99;
    isSW1_pushed=false;
  }
  return ret;
}
// if pushed return noneZero
int is_sw2_pushed() {
  int ret=0;
  if (isSW2_pushed==true) {
    ret = 99;
    isSW2_pushed=false;
  }
  return ret;
}

/// END OF FILE ///
