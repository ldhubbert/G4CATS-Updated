#include <TMath.h>
{
  //Open file filled by Geant4 simulation 
  TFile f("~/Vincent/G4CATS/Out/B4_500MeV.root");

  //Create a canvas and divide it into 2x2 pads
  TCanvas* c1 = new TCanvas("c1", "", 20, 20, 1000, 1000);
  c1->Divide(1,1);

  //Draw Eabs histogram in the pad 1
  c1->cd(1);

  //Smearing the data:
  //STEP ONE
  //To smear the data, first we need to make a Gaussian distribution to simulate the detector efficiency.
  //The mean of this Gaussian will be 0MeV, and the standard deviation will be 0.12(sqrt(photon beam)), since we want to smear the results by 12%.
  //The more we want to smear the results by, the wider the Gaussian curve will be, attributing more error to the histogram results.
  //gaus(0) refers to a Gaussian distribution with parameters as commented below

  TF1 *f1 = new TF1("f1", "gaus(0)", -50, 50);
  //Fraction being raised to power
  f1->SetParameter(0, (1/(0.12*TMath::Sqrt(500))*(TMath::Sqrt(2*TMath::Pi()))));
  //Mean
  f1->SetParameter(1, 0);
  //Standard Deviation
  f1->SetParameter(2, (0.12*TMath::Sqrt(500)));

  //Looking for the branch, "B4", in file f (the 500MeV output file)
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
  TH1F *h1 = new TH1F("h1", "h1", 200, 400, 550);

  //The while loop goes through each branch and reads entries.
  //So for the first time around the loop, entry 1 is read from each branch (Ecore up to Eann6)
  while (r1.Next())
  {
	//cout << *Ecore + *Eann1 + *Eann2 + *Eann3 + *Eann4 + * Eann5 + *Eann6 + f1->GetRandom() << endl;
	h1->Fill(*Ecore + *Eann1 + *Eann2 + *Eann3 + *Eann4 + *Eann5 + *Eann6 + f1->GetRandom());
  }

  TLine *line = new TLine(500, 0, 500, 7350);

  h1->Draw();
  h1->SetTitle("12% Gaussian Smear on 500MeV Beam");

  line->Draw();

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
	else if ((x > (HalfMaxYValue-400)) && (x < HalfMaxYValue))
		{
		cout << "A lower bin number was found with a number of counts close to HalfMaxYValue." << endl;
		cout << i << endl;
		cout << h1->GetBinContent(i) << endl;
		}
	//Upper Bound
	else if ((x < (HalfMaxYValue+400)) && (x > HalfMaxYValue))
		{
		cout << "An upper bin number was found with a number of counts close to HalfMaxYValue." << endl;
		cout << i << endl;
		cout << h1->GetBinContent(i) << endl;
		}
	}
  cout << "Contents of Bin 124:" << endl;
  cout << h1->GetBinContent(124) << endl;
  cout << "Contents of Bin 136:" << endl;
  cout << h1->GetBinContent(136) << endl;

  //Getting bin center that roughly corresponds to HalfMaxYValue on lower threshold
  Double_t LowerWholeBinFraction = h1->GetBinContent(123)/h1->GetBinContent(124);
  cout << "Lower Bin Fraction:" << endl;
  cout << LowerWholeBinFraction << endl;
  cout << "x-value corresponding to the center of bin 123:" << endl;
  Double_t Center123 = h1->GetBinCenter(123);
  cout << Center123 << endl;
  Double_t Center124 = h1->GetBinCenter(124);
  cout << "x-value corresponding to the center of bin 124:" << endl;
  cout << Center124 << endl;
  Double_t LowerBinWidth = Center124 - Center123;
  cout << "Lower Bin Width:" << endl;
  cout << LowerBinWidth << endl;

  Double_t LowerXValue = Center123 + (LowerBinWidth)*(LowerWholeBinFraction);
  cout << "/////////////////////////////////////" << endl;
  cout << LowerXValue << endl;
  cout << "/////////////////////////////////////" << endl;

  //Getting bin center that roughly corresponds to HalfMaxYValue on upper threshold
  Double_t UpperWholeBinFraction = h1->GetBinContent(136)/h1->GetBinContent(135);
  cout << "Upper Bin Fraction:" << endl;
  cout << UpperWholeBinFraction << endl;
  cout << "x-value corresponding to the center of bin 135:" << endl;
  Double_t Center135 = h1->GetBinCenter(135);
  cout << Center135 << endl;
  Double_t Center136 = h1->GetBinCenter(136);
  cout << "x-value corresponding to the center of bin 136:" << endl;
  cout << Center136 << endl;
  Double_t UpperBinWidth = Center136 - Center135;
  cout << "Upper Bin Width:" << endl;
  cout << UpperBinWidth << endl;

  Double_t UpperXValue = Center136 + (UpperBinWidth)*(UpperWholeBinFraction);
  cout << "//////////////////////////////////////" << endl;
  cout << UpperXValue << endl;
  cout << "//////////////////////////////////////" << endl;

  //Final width
  Double_t FinalWidth = UpperXValue - LowerXValue;
  cout << "Final width for the FWHM calculation:" << endl;
  cout << FinalWidth << endl;
  Double_t FWHM = (FinalWidth/500)*100;
  cout << "FWHM:" << endl;
  cout << FWHM << endl;

  //When sent to Dave, the FWHM was 1.92892% the incident beam energy.
}
