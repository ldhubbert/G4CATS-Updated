#include <TMath.h>
{
  //Open file filled by Geant4 simulation 
  TFile f("~/Vincent/G4CATS/Out/B4_100MeV.root");

  //Create a canvas and divide it into 2 pads
  TCanvas* c1 = new TCanvas("c1", "", 20, 20, 1000, 1000);
  c1->Divide(1,2);

  //Draw Eabs histogram in the pad 2
  //c1->cd(3);

  //Smearing the data:
  //STEP ONE
  //To smear the data, first we need to make a Gaussian distribution to simulate the detector efficiency.
  //The mean of this Gaussian will be 0MeV, and the standard deviation will be 0.0075, since we want to smear the results by 0.75%.
  //The more we want to smear the results by, the wider the Gaussian curve will be, attributing more error to the histogram results.
  //gaus(0) refers to a Gaussian distribution with parameters as commented below

  TF1 *f1 = new TF1("f1", "gaus", 0, 2);
  //Fraction being raised to power
  //f1->SetParameter(0, (1/((0.01)*(TMath::Sqrt(2*TMath::Pi())))));
  f1->SetParameter(0, 1);
  //Mean
  f1->SetParameter(1, 1);
  //Standard Deviation
  f1->SetParameter(2, 0.0075);

  //f1->Draw();

  c1->cd(2);

  //Looking for the branch, "B4", in file f (the 100MeV output file)
  TTreeReader r1("B4", &f);

  //Reading each branch below as defined in B4
  //<Double_t> tells TTreeReaderValue what type of data it's extracting
  TTreeReaderValue<Double_t> Ecore(r1, "Ecore");
  TTreeReaderValue<Double_t> Eann1(r1, "Eann1");
  TTreeReaderValue<Double_t> Eann2(r1, "Eann2");
  TTreeReaderValue<Double_t> Eann3(r1, "Eann3");
  TTreeReaderValue<Double_t> Eann4(r1, "Eann4");
  TTreeReaderValue<Double_t> Eann5(r1, "Eann5");
  TTreeReaderValue<Double_t> Eann6(r1, "Eann6");

  //Create histogram
  TH1F *h1 = new TH1F("Histogram 2", "h1", 200, 50, 120);

  //The while loop goes through each branch and reads entries.
  //So for the first time around the loop, entry 1 is read from each branch (Ecore up to Eann6)
  while (r1.Next())
  {
	h1->Fill((*Ecore + *Eann1 + *Eann2 + *Eann3 + *Eann4 + *Eann5 + *Eann6)*(f1->GetRandom()));
  } 

  TLine *line = new TLine(100, 0, 100, 12500);

  h1->Draw();
  h1->SetTitle("0.75% Gaussian Smear on 100MeV Beam");

  line->Draw();

  //Compare to normal 100MeV Histogram (taken from code in Histogram folder)
  c1->cd(1);
  TH1F *h2 = new TH1F("Histogram 1", "", 200, 50, 120);
  TTree *B4 = (TTree*)f.Get("B4");
  B4->Draw("Ecore+Eann1+Eann2+Eann3+Eann4+Eann5+Eann6>>Histogram 1");
  h2->GetXaxis()->SetTitle("Energy (MeV)");
  h2->GetYaxis()->SetTitle("Counts");
  h2->SetTitle("100MeV Beam Before Smearing");
  h2->Draw();

  c1->cd(2);

  //Start of FWHM Section
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
	else if ((x > (HalfMaxYValue-1500)) && (x < HalfMaxYValue))
		{
		cout << "A lower bin number was found with a number of counts close to HalfMaxYValue." << endl;
		cout << i << endl;
		cout << h1->GetBinContent(i) << endl;
		}
	//Upper Bound
	else if ((x < (HalfMaxYValue+1500)) && (x > HalfMaxYValue))
		{
		cout << "An upper bin number was found with a number of counts close to HalfMaxYValue." << endl;
		cout << i << endl;
		cout << h1->GetBinContent(i) << endl;
		}
	}

  //cout << "Contents of Bin 145:" << endl;
  //cout << h1->GetBinContent(145) << endl;
  //cout << "Contents of Bin 137:" << endl;
  //cout << h1->GetBinContent(137) << endl;

  //Getting bin center that roughly corresponds to HalfMaxYValue on lower threshold
  Double_t LowerWholeBinFraction = h1->GetBinContent(138)/h1->GetBinContent(139);
  cout << "Lower Bin Fraction:" << endl;
  cout << LowerWholeBinFraction << endl;
  cout << "x-value corresponding to the center of bin 138:" << endl;
  Double_t Center138 = h1->GetBinCenter(138);
  cout << Center138 << endl;
  Double_t Center139 = h1->GetBinCenter(139);
  cout << "x-value corresponding to the center of bin 139:" << endl;
  cout << Center139 << endl;
  Double_t LowerBinWidth = Center139 - Center138;
  cout << "Lower Bin Width:" << endl;
  cout << LowerBinWidth << endl;

  Double_t LowerXValue = Center138 + (LowerBinWidth)*(LowerWholeBinFraction);
  cout << "/////////////////////////////////////" << endl;
  cout << LowerXValue << endl;
  cout << "/////////////////////////////////////" << endl;

  //Getting bin center that roughly corresponds to HalfMaxYValue on upper threshold
  Double_t UpperWholeBinFraction = h1->GetBinContent(146)/h1->GetBinContent(145);
  cout << "Upper Bin Fraction:" << endl;
  cout << UpperWholeBinFraction << endl;
  cout << "x-value corresponding to the center of bin 145:" << endl;
  Double_t Center145 = h1->GetBinCenter(145);
  cout << Center145 << endl;
  Double_t Center146 = h1->GetBinCenter(146);
  cout << "x-value corresponding to the center of bin 146:" << endl;
  cout << Center146 << endl;
  Double_t UpperBinWidth = Center146 - Center145;
  cout << "Upper Bin Width:" << endl;
  cout << UpperBinWidth << endl;

  Double_t UpperXValue = Center146 + (UpperBinWidth)*(UpperWholeBinFraction);
  cout << "//////////////////////////////////////" << endl;
  cout << UpperXValue << endl;
  cout << "//////////////////////////////////////" << endl;

  //Final width
  Double_t FinalWidth = UpperXValue - LowerXValue;
  cout << "Final width for the FWHM calculation:" << endl;
  cout << FinalWidth << endl;
  Double_t FWHM = (FinalWidth/100)*100;
  cout << "FWHM:" << endl;
  cout << FWHM << endl;

  //Display FWHM on bottom pad 
  c1->cd(2);
  TString FWHM_string;
  FWHM_string = Form("FWHM: %lf", FWHM);
  TPaveLabel *a = new TPaveLabel(0,3000,5,3500, FWHM_string);
  a->Draw();
}
