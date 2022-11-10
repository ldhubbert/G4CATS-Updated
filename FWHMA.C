void FWHMA()
{
gStyle->SetOptStat(0);  
// Open file filled by Geant4 simulation 
  TFile *f = new TFile("B4.root");
  
  TTree *B4 = (TTree*)f->Get("B4");
  
  TH1F *h1 = new TH1F("h1","new CATS sim",100,450,510);  
  
  Double_t Ecore,Eann1,Eann2,Eann3,Eann4,Eann5,Eann6; 
  B4->SetBranchAddress("Ecore",&Ecore);
  B4->SetBranchAddress("Eann1",&Eann1);
  B4->SetBranchAddress("Eann2",&Eann2);
  B4->SetBranchAddress("Eann3",&Eann3);
  B4->SetBranchAddress("Eann4",&Eann4);
  B4->SetBranchAddress("Eann5",&Eann5);
  B4->SetBranchAddress("Eann6",&Eann6);

  Int_t max = B4->GetEntries();
  Double_t Etot;

  for (int i=0;i<max;i++){
	 B4->GetEntry(i);
	 Etot=Ecore+Eann1+Eann2+Eann3+Eann4+Eann5+Eann6;
	 h1->Fill(Etot);//Etot*1000 or Etot+3 
  } 
  h1->SetFillColor(7);
 
   int bin1 = h1->FindFirstBinAbove(h1->GetMaximum()/2);
   int bin2 = h1->FindLastBinAbove(h1->GetMaximum()/2);
   double fwhm = h1->GetBinCenter(bin2) - h1->GetBinCenter(bin1);
   cout << fwhm << endl;  

   h1->SetTitle("new CATS sim;Energy (MeV);Counts");
   h1->Draw();
}

