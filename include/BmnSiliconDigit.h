#ifndef BMNSILICONDIGIT_H
#define BMNSILICONDIGIT_H

#include <iostream>
#include <vector>

#include "TNamed.h"

using namespace std;

/*
    int fStation - номер станции кремниев. 0 - верхняя, 1 - средняя, 2 - нижняя;
    int fModule - номер модуля в станции от 0 до 1 в верхней и нижней станции, от 0 до 3 в средней. Схема с номерами модулей в приложенном файле modules_numiration.png.
    int fLayer - сторона кремния. 0 - X (прямые стрипы), 1 - Y (косые стрипы);
    int fStrip - номер сработавшего стрипа (0 - 639);
    double fSignal - амплитуда сигнала;
    bool fIsGoodDigit - 0 если стрип помечен как шумящий. Перед работой со стрипом проверьте что это поле равно 1.
 */

class BmnSiliconDigit:public TNamed {
private:
    int fStation;
    int fModule;
    int fLayer; // 0 - lower layer, 1 - upper layer
    int fStrip;
    double fSignal;
    bool fIsGoodDigit;
    
public:
    BmnSiliconDigit();
    virtual ~BmnSiliconDigit();


    BmnSiliconDigit(BmnSiliconDigit* digit);
    BmnSiliconDigit(int iStation, int iModule, int iLayer, int iStrip, double iSignal);



    int GetStation() {
        return fStation;
    }

    int GetModule() {
        return fModule;
    }

    int GetStripLayer() {
        return fLayer;
    }

    int GetStripNumber() {
        return fStrip;
    }

    double GetStripSignal() {
        return fSignal;
    }

    void SetStation(int station) {
        fStation = station;
    }

    void SetModule(int module) {
        fModule = module;
    }

    void SetStripLayer(int layer) {
        fLayer = layer;
    }

    void SetStripNumber(int num) {
        fStrip = num;
    }

    void SetStripSignal(double signal) {
        fSignal = signal;
    }
        
    void SetIsGoodDigit(bool tmp) { fIsGoodDigit = tmp; }
    bool IsGoodDigit() { return fIsGoodDigit; }
    void PrintHit(unsigned int digiN);

    ClassDef(BmnSiliconDigit,1);
};

#endif /* BMNSILICONDIGIT_H */

