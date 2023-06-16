#include "physics.h"
#include "TRandom3.h"

void ComptonSmear( Double_t ke = 200, Double_t mp = 938.27)
{

	Int_t i;
	Double_t costh, qtheta, Egamma;
	Double_t qm, qth, qph, qmom;
	Double_t qx, qy, qz, qe;
	Double_t th_smr, eg_smr;
	TLorentzVector k, p, p1, q;
	TRandom3 gen( 0);

	TCanvas *c1 = new TCanvas ( "c1", "Energy Smear of Recoil Photon", 50, 10, 500, 700);
	c1->Divide( 1, 3);

// Set photon energy and momentum; default is 200 MeV;
// Beam direction is along z
	k.SetPxPyPzE( 0, 0, ke, ke);

// Set target to a proton at rest
	p.SetPxPyPzE( 0, 0, 0, mp);

// Photon with phi=0
	qm = 0;
	qph = 0;
	
	TH1D *h1 = new TH1D( "h1", "Theta", 180, 0, 180);
	TH1D *h2 = new TH1D( "h2", "Egamma", 200, 100, 300);
	TH1D *h3 = new TH1D( "h3", "Mass of Proton Smear", 100, 900, 1000);

	for ( i = 0; i <= 10000; i++)
	{

		costh = gen.Rndm()*2 - 1;
		Egamma = (ke*mp)/(mp + ke*(1-costh)); 
		qtheta = acos( costh)/kD2R;

		th_smr = 3/qtheta;
		eg_smr = 0.02/pow( Egamma/1000, 0.25);

		qth = qtheta*gen.Gaus( 1, th_smr);
		qe = Egamma*gen.Gaus( 1, eg_smr);

		// Calculate scattered photon momentum components
		qx = qe*sin( qth*kD2R)*cos( qph*kD2R);
		qy = qe*sin( qth*kD2R)*sin( qph*kD2R);
		qz = qe*cos( qth*kD2R);
	
		// Set recoil photon 4-momentum
		q.SetPxPyPzE( qx, qy, qz, qe);

		// Calculate recoil proton 4-momentum using 4-mom conservation
		p1 = k + p - q;

		h1->Fill( qth);
		h2->Fill( qe);
		h3->Fill( p1.Mag());

	}

	c1->cd(1);
	h1->Draw();
	c1->cd(2);
	h2->Draw();
	c1->cd(3);
	h3->Draw();

}
