#include "TF1.h"
#include "TMath.h"
Double_t MyMethod1(Double_t *x, Double_t *par)
{
	TF1 *inttest = new TF1("inttest", "TMath::Power(TMath::E(),-1*x*x)", -1*TMath::Infinity(), TMath::Infinity());
	Double_t integral_answer = inttest->Integral(0,(par[4]*(x[0] - par[0]))/(par[1]*TMath::Sqrt(2)));

	return integral_answer;
}

//Double_t MyMethod2(Double_t (*PointerToMyMethod1)(Double_t *, Double_t*), Double_t *x, Double_t *par)
//{
//	Double_t func2 = ((2 * TMath::Power(TMath::E(),(TMath::Power((-((x[0] - par[0])/par[1]) - par[2]),2)/(2*par[3]*par[3])) * (1 + 2/TMath::Sqrt(TMath::Pi()) * PointerToMyMethod1(x, par))))/(2*par[1]*par[3]*TMath::Sqrt(2*TMath::Pi())));

//	return func2;
//}

void maincode()
{
	//Normal Histogram Stuff
	//gStyle->SetOptTitle(1);
	//gStyle->SetOptStat(0);
	TCanvas* c1 = new TCanvas("c1", "", 20, 20, 1000, 1000);
	c1->Divide(1,1);
	c1->cd(1);

/*	TString filename = "~/Vincent/G4CATS/Out/B4_200MeV.root";
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
*/
  	//testing Integral function
  	//TF1 *test = new TF1("test", "cos(x)", 0, 10);
  	//Double_t a = test->TF1::Integral(2,4);
  	//cout << a << endl;

  	//Skewed Gaussian Formula
  	//TF1 *integral_function = new TF1("integral_function", "TMath::Power(TMath::E(), -1*x[0]*x[0])", -1*TMath::Infinity(), TMath::Infinity());
  	//TF1 *f1 = new TF1("f1", "((2 * TMath::Power(TMath::E(),(TMath::Power((-((x[0] - [0])/[2]) - [3]),2))/(2*TMath::Power([4],2))) * (1 + 2/TMath::Sqrt(TMath::Pi()) * integral_function->Integral(0,([5]*(x[0] - [0]))/([2]*TMath::Sqrt(2))))", 180, 210);
  	//f1->SetParameter(1, 200);
  	//f1->SetParameter(2, 200);
  	//f1->SetParameter(3, MaxYValue);
  	//f1->SetParameter(4, h1->GetStdDev());
  	//f1->SetParameter(5, -10);
  	//f1->Draw("SAME");
  
  	//Trying out TwoBody strategy

	//Double_t (*PointerToMyMethod1)(Double_t*, Double_t*) = MyMethod1;
	//Double_t result = MyMethod2(PointerToMyMethod1, x, par);

/*	Double_t par[5];
	par[0] = 200;
	par[1] = 1;
	par[2] = 200;
	par[3] = 1;
	par[4] = -10;
*/
	TF1 *lol = new TF1("lol", [&](Double_t *x, Double_t *par){ return ((2 * TMath::Power(TMath::E(),(TMath::Power((-((x[0] - par[0])/par[1]) - par[2]),2)/(2*par[3]*par[3])) * (1 + 2/TMath::Sqrt(TMath::Pi()) * MyMethod1(x, par))))/(2*par[1]*par[3]*TMath::Sqrt(2*TMath::Pi()))); }, 180, 210, 3);

	Double_t par[5];
	par[0] = 200;
	par[1] = 1;
	par[2] = 200;
	par[3] = 1;
	par[4] = -10;

  	//TF1 *lol = new TF1("lol", MyMethod2, 180, 210, 3);

	//lol->SetParameter(0, 199.95);
	//lol->SetParameter(1, 1);
	//lol->SetParameter(2, 100);
	//lol->SetParameter(3, 1);
 
	//These parameters must be the same as those set to the TF1 function above
/*	Double_t parameters[3] = {1,199.95,1};

	Double_t max = 14000;
	Double_t haha = 199.95;
	Double_t b = MyMethod2(MyMethod1, &haha, parameters);
	cout << b << endl;
	Double_t c = (max / b);
	cout << c << endl;
	lol->SetParameter(0, c);
	
*/	

	lol->Draw();

	
}

