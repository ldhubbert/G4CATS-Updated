{
  //gROOT->Reset();
  //gROOT->SetStyle("Plain");
  //gStyle->SetOptStat(0);

  // Open file filled by Geant4 simulation 
  TFile f("~/Vincent/G4CATS/Out/B4_500MeV.root");

  // Create a canvas and divide it into 2x2 pads
  TCanvas* c1 = new TCanvas("c1", "", 20, 20, 1000, 1000);
  c1->Divide(1,1);

  // Draw Eabs histogram in the pad 1
  c1->cd(1);

  //gStyle->SetOptFit(1111);// this gives you more info on the histogram.
  TTree *B4 = (TTree*)f.Get("B4");
  
  B4->Draw("Ecore+Eann1+Eann2+Eann3+Eann4+Eann5+Eann6>>h1(200,450.,505)");
  TF1 f1("f1","[0] * TMath::Landau([1]-x, 0., [2])", 450., 505);
  
  //Note: the [0] parameter is for amplitude. the [1] paramter is for the mean of the histogram. the [2] parameter is for the width of the Lamdau curve.
  //HOWEVER, [0] and [2] are kind of arbitrary since the graph calculates most of the parameters on its own. So, I set both equal to 1.
  f1.SetParameters(1, h1->GetMean(), 1);
  //f1.SetParameters(50000, 498.4, 1);
  h1->Fit("f1");
  h1->SetFillStyle( 3001);
  h1->SetFillColor(7);
  
  //h1->Integral();
  //Double_t x = h1->Integral();
  //cout << x << endl;
  
  h1->Draw( "hist same");
  h1->SetTitle("new CATS sim;Energy (MeV);Counts");
}
