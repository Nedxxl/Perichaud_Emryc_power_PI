#include "Tpartage.hpp"

TPartage::TPartage()
{
}

TPartage::~TPartage()
{
}

void TPartage::setModbusValue(float val, bool change)
{
    mutex.take();
    modbusValue = val;
    changeModbusValue = change;
    mutex.release();
}

void TPartage::setVan(float val, bool change)
{
    mutex.take();
    van = val;
    changeVan = change;
    mutex.release();
}

void TPartage::setVbn(float val, bool change)
{
    mutex.take();
    vbn = val;
    changeVbn = change;
    mutex.release();
}

void TPartage::setVab(float val, bool change)
{
    mutex.take();
    vab = val;
    changeVab = change;
    mutex.release();
}

void TPartage::setIa(float val, bool change)
{
    mutex.take();
    ia = val;
    changeIa = change;
    mutex.release();
}   

void TPartage::setIb(float val, bool change)
{
    mutex.take();
    ib = val;
    changeIb = change;
    mutex.release();
}

void TPartage::setKw(float val, bool change)
{
    mutex.take();
    kw = val;
    changeKw = change;
    mutex.release();
}

void TPartage::setFp(float val, bool change)
{
    mutex.take();
    fp = val;
    changeFp = change;
    mutex.release();
}

void TPartage::setKwh(float val, bool change)
{
    mutex.take();
    kwh = val;
    changeKwh = change;
    mutex.release();
}

void TPartage::setWait(bool val)
{
    mutex.take();
    wait = val;
    mutex.release();
}

float TPartage::getModbusValue(void)
{
    float val;
    mutex.take();
    val = modbusValue;
    mutex.release();
    return val;
}

float TPartage::getVan(void)
{
    float val;
    mutex.take();
    val = van;
    mutex.release();
    return val;
}

float TPartage::getVbn(void)
{
    float val;
    mutex.take();
    val = vbn;
    mutex.release();
    return val;
}

float TPartage::getVab(void)
{
    float val;
    mutex.take();
    val = vab;
    mutex.release();
    return val;
}

float TPartage::getIa(void)
{
    float val;
    mutex.take();
    val = ia;
    mutex.release();
    return val;
}

float TPartage::getIb(void)
{
    float val;
    mutex.take();
    val = ib;
    mutex.release();
    return val;
}

float TPartage::getKw(void)
{
    float val;
    mutex.take();
    val = kw;
    mutex.release();
    return val;
}

float TPartage::getFp(void)
{
    float val;
    mutex.take();
    val = fp;
    mutex.release();
    return val;
}

float TPartage::getKwh(void)
{
    float val;
    mutex.take();
    val = kwh;
    mutex.release();
    return val;
}

bool TPartage::getWait(void)
{
    bool val;
    mutex.take();
    val = wait;
    mutex.release();
    return val;
}
