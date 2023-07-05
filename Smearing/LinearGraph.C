#include <TMath.h>
{
	TCanvas *c1 = new TCanvas("c1", "", 20, 20, 1000, 1000);
	c1->Divide(1, 1);
	c1->cd(1);

	//Code From 100MeV Smear
	//Gaussian and Filling Histogram
	TFile a("~/Vincent/G4CATS/Out/B4_100MeV.root");

	TF1 *f1 = new TF1("f1", "gaus(0)", -3, 3);
	f1->SetParameter(0, (1/((0.07*TMath::Sqrt(100))*(TMath::Sqrt(2*TMath::Pi())))));
	f1->SetParameter(1, 0);
	f1->SetParameter(2, 0.07*TMath::Sqrt(100));

	TTreeReader r1("B4", &a);

	TTreeReaderValue<Double_t> Ecore(r1, "Ecore");
	TTreeReaderValue<Double_t> Eann1(r1, "Eann1");
	TTreeReaderValue<Double_t> Eann2(r1, "Eann2");
	TTreeReaderValue<Double_t> Eann3(r1, "Eann3");
	TTreeReaderValue<Double_t> Eann4(r1, "Eann4");
	TTreeReaderValue<Double_t> Eann5(r1, "Eann5");
	TTreeReaderValue<Double_t> Eann6(r1, "Eann6");

	TH1F *h1 = new TH1F("", "", 200, 85, 105);

	while (r1.Next())
	{
		h1->Fill(*Ecore + *Eann1 + *Eann2 + *Eann3 + *Eann4 + *Eann5 + *Eann6 + f1->GetRandom());
	}
	
	//100MeV FWHM Code
	Double_t BinWithMostCounts = h1->GetMaximumBin();
	Double_t MaxYValue = h1->GetBinContent(BinWithMostCounts);
	Double_t HalfMaxYValue = MaxYValue/2;

	Double_t FWHMLeftXValue = 0;
	int binA = 0;
	h1->GetBinWithContent(HalfMaxYValue, binA, 0, BinWithMostCounts, 0);

	if (binA == 0)
	{
		Double_t Lower2 = h1->FindFirstBinAbove(HalfMaxYValue, 1, 0, BinWithMostCounts);
		Double_t Lower2Contents = h1->GetBinContent(Lower2);

		Double_t Lower1 = Lower2 - 1;
		Double_t Lower1Contents = h1->GetBinContent(Lower1);

		Double_t LowerBinFraction = Lower1Contents/Lower2Contents;
		Double_t CenterLower1 = h1->GetBinCenter(Lower1);
		Double_t CenterLower2 = h1->GetBinCenter(Lower2);
		Double_t LowerBinWidth = CenterLower2 - CenterLower1;
		FWHMLeftXValue = CenterLower1 + (LowerBinWidth)*(LowerBinFraction);
	}

	else if (binA != 0)
	{
		FWHMLeftXValue = h1->GetBinCenter(binA);
	}

	int binB = 0;
	h1->GetBinWithContent(HalfMaxYValue, binN, BinWithMostCounts, 200, 0);
	if (binB == 0)
	{
		Double_t Upper1 = h1->FindLastBinAbove(HalfMaxYValue, 1, BinWithMostCounts, 200);
		Double_t Upper1Contents = h1->GetBinContent(Upper1);

		Double_t Upper2 = Upper1 + 1;
		Double_t Upper2Contents = h1->GetBinContent(Upper2);

		Double_t UpperBinFraction = Upper2Contents/Upper1Contents;
		Double_t CenterUpper1 = h1->GetBinCenter(Upper1);
		Double_t CenterUpper2 = h1->GetBinCenter(Upper2);
		Double_t UpperBinWidth = CenterUpper2 - CenterUpper1;
		FWHMRightXValue = CenterUpper2 + (UpperBinWidth)*(UpperBinFraction);
	}

	else if (binB != 0)
	{
		FWHMRightXValue = h1->GetBinCenter(binB);
	}

	Double_t FinalWidth = FWHMRightXValue - FWHMLeftXValue;
	Double_t FWHM = (FinalWidth/100)*100;

	///////////////////////////////////////////////////////////////////////////////////////////////

	//Code From 200MeV Smear
	//Gaussian and Filling Histogram
	TFile b("~/Vincent/G4CATS/Out/B4_200MeV.root");

	TF1 *f2 = new TF1("f2", "gaus(0)", -5, 5);
	f2->SetParameter(0, (1/((0.09*TMath::Sqrt(200))*(TMath::Sqrt(2*TMath::Pi())))));
	f2->SetParameter(1, 0);
	f2->SetParameter(2, 0.09*TMath::Sqrt(200));

	TTreeReader r2("B4", &b);

	TTreeReaderValue<Double_t> Ecore(r2, "Ecore");
	TTreeReaderValue<Double_t> Eann1(r2, "Eann1");
	TTreeReaderValue<Double_t> Eann2(r2, "Eann2");
	TTreeReaderValue<Double_t> Eann3(r2, "Eann3");
	TTreeReaderValue<Double_t> Eann4(r2, "Eann4");
	TTreeReaderValue<Double_t> Eann5(r2, "Eann5");
	TTreeReaderValue<Double_t> Eann6(r2, "Eann6");

	TH1F *h2 = new TH1F("", "", 300, 180, 210);

	while (r2.Next())
	{
		h2->Fill(*Ecore + *Eann1 + *Eann2 + *Eann3 + *Eann4 + *Eann5 + *Eann6 + f2->GetRandom());
	}
	
	//200MeV FWHM Code
	Double_t BinWithMostCounts_2 = h2->GetMaximumBin();
	Double_t MaxYValue_2 = h2->GetBinContent(BinWithMostCounts_2);
	Double_t HalfMaxYValue_2 = MaxYValue_2/2;

	Double_t FWHMLeftXValue_2 = 0;
	int binA2 = 0;
	h1->GetBinWithContent(HalfMaxYValue_2, binA_2, 0, BinWithMostCounts_2, 0);

	if (binA_2 == 0)
	{
		Double_t Lower2_2 = h2->FindFirstBinAbove(HalfMaxYValue_2, 1, 0, BinWithMostCounts_2);
		Double_t Lower2Contents_2 = h2->GetBinContent(Lower2_2);

		Double_t Lower1_2 = Lower2_2 - 1;
		Double_t Lower1Contents_2 = h2->GetBinContent(Lower1_2);

		Double_t LowerBinFraction_2 = Lower1Contents_2/Lower2Contents_2;
		Double_t CenterLower1_2 = h2->GetBinCenter(Lower1_2);
		Double_t CenterLower2_2 = h2->GetBinCenter(Lower2_2);
		Double_t LowerBinWidth_2 = CenterLower2_2 - CenterLower1_2;
		FWHMLeftXValue_2 = CenterLower1_2 + (LowerBinWidth_2)*(LowerBinFraction_2);
	}

	else if (binA_2 != 0)
	{
		FWHMLeftXValue_2 = h2->GetBinCenter(binA_2);
	}

	int binB_2 = 0;
	h1->GetBinWithContent(HalfMaxYValue_2, binB_2, BinWithMostCounts_2, 300, 0);
	if (binB_2 == 0)
	{
		Double_t Upper1_2 = h2->FindLastBinAbove(HalfMaxYValue_2, 1, BinWithMostCounts_2, 300);
		Double_t Upper1Contents_2 = h2->GetBinContent(Upper1_2);

		Double_t Upper2_2 = Upper1_2 + 1;
		Double_t Upper2Contents_2 = h2->GetBinContent(Upper2_2);

		Double_t UpperBinFraction_2 = Upper2Contents_2/Upper1Contents_2;
		Double_t CenterUpper1_2 = h2->GetBinCenter(Upper1_2);
		Double_t CenterUpper2_2 = h2->GetBinCenter(Upper2_2);
		Double_t UpperBinWidth_2 = CenterUpper2_2 - CenterUpper1_2;
		FWHMRightXValue_2 = CenterUpper2_2 + (UpperBinWidth_2)*(UpperBinFraction_2);
	}

	else if (binB_2 != 0)
	{
		FWHMRightXValue_2 = h2->GetBinCenter(binB_2);
	}

	Double_t FinalWidth_2 = FWHMRightXValue_2 - FWHMLeftXValue_2;
	Double_t FWHM_2 = (FinalWidth_2/200)*100;

	///////////////////////////////////////////////////////////////////////////////////////////////////

	//Code From 200MeV Smear
	//Gaussian and Filling Histogram
	TFile c("~/Vincent/G4CATS/Out/B4_300MeV.root");

	TF1 *f3 = new TF1("f3", "gaus(0)", -5, 5);
	f3->SetParameter(0, (1/((0.11*TMath::Sqrt(300))*(TMath::Sqrt(2*TMath::Pi())))));
	f3->SetParameter(1, 0);
	f3->SetParameter(2, 0.11*TMath::Sqrt(300));

	TTreeReader r3("B4", &c);

	TTreeReaderValue<Double_t> Ecore(r3, "Ecore");
	TTreeReaderValue<Double_t> Eann1(r3, "Eann1");
	TTreeReaderValue<Double_t> Eann2(r3, "Eann2");
	TTreeReaderValue<Double_t> Eann3(r3, "Eann3");
	TTreeReaderValue<Double_t> Eann4(r3, "Eann4");
	TTreeReaderValue<Double_t> Eann5(r3, "Eann5");
	TTreeReaderValue<Double_t> Eann6(r3, "Eann6");

	TH1F *h3 = new TH1F("", "", 400, 270, 310);

	while (r3.Next())
	{
		h3->Fill(*Ecore + *Eann1 + *Eann2 + *Eann3 + *Eann4 + *Eann5 + *Eann6 + f3->GetRandom());
	}
	
	//300MeV FWHM Code
	Double_t BinWithMostCounts_3 = h3->GetMaximumBin();
	Double_t MaxYValue_3 = h3->GetBinContent(BinWithMostCounts_3);
	Double_t HalfMaxYValue_3 = MaxYValue_3/2;

	Double_t FWHMLeftXValue_3 = 0;
	int binA_3 = 0;
	h3->GetBinWithContent(HalfMaxYValue_3, binA_3, 0, BinWithMostCounts_3, 0);

	if (binC == 0)
	{
		Double_t Lower2 = h1->FindFirstBinAbove(HalfMaxYValue, 1, 0, BinWithMostCounts);
		Double_t Lower2Contents = h1->GetBinContent(Lower2);

		Double_t Lower1 = Lower2 - 1;
		Double_t Lower1Contents = h1->GetBinContent(Lower1);

		Double_t LowerBinFraction = Lower1Contents/Lower2Contents;
		Double_t CenterLower1 = h1->GetBinCenter(Lower1);
		Double_t CenterLower2 = h1->GetBinCenter(Lower2);
		Double_t LowerBinWidth = CenterLower2 - CenterLower1;
		FWHMLeftXValue = CenterLower1 + (LowerBinWidth)*(LowerBinFraction);
	}

	else if (binC != 0)
	{
		FWHMLeftXValue = h1->GetBinCenter(binC);
	}

	int binD = 0;
	h1->GetBinWithContent(HalfMaxYValue, binD, BinWithMostCounts, 300, 0);
	if (binD == 0)
	{
		Double_t Upper1 = h1->FindLastBinAbove(HalfMaxYValue, 1, BinWithMostCounts, 300);
		Double_t Upper1Contents = h1->GetBinContent(Upper1);

		Double_t Upper2 = Upper1 + 1;
		Double_t Upper2Contents = h1->GetBinContent(Upper2);

		Double_t UpperBinFraction = Upper2Contents/Upper1Contents;
		Double_t CenterUpper1 = h1->GetBinCenter(Upper1);
		Double_t CenterUpper2 = h1->GetBinCenter(Upper2);
		Double_t UpperBinWidth = CenterUpper2 - CenterUpper1;
		FWHMRightXValue = CenterUpper2 + (UpperBinWidth)*(UpperBinFraction);
	}

	else if (binD != 0)
	{
		FWHMRightXValue = h1->GetBinCenter(binD);
	}

	Double_t FinalWidth = FWHMRightXValue - FWHMLeftXValue;
	Double_t FWHM = (FinalWidth/200)*100;

	//Code From 300MeV Smear
	//Gaussian and Filling Histogram
	TFile c("~/Vincent/G4CATS/Out/B4_300MeV.root");

	TF1 *f3 = new TF1("f3", "gaus(0)", -8.5, 8.5);
	f1->SetParameter(0, (1/((0.11*TMath::Sqrt(300))*(TMath::Sqrt(2*TMath::Pi())))));
	f1->SetParameter(1, 0);
	f1->SetParameter(2, 0.11*TMath::Sqrt(300));

	TTreeReader r1("B4", &c);

	TTreeReaderValue<Double_t> Ecore(r1, "Ecore");
	TTreeReaderValue<Double_t> Eann1(r1, "Eann1");
	TTreeReaderValue<Double_t> Eann2(r1, "Eann2");
	TTreeReaderValue<Double_t> Eann3(r1, "Eann3");
	TTreeReaderValue<Double_t> Eann4(r1, "Eann4");
	TTreeReaderValue<Double_t> Eann5(r1, "Eann5");
	TTreeReaderValue<Double_t> Eann6(r1, "Eann6");

	TH1F *h1 = new TH1F("", "", 400, 270, 310);

	while (r1.Next())
	{
		h1->Fill(*Ecore + *Eann1 + *Eann2 + *Eann3 + *Eann4 + *Eann5 + *Eann6 + f1->GetRandom());
	}
	
	//300MeV FWHM Code
	Double_t BinWithMostCounts = h1->GetMaximumBin();
	Double_t MaxYValue = h1->GetBinContent(BinWithMostCounts);
	Double_t HalfMaxYValue = MaxYValue/2;

	Double_t FWHMLeftXValue = 0;
	int binC = 0;
	h1->GetBinWithContent(HalfMaxYValue, binC, 0, BinWithMostCounts, 0);

	if (binC == 0)
	{
		Double_t Lower2 = h1->FindFirstBinAbove(HalfMaxYValue, 1, 0, BinWithMostCounts);
		Double_t Lower2Contents = h1->GetBinContent(Lower2);

		Double_t Lower1 = Lower2 - 1;
		Double_t Lower1Contents = h1->GetBinContent(Lower1);

		Double_t LowerBinFraction = Lower1Contents/Lower2Contents;
		Double_t CenterLower1 = h1->GetBinCenter(Lower1);
		Double_t CenterLower2 = h1->GetBinCenter(Lower2);
		Double_t LowerBinWidth = CenterLower2 - CenterLower1;
		FWHMLeftXValue = CenterLower1 + (LowerBinWidth)*(LowerBinFraction);
	}

	else if (binC != 0)
	{
		FWHMLeftXValue = h1->GetBinCenter(binC);
	}

	int binD = 0;
	h1->GetBinWithContent(HalfMaxYValue, binD, BinWithMostCounts, 300, 0);
	if (binD == 0)
	{
		Double_t Upper1 = h1->FindLastBinAbove(HalfMaxYValue, 1, BinWithMostCounts, 300);
		Double_t Upper1Contents = h1->GetBinContent(Upper1);

		Double_t Upper2 = Upper1 + 1;
		Double_t Upper2Contents = h1->GetBinContent(Upper2);

		Double_t UpperBinFraction = Upper2Contents/Upper1Contents;
		Double_t CenterUpper1 = h1->GetBinCenter(Upper1);
		Double_t CenterUpper2 = h1->GetBinCenter(Upper2);
		Double_t UpperBinWidth = CenterUpper2 - CenterUpper1;
		FWHMRightXValue = CenterUpper2 + (UpperBinWidth)*(UpperBinFraction);
	}

	else if (binD != 0)
	{
		FWHMRightXValue = h1->GetBinCenter(binD);
	}

	Double_t FinalWidth = FWHMRightXValue - FWHMLeftXValue;
	Double_t FWHM = (FinalWidth/200)*100;













	//END
	TCanvas* c1 = new TCanvas("c1", "", 20, 20, 1000, 1000);
	c1->Divide(1,1);
	c1->cd(1);


}
