/* 
 * TwoBody
 *
 * This macro does all sorts of great stuff and has been updated numerous time
 * over the last five years.
 *
 * 02.05.2007		DLH		First version.
 * 24.09.2011		DLH		Adding dilepton stuff.
 *
 */

#include "/Users/dhornidge/Code/lib/physics.h"

void TwoBodyLab( Double_t ke = 200, Double_t qth = 45) {

	Double_t km, Ek, kmom;
	Double_t pm;
	Double_t qm, qth, qph, qmom;
	Double_t qx, qy, qz, qe;
	Double_t ang;
	TLorentzVector k, p, p1, q;
	TString name;
	
// Beam is a photon
//	km = 0;
// Beam is a charged pion
	km = kMPI_MEV;

	Ek = ke + km;
	kmom = momentum( Ek, km);

// Target is a proton at rest
	pm = kMP_MEV;

// Set beam energy and momentum;
// Beam direction is along z
	k.SetPxPyPzE( 0, 0, kmom, Ek);

// Target is at rest
	p.SetPxPyPzE( 0, 0, 0, pm);

// Set mass of particle to
//	qm = kMPI0_MEV;		// pi0
//	qm = kMPI_MEV;			// charged pion
	qm = 0;					// photon

// Convert theta to radians; default is pi/4
// Phi is zero since we are dealing with two-body kinematics and no
// polarization.
	qth *= kD2R;
	qph = 0;

// Calculate momentum using kinematics function
	qmom = qp( k.E(), p.E(), qth, qm);
// Calculate energy
	qe = energy( qmom, qm);

// Calculate momentum components
	qx = qmom*sin( qth)*cos( qph);
	qy = qmom*sin( qth)*sin( qph);
	qz = qmom*cos( qth);

// Set 4-momentum
	q.SetPxPyPzE( qx, qy, qz, qe);

// Calculate recoil 4-momentum using 4-mom conservation
	p1 = k + p - q;

// Calculate angle between two vectors for fun
	ang = q.Vect().Angle(p1.Vect());

// Output
	cout << "      E     m       p    theta   phi " << endl;

// Beam photon
	name = Form( "k:  %5.1f  %5.1f  %5.1f  %5.1f  %5.1f\n", k.E(), k.M(),
			k.Vect().Mag(), k.Theta()/kD2R, k.Phi()/kD2R);
	cout << name;

// Target
	name = Form( "p:  %5.1f  %5.1f  %5.1f  %5.1f  %5.1f\n", p.E(), p.M(),
			p.Vect().Mag(), p.Theta()/kD2R, p.Phi()/kD2R);
	cout << name;

// Produced particle
	name = Form( "q:  %5.1f  %5.1f  %5.1f  %5.1f  %5.1f\n", q.E(), q.M(),
			q.Vect().Mag(), q.Theta()/kD2R, q.Phi()/kD2R);
	cout << name;

// Recoiling target
	name = Form( "p1: %5.1f  %5.1f  %5.1f  %5.1f  %5.1f\n", p1.E(), p1.M(),
			p1.Vect().Mag(), p1.Theta()/kD2R, p1.Phi()/kD2R);
	cout << name;

//	cout << p1.Px() << " " << q.Px() << endl;
//	cout << p1.Py() << " " << q.Py() << endl;
//	cout << k.Pz() << " " << p1.Pz() + q.Pz() << endl;

}

/*
 * TwoBodyCM
 *
 * This is the same as the function above except that as input it uses the CM
 * scattered angle instead of the lab scattered angle.  Moreover, all CM
 * quantities are also calculated and output.  This function makes heavy use of
 * the boosting capability of the TLorentzVectors, and is quite a bit more
 * elegant that the above function.  Note also that inputing the CM angle
 * instead of the lab angle gives you a different result!
 *
 * DLH 02.05.2007
 *
 */

