#include <iostream>
#include "include/DataTaking.h"
#include "TFile.h"
#include "TNamed.h"

int main() {
  TString dir("/Users/andreizelenov/Documents/SPD/MINI_SPD/");
  Int_t runId = 1;
  TString fileName = Form("data/stand_run000%d_digits.root", runId);
  TString RootName(dir + fileName);
  
  TFile *AnaFile;
  AnaFile = TFile::Open(RootName, "read");
  TTree *fTreeDigits;
  AnaFile->GetObject("cbmsim", fTreeDigits);

  auto *dataTakinkg = new DataTakinkg(fTreeDigits);

  std::cout << "I did it" << std::endl;
//  AnaFile->TFile::Close();

  return 0;
}
