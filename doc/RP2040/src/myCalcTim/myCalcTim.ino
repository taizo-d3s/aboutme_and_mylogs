
// globals
int ms10time;
bool is_finish;
int bzon;

int ref_adval;

// call per 10msec by timer
bool tm10ms(struct repeating_timer *t)
{
  // for LCD
  blinkdisp();
  // for bz
  bz_proc();

  // calc time
  if (ms10time!=0) {
    if ( is_finish == true ) {
      // nothing to do
    } else {
      ms10time++;
    }
  }
  return true;
}

void setup() {
  init_hardware();
  is_finish = false;

  // この4秒で、ボタンが押されていたら、センサ調整モードに入る。
  if ( is_adjmode()) {
    Serial.println("adj mode");
    while(1) {
      disp_adj();
    }
  } else {
    Serial.println("ready to calc watch");
    ref_adval = analogRead(A1);
    disp_refad(ref_adval);
    delay(800);
  }
}

void loop() {

  btn_proc();

  if (is_sw2_pushed()) {
    if (ms10time!=0) {
      Serial.println("SW2 is pushed!! Reset all and Waiting next trigger!!");
      is_finish = false;
      ms10time=0;
    }
    delay(200);
  }

  if ( analogRead(A0) > ref_adval ) {
    if (ms10time!=0) {
      is_finish = true;
      bz(50);
    } else {
      // first detect
      ms10time++;
      bz(10);
    }
    disp_start(ms10time);
    delay(200);
  }

  if (is_sw1_pushed()) {
    Serial.println("SensorDetect(MOGI)");

    if (ms10time!=0) {
      is_finish = true;
      bz(50);
    } else {
      // first detect
      ms10time++;
      bz(10);
    }
    delay(200);
  }

  // DISPLAY
  if (ms10time==0) {
    disp_ready();    
  } else {
    disp_laptime(ms10time);
  }

  //need this??

//  delay(5);
}

/// END OF FILE ///
