void FWHM()
{
  //gROOT->Reset();
  //gROOT->SetStyle("Plain");

  //gStyle->SetOptStat(0);   

  // Open file filled by Geant4 simulation 
  TFile f("B4.root");

  TCanvas* c1 = new TCanvas("c1", "", 20, 20, 1000, 1000);
  //c1->Divide(1,1);
  //c1->cd(1);

  //gStyle->SetOptFit(1111);
  TTree *B4 = (TTree*)f.Get("B4");
  TH1F *h1 = new TH1F("h1","new CATS sim",100,0,510);  
  
  Double_t Ecore,Eann1,Eann2,Eann3,Eann4,Eann5,Eann6; 
  B4->SetBranchAddress("Ecore",&Ecore);
  B4->SetBranchAddress("Eann1",&Eann1);
  B4->SetBranchAddress("Eann2",&Eann2);
  B4->SetBranchAddress("Eann3",&Eann3);
  B4->SetBranchAddress("Eann4",&Eann4);
  B4->SetBranchAddress("Eann5",&Eann5);
  B4->SetBranchAddress("Eann6",&Eann6);

  Int_t max = B4->GetEntries();

  for (int i=0;i<max;i++){
	  B4->GetEntry(i);
		h1->Fill(Ecore); 
		cout<< Ecore << endl;
  } 
 
  //B4->Draw("Ecore+Eann1+Eann2+Eann3+Eann4+Eann5+Eann6>>h1(100,450,505)");
  //B4->Draw("Ecore>>h1(100,450.,505)","Ecore<500");
  h1->SetFillStyle( 3001);
  h1->SetFillColor(7);
 
 //Find number of events counted 
  //h1->Integral();
  //Double_t x = h1->Integral();
  //cout << x << endl;

  h1->SetTitle("new CATS sim;Energy (MeV);Counts");
   int bin1 = h1->FindFirstBinAbove(h1->GetMaximum()/2);
   int bin2 = h1->FindLastBinAbove(h1->GetMaximum()/2);
   double fwhm = h1->GetBinCenter(bin2) - h1->GetBinCenter(bin1);
 cout << fwhm << endl;  

 h1->Paint();
 c1->Modified();
 c1->Update();
 h1->Print();
}