void TwoBodyCM( Double_t ke = 200, Double_t qth_cm = 45) {

	TLorentzVector k, p, p1, q, pIn;
	TLorentzVector k_cm, p_cm, p1_cm, q_cm;
	TVector3 cmBoost, labBoost;
	
	Double_t qm, qph_cm, mom_cm;
	Double_t qx_cm, qy_cm, qz_cm, qe_cm;
	Double_t pm, S;
	Double_t ang;
	Double_t W;

	TString name;

//	pm = kMP_MEV;
	pm = kME_MEV;
// Set photon energy and momentum; default is 200 MeV;
// Beam direction is along z
	k.SetPxPyPzE( 0, 0, ke, ke);
// Set target to a proton at rest
	p.SetPxPyPzE( 0, 0, 0, pm);

// Total incoming 4-momentum
	pIn = k + p;
// The 3-vector boosts to and from the lab and CM frames
	labBoost = pIn.BoostVector();
	cmBoost = -pIn.BoostVector();
// Boosting the initial state particles' 4-momentum to the CM frame
	k_cm = k;
	k_cm.Boost( cmBoost);
	p_cm = p;
	p_cm.Boost( cmBoost);

// Set mass to:
//	qm = kMPI0_MEV;		// neutral pion
	qm = 0;					// photon

// Convert angle to radians
	qth_cm *= kD2R;

// Phi symmetry, so set phi to zero
	qph_cm = 0;

// Calculate cm energy
	S = 2*ke*pm + pm*pm;
	W = sqrt( S);
	name = Form( "W = %6.1f\n", W);
	cout << name;
	qe_cm = (S - pm*pm + qm*qm)/2/sqrt( S);

// Calculate cm momentum (it is the same for both the produced particle and
// the target by definition!)
	mom_cm = momentum( qe_cm, qm);

// Calculate cm momentumm components
	qx_cm = mom_cm*sin( qth_cm)*cos( qph_cm);
	qy_cm = mom_cm*sin( qth_cm)*sin( qph_cm);
	qz_cm = mom_cm*cos( qth_cm);

// Set cm 4-momentum
	q_cm.SetPxPyPzE( qx_cm, qy_cm, qz_cm, qe_cm);

// Calculate the lab parameters by boosting the cm 4-momentum to the lab
// frame
	q = q_cm;
	q.Boost( labBoost);

// Calculate recoil proton 4-momentum using 4-mom conservation
	p1 = k + p - q;

// Calculate the recoil proton cm parameters by boosting the lab 4-momentum to
// the cm frame
	p1_cm = p1;
	p1_cm.Boost( cmBoost);

// Calculate angle between two vectors for fun
	ang = q.Vect().Angle( p1.Vect());

// Output
	cout << "          E     m      T    p    theta   phi " << endl;

// Lab
// Beam photon
	name = Form( "k:     %6.1f  %5.1f  %5.1f %5.1f  %5.1f  %5.1f\n", k.E(), k.M(),
			k.E()-k.M(), k.Vect().Mag(), k.Theta()/kD2R, k.Phi()/kD2R);
	cout << name;

// Target
	name = Form( "p:     %6.1f  %5.1f  %5.1f %5.1f  %5.1f  %5.1f\n", p.E(), p.M(),
			p.E()-p.M(), p.Vect().Mag(), p.Theta()/kD2R, p.Phi()/kD2R);
	cout << name;

// Produced particle
	name = Form( "q:     %6.1f  %5.1f  %5.1f %5.1f  %5.1f  %5.1f\n", q.E(), q.M(),
			q.E()-q.M(), q.Vect().Mag(), q.Theta()/kD2R, q.Phi()/kD2R);
	cout << name;

// Recoiling target
	name = Form( "p1:    %6.1f  %5.1f  %5.1f %5.1f  %5.1f  %5.1f\n", p1.E(), p1.M(),
			p1.E()-p1.M(), p1.Vect().Mag(), p1.Theta()/kD2R, p1.Phi()/kD2R);
	cout << name;

// CM
// Beam photon
	name = Form( "k_cm:  %6.1f  %5.1f  %5.1f %5.1f  %5.1f\n", k_cm.E(), k_cm.M(),
			k_cm.E()-k_cm.M(), k_cm.Vect().Mag(), k_cm.Theta()/kD2R,
			k_cm.Phi()/kD2R);
	cout << name;

// Target
	name = Form( "p_cm:  %6.1f  %5.1f  %5.1f %5.1f  %5.1f  %5.1f\n", p_cm.E(),
			p_cm.M(), p_cm.E()-p_cm.M(), p_cm.Vect().Mag(), p_cm.Theta()/kD2R,
			p_cm.Phi()/kD2R);
	cout << name;

// Produced particle
	name = Form( "q_cm:  %6.1f  %5.1f  %5.1f %5.1f  %5.1f  %5.1f\n", q_cm.E(),
			q_cm.M(), q_cm.E()-q_cm.M(), q_cm.Vect().Mag(), q_cm.Theta()/kD2R,
			q_cm.Phi()/kD2R);
	cout << name;

// Recoiling target
	name = Form( "p1_cm: %6.1f  %5.1f  %5.1f %5.1f  %5.1f  %5.1f\n", p1_cm.E(),
			p1_cm.M(), p1_cm.E()-p1_cm.M(), p1_cm.Vect().Mag(),
			p1_cm.Theta()/kD2R, p1_cm.Phi()/kD2R);
	cout << name;

}

