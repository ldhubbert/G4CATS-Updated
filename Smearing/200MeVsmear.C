#include <TMath.h>
{
  //Open file filled by Geant4 simulation 
  TFile f("~/Vincent/G4CATS/Out/B4_200MeV.root");

  //Create a canvas and divide it into 2 pads
  TCanvas* c1 = new TCanvas("c1", "", 20, 20, 1000, 1000);
  c1->Divide(1,2);

  //Draw Eabs histogram in the pad 2
  c1->cd(2);

  //Smearing the data:
  //STEP ONE
  //To smear the data, first we need to make a Gaussian distribution to simulate the detector efficiency.
  //The mean of this Gaussian will be 0MeV, and the standard deviation will be 0.08(sqrt(photon beam)), since we want to smear the results by 8%.
  //The more we want to smear the results by, the wider the Gaussian curve will be, attributing more error to the histogram results.
  //gaus(0) refers to a Gaussian distribution with parameters as commented below

  TF1 *f1 = new TF1("f1", "gaus(0)", -2, 2);
  //Fraction being raised to power
  f1->SetParameter(0, (1/(0.08*TMath::Sqrt(200))*(TMath::Sqrt(2*TMath::Pi()))));
  //Mean
  f1->SetParameter(1, 0);
  //Standard Deviation
  f1->SetParameter(2, (0.08*TMath::Sqrt(200)));

  //Looking for the branch, "B4", in file f (the 200MeV output file)
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
  TH1F *h1 = new TH1F("Histogram 2", "h1", 300, 175, 205);

  //The while loop goes through each branch and reads entries.
  //So for the first time around the loop, entry 1 is read from each branch (Ecore up to Eann6)
  while (r1.Next())
  {
	//cout << *Ecore + *Eann1 + *Eann2 + *Eann3 + *Eann4 + * Eann5 + *Eann6 + f1->GetRandom() << endl;
	h1->Fill(*Ecore + *Eann1 + *Eann2 + *Eann3 + *Eann4 + *Eann5 + *Eann6 + f1->GetRandom());
  } 
  TLine *line = new TLine(200, 0, 200, 5900);

  h1->Draw();
  h1->SetTitle("8% Gaussian Smear on 200MeV Beam");

  line->Draw();

  //Compare to normal 200MeV Histogram (taken from code in Histogram folder)
  c1->cd(1);
  TH1F *h2 = new TH1F("Histogram 1", "", 200, 175, 205);
  TTree *B4 = (TTree*)f.Get("B4");
  B4->Draw("Ecore+Eann1+Eann2+Eann3+Eann4+Eann5+Eann6>>Histogram 1");
  h2->GetXaxis()->SetTitle("Energy (MeV)");
  h2->GetYaxis()->SetTitle("Counts");
  h2->SetTitle("200MeV Beam Before Smearing");
  h2->Draw();

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

  for (Int_t i = 0; i < 300; i++)
	{
	Double_t x = h1->GetBinContent(i);
	if (x == HalfMaxYValue)
		{
		cout << "The bin number with HalfMaxYValue contents is:" << endl;
		cout << i << endl;
		}
	//Lower Bound
	else if ((x > (HalfMaxYValue-50)) && (x < HalfMaxYValue))
		{
		cout << "A lower bin number was found with a number of counts close to HalfMaxYValue." << endl;
		cout << i << endl;
		cout << h1->GetBinContent(i) << endl;
		}
	//Upper Bound
	else if ((x < (HalfMaxYValue+50)) && (x > HalfMaxYValue))
		{
		cout << "An upper bin number was found with a number of counts close to HalfMaxYValue." << endl;
		cout << i << endl;
		cout << h1->GetBinContent(i) << endl;
		}
	}

/*  cout << "Content of Bin 258:" << endl;
  cout << h1->GetBinContent(258) << endl;
  cout << "Contents of Bin 226:" << endl;
  cout << h1->GetBinContent(226) << endl;
  cout << "Contents of Bin 259:" << endl;
  cout << h1->GetBinContent(259) << endl;
*/
  //Getting bin center that roughly corresponds to HalfMaxYValue on lower threshold
  Double_t LowerWholeBinFraction = h1->GetBinContent(225)/h1->GetBinContent(226);
  cout << "Lower Bin Fraction:" << endl;
  cout << LowerWholeBinFraction << endl;
  cout << "x-value corresponding to the center of bin 225:" << endl;
  Double_t Center225 = h1->GetBinCenter(225);
  cout << Center225 << endl;
  Double_t Center226 = h1->GetBinCenter(226);
  cout << "x-value corresponding to the center of bin 226:" << endl;
  cout << Center226 << endl;
  Double_t LowerBinWidth = Center226 - Center225;
  cout << "Lower Bin Width:" << endl;
  cout << LowerBinWidth << endl;

  Double_t LowerXValue = Center225 + (LowerBinWidth)*(LowerWholeBinFraction);
  cout << "/////////////////////////////////////" << endl;
  cout << LowerXValue << endl;
  cout << "/////////////////////////////////////" << endl;

  //Getting bin center that roughly corresponds to HalfMaxYValue on upper threshold
  Double_t UpperWholeBinFraction = h1->GetBinContent(259)/h1->GetBinContent(258);
  cout << "Upper Bin Fraction:" << endl;
  cout << UpperWholeBinFraction << endl;
  cout << "x-value corresponding to the center of bin 258:" << endl;
  Double_t Center258 = h1->GetBinCenter(258);
  cout << Center258 << endl;
  Double_t Center259 = h1->GetBinCenter(259);
  cout << "x-value corresponding to the center of bin 259:" << endl;
  cout << Center259 << endl;
  Double_t UpperBinWidth = Center259 - Center258;
  cout << "Upper Bin Width:" << endl;
  cout << UpperBinWidth << endl;

  Double_t UpperXValue = Center259 + (UpperBinWidth)*(UpperWholeBinFraction);
  cout << "//////////////////////////////////////" << endl;
  cout << UpperXValue << endl;
  cout << "//////////////////////////////////////" << endl;

  //Final width
  Double_t FinalWidth = UpperXValue - LowerXValue;
  cout << "Final width for the FWHM calculation:" << endl;
  cout << FinalWidth << endl;
  Double_t FWHM = (FinalWidth/200)*100;
  cout << "FWHM:" << endl;
  cout << FWHM << endl;

  //Display FWHM on bottom pad 
  c1->cd(2);
  TString FWHM_string;
  FWHM_string = Form("FWHM: %lf", FWHM);
  TPaveLabel *a = new TPaveLabel(80,3000,85,3500, FWHM_string);
  a->Draw();
}
