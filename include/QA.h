#ifndef REALDATATESTS_QA_H
#define REALDATATESTS_QA_H

#include "TGraphErrors.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TFile.h"
#include "TDirectory.h"
#include <iostream>

using namespace std;

class QA {
public:
  QA(Int_t runId);
  void drawingPics();

  virtual ~QA();
  TH1D* Station0[2][2];
  TH1D* Station1[4][2];
  TH1D* Station2[2][2];

private:
  void init();
  Int_t runId;
};


#endif //REALDATATESTS_QA_H
