#ifndef MYANA_h
#define MYANA_h

#include "t1.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include <string>
#include <stdio.h>

class MyAna : public t1 {
	public:
		MyAna(TTree *tree=0):t1(tree){};
		~MyAna() {};
		virtual void Loop(std::string filename);
		void initialize(std::string filename);
		void execute();
		void finalize();
		void clear();

	private:
		TFile *m_file;
		Int_t total_event;
		Int_t eventID;
		Int_t saveID;
		Int_t detID;
		Int_t partID;
		Double_t x;
		Double_t y;
		Double_t z;
		Double_t px;
		Double_t py;
		Double_t pz;
		Double_t ke;
		Double_t t;

		TTree *particle;
};
#endif
