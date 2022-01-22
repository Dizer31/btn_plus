#pragma once

struct BtnFlags {
    bool _btnState : 1;
    bool _btnFlag : 1;
    bool _btnHoldF : 1;
    bool _stepHoldF : 1;

    bool _btnPressFlag : 1;
    bool _btnReleaseFlag : 1;
    bool _btnHoldFlag : 1;

    bool _stepF : 1;
    bool _stepFunF : 1;
};

class Btn {
public:
    Btn(uint8_t pin, uint8_t deb = 50, uint8_t stepT = 200) {
        _pin = pin;
        _deb = deb;
        _stepT = stepT;
        _step = 200;
        pinMode(_pin, INPUT_PULLUP);
    }

    void setStep(int x) {
        _step = x;
    }

    void setDeb(int x) {
        _deb = x;
    }

    void setStepHold(int x) {
        _stepT = x;
    }

    void tick() {
        BtnFlags._btnState = !digitalRead(_pin);
        uint32_t _mil = millis();
        //debug(_stepCon);
        /*
          if (btnState && !BtnFlags && (millis() - tmr > 20)) {
            BtnFlags = true;
            tmr = millis();
            debug("press");
          }
        */
        if (BtnFlags._btnState && !BtnFlags._btnFlag && (_mil - _tmr > _deb)) {
            BtnFlags._btnFlag = true;
            BtnFlags._btnPressFlag = true;
            _tmr = _mil;
            _hold = _mil;
            _tmrStep = _mil;
            //debug("press");
        }

        if (BtnFlags._btnFlag && (_mil - _tmrStep < _step)) {
            BtnFlags._stepF = true;
            BtnFlags._stepFunF = true;
        } else if ((_mil - _tmrStep >= _step)) {
            _stepCon = 0;
        }

        if (!BtnFlags._btnState && BtnFlags._btnFlag) {
            if (BtnFlags._stepF)_stepCon++;
            BtnFlags._btnFlag = false;
            BtnFlags._btnHoldF = false;
            BtnFlags._stepHoldF = false;
            BtnFlags._btnReleaseFlag = false;
            BtnFlags._btnHoldFlag = false;
            BtnFlags._stepF = false;
            //debug("release");
        }

        if (BtnFlags._btnState && BtnFlags._btnFlag && !BtnFlags._btnHoldF && (_mil - _hold > 1000)) {
            BtnFlags._btnHoldF = true;
            BtnFlags._btnHoldFlag = true;
            _hold = _mil;
            //debug("hold");
        }

        if (BtnFlags._btnHoldF && (_mil - _stepHold > _stepT)) {
            _stepHold = _mil;
            BtnFlags._stepHoldF = true;
            //debug("step hold");
        }
    }

    bool isHold() {
        if (BtnFlags._btnHoldFlag) {
            BtnFlags._btnHoldFlag = false;
            return true;
        } else return false;
    }

    bool isHolded() {
        if (BtnFlags._stepHoldF) {
            BtnFlags._stepHoldF = false;
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
        if (!BtnFlags._btnReleaseFlag) {
            BtnFlags._btnReleaseFlag = true;
            return true;
        } else return false;
    }

    bool isSingle() {
        if (_stepCon == 1 && BtnFlags._stepFunF) {
            BtnFlags._stepFunF = false;
            return true;
        } else return false;
    }

    bool isDouble() {
        if (_stepCon == 2 && BtnFlags._stepFunF) {
            BtnFlags._stepFunF = false;
            return true;
        } else return false;
    }

    bool isTriple() {
        if (_stepCon == 3 && BtnFlags._stepFunF) {
            BtnFlags._stepFunF = false;
            return true;
        } else return false;
    }
private:
    BtnFlags BtnFlags;

    uint8_t _pin;
    uint16_t _deb;
    uint16_t _step;
    uint16_t _stepT;

    uint32_t _tmr;
    uint32_t _hold;
    uint32_t _stepHold;

    uint16_t _stepCon;
    uint32_t _tmrStep;
};