void Compton( Double_t eg)
{
	TString name;
	UInt_t flag;

	c1 = new TCanvas( "c1", "Compton Kinematics", 0, 0, 700, 700);
	c1->SetGrid();
	c1->Divide(1,2);

	flag = 1;
//	f2 = new TF1( "KE", TwoBodyCMOut, 0, 180, 2);
	f2 = new TF1( "KE", TwoBodyLabOut, 0, 90, 2);
	name = "Scattered Particle Lab Kinetic Energy";
	f2->SetTitle( name);
	f2->SetParameters( eg, flag);
//	f2->GetXaxis()->SetTitle( "#theta^{#gamma'}_{CM} (deg)");
	f2->GetXaxis()->SetTitle( "#theta_{p'} (deg)");
	f2->GetYaxis()->SetTitle( "T^{#gamma'} (MeV)");
//	f2->GetYaxis()->SetTitle( "T^{p'} (MeV)");
	c1->cd(1);
	f2->Draw();

	Double_t lim = eg;

//	l = new TLine( 0, lim, 180, lim);
	l = new TLine( 0, lim, 90, lim);
	l->SetLineStyle( 2);
	l->Draw();

//	cout << f1->Eval( 20);
//	cout << " - ";
//	cout << f1->Eval( 160);
//	cout << endl;

//	cout << f2->Eval( 20);
//	cout << " - ";
//	cout << f2->Eval( 160);
//	cout << endl;

	flag = 0;
//	f1 = new TF1( "Theta", TwoBodyCMOut, 0, 180, 2);
	f1 = new TF1( "Theta", TwoBodyLabOut, 0, 90, 2);
	f1->SetParameters( eg, flag);
	name = "Scattered Particle Lab Angle";
	f1->SetTitle( name);
//	f1->GetXaxis()->SetTitle( "#theta^{#gamma'}_{CM} (deg)");
	f1->GetXaxis()->SetTitle( "#theta_{p'} (deg)");
	f1->GetYaxis()->SetTitle( "#theta^{#gamma'}_{lab} (deg)");
	c1->cd(2);
	f1->Draw();

	name = Form( "/Users/dave/Desktop/compton_%d.pdf", UInt_t( eg));
	c1->Print( name);

}

