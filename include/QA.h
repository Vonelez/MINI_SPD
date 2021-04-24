#ifndef REALDATATESTS_QA_H
#define REALDATATESTS_QA_H

#include "TGraphErrors.h"
#include "TH2D.h"
#include "SettingVShape.h"
#include "FittingShape.h"
#include "Derivative.h"

class QA {
public:
  QA(SettingVShape *vshape, FittingShape *fittingShape, Derivative *derivative, Long_t runNum);

  virtual ~QA();

private:
  TH2D *vShape;
  TGraphErrors *meanValueGraph, *sigmaGraph, *ndfGraph, *chi2_ndfGraph, *chi2Graph;
  TGraphErrors *derivativeGraph, *derivMassi, *coordResolGraph, *coordResolCut;
  Long_t runNum;

  void init();

  void drawingPics();
};


#endif //REALDATATESTS_QA_H
