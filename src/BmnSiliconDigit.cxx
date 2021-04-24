#include <stdio.h>

#include "../include/BmnSiliconDigit.h"


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
	printf("%4d ; s: %2d m: %2d l: %2d ss: %4d  amp: %5.2f good: %1d\n", digiN, fStation, fModule, fLayer, fStrip, fSignal, int(fIsGoodDigit));
}

