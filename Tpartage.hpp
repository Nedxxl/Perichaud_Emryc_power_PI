#ifndef TPARTAGE_HPP
#define TPARTAGE_HPP

#include "mutex.hpp"
#include "singleton.hpp"
#include "sem.hpp"
#include <stdint.h>
#include <string.h>
#include "screen.hpp"
#include "mqtt.hpp"

class TPartage : public TSingleton<TPartage>
{
    friend class TSingleton<TPartage>;

private:
    float modbusValue = 0;
    float van = 0;
    float vbn = 0;
    float vab = 0;
    float ia = 0;
    float ib = 0;
    float kw = 0;
    float fp = 0;
    float kwh = 0;
    bool wait = false;

    bool changeModbusValue = false;
    bool changeVan = false;
    bool changeVbn = false;
    bool changeVab = false;
    bool changeIa = false;
    bool changeIb = false;
    bool changeKw = false;
    bool changeFp = false;
    bool changeKwh = false;

public:
    TMutex mutex;
    TScreen *screen = new TScreen();
    TPartage();
    ~TPartage();

    void setModbusValue(float val, bool change = true);
    void setVan(float val, bool change = true);
    void setVbn(float val, bool change = true);
    void setVab(float val, bool change = true);
    void setIa(float val, bool change = true);
    void setIb(float val, bool change = true);
    void setKw(float val, bool change = true);
    void setFp(float val, bool change = true);
    void setKwh(float val, bool change = true);
    void setWait(bool val);

    float getModbusValue(void);
    float getVan(void);
    float getVbn(void);
    float getVab(void);
    float getIa(void);
    float getIb(void);
    float getKw(void);
    float getFp(void);
    float getKwh(void);
    bool getWait(void);
};

#endif // TPARTAGE_HPP