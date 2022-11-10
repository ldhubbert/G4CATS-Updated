//void FitLandau()
{
  //gROOT->Reset();
  //gROOT->SetStyle("Plain");

  //gStyle->SetOptStat(0);
  // Draw histos filled by Geant4 simulation 
  //   

  // Open file filled by Geant4 simulation 
  TFile f("B4.root");

  // Create a canvas and divide it into 2x2 pads
  TCanvas* c1 = new TCanvas("c1", "", 20, 20, 1000, 1000);
  c1->Divide(1,1);

  // Draw Eabs histogram in the pad 1
  c1->cd(1);

  gStyle->SetOptFit(1111);
  TTree *B4 = (TTree*)f.Get("B4");
  TF1 f1("f1","[0] * TMath::Landau([1]-x, 0., [2])", 450., 505);
  f1.SetParameters(50000,498.4,1);
  B4->Draw("Ecore+Eann1+Eann2+Eann3+Eann4+Eann5+Eann6>>h1(100,450.,505)");
  //B4->Draw("Ecore>>h1(100,450.,505)","Ecore<500");
  h1->Fit("f1");
  h1->SetFillStyle( 3001);
  h1->SetFillColor(7);
  
  h1->Integral();
  Double_t x = h1->Integral();
  cout << x << endl;
  
  h1->Draw( "hist same");
  h1->SetTitle("new CATS sim;Energy (MeV);Counts");

}
