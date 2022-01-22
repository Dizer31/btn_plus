#define debugMode
#ifdef debugMode
#define debug(x) Serial.println(x)
#else
#define debug(x)
#endif

#include"lib_v1.2.h"
#define BTN 3
Button btn1(BTN);
//Button btn2(4);
//Button btn3(5);

void setup() {
    Serial.begin(9600);
    debug(__TIME__);

    btn1.setDeb(50);
    btn1.setHold(500);
    btn1.setClickTimeOut(160);
}

byte con = 0;
void loop() {
    btn1.tick();
    //btn2.tick();
    //btn3.tick();

    //if (btn.isPress())debug("press");
    //if (btn.isRelease())debug("release");
    //if (btn.isHold())debug("hold");
    //if (btn.isHolded())debug(++con);

    if (btn1.isSingle())debug("isSingle 1");
    if (btn1.isDouble())debug("isDouble 1");
    if (btn1.isTriple())debug("isTriple 1");

    /*
    if (btn2.isSingle())debug("isSingle 2");
    if (btn2.isDouble())debug("isDouble 2");
    if (btn2.isTriple())debug("isTriple 2");

    if (btn3.isSingle())debug("isSingle 3");
    if (btn3.isDouble())debug("isDouble 3");
    if (btn3.isTriple())debug("isTriple 3");
    */

    //debug(btn.getClikcs());
}

/*
    if (btnState && !btnFlag && (millis() - tmr > 20)) {
        btnFlag = true;
        tmr = millis();
        debug("press");
    }
*/
/*
    if (btnState && !btnFlag && (millis() - tmr > 50)) {
        btnFlag = true;
        tmr = millis();
        hold = millis();
        debug("press");
    }

    if (!btnState && btnFlag) {
        btnFlag = false;
        btnHold = false;
        debug("release");
    }

    if (btnState && btnFlag && !btnHold && (millis() - hold > 1000)) {
        btnHold = true;
        hold = millis();
        debug("hold");
    }

    if (btnHold && (millis() - stepHold > 500)) {
        static byte con = 0;
        stepHold = millis();
        debug(con++);
    }
*/