void Pi0Prod()
{
	Double_t eg;
	TString name;
	UInt_t flag;

	TCanvas *c1 = new TCanvas( "c1", "Pi0 Production Kinematics", 0, 0, 700, 400);

	eg = 300;
	flag = 2;
	TF1 *f1 = new TF1( "KE", TwoBodyLabOut, 0, 90, 2);
	name = "Recoil Proton KE vs. Angle";
	f1->SetTitle( name);
	f1->SetParameters( eg, flag);
	f1->GetXaxis()->SetTitle( "#theta_{p'} (deg)");
	f1->GetYaxis()->SetTitle( "T^{p'} (MeV)");
	f1->Draw();

	TF1 *f2 = new TF1( "KE", TwoBodyLabOut, 0, 90, 2);
	eg = 250;
	flag = 2;
	f2->SetParameters( eg, flag);
	f2->SetLineColor( 2);
	f2->Draw( "same");

	TF1 *f3 = new TF1( "KE", TwoBodyLabOut, 0, 90, 2);
	eg = 200;
	flag = 2;
	f3->SetParameters( eg, flag);
	f3->SetLineColor( 6);
	f3->Draw( "same");

	TF1 *f4 = new TF1( "KE", TwoBodyLabOut, 0, 90, 2);
	eg = 150;
	flag = 2;
	f4->SetParameters( eg, flag);
	f4->SetLineColor( 4);
	f4->Draw( "same");

	name = "E_{#gamma} (MeV)";
	TLegend *tl = new TLegend( 0.75, 0.62, 0.90, 0.88, name, "NDC");
	tl->SetTextFont( 132);
	tl->SetFillStyle(0);
	tl->SetBorderSize(0);
	tl->Draw();

	tl->AddEntry( f1, "300", "L");
	tl->AddEntry( f2, "250", "L");
	tl->AddEntry( f3, "200", "L");
	tl->AddEntry( f4, "150", "L");

	TPaveText *pt = new TPaveText( 47, 76, 57, 84);
	pt->AddText( "butanol");
	pt->SetTextFont( 132);
	pt->SetFillStyle( 0);
	pt->SetBorderSize( 0);
	pt->Draw();

	TPaveText *pt = new TPaveText( 47, 51, 67, 59);
	pt->AddText( "liquid hydrogen");
	pt->SetTextFont( 132);
	pt->SetFillStyle( 0);
	pt->SetBorderSize( 0);
	pt->Draw();

	TPaveText *pt = new TPaveText( 22, 5, 28, 13);
	pt->AddText( "APT");
	pt->SetTextFont( 132);
	pt->SetFillStyle( 0);
	pt->SetBorderSize( 0);
	pt->Draw();

	Double_t lim = 75;
	TLine *l = new TLine( 0, lim, 90, lim);
	l->SetLineStyle( 2);
	l->Draw();

	Double_t lim = 50;
	TLine *l = new TLine( 0, lim, 90, lim);
	l->SetLineStyle( 2);
	l->Draw();

	TLine *Double_t lim = 5;
	l = new TLine( 0, lim, 90, lim);
	l->SetLineStyle( 2);
	l->Draw();

//	name = Form( "/Users/dave/Desktop/_%d.pdf", UInt_t( eg));
	name = "RecoilKE.pdf";
	c1->Print( name);

}

void ThetaMin()
{
	UInt_t i;
	UInt_t flag = 1;
	Double_t Tmin;
	Double_t eg;
	Double_t tm1[500], tm2[500], tm3[500], tm4[500], egam[500];

	TString name;

	f2 = new TF1( "KE", TwoBodyCMOut, 0, 180, 2);

	i = 0;
	Tmin = 20;
	for ( eg = 170; eg <= 350; eg += 1)
	{
		f2->SetParameters( eg, flag);

		egam[i] = eg;

		for ( Double_t cmth = 180; cmth >= 0; cmth -= 1)
		{
			if (f2->Eval( cmth) <= Tmin) {
				tm1[i++] = cmth;
				break;
			}
		}
	}

	i = 0;
	Tmin = 40;
	for ( eg = 170; eg <= 350; eg += 1)
	{
		f2->SetParameters( eg, flag);

		egam[i] = eg;

		for ( Double_t cmth = 180; cmth >= 0; cmth -= 1)
		{
			if (f2->Eval( cmth) <= Tmin) {
				tm2[i++] = cmth;
				break;
			}
		}
	}

	i = 0;
	Tmin = 60;
	for ( eg = 170; eg <= 350; eg += 1)
	{
		f2->SetParameters( eg, flag);

		egam[i] = eg;

		for ( Double_t cmth = 180; cmth >= 0; cmth -= 1)
		{
			if (f2->Eval( cmth) <= Tmin) {
				tm3[i++] = cmth;
				break;
			}
		}
	}

	/*
	i = 0;
	Tmin = 200;
	for ( eg = 170; eg <= 350; eg += 1)
	{
		f2->SetParameters( eg, flag);

		egam[i] = eg;

		for ( Double_t cmth = 180; cmth >= 0; cmth -= 1)
		{
			if (f2->Eval( cmth) <= Tmin) {
				tm4[i++] = cmth;
				break;
			}
		}
	}
	*/

	c1 = new TCanvas( "c1", "Compton Kinematics", 0, 0, 700, 400);
	c1->SetGrid();

	gr = new TGraph( i-1, egam, tm1);
	gr->SetTitle("Minimum #theta^{cm}_{#gamma'}");
	gr->GetXaxis()->SetTitleOffset( 1.0);
	gr->GetXaxis()->SetTitleSize( 0.045);
	gr->GetYaxis()->SetTitleOffset( 1.0);
	gr->GetYaxis()->SetTitleSize( 0.045);
	gr->GetXaxis()->SetTitle("E_{#gamma} (MeV)");
	gr->GetYaxis()->SetTitle("#theta^{min}_{#gamma'} (deg)");
	gr->GetYaxis()->SetRangeUser(0,180);
	gr->Draw("AL");
	gr->SetLineWidth(2);

	gr2 = new TGraph( i-1, egam, tm2);
	gr2->Draw("Lsame");
	gr2->SetLineWidth(2);
	gr2->SetLineStyle(2);
	gr3 = new TGraph( i-1, egam, tm3);
	gr3->Draw("Lsame");
	gr3->SetLineStyle(3);
	gr3->SetLineWidth(2);
/*
	gr4 = new TGraph( i-1, egam, tm4);
	gr4->Draw("Lsame");
	gr4->SetLineStyle(4);
	gr4->SetLineWidth(2);
*/

	name = "T^{min}_{p'}";
	tl = new TLegend( 0.6, 0.6, 0.75, 0.8, name, "NDC");
	tl->SetTextFont( 132);
	tl->SetFillStyle(0);
	tl->SetBorderSize(0);
	tl->Draw();

	tl->AddEntry( gr, "20 MeV", "L");
	tl->AddEntry( gr2, "40 MeV", "L");
	tl->AddEntry( gr3, "60 MeV", "L");
//	tl->AddEntry( gr4, "200 MeV", "L");

//	name = Form( "Tmin_%d.pdf", (int) Tmin);
	name = "Tmin.eps";
	c1->Print( name);
}

