#include "MyAna.h"
#include <iostream>
#include <cmath>
#include <TROOT.h>
#include <TRandom.h>
#include <TCanvas.h>
#include <string.h>
#include <cstring>
#include <stdio.h>
#include "TSystem.h"

void MyAna::Loop (std::string filename)
{
	//  cout << "Loop()" << endl;

	initialize (filename);

	if (fChain == 0)
		return;

	Long64_t nentries = fChain->GetEntriesFast ();
	Int_t nbytes = 0, nb = 0;

	for (Long64_t jentry = 0; jentry < nentries; jentry++)
	{
		Long64_t ientry = LoadTree (jentry);
		if (ientry < 0)
			break;
		nb = fChain->GetEntry (jentry);
		nbytes += nb;

		clear ();
		execute ();

	}

	finalize ();

}

void MyAna::initialize (std::string filename)
{

	std::cout << filename << std::endl;
	std::cout << "initialize()" << std::endl;
	filename.append ("_hist.root");
	char *out = (char *) filename.c_str ();
	m_file = new TFile (out, "recreate");

	total_event = 0; // count total number of muon events

	// Define particle tree

	particle = new TTree("particle","All Particle");
	particle->Branch("eventID",&eventID,"eventID/I");
	particle->Branch("saveID",&saveID,"saveID/I");
	particle->Branch("detID",&detID,"detID/I");
	particle->Branch("partID",&partID,"partID/I");
	particle->Branch("x",&x,"x/D");
	particle->Branch("y",&y,"y/D");
	particle->Branch("z",&z,"z/D");
	particle->Branch("px",&px,"px/D");
	particle->Branch("py",&py,"py/D");
	particle->Branch("pz",&pz,"pz/D");
	particle->Branch("ke",&ke,"ke/D");
	particle->Branch("t",&t,"t/D");


	std::cout << "### x1  " << "y1  " << "px1  " << "py1  " << "pz1  "  << "x2  " << "y2  " << "px2  " << "py2  " << "pz2  " << "x3  " << "y3  " << "px3  " << "py3  " << "pz3  " << "x4 " << "y4 " << "px4  " << "py4  " << "pz4  " << std::endl; 
}

void MyAna::execute ()
{
	 /*
	if(total_event%10000 == 0){
		std::cout << "Event ID: " << eventID << std::endl;
	}  // */
	total_event++; 


	for(int i=0;i<save_n;i++){
		if(save_particleID[i] !=13 && save_particleID[i] !=-13){
			continue;
		}
		eventID = total_event;
		saveID  = i;
		detID = save_detID[i];
		partID = save_particleID[i];
		x  = save_x[i];
		y  = save_y[i];
		z  = save_z[i];
		px = save_px[i];
		py = save_py[i];
		pz = save_pz[i];
		ke = save_ke[i];
		t  = save_time[i];
		particle->Fill();
		std::cout << x << "  " << y << "  " << px  << "  " << py << "  " << pz << "  ";
	}
	std::cout << "  " << std::endl;
}

void MyAna::finalize ()
{
	std::cout << "Finalizing......" << std::endl;
	std::cout << "Total Event: " << total_event << std::endl;
	std::cout << std::endl;

	std::cout << "March comes like a lion!" << std::endl;
	particle->Write();

	m_file->Write ();
	m_file->Close ();
}

void MyAna::clear (){}
