// ROOT macro file for plotting example B4 histograms 
// 
// Can be run from ROOT session:
// root[0] .x plotHisto.C
//not done... need to figure out a way to plot with more bins + axis limits
{
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  
  // Draw histos filled by Geant4 simulation 
  //   

  // Open file filled by Geant4 simulation 
  TFile f("B4.root");

  // Create a canvas and divide it into 2x2 pads
  TCanvas* c1 = new TCanvas("c1", "", 20, 20, 1000, 1000);
  c1->Divide(1,1);
  
  // Draw Eabs histogram in the pad 1
  c1->cd(1);
 
  TTree *B4 = (TTree*)f.Get("B4");
  //B4->Draw("Ecore>>Ecore(25,4,5.1)");
  B4->Draw("Ecore+Eann1+Eann2+Eann3+Eann4+Eann5+Eann6>>Ecore(50,4,5.1)");
  //TH1F *Ecore = new TH1F("Ecore","Ecore",3000,80,110);
  //B4->Draw("Ecore>>Ecore(300,4,5.5)");
  //Ecore->GetXaxis()->SetRangeUser(80,110);
  //B4->Draw("Ecore");
  //TH1D* hist1 = (TH1D*)f.Get("Ecore");
  //hist1->GetXaxis()->SetRangeUser(80,110);
  //hist1->Draw("hist1>>hist1(1000,80,110)");
  //hist1->Draw("HIST");
  
}  
