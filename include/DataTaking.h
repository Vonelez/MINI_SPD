#ifndef DATA_TACKING_H
#define DATA_TACKING_H

#include "BmnSiliconDigit.h"
#include "TGraphErrors.h"
#include "TTree.h"
#include "TBranch.h"
#include "TClonesArray.h"
#include "TCanvas.h"
#include "TH1.h"
#include <iostream>
#include <fstream>
#include <vector>

 
class DataTakinkg {
public:
  DataTakinkg(TTree *fTreeDigits, Int_t runId);

  virtual ~DataTakinkg();

private:
  Int_t runId;
  Double_t conversion;
  Int_t nEntries;
  Int_t count_processed;

  TTree *fTreeDigits;
  TBranch *fBranchSiDigits;
  TClonesArray *fSiliconDigits;

  std::vector <std::vector <int> > siliconHit;
  std::vector <int> hit;
  int trackCondidate[3][2]; 
  
  double station_z_axis[3] = {0., 344.8, 835.9};
  std::vector<double> hit_converted;
  std::vector <std::vector<double> > y_smeared;
  double delta_station2_reco = 0;
  double delta_station1_reco = 0;

  virtual void merging();
};
#endif