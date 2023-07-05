//#include "TF1.h"
//#include "TMath.h"

Double_t MyMethod(Double_t *x, Double_t *par)
{

	Double_t exponent = ((-((x[0] - par[2])/par[3]) - par[0]) * (-((x[0] - par[2])/par[3]) - par[0])) / (2 * par[1] * par[1]);
	Double_t erf_top_limit = par[4] * (x[0] - par[2]) / (par[3] * TMath::Sqrt(2));
	Double_t function = (1 / (par[3] * par[1] * TMath::Sqrt(2 * TMath::Pi()))) * TMath::Exp(exponent) * (1 + TMath::Erf(erf_top_limit));

	return function;

}
int main()
{
	//Normal Histogram Stuff
	//gStyle->SetOptTitle(1);
	//gStyle->SetOptStat(0);
	TCanvas* c1 = new TCanvas("c1", "", 20, 20, 1000, 1000);
	c1->Divide(1,2);
	c1->cd(1);

	TString filename = "~/Vincent/G4CATS/Out/B4_200MeV.root";
	TFile *f = TFile::Open(filename);

	TH1F* h1 = new TH1F("Histogram Statistics", "", 300, 180, 210);

	TTreeReader r1("B4", f);
	TTreeReaderValue<Double_t> Ecore(r1, "Ecore");
	TTreeReaderValue<Double_t> Eann1(r1, "Eann1");
	TTreeReaderValue<Double_t> Eann2(r1, "Eann2");
	TTreeReaderValue<Double_t> Eann3(r1, "Eann3");
	TTreeReaderValue<Double_t> Eann4(r1, "Eann4");
	TTreeReaderValue<Double_t> Eann5(r1, "Eann5");
	TTreeReaderValue<Double_t> Eann6(r1, "Eann6");

	while (r1.Next())
	{
		h1->Fill(*Ecore + *Eann1 + *Eann2 + *Eann3 + *Eann4 + *Eann5 + *Eann6);
	}

  	h1->GetXaxis()->SetTitle("Energy (MeV)");
  	h1->GetYaxis()->SetTitle("Counts");
  	h1->SetTitle("Energy Recorded by G4 CATS sim -- 200MeV Photon Beam");
	h1->Draw();

  	//Start of FWHM Section
  	//Creating a Skewed Gaussian Function
  	Double_t BinWithMostCounts = h1->GetMaximumBin();
  	Double_t MaxYValue = h1->GetBinContent(BinWithMostCounts);
  	Double_t CenterPeak = h1->GetBinCenter(BinWithMostCounts);
	Double_t StdDev = h1->GetStdDev();

	c1->cd(2);

	TF1 *graph_function = new TF1("graph_function", MyMethod, 180, 210, 5);

	//0 is the mean; 1 is the standard deviation; 2 is E; 3 is w; 4 is a (the shape parameter)
	graph_function->SetParameter(0, CenterPeak);
	graph_function->SetParameter(1, StdDev);
	graph_function->SetParameter(2, 0);
	graph_function->SetParameter(3, 1);
	graph_function->SetParameter(4, -10);
 
	//These parameters must be the same as those set to the TF1 function above
/*	Double_t parameters[5] = {CenterPeak, StdDev, 0, 1, -10};

	

	Double_t max = 14000;
	Double_t haha = 199.95;
	Double_t b = MyMethod2(MyMethod1, &haha, parameters);
	cout << b << endl;
	Double_t c = (max / b);
	cout << c << endl;
	lol->SetParameter(0, c);
*/	
	

	graph_function->Draw("SAME");

	return 0;
	
}

