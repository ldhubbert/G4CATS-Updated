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
  //Rretrieves a TTree object named "B4" from the root file 'f' and assigns it to the pointer variable 'B4' (first B4 is the pointer name.):
  TTree *B4 = (TTree*)f.Get("B4");

  //I (Laura) added the following line
  TH1F* h1 = new TH1F("h1", "", 200, 450, 510);

  //B4->Draw("Ecore+Eann1+Eann2+Eann3+Eann4+Eann5+Eann6>>h1(200,450.,505)");
  B4->Draw("Ecore+Eann1+Eann2+Eann3+Eann4+Eann5+Eann6>>h1");
  h1->GetXaxis()->SetTitle("Energy (MeV)");
  h1->GetYaxis()->SetTitle("Counts");
  h1->SetTitle("Energy Recorded by G4 CATS sim -- 500MeV Photon Beam");

  //FWHM section starts
  //For this histogram, the FWHM will be from a bin on the left-hand side of the max peak with a number of counts approximately equal to HalfMaxYValue to the spike at 500MeV.
  Double_t BinWithMostCounts = h1->GetMaximumBin();
  cout << "Bin With Most Counts:" << endl;
  cout << BinWithMostCounts << endl;
  Double_t MaxYValue = h1->GetBinContent(BinWithMostCounts);
  cout << "Most Counts in 1 bin:" << endl;
  cout << MaxYValue << endl;
  Double_t HalfMaxYValue = MaxYValue/2;
  cout << "Half of Max Counts:" << endl;
  cout << HalfMaxYValue << endl;

 for (Int_t i = 0; i < 200; i++)
	{
	Double_t x = h1->GetBinContent(i);
	if (x == HalfMaxYValue)
		{
		cout << "The bin number with HalfMaxYValue contents is:" << endl;
		cout << i << endl;
		}
	//Lower Bound
	else if ((x > (HalfMaxYValue-4)) && (x < HalfMaxYValue))
		{
		cout << "A lower bin number was found with a number of counts close to HalfMaxYValue." << endl;
		cout << i << endl;
		cout << h1->GetBinContent(i) << endl;
		}
	//Upper Bound
	else if ((x < (HalfMaxYValue+130)) && (x > HalfMaxYValue))
		{
		cout << "An upper bin number was found with a number of counts close to HalfMaxYValue." << endl;
		cout << i << endl;
		cout << h1->GetBinContent(i) << endl;
		}
	}

  //Getting bin center that roughly corresponds to HalfMaxYValue on lower threshold
  Double_t LowerWholeBinFraction = h1->GetBinContent(152)/h1->GetBinContent(153);
  cout << "Lower Bin Fraction:" << endl;
  cout << LowerWholeBinFraction << endl;
  cout << "x-value corresponding to the center of bin 152:" << endl;
  Double_t Center152 = h1->GetBinCenter(152);
  cout << Center152 << endl;
  Double_t Center153 = h1->GetBinCenter(153);
  cout << "x-value corresponding to the center of bin 153:" << endl;
  cout << Center153 << endl;
  Double_t LowerBinWidth = Center153 - Center152;
  cout << "Lower Bin Width:" << endl;
  cout << LowerBinWidth << endl;

  Double_t LowerXValue = Center152 + (LowerBinWidth)*(LowerWholeBinFraction);
  cout << "/////////////////////////////////////" << endl;
  cout << LowerXValue << endl;
  cout << "/////////////////////////////////////" << endl;

  //Final width
  Double_t FinalWidth = 500 - LowerXValue;
  cout << "Final width for the FWHM calculation:" << endl;
  cout << FinalWidth << endl;
  Double_t FWHM = (FinalWidth/500)*100;
  cout << "FWHM:" << endl;
  cout << FWHM << endl;
}

