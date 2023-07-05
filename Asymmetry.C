#include "/Users/dhornidge/Code/lib/physics.h"

// Asymmetry Function
Double_t AsymFunc( Double_t*, Double_t*);

// Smearing
void Smear()
{
	UInt_t i = 0;
	UInt_t N;
	Double_t x[100], dx[100], y[100], dy[100];
	Double_t err, yy[100], phi;
	Double_t param[3];
	TRandom3 gen( 0);
	TString name;

// Fit a user function to the graph.
	TF1 *f1 = new TF1( "AsymFunc", AsymFunc, 0, 360, 3);
	f1->SetParameters( 1, 0.5, 0);

	// relative error
	err = 0.05;

	for ( phi = 0; phi < 360; phi += 10)
	{
		x[i] = phi;
		dx[i] = 0;
		yy[i] = f1->Eval( phi);
		dy[i] = err*yy[i];
		y[i] = yy[i]*gen.Gaus( 1, err);

		cout << i;
		cout << "  " << x[i];
		cout << "  " << dx[i];
		cout << "  " << yy[i];
		cout << "  " << y[i];
		cout << "  " << dy[i];
		cout << endl;

		i++;
	}
	N = i;

	TCanvas *c1 = new TCanvas( "c1", "Asymmmetry Test", 200, 10, 1000, 500);
	c1->SetFillColor( 42);
	c1->SetGrid();
	c1->GetFrame()->SetFillColor( 21);
	c1->GetFrame()->SetBorderSize( 12);
	c1->Divide( 2, 1);

	c1->cd( 1);
	TGraphErrors *gr = new TGraphErrors( N, x, yy, dx, dy);
	gr->SetTitle( "Unsmeared");
	gr->SetMarkerColor( 4);
	gr->SetMarkerStyle( 21);
	gr->GetXaxis()->SetTitleOffset( 1.1);
	gr->GetYaxis()->SetTitleOffset( 1.0);
	gr->GetYaxis()->SetTitleSize( 0.05);
	gr->GetXaxis()->SetTitle("#Phi (deg)");
	gr->GetYaxis()->SetTitle("#Sigma");
	gr->GetXaxis()->SetLabelSize( 0.03);
	gr->GetYaxis()->SetLabelSize( 0.03);
	gr->GetXaxis()->CenterTitle();
	gr->GetYaxis()->CenterTitle();
	gr->Draw( "AP");

	c1->cd( 2);
	TGraphErrors *gr2 = new TGraphErrors( N, x, y, dx, dy);
	gr2->SetTitle( "Smeared");
	gr2->SetMarkerColor( 2);
	gr2->SetMarkerStyle( 21);
	gr2->GetXaxis()->SetTitleOffset( 1.1);
	gr2->GetYaxis()->SetTitleOffset( 1.0);
	gr2->GetYaxis()->SetTitleSize( 0.05);
	gr2->GetXaxis()->SetTitle("#Phi (deg)");
	gr2->GetYaxis()->SetTitle("#Sigma");
	gr2->GetXaxis()->SetLabelSize( 0.03);
	gr2->GetYaxis()->SetLabelSize( 0.03);
	gr2->GetXaxis()->CenterTitle();
	gr2->GetYaxis()->CenterTitle();
	gr2->Draw( "AP");

	ofstream outFile( "asym_smear_test.dat");
	for( i = 0; i < N; i++) {
		name = Form( "%3.0f  %6.4f  %6.4f", x[i], y[i], dy[i]);
		outFile << name << endl;
	}
	outFile.close();

}

// Draw and Fit
void DrawFit()
{
	UInt_t i = 0, N;
	Double_t x[100], dx[100], y[100], dy[100];
	Double_t param[3];

	ifstream inFile( "asym_smear_test.dat");
	while( !inFile.eof()) {
		inFile >> x[i] >> y[i] >> dy[i];
		dx[i++] = 0;
	}
	inFile.close();
	N = i;

	TCanvas *c1 = new TCanvas( "c1", "Asymmmetry Test", 200, 10, 700, 500);
	c1->SetFillColor( 42);
	c1->SetGrid();
	c1->GetFrame()->SetFillColor( 21);
	c1->GetFrame()->SetBorderSize( 12);

	// create the TGraphErrors and draw it
	TGraphErrors *gr = new TGraphErrors( N, x, y, dx, dy);

	gr->SetTitle( "Asymmetry Test");
	gr->SetMarkerColor( 4);
	gr->SetMarkerStyle( 21);
	gr->GetXaxis()->SetTitleOffset( 1.1);
	gr->GetYaxis()->SetTitleOffset( 1.0);
	gr->GetYaxis()->SetTitleSize( 0.05);
	gr->GetXaxis()->SetTitle("#Phi (deg)");
	gr->GetYaxis()->SetTitle("#Sigma");
	gr->GetXaxis()->SetLabelSize( 0.03);
	gr->GetYaxis()->SetLabelSize( 0.03);
	gr->GetXaxis()->CenterTitle();
	gr->GetYaxis()->CenterTitle();

// Fit a user function to the graph.
	TF1 *f1 = new TF1( "AsymFunc", AsymFunc, 0, 360, 3);
	gr->Fit( "AsymFunc");

// Read parameters into array param.
	f1->GetParameters( &param[0]);

// Print three parameters to screen.
	cout << param[0];
	cout << "   " << param[1];
	cout << "   " << param[2];
	cout << endl;

// Change the displayed fitting statistics.
	gStyle->SetOptFit( 111);

	gr->Draw( "AP");
	c1->Update();  
}

Double_t AsymFunc( Double_t *x, Double_t *par)
{
	Double_t sigma, dsdo, asym, phi, phi0;

	dsdo = par[0];
	sigma = par[1];
	phi0 = par[2];
	phi = x[0];

	asym = dsdo*(1-sigma*cos( 2*phi*kD2R + phi0));

	return( asym);
}