//
// TwoBodyCMOut
//
// This function outputs either lab recoil theta or kinetic energy as a
// function of scattered CM theta for a fixed incident photon energy.
//
Double_t TwoBodyCMOut( Double_t *x, Double_t *par)
{

	TLorentzVector k, p, p1, q, pIn;
	TLorentzVector k_cm, p_cm, p1_cm, q_cm;
	TVector3 cmBoost, labBoost;
	
	UInt_t flag;
	Double_t ke, qth_cm;
	Double_t qm, qph_cm, mom_cm;
	Double_t qx_cm, qy_cm, qz_cm, qe_cm;
	Double_t pm, S;
	Double_t ang;

// Scattered particle angle in CM frame
	qth_cm = x[0];

// Incident photon energy
	ke = par[0];

// Flag determining output theta or KE
	flag = (int) par[1];

// Target mass
	pm = kMP_MEV;

// Set photon energy and momentum
// Beam direction is along z
	k.SetPxPyPzE( 0, 0, ke, ke);

// Set target to a proton at rest
	p.SetPxPyPzE( 0, 0, 0, pm);

// Total incoming 4-momentum
	pIn = k + p;

// The 3-vector boosts to and from the lab and CM frames
	labBoost = pIn.BoostVector();
	cmBoost = -pIn.BoostVector();

// Boosting the initial state particles' 4-momentum to the CM frame
	k_cm = k;
	k_cm.Boost( cmBoost);
	p_cm = p;
	p_cm.Boost( cmBoost);

// Set mass to:
	qm = kMPI0_MEV;		// neutral pion
//	qm = 0;					// photon

// Convert angle to radians
	qth_cm *= kD2R;

// Phi symmetry, so set phi to zero
	qph_cm = 0;

// Calculate CM energy
	S = 2*ke*pm + pm*pm;
	qe_cm = (S - pm*pm + qm*qm)/2/sqrt(S);

// Calculate CM momentum (it is the same for both the scattered particle and
// target recoil by definition!)
	mom_cm = momentum( qe_cm, qm);

// Calculate CM momentumm components
	qx_cm = mom_cm*sin( qth_cm)*cos(qph_cm);
	qy_cm = mom_cm*sin( qth_cm)*sin(qph_cm);
	qz_cm = mom_cm*cos( qth_cm);

// Set CM 4-momentum
	q_cm.SetPxPyPzE( qx_cm, qy_cm, qz_cm, qe_cm);

// Calculate the lab parameters by boosting the CM 4-momentum to the lab
// frame
	q = q_cm;
	q.Boost( labBoost);

// Calculate recoil proton 4-momentum using 4-mom conservation
	p1 = k + p - q;

	if ( flag[0] == 0) return( p1.Theta()/kD2R);
	else if ( flag[0] == 1) return( p1.E()-p1.M());
}

