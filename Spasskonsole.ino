#include "soc/ledc_reg.h"
#include "soc/ledc_struct.h"
#include "Wire.h"
#include <Arduino.h>
#include <ArduinoOTA.h>
#include "KeyboardController.h"
#include "GameController.h"
#include "DisplayController.h"
#include "SoundController.h"
#include "MemController.h"

hw_timer_t *timerSound=NULL;
hw_timer_t *timerGameloop=NULL;
hw_timer_t *timerKeyboard=NULL;

// my own version of the the ledcwrite library function, because it crashes in combination with I2C communication when using the mutex
#define LEDC_CHAN(g,c) LEDC.channel_group[(g)].channel[(c)]
void my_ledcWrite(uint8_t chan, uint32_t duty){
    uint8_t group=(chan/8), channel=(chan%8);
//    LEDC_MUTEX_LOCK();          // commented out to avoid crashing when I2C is written to
    LEDC_CHAN(group, channel).duty.duty = duty << 4;//25 bit (21.4)
    if(duty) {
        LEDC_CHAN(group, channel).conf0.sig_out_en = 1;//This is the output enable control bit for channel
        LEDC_CHAN(group, channel).conf1.duty_start = 1;//When duty_num duty_cycle and duty_scale has been configured. these register won't take effect until set duty_start. this bit is automatically cleared by hardware.
        if(group) {
            LEDC_CHAN(group, channel).conf0.val |= BIT(4);
        } else {
            LEDC_CHAN(group, channel).conf0.clk_en = 1;
        }
    } else {
        LEDC_CHAN(group, channel).conf0.sig_out_en = 0;//This is the output enable control bit for channel
        LEDC_CHAN(group, channel).conf1.duty_start = 0;//When duty_num duty_cycle and duty_scale has been configured. these register won't take effect until set duty_start. this bit is automatically cleared by hardware.
        if(group) {
            LEDC_CHAN(group, channel).conf0.val &= ~BIT(4);
        } else {
            LEDC_CHAN(group, channel).conf0.clk_en = 0;
        }
    }
  //  LEDC_MUTEX_UNLOCK();          // commented out to avoid crashing when I2C is written to
}

//void IRAM_ATTR onSound() {
/*  int16_t o;
  my_ledcWrite(PWM_CHANNEL, o<<1);  // use 11bit PWM*/
//}

void IRAM_ATTR onKeyboard() {
  scanKeyboard();
}

void IRAM_ATTR onGameloop() {
  play();
}

void setup() {
Serial.begin(115200);
  
/*  WiFi.mode(WIFI_STA);
  WiFi.begin("TSQ", "ficken9000!#");
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
    delay(5000);
  WiFi.config(IPAddress(192,168,178,147), IPAddress(192,168,178,1), IPAddress(255,255,255,0));  

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
    }
  });
  ArduinoOTA.onEnd([]() {
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
  });
  ArduinoOTA.onError([](ota_error_t error) {
  });
  ArduinoOTA.begin();
*/
  initKeyboardController();
  initDisplayController();
  initSoundController();
  initGameController();

/*  ledcAttachPin(OUTPIN, PWM_CHANNEL);
  ledcSetup(PWM_CHANNEL, 39062, 11); // max frequency, 11 bit resolution, i.e. 39062,5hz
  
  timerSound=timerBegin(0, 64, true);                       // pre-scaler of 64
  timerAttachInterrupt(timerSound, &onSound, true);
  timerAlarmWrite(timerSound, 32, true);                    // sound loop runs at 39.062,5hz
  timerStart(timerSound);
  timerAlarmEnable(timerSound);
*/
  timerGameloop=timerBegin(1, 80, true);                    // pre-scaler of 80, resulting in 1Mhz
  timerAttachInterrupt(timerGameloop, &onGameloop, true);
  timerAlarmWrite(timerGameloop, 40000, true);              // called 25 times/s
  timerStart(timerGameloop);
  timerAlarmEnable(timerGameloop);

  timerKeyboard=timerBegin(2, 80, true);                    // pre-scaler of 80, resulting in 1Mhz
  timerAttachInterrupt(timerKeyboard, &onKeyboard, true);
  timerAlarmWrite(timerKeyboard, 8000, true);              // called 125 times/s
  timerStart(timerKeyboard);
  timerAlarmEnable(timerKeyboard);
}

void loop() {
//  ArduinoOTA.handle();
  displayShow();
  processSound();
}
