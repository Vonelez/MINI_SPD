#include "DataTaking.h"
#include "QA.h"
#include "BmnSiliconDigit.h"

using namespace std;

DataTakinkg::DataTakinkg(TTree *fTreeDigits, Int_t runId) {
  this->fTreeDigits = fTreeDigits;
  this->runId = runId;
  fSiliconDigits = new TClonesArray("BmnSiliconDigit");
  fBranchSiDigits = fTreeDigits->GetBranch("SILICON");
  fBranchSiDigits->SetAutoDelete(kTRUE);
  fTreeDigits->SetBranchAddress("SILICON", &fSiliconDigits);
  conversion = 25.0 / 1024;
  count_processed = 0;
  merging();
}

DataTakinkg::~DataTakinkg() = default;


void DataTakinkg::merging() {

  nEntries = (Int_t) fTreeDigits->GetEntries();
  cout << "requesting " << nEntries << " events..." << endl;

  auto *output = new QA(runId);

  cout << "Begin analysis..." << endl;
  for (Int_t i = 0; i < nEntries; i++) {
    // progress bar
    // int barWidth = 70;
    // cout << "\033[0;32m[\033[0m";
    // auto pos = (int) (barWidth * ((float) i / (float) nEntries));
    // for (int bar = 0; bar < barWidth; ++bar) {
    //   if (bar < pos) cout << "\033[0;32m=\033[0m";
    //   else if (bar == pos) cout << "\033[0;32m>\033[0m";
    //   else cout << " ";
    // }
    // cout << "\033[0;32m]\033[0m " << "\033[0;31m" << int(((float) i / (float) nEntries) * 100.0 + 1) << "%\r \033[0m";
    // cout.flush();
    // progress bar
    fBranchSiDigits->GetEntry(i);
    unsigned int nDigits = fSiliconDigits->GetEntries();
    // printf("nDigits: %d\n", nDigits);
    printf("Event Number: %d\n", i);
    for (unsigned int iDigit = 0; iDigit < nDigits; iDigit++) {
      // cout << "point 0" << endl;
      BmnSiliconDigit * siDigit = (BmnSiliconDigit *)fSiliconDigits->At(iDigit);
      
      // siDigit->PrintHit(iDigit);
      // cout << "point 1" << endl;
      if (!siDigit->IsGoodDigit()) cout << siDigit->IsGoodDigit() << " not Good " << endl;
      // if (!siDigit->IsGoodDigit()) continue;

      int station = siDigit->GetStation();
      // printf("station: %d\n", station);
      int module = siDigit->GetModule();
      // printf("module: %d\n", module);
      int layer = siDigit->GetStripLayer();
      // printf("layer: %d\n", layer);
      int strip = siDigit->GetStripNumber();
      // printf("strip: %d\n", strip);
      double signal = siDigit->GetStripSignal();
      // printf("signal: %f\n", signal);
      // cout << "point 2" << endl;
      // h1Signal[station]->Fill(abs(signal));
      // cout << "point 3" << endl;
      if (station == 0) {
        output->Station0[module][layer]->Fill(signal);
      } else if (station == 1) {
        output->Station1[module][layer]->Fill(signal);
        // printf("Event Number: %d\n", i);
        // siDigit->PrintHit(iDigit);
      } else {
        output->Station2[module][layer]->Fill(signal);
      }
    }
    count_processed++;
  }
  output->drawingPics();
  cout << endl;
}
