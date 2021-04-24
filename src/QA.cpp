#include "../include/QA.h"

QA::QA(SettingVShape *vshape, FittingShape *fittingShape, Derivative *derivative, Long_t runNum) {
  vShape = vshape->GetShape();
  meanValueGraph = fittingShape->getMeanGraph();
  sigmaGraph = fittingShape->getSigmaGraph();
  ndfGraph = fittingShape->getNdfGraph();
  chi2_ndfGraph = fittingShape->getChi2_ndfGraph();
  chi2Graph = fittingShape->getChi2Graph();
  derivativeGraph = derivative->getDerivGraph();
  derivMassi = derivative->getDerivGraphMassi();
  coordResolGraph = derivative->getCoordinateResolGraph();
  coordResolCut = derivative->getCoordinateResolGraphCut();
  this->runNum = runNum;

  init();
  drawingPics();
}

QA::~QA() = default;

void QA::init() {
  vShape->GetXaxis()->SetTitle("U (mm)");
  vShape->GetYaxis()->SetTitle("T (ns)");
  vShape->SetTitle("Initial vShape");

  meanValueGraph->GetXaxis()->SetTitle("U (mm)");
  meanValueGraph->GetYaxis()->SetTitle("T (ns)");
  meanValueGraph->GetYaxis()->SetTitleOffset(1.4);
  meanValueGraph->SetTitle("T = f(U)");

  sigmaGraph->GetXaxis()->SetTitle("U (mm)");
  sigmaGraph->GetYaxis()->SetTitle("#sigma_{T} (ns)");
  sigmaGraph->SetTitle("#sigma_{T} = f(U)");


  ndfGraph->GetXaxis()->SetTitle("U (mm)");
  ndfGraph->GetYaxis()->SetTitle("NDF");

  chi2_ndfGraph->GetXaxis()->SetTitle("U (mm)");
  chi2_ndfGraph->GetYaxis()->SetTitle("#chi^{2} / NDF");

  chi2Graph->GetXaxis()->SetTitle("U (mm)");
  chi2Graph->GetYaxis()->SetTitle("#chi^{2}");

  derivativeGraph->GetXaxis()->SetTitle("U (mm)");
  derivativeGraph->GetYaxis()->SetTitle("F'");
  derivativeGraph->SetTitle("F' = f(U)");

  coordResolGraph->GetXaxis()->SetTitle("U (mm)");
  coordResolGraph->GetYaxis()->SetTitle("#sigma_{U} (mm)");
  coordResolGraph->SetTitle("#sigma_{U} = f(#sigma_{T})");

  coordResolCut->GetXaxis()->SetTitle("U (mm)");
  coordResolCut->GetYaxis()->SetTitle("#sigma_{U} (mm)");
  coordResolCut->SetTitle("#sigma_{U} with #chi^{2} / NDF < 5 Cut");
}

void QA::drawingPics() {
  TString imgFolder("img/run_");
  imgFolder += runNum;
  TString fileName("/results.root");
  TFile binsFile(imgFolder + fileName, "RECREATE");
  vShape->Write("vShape");
  meanValueGraph->Write("meanValue");
  sigmaGraph->Write("sigma");
  ndfGraph->Write("NDF");
  chi2_ndfGraph->Write("chi2/NDF");
  chi2Graph->Write("chi2");
  derivativeGraph->Write("derivative");
  derivMassi->Write("derivMassi");
  coordResolGraph->Write("coordResol");
  coordResolCut->Write("coordResolCut");
  binsFile.Close();
  cout << "~~~ RootFile was saved ~~~" << endl;

  TString shapeName = imgFolder + "/vShape.pdf";
  TCanvas *shape = new TCanvas("Shape", "Shape", 1400, 1000);
  shape->cd();
  vShape->Draw("COLZ");
  shape->SaveAs(shapeName, "Q");

  TString meanValueName = imgFolder + "/fitMean.pdf";
  TCanvas *meanValue = new TCanvas("fit mean value", "fit mean value", 1400, 1000);
  meanValue->cd();
  meanValueGraph->SetMarkerColor(kGreen + 2);
  meanValueGraph->SetMarkerSize(1.2);
  meanValueGraph->SetMarkerStyle(24);
  meanValueGraph->Draw("AP");
  meanValue->SaveAs(meanValueName, "Q");

  TString sigmaName = imgFolder + "/fitSigma.pdf";
  TCanvas *sigma = new TCanvas("fit sigma", "fit sigma", 1400, 1000);
  sigma->cd();
  sigmaGraph->SetMarkerColor(kRed + 2);
  sigmaGraph->SetMarkerSize(1.2);
  sigmaGraph->SetMarkerStyle(24);
  sigmaGraph->Draw("AP");
  sigma->SaveAs(sigmaName, "Q");

  TString derivativeName = imgFolder + "/derivative.pdf";
  TCanvas *derivative = new TCanvas("derivative", "derivative", 1400, 1000);
  derivative->cd();
  derivativeGraph->SetMarkerColor(kBlue + 2);
  derivativeGraph->SetMarkerSize(1.2);
  derivativeGraph->SetMarkerStyle(24);
  derivativeGraph->Draw("AP");
  derivative->SaveAs(derivativeName, "Q");

  TString coordResolName = imgFolder + "/coordResol.pdf";
  TCanvas *coordResol = new TCanvas("coord resolution", "coord resolution", 1400, 1000);
  coordResol->cd();
  coordResolGraph->GetYaxis()->SetRangeUser(0., 0.5);
  coordResolGraph->SetMarkerColor(kYellow + 2);
  coordResolGraph->SetMarkerSize(1.2);
  coordResolGraph->SetMarkerStyle(24);
  coordResolGraph->Draw("AP");
  coordResol->SaveAs(coordResolName, "Q");
}