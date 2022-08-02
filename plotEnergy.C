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
 // B4->Draw("Ecore>>Ecore(100,90,105)");
  B4->Draw("Ecore>>Ecore(500,480,505)");
  //TH1F *Ecore = new TH1F("Ecore","Ecore",3000,80,110);
  //Ecore->GetXaxis()->SetRangeUser(80,110);
  //B4->Draw("Ecore");
  //TH1D* hist1 = (TH1D*)f.Get("Ecore");
  //hist1->GetXaxis()->SetRangeUser(80,110);
  //hist1->Draw("hist1>>hist1(1000,80,110)");
  //hist1->Draw("HIST");
  
  // Draw Labs histogram in the pad 2
  //c1->cd(2);
  //TH1D* hist2 = (TH1D*)f.Get("Labs");
  //hist2->Draw("HIST");
  
  // Draw Egap histogram in the pad 3
  // with logaritmic scale for y
  //TH1D* hist3 = (TH1D*)f.Get("Egap");
  //c1->cd(3);
  //gPad->SetLogy(1);
  //hist3->Draw("HIST");
  
  // Draw Lgap histogram in the pad 4
  // with logaritmic scale for y
  //c1->cd(4);
  //gPad->SetLogy(1);
  //TH1D* hist4 = (TH1D*)f.Get("Lgap");
  //hist4->Draw("HIST");
}  
