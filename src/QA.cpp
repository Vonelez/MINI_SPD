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
      Station0[i][j] = new TH1D(Form("Station0_module%d_layer%d", i, j), "Signal hist", 2000, 0., 0.);
      Station2[i][j] = new TH1D(Form("Station2_module%d_layer%d", i, j), "Signal hist", 2000, 0., 0.);
    }
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      Station1[i][j] = new TH1D(Form("Station1_module%d_layer%d", i, j), "Signal hist", 2000, 0., 0.);
    }
  }

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      if (j == 0) {
        Correlations[i][j] = new TH2D(Form("Correlation_X_type_%d", i), "Correlation hist", 128, 1., 641., 128, 1., 641.);
      } else {
        Correlations[i][j] = new TH2D(Form("Correlation_Y_type_%d", i), "Correlation hist", 128, 1., 641., 128, 1., 641.);
      }
    }
  }  
  Correlations[0][0]->GetXaxis()->SetTitle("Station 2 / strip number");
  Correlations[0][0]->GetYaxis()->SetTitle("Station 1 / strip number");

  Correlations[0][1]->GetXaxis()->SetTitle("Station 2 / strip number");
  Correlations[0][1]->GetYaxis()->SetTitle("Station 1 / strip number");

  Correlations[1][0]->GetXaxis()->SetTitle("Station 2 / strip number");
  Correlations[1][0]->GetYaxis()->SetTitle("Station 0 / strip number");

  Correlations[1][1]->GetXaxis()->SetTitle("Station 2 / strip number");
  Correlations[1][1]->GetYaxis()->SetTitle("Station 0 / strip number");

  Correlations[2][0]->GetXaxis()->SetTitle("Station 0 / strip number");
  Correlations[2][0]->GetYaxis()->SetTitle("Station 1 / strip number");

  Correlations[2][1]->GetXaxis()->SetTitle("Station 0 / strip number");
  Correlations[2][1]->GetYaxis()->SetTitle("Station 1 / strip number");
}

void QA::drawingPics() {
  TString imgFolder("/Users/andreizelenov/Documents/SPD/MINI_SPD/img/run_");
  imgFolder += runId;
  TString fileName("/results.root");
  TFile outFIle(imgFolder + fileName, "RECREATE");
  TDirectory *cd_station0 = outFIle.mkdir("station0");
  TDirectory *cd_station1 = outFIle.mkdir("station1");
  TDirectory *cd_station2 = outFIle.mkdir("station2");
  TDirectory *cd_correlations = outFIle.mkdir("correlations");

  cd_station0->cd();
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      Station0[i][j]->Write(Form("module%d_layer%d", i, j));
      auto Station0_canvas = new TCanvas("Station0_canvas", "Station0_canvas", 1400, 1000);
      Station0_canvas->cd();
      Station0[i][j]->Draw();
      Station0_canvas->SaveAs(imgFolder + Form("/signal/Station0_module%d_layer%d.pdf", i, j), "Q");
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
      Station1_canvas->SaveAs(imgFolder + Form("/signal/Station1_module%d_layer%d.pdf", i, j), "Q");
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
      Station2_canvas->SaveAs(imgFolder + Form("/signal/Station2_module%d_layer%d.pdf", i, j), "Q");
      delete Station2_canvas;
    }
  }

  cd_correlations->cd();
  for (int i = 0; i < 3; i++) {
    Correlations[i][0]->Write(Form("Correlation_X_type_%d", i));
    Correlations[i][1]->Write(Form("Correlation_Y_type_%d", i));
    auto correlations_canvas = new TCanvas("correlations_canvas", "correlations_canvas", 1400, 2000);
    correlations_canvas->Divide(1, 2);
    correlations_canvas->cd(1);
    Correlations[i][0]->Draw("COLZ");
    correlations_canvas->cd(2);
    Correlations[i][1]->Draw("COLZ");
    correlations_canvas->SaveAs(imgFolder + Form("/signal/Correlations_type_%d.pdf", i), "Q");
    delete correlations_canvas;
  }

  auto correlations_canvas_only_X = new TCanvas("correlations_canvas", "correlations_canvas", 1900, 3000);
    correlations_canvas_only_X->Divide(1, 3);
    correlations_canvas_only_X->cd(1);
    Correlations[0][0]->Draw("COLZ");
    correlations_canvas_only_X->cd(2);
    Correlations[1][0]->Draw("COLZ");
    correlations_canvas_only_X->cd(3);
    Correlations[2][0]->Draw("COLZ");
    correlations_canvas_only_X->SaveAs(imgFolder + "/signal/Correlations_onlyX.pdf", "Q");
    delete correlations_canvas_only_X;


  outFIle.Close();
  cout << "~~~ RootFile was saved ~~~" << endl;
}