//
// TwoBodyLabOut
//
// This function outputs either lab scattered theta or kinetic energy as a
// function of recoil lab theta for a fixed incident photon energy.
//
Double_t TwoBodyLabOut( Double_t *x, Double_t *par)
{
	UInt_t flag;
	Double_t pth, ke;
	Double_t pm, pph, pmom;
	Double_t px, py, pz, pe;
	Double_t qm;
	TLorentzVector k, p, p1, q, pIn;
	
// Recoil particle angle in lab frame
	pth = x[0];

// Incident photon energy
	ke = par[0];

// Flag determining output theta or KE
	flag = UInt_t( par[1]);

// Target mass
	pm = kMP_MEV;

// Set mass to:
//	qm = kMPI0_MEV;		// neutral pion
	qm = 0;					// photon

// Convert angle to radians
	pth *= kD2R;

// Phi symmetry, so set phi to zero
	pph = 0;

// Set photon energy and momentum
// Beam direction is along z
	k.SetPxPyPzE( 0, 0, ke, ke);

// Set target to a proton at rest
	p.SetPxPyPzE( 0, 0, 0, pm);

// Calculate recoil momentum using kinematics function
	pmom = pp( k.E(), p.M(), pth, qm);
// Calculate energy
	pe = energy( pmom, pm);

// Calculate momentum components
	px = pmom*sin( pth)*cos( pph);
	py = pmom*sin( pth)*sin( pph);
	pz = pmom*cos( pth);

// Set 4-momentum
	p1.SetPxPyPzE( px, py, pz, pe);

// Calculate recoil 4-momentum using 4-mom conservation
	q = k + p - p1;

	if ( flag == 0) return( q.Theta()/kD2R);
	else if ( flag == 1) return( q.E()-q.M());
	else if ( flag == 2) return( p1.E()-p1.M());
}

/* 
 * qp
 *
 * Simple photoproduction from an at-rest target.
 *
 * Momentum of produced particle as a function of incident photon energy,
 * target mass, scattered theta, and scattered particle mass.
 *
 * Note that the target particle must also exist in the final state, i.e. this
 * routine does not work for charged production.
 *
 */
Double_t qp( Double_t ke, Double_t pm, Double_t qth, Double_t qm)
{
	Double_t qmom;
	Double_t W, S;
	Double_t A, B, C, a, b, c;

	W = ke + pm;
	S = 2*ke*pm + pm*pm;

	A = S - pm*pm + qm*qm;
	B = 2*ke*cos( qth);
	C = 2*W;

	a = C*C - B*B;
	b = -2*A*B;
	c = Sqr( C*qm) - A*A;

	qmom = (-b + sqrt( b*b - 4*a*c))/2/a;

	if ( qmom != qmom) return( -1);
	else return( qmom);
}

/* 
 * pp
 *
 * Simple photoproduction from an at-rest target.
 *
 * Momentum of target recoil as a function of incident photon energy, target
 * mass, target recoil theta, and scattered particle mass.
 *
 * Note that the target particle must also exist in the final state, i.e. this
 * routine does not work for charged production.
 *
 */
Double_t pp( Double_t ke, Double_t pm, Double_t pth, Double_t qm)
{
	Double_t pmom;
	Double_t W, S;
	Double_t A, B, C, a, b, c;

	W = ke + pm;
	S = 2*ke*pm + pm*pm;

	A = S + pm*pm - qm*qm;
	B = 2*ke*cos( pth);
	C = 2*W;

	a = C*C - B*B;
	b = -2*A*B;
	c = Sqr( C*pm) - A*A;

	pmom = (-b + sqrt( b*b - 4*a*c))/2/a;

	if ( pmom != pmom) return( -1);
	else return( pmom);
}

Double_t energy( Double_t mom, Double_t m)
{
	return( sqrt(mom*mom + m*m));
}

Double_t momentum( Double_t en, Double_t m)
{
	if ( en >= m) return( sqrt( en*en - m*m));
	else return( -1);
}

Double_t Sqr( Double_t x)
{
	return( x*x);
}

