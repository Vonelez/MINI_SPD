#include "DataTaking.h"
#include "QA.h"
#include "BmnSiliconDigit.h"

using namespace std;

DataTakinkg::DataTakinkg(TTree *fTreeDigits, Int_t runId)
{
  this->fTreeDigits = fTreeDigits;
  this->runId = runId;
  fSiliconDigits = new TClonesArray("BmnSiliconDigit");
  fBranchSiDigits = fTreeDigits->GetBranch("SILICON");
  fBranchSiDigits->SetAutoDelete(kTRUE);
  fTreeDigits->SetBranchAddress("SILICON", &fSiliconDigits);
  count_processed = 0;
  merging();
}

DataTakinkg::~DataTakinkg() = default;

void DataTakinkg::merging()
{

  nEntries = (Int_t)fTreeDigits->GetEntries();
  cout << "requesting " << nEntries << " events..." << endl;

  auto *output = new QA(runId);

  cout << "Begin analysis..." << endl;
  int nIdealTracks = 0;
  for (Int_t i = 0; i < nEntries; i++)
  {
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
    if (nDigits != 6)
      continue;
    siliconHit.clear();
    printf("Event Number: %d\n", i);
    for (unsigned int iDigit = 0; iDigit < nDigits; iDigit++)
    {
      BmnSiliconDigit *siDigit = (BmnSiliconDigit *)fSiliconDigits->At(iDigit);

      int station = siDigit->GetStation();
      int module = siDigit->GetModule();
      int layer = siDigit->GetStripLayer();
      int strip = siDigit->GetStripNumber();
      double signal = siDigit->GetStripSignal();
      if (station == 0)
      {
        output->Station0[module][layer]->Fill(signal);
      }
      else if (station == 1)
      {
        output->Station1[module][layer]->Fill(signal);
        if (module == 3)
          module = 1;
      }
      else
      {
        output->Station2[module][layer]->Fill(signal);
      }

      if (module != 1)
        continue;
      else
        // siDigit->PrintHit(iDigit);

        hit.push_back(station);
      hit.push_back(module);
      hit.push_back(layer);
      hit.push_back(strip);
      siliconHit.push_back(hit);
      hit.clear();
    }
    count_processed++;
    int check[3] = {0, 0, 0};
    for (int i = 0; i < siliconHit.size(); i++)
    {
      if (siliconHit[i].at(0) == 0)
      {
        check[0]++;
      }
      else if (siliconHit[i].at(0) == 1)
      {
        check[1]++;
      }
      else if (siliconHit[i].at(0) == 2)
      {
        check[2]++;
      }
    }

    if (check[0] > 0 && check[1] > 0 && check[2] > 0)
    {
      for (int i = 0; i < siliconHit.size(); i++)
      {
        BmnSiliconDigit *siDigit = (BmnSiliconDigit *)fSiliconDigits->At(i);
        siDigit->PrintHit(i);
      }
    }

    if (siliconHit.size() != 6)
      continue;
    int counter = 0;
    for (int i = 0; i < 3; i++)
    {
      if (siliconHit[2 * i].at(0) != siliconHit[2 * i + 1].at(0))
        continue;
      else if (siliconHit[2 * i].at(1) != siliconHit[2 * i + 1].at(1))
        continue;
      else if (siliconHit[2 * i].at(2) == siliconHit[2 * i + 1].at(2))
        continue;
      else
        counter++;
    }

    // printf("Event Number: %d\n", i);
    if (counter == 3)
    {
      for (int i = 0; i < 6; i++)
      {
        BmnSiliconDigit *siDigit = (BmnSiliconDigit *)fSiliconDigits->At(i);
        // siDigit->PrintHit(i);
        // cout << "end of hit candidate \n";
      }
      nIdealTracks++;
      if (abs(siliconHit[0].at(3) - siliconHit[2].at(3)) > 400)
        continue;
      if (abs(siliconHit[4].at(3) - siliconHit[2].at(3)) > 300)
        continue;
      siliconHit[2].at(3) = siliconHit[2].at(3) - 34;

      output->Correlations[0][0]->Fill(siliconHit[0].at(3), siliconHit[2].at(3)); //station 2 and 1 – X

      output->Correlations[0][1]->Fill(siliconHit[1].at(3), siliconHit[3].at(3)); //station 2 and 1 – Y

      output->Correlations[1][0]->Fill(siliconHit[0].at(3), siliconHit[4].at(3)); //station 2 and 0 – X

      output->Correlations[1][1]->Fill(siliconHit[1].at(3), siliconHit[5].at(3)); //station 2 and 0 – Y

      output->Correlations[2][0]->Fill(siliconHit[4].at(3), siliconHit[2].at(3)); //station 0 and 1 – X

      output->Correlations[2][1]->Fill(siliconHit[5].at(3), siliconHit[3].at(3)); //station 0 and 1 – Y

      hit_converted = {siliconHit[4].at(3) * 0.095, siliconHit[2].at(3) * 0.095, siliconHit[0].at(3) * 0.095};
      y_smeared.push_back(hit_converted);
      hit_converted.clear();
    }
  }
  output->drawingPics();
  cout << "Num of ideal tracks: " << nIdealTracks << endl;
  cout << endl;

  for (int k = 0; k < 1; k++)
  {
    cout << "ITERATION " << k + 1 << endl;
    for (int i = 0; i < y_smeared.size(); i++)
    {
      y_smeared[i].at(2) = y_smeared[i].at(2) - delta_station2_reco;
      y_smeared[i].at(1) = y_smeared[i].at(1) - delta_station1_reco;
    }
    double a_mean = 0;
    for (int i = 0; i < y_smeared.size(); i++)
    {
      a_mean += (y_smeared[i].at(2) - y_smeared[i].at(0)) / (station_z_axis[2] - station_z_axis[0]);
      // delta_station2_reco_hist->Fill(y_smeared[i].at(2) - y_smeared[i].at(0));
    }
    a_mean = a_mean / y_smeared.size();

    delta_station2_reco = a_mean * (station_z_axis[2] - station_z_axis[0]);

    cout << "delta in station 2 is \t" << delta_station2_reco << endl;

    double Delta = 0;
    double a_reco = 0;
    double b_reco = 0;
    double alpha = 0;
    double beta = 0;
    delta_station1_reco = 0;
    for (int i = 0; i < y_smeared.size(); i++)
    {
      double z = 0;
      double y = 0;
      double S = 0;
      double S_z = 0;
      double S_y = 0;
      double S_zz = 0;
      double S_zy = 0;
      for (int l = 0; l < 3; ++l)
      {
        z = station_z_axis[l];
        if (l == 2)
          y = y_smeared[i].at(l) - delta_station2_reco;
        else
          y = y_smeared[i].at(l);

        S++;
        S_z += z;
        S_y += y;
        S_zz += pow(z, 2);
        S_zy += z * y;
      }
      Delta = (S * S_zz) - pow(S_z, 2);

      b_reco = (S_zz * S_y - S_z * S_zy) / Delta;
      a_reco = (S * S_zy - S_z * S_y) / Delta;

      alpha = (3 * station_z_axis[1] - S_z) / ((S * S_zz) - pow(S_z, 2));
      beta = (S_zz - station_z_axis[1] * S_z) / ((S * S_zz) - pow(S_z, 2));
      delta_station1_reco += (y_smeared[i].at(1) - a_reco * station_z_axis[1] - b_reco) / (1 - alpha * station_z_axis[1] - beta);
      // delta_station1_reco_hist->Fill((y_smeared[i].at(1) - a_reco * station_z_axis[1] - b_reco) / (1 - alpha * station_z_axis[1] - beta));
    }

    delta_station1_reco = delta_station1_reco / y_smeared.size();

    cout << "delta in station 1 is \t" << delta_station1_reco << endl;

    // auto shifts_canvas = new TCanvas("shifts_canvas", "shifts_canvas", 1400, 2000);
    // shifts_canvas->Divide(1, 2);
    // shifts_canvas->cd(1);
    // delta_station1_reco_hist->Draw();
    // shifts_canvas->cd(2);
    // delta_station2_reco_hist->Draw();
    // shifts_canvas->SaveAs("/Users/andreizelenov/Documents/SPD/shifts.pdf", "Q");
    // delete shifts_canvas;
  }
}
