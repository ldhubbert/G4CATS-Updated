#include <TMath.h>
#include <TF1.h>
#include <TAxis.h>

//This code contains the standard formula for t. Nevertheless, it should produce the same information as that of t_graph.C
Double_t t_graph(Double_t *x)
{
	//x[0] represents theta
	
	//Two parameters
	Double_t initial_energy = 1000;
	Double_t mass_proton = 938.27208816;
	Double_t fraction = initial_energy/(1 + ((initial_energy * (1 - TMath::Cos(x[0])))/mass_proton));

	Double_t t = (-2 * initial_energy * fraction * (1 - TMath::Cos(x[0])));
	return t;
}

void maincode()
{
	TCanvas *c1 = new TCanvas("c1", "", 20, 20, 1000, 1000);

	int array_size = 8;
	//Here, the x_values correspond to theta
	Double_t x_values[array_size];
	//Here, the y_values correspond to the t values
	Double_t y_values[array_size];

	for (int x = 20; x <= 160; x = x + 20)
	{
		//This is to pass a double into t
		//Also, change from degrees to radians for the TMath::Cos statement to work
		Double_t double_x = static_cast<Double_t>(x) * (TMath::Pi() / 180);
		//So array starts numbering at 0
		int array_numbering = (static_cast<Double_t>(x)/20) - 1;
		x_values[array_numbering] = x;
		y_values[array_numbering] = t_graph(&double_x)/1000000;
	}

	TGraph *g1 = new TGraph(array_size, x_values, y_values);
	g1->SetTitle("t vs. Theta for a 1000MeV Incident Photon Beam");
	g1->GetYaxis()->SetTitle("t (in GeV^2)");
	g1->GetXaxis()->SetTitle("Theta (in degrees)");
	g1->GetYaxis()->CenterTitle();
	g1->GetXaxis()->CenterTitle();
	g1->SetMarkerColor(4);
	g1->SetMarkerStyle(21);
	g1->Draw("AP");
}
