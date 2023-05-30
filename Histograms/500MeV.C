{
  //NOTE: VINCENT'S MODIFIED CODE BY LAURA
  //gROOT->Reset();
  //gROOT->SetStyle("Plain");

  //gStyle->SetOptStat(0);
  // Draw histos filled by Geant4 simulation 
  //   

  //Open file filled by Geant4 simulation 
  TFile f("~/Vincent/G4CATS/Out/B4_500MeV.root");

  //Create a canvas and divide it into 2x2 pads
  TCanvas* c1 = new TCanvas("c1", "", 20, 20, 1000, 1000);
  c1->Divide(1,1);

  //Draw Eabs histogram in the pad 1
  c1->cd(1);

  //I (Laura) added the following line
  TTree *B4 = (TTree*)f.Get("B4");

  //I (Laura) added the following line
  TH1F* h1 = new TH1F("h1", "", 200, 450, 510);

  //B4->Draw("Ecore+Eann1+Eann2+Eann3+Eann4+Eann5+Eann6>>h1(200,450.,505)");
  B4->Draw("Ecore+Eann1+Eann2+Eann3+Eann4+Eann5+Eann6>>h1");
  h1->GetXaxis()->SetTitle("Energy (MeV)");
  h1->GetYaxis()->SetTitle("Counts");
  h1->SetTitle("Energy Recorded by G4 CATS sim -- 500MeV Photon Beam");
}

