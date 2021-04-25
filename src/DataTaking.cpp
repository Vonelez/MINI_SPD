#include "../include/DataTaking.h"
#include "../include/BmnSiliconDigit.h"

DataTakinkg::DataTakinkg(TTree *fTreeDigits) {
  this->fTreeDigits = fTreeDigits;
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

  TString histName;
  TString histDiscription;
  for (int iStation = 0; iStation < 3; iStation++)
  {
      histName = Form("h1_amplitude_station%d", iStation);
      histDiscription = Form("Silicon signal amplitude (station %d);AU;", iStation);
      h1Signal[iStation] = new TH1D(histName, histDiscription, 80, 0, 800);
  }

  cout << "Begin analysis..." << endl;
  for (Int_t i = 0; i < nEntries; i++) {
<<<<<<< HEAD
/// progress bar
    int barWidth = 70;
    cout << "\033[0;32m[\033[0m";
    auto pos = (int) (barWidth * ((float) i / (float) nEntries));
    for (int bar = 0; bar < barWidth; ++bar) {
      if (bar < pos) cout << "\033[0;32m=\033[0m";
      else if (bar == pos) cout << "\033[0;32m>\033[0m";
      else cout << " ";
    }
    cout << "\033[0;32m]\033[0m " << "\033[0;31m" << int(((float) i / (float) nEntries) * 100.0 + 1) << "%\r \033[0m";
    cout.flush();
/// progress bar
=======
// /// progress bar
//     int barWidth = 70;
//     cout << "\033[0;32m[\033[0m";
//     auto pos = (int) (barWidth * ((float) i / (float) nEntries));
//     for (int bar = 0; bar < barWidth; ++bar) {
//       if (bar < pos) cout << "\033[0;32m=\033[0m";
//       else if (bar == pos) cout << "\033[0;32m>\033[0m";
//       else cout << " ";
//     }
//     cout << "\033[0;32m]\033[0m " << "\033[0;31m" << int(((float) i / (float) nEntries) * 100.0 + 1) << "%\r \033[0m";
//     cout.flush();
// /// progress bar
>>>>>>> 721f003f27300bba86de141cb8101cb7c30cf203
    fBranchSiDigits->GetEntry(i);
    Int_t nDigits = fSiliconDigits->GetEntriesFast();
        // printf("nDigits: %d\n", nDigits);
        for (size_t iDigit = 0; iDigit < nDigits; iDigit++) {
          auto siDigit = (BmnSiliconDigit *)fSiliconDigits->At(iDigit);

          if (!siDigit->IsGoodDigit()) continue;

          Int_t station = siDigit->GetStation();
          Int_t module = siDigit->GetModule();
          Int_t layer = siDigit->GetStripLayer();
          Int_t strip = siDigit->GetStripNumber();
          Double_t signal = siDigit->GetStripSignal();

          h1Signal[station]->Fill(abs(signal));
        }

    count_processed++;
  }
  cout << endl;
}
