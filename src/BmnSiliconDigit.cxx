#include <stdio.h>
#include "../include/BmnSiliconDigit.h"

using namespace std;

BmnSiliconDigit::BmnSiliconDigit() {
    fStation = -1;
    fModule = 0;
    fLayer = 0;
    fStrip = 0;
    fSignal = 0.0;
    fIsGoodDigit = true;
}

BmnSiliconDigit::BmnSiliconDigit(BmnSiliconDigit* digit) {
    fStation = digit->fStation;
    fModule = digit->fModule;
    fLayer = digit->fLayer;
    fStrip = digit->fStrip;
    fSignal = digit->fSignal;
    fIsGoodDigit = digit->fIsGoodDigit;
}

BmnSiliconDigit::BmnSiliconDigit(int iStation, int iModule, int iLayer, int iStrip, double iSignal) {
    fStation = iStation;
    fModule = iModule;
    fLayer = iLayer;
    fStrip = iStrip;
    fSignal = iSignal;
    fIsGoodDigit = true;
}

BmnSiliconDigit::~BmnSiliconDigit() {

}

void BmnSiliconDigit::PrintHit(unsigned int digiN){
	printf("%4d --- station: %2d | module: %2d | layer: %2d | strip: %4d | signal: %5.2f | good: %1d\n", digiN, fStation, fModule, fLayer, fStrip, fSignal, int(fIsGoodDigit));
}

