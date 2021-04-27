#include "../include/QA.h"

QA::QA(Int_t runId) {
  this->runId = runId;
  init();
  // drawingPics();
}

QA::~QA() = default;

void QA::init() {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      Station0[i][j] = new TH1D(Form("Station0_module%d_layer%d", i, j), "Signal hist", 10000, 0., 0.);
      Station2[i][j] = new TH1D(Form("Station2_module%d_layer%d", i, j), "Signal hist", 10000, 0., 0.);
    }
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      Station1[i][j] = new TH1D(Form("Station1_module%d_layer%d", i, j), "Signal hist", 10000, 0., 0.);
    }
  }
}

void QA::drawingPics() {
  TString imgFolder("/Users/andreizelenov/Documents/SPD/MINI_SPD/img/run_");
  imgFolder += runId;
  TString fileName("/results.root");
  TFile outFIle(imgFolder + fileName, "RECREATE");
  TDirectory *cd_station0 = outFIle.mkdir("station0");
  TDirectory *cd_station1 = outFIle.mkdir("station1");
  TDirectory *cd_station2 = outFIle.mkdir("station2");

  cd_station0->cd();
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      Station0[i][j]->Write(Form("module%d_layer%d", i, j));
    }
  }

  cd_station1->cd();
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      Station1[i][j]->Write(Form("module%d_layer%d", i, j));
    }
  }

  cd_station2->cd();
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      Station2[i][j]->Write(Form("module%d_layer%d", i, j));
    }
  }

  outFIle.Close();
  cout << "~~~ RootFile was saved ~~~" << endl;
}