#pragma once

struct BtnFlags {
    bool _btnState : 1;
    bool _btnFlag : 1;
    bool _btnHold : 1;

    //-----function flag-----//
    bool _btnStepFlag : 1;
    bool _btnHoldFlag : 1;
    bool _btnPressFlag : 1;
    bool _btnReleaseFlag : 1;
    bool _btnCounterFlag : 1;
    //-----function flag-----//
};

class Button {
public:
    Button(uint8_t pin, uint8_t deb = 50) {
        _pin = pin;
        _deb = deb;
        _hold = 400;
        _step = 200;
        _counter = 0;
        _clickTimeOut = 100;
        pinMode(_pin, INPUT_PULLUP);
    }

    void setStep(uint8_t x) { _step = x; }  //del isHolded()
    void setHold(uint8_t x) { _hold = x; }  //del
    void setDeb(uint8_t x) { _deb = x; }    //del
    void setClickTimeOut(uint8_t x) { _clickTimeOut = x; }
    uint16_t getClikcs() { return _lastCounter; }
    
    bool isHold() {
        if (BtnFlags._btnHoldFlag) {
            BtnFlags._btnHoldFlag = false;
            return true;
        } else return false;
    }

    bool isHolded() {
        if (BtnFlags._btnStepFlag) {
            BtnFlags._btnStepFlag = false;
            return true;
        } else return false;
    }

    bool isPress() {
        if (BtnFlags._btnPressFlag) {
            BtnFlags._btnPressFlag = false;
            return true;
        } else return false;
    }

    bool isRelease() {
        if (BtnFlags._btnReleaseFlag) {
            BtnFlags._btnReleaseFlag = false;
            return true;
        } else return false;
    }

    bool isSingle() {
        if (BtnFlags._btnCounterFlag && _lastCounter == 1) {
            BtnFlags._btnCounterFlag = false;
            return true;
        } else return false;
    }

    bool isDouble() {
        if (BtnFlags._btnCounterFlag && _lastCounter == 2) {
            BtnFlags._btnCounterFlag = false;
            return true;
        } else return false;
    }

    bool isTriple() {
        if (BtnFlags._btnCounterFlag && _lastCounter == 3) {
            BtnFlags._btnCounterFlag = false;
            return true;
        } else return false;
    }

    void tick() {
        BtnFlags._btnState = !digitalRead(_pin);

        if (BtnFlags._btnState && !BtnFlags._btnFlag && (millis() - _tmr >= _deb)) {
            BtnFlags._btnFlag = true;
            BtnFlags._btnPressFlag = true;  //func flag
            _tmr = millis();
            //debug("press");
        }

        if (!BtnFlags._btnState && BtnFlags._btnFlag) {
            BtnFlags._btnFlag = false;
            BtnFlags._btnHold = false;
            BtnFlags._btnReleaseFlag = true;   //func flag
            _tmr = millis();
            //debug("release");
            if (!BtnFlags._btnHold)_counter++;

        }

        if (BtnFlags._btnState && BtnFlags._btnFlag && !BtnFlags._btnHold && (millis() - _tmr >= _hold)) {
            BtnFlags._btnHold = true;
            BtnFlags._btnHoldFlag = true;   //func flag
            _tmr = millis();
            //debug("hold");
            _lastCounter = 0;
            _counter = 0;
        }

        if (BtnFlags._btnHold && (millis() - _stepTmr >= _step)) {
            _stepTmr = millis();
            BtnFlags._btnStepFlag = true;  //func flag
            //debug("step hold");
        }

        if (_counter != 0 && (millis() - _tmr >= _clickTimeOut)) {
            _lastCounter = _counter;
            _counter = 0;
            BtnFlags._btnCounterFlag = true;
        }

    }

private:
    BtnFlags BtnFlags;

    uint8_t _pin;       //?????? ????????????
    uint16_t _deb;      //???????????????? ???? ????????????????????????
    uint16_t _step;     //?????????????? ???????????????????????? ?????????????? isHolded()
    uint16_t _hold;     //???????????????? ???? ??????????????????

    uint32_t _tmr;      //????????????
    uint32_t _stepTmr;  //???????????? ?????????????? isHolded()

    uint16_t _counter;
    uint16_t _lastCounter;
    uint8_t _clickTimeOut;
};