void Wfunc()
{
	UInt_t i;
	Double_t pm, S, W;
	TString name;

// TAPS 2001
//	UInt_t n = 5;
//	Double_t ke[] = { 148.5, 154.2, 159.5, 161.0, 165.6 };

// CB-TAPS 2008
//	UInt_t n = 9;
//	Double_t ke[] = { 149.0, 153.8, 155.0, 159.8, 161.0, 165.8, 170.6, 180.2, 279.4 };

//	UInt_t n = 6;
//	Double_t ke[] = { 150, 155, 160, 170, 180, 280 };

//	UInt_t n = 1;
//	Double_t ke[] = { 320};

//	UInt_t n = 26;
//	Double_t ke[] = { 147.1, 149.5, 151.9, 154.3, 156.7, 159.1, 161.5, 163.9,
//	166.3, 168.7, 171.1, 173.5, 175.9, 178.3, 180.7, 183.1, 185.5, 187.9, 190.3,
//	192.8, 195.2, 197.6, 200.0, 202.4, 204.8, 207.2 };

//	UInt_t n = 2;
//	Double_t ke[] = { 145, 210};

	pm = kMN_MEV;

	Double_t ke;

//	Double_t Wold = 145;
	Double_t Wold = 200;
	for ( i =  0; i < 81; i++) {
//	for ( i =  0; i < 28; i++) {

		ke = 200 + 10*i;
//		ke = 145 + 2*i;

//		S = 2*ke[i]*pm + pm*pm;
		S = 2*ke*pm + pm*pm;
		W = sqrt( S);
		dW = Wold - W;
//		name = Form( "ke = %6.1f  W = %6.1f\n", ke[i], W);
//		name = Form( "%6.1f  %6.1f\n", ke[i], W);
		name = Form( "%6.1f  %6.1f  %6.1f\n", ke, W, dW);
		cout << name;
		Wold = W;
	}
}

Double_t q_pi( Double_t ke)
{
	Double_t S, W, mp, mn, mpi, q, q0;

	mp = kMP_MEV;
	mn = kMN_MEV;
	mpi = kMPI_MEV;

	S = 2*ke*mp + mp*mp;
	W = sqrt( S);
	q0 = (S - mn*mn + mpi*mpi)/2/sqrt(S);

	q = momentum( q0, mpi);

	q /= kMPI_MEV;

	return( q);
}

Double_t ImEop( Double_t *x, Double_t *par)
{
	Double_t ke, beta;
	Double_t Eop_npi, a_ex;
	Double_t ImE;

	ke = x[0];
	beta = par[0];

	if ( q_pi( ke) <= 0) ImE = 0;
	else ImE = q_pi( ke)*beta;

	return( ImE);
}

void PlotImEop()
{
	TString name;

	c1 = new TCanvas( "c1", "ImE0+", 0, 0, 500, 400);

	f1 = new TF1( "f1", ImEop, 140, 200, 1);
	f1->SetParameter( 0, 3.38);
	name = "Im E_{0+}^{#pi^{0}p}";
	f1->SetTitle( name);
	f1->GetXaxis()->SetTitle( "E_{#gamma} (MeV)");
	f1->GetXaxis()->SetTitleSize( 0.045);
	f1->Draw();

	f2 = new TF1( "f2", ImEop, 140, 200, 1);
	f2->SetParameter( 0, 2.78);
	f2->SetLineStyle( 2);
	f2->Draw( "same");

	name = "";
	tl = new TLegend( 0.2, 0.6, 0.4, 0.75, name, "NDC");
	tl->SetTextFont( 132);
	tl->SetFillStyle( 0);
	tl->SetBorderSize( 0);

	tl->AddEntry( f1, "Unitarity", "L");
	tl->AddEntry( f2, "ChPT", "L");
	tl->Draw();

	cout << f1->Eval( 190.3) << endl;
}

void Aron( Double_t eg=148)
{
	Double_t cmth, th, ke;
	TString name;

	f1 = new TF1( "LabTheta", TwoBodyCMOut, 0, 180, 2);
	f1->SetParameters( eg, 0); // lab theta

	f2 = new TF1( "LabKE", TwoBodyCMOut, 0, 180, 2);
	f2->SetParameters( eg, 1); // lab KE

	cout << " CM Th   Lab Th   Lab KE" << endl;
	cout << " (deg)   (deg)    (MeV)" << endl;
	cout << "------------------------" << endl;
	for ( cmth = 0; cmth <= 180; cmth += 10) {

		th = f1->Eval( cmth);
		ke = f2->Eval( cmth);

		name = Form( "%3.0f      %4.1f      %4.1f\n", cmth, th, ke);
		cout << name;

	}
}
