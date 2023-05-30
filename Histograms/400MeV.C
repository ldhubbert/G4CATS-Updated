{
  TFile f("~/Vincent/G4CATS/Out/B4_400MeV.root");

  TCanvas* c1 = new TCanvas("c1", "", 20, 20, 1000, 1000);
  c1->Divide(1,1);
  
  c1->cd(1);

  TTree *B4 = (TTree*)f.Get("B4");

  TH1F* h1 = new TH1F("h1", "", 200, 360, 405);

  B4->Draw("Ecore+Eann1+Eann2+Eann3+Eann4+Eann5+Eann6>>h1");
  h1->GetXaxis()->SetTitle("Energy (MeV)");
  h1->GetYaxis()->SetTitle("Counts");
  h1->SetTitle("Energy Recorded by G4 CATS sim -- 400MeV Photon Beam");
}
