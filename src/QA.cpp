#include "QA.h"

using namespace std;

QA::QA(Int_t runId) {
  this->runId = runId;
  init();
  // drawingPics();
}

QA::~QA() = default;

void QA::init() {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      Station0[i][j] = new TH1D(Form("Station0_module%d_layer%d", i, j), "Signal hist", 5000, 0., 0.);
      Station2[i][j] = new TH1D(Form("Station2_module%d_layer%d", i, j), "Signal hist", 5000, 0., 0.);
    }
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      Station1[i][j] = new TH1D(Form("Station1_module%d_layer%d", i, j), "Signal hist", 5000, 0., 0.);
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
      auto Station0_canvas = new TCanvas("Station0_canvas", "Station0_canvas", 1400, 1000);
      Station0_canvas->cd();
      Station0[i][j]->Draw();
      Station0_canvas->SaveAs(Form("img/run_%d/sigal/Station0_module%d_layer%d.pdf", runId, i, j), "Q");
      delete Station0_canvas;
    }
  }

  cd_station1->cd();
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      Station1[i][j]->Write(Form("module%d_layer%d", i, j));
      auto Station1_canvas = new TCanvas("Station1_canvas", "Station1_canvas", 1400, 1000);
      Station1_canvas->cd();
      Station1[i][j]->Draw();
      Station1_canvas->SaveAs(Form("img/run_%d/signal/Station1_module%d_layer%d.pdf", runId, i, j), "Q");
      delete Station1_canvas;
    }
  }

  cd_station2->cd();
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      Station2[i][j]->Write(Form("module%d_layer%d", i, j));
      auto Station2_canvas = new TCanvas("Station2_canvas", "Station2_canvas", 1400, 1000);
      Station2_canvas->cd();
      Station2[i][j]->Draw();
      Station2_canvas->SaveAs(Form("img/run_%d/signal/Station2_module%d_layer%d.pdf", runId, i, j), "Q");
      delete Station2_canvas;
    }
  }

  outFIle.Close();
  cout << "~~~ RootFile was saved ~~~" << endl;
}