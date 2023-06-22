{
  TFile f("~/Vincent/G4CATS/Out/B4_200MeV.root");
  
  TCanvas* c1 = new TCanvas("c1", "", 20, 20, 1000, 1000);
  c1->Divide(1,1);
  
  c1->cd(1);

  TTree *B4 = (TTree*)f.Get("B4");

  TH1F* h1 = new TH1F("h1", "", 300, 175, 205);

  B4->Draw("Ecore+Eann1+Eann2+Eann3+Eann4+Eann5+Eann6>>h1");
  h1->GetXaxis()->SetTitle("Energy (MeV)");
  h1->GetYaxis()->SetTitle("Counts");
  h1->SetTitle("Energy Recorded by G4 CATS sim -- 200MeV Photon Beam");

  //Start of FWHM Section
  //Try a Gaussian Fit instead to calculate the FWHM. This strategy kind of sucked.
/*  Double_t BinWithMostCounts = h1->GetMaximumBin();
  cout << "Bin With Most Counts:" << endl;
  cout << BinWithMostCounts << endl;
  Double_t MaxYValue = h1->GetBinContent(BinWithMostCounts);
  cout << "Most Counts in 1 bin:" << endl;
  cout << MaxYValue << endl;

  for (Int_t i = 0; i < 300; i++)
	{
	Double_t x = h1->GetBinContent(i);
	if (x == MaxYValue)
		{
		cout << "The bin number with MaxYValue contents is:" << endl;
		cout << i << endl;
		}
	//Lower Bound
	else if ((x > (MaxYValue-9500)) && (x < MaxYValue))
		{
		cout << "A lower bin number was found with a number of counts close to MaxYValue." << endl;
		cout << i << endl;
		cout << h1->GetBinContent(i) << endl;
		}
	//Upper Bound
	else if ((x < (MaxYValue+9500)) && (x > MaxYValue))
		{
		cout << "An upper bin number was found with a number of counts close to MaxYValue." << endl;
		cout << i << endl;
		cout << h1->GetBinContent(i) << endl;
		}
	}

  //Bin 245
  Double_t Center245 = h1->GetBinCenter(245);
  cout << "x-value corresponding to the center of bin 245:" << endl;
  cout << Center245 << endl;

  //Bin 251
  Double_t Center251 = h1->GetBinCenter(251);
  cout << "x-value corresponding to the center of bin 251:" << endl;
  cout << Center251 << endl;

  //Final width
  Double_t FinalWidth = Center251 - Center245;
  cout << "Final width for the FWHM calculation:" << endl;
  cout << FinalWidth << endl;
  Double_t FWHM = (FinalWidth/200)*100;
  cout << "FWHM:" << endl;
  cout << FWHM << endl;
*/

  //Fit the original histogram with a fit of some kind to try to calculate a better estimate of the FWHM
  //Trying a Gaussian fit
  TF1 *f1 = new TF1("fit function", "gaus", 180, 205);
  f1->SetParameter(1, 1);
  f1->SetParameter(2, h1->GetMean());
  f1->SetParameter(3, h1->GetStdDev());

  f1->Draw("Same");
  //h1->Fit("fit function");
  //
}
