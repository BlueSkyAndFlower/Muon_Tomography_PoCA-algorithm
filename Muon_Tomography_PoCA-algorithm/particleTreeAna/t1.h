//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Sep 30 17:05:44 2024 by ROOT version 6.24/06
// from TTree t1/a simple Tree with simple variables
// found on file: musrSim_0_try.root
//////////////////////////////////////////////////////////

#ifndef t1_h
#define t1_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class t1 {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Double_t        timeToNextEvent;
   Double_t        muTargetMomX;
   Double_t        muTargetMomY;
   Double_t        muTargetMomZ;
   Int_t           mup_n;
   Int_t           mup_TrackID[9];   //[mup_n]
   Double_t        mup_GenposX[9];   //[mup_n]
   Double_t        mup_GenposY[9];   //[mup_n]
   Double_t        mup_GenposZ[9];   //[mup_n]
   Int_t           det_n;
   Double_t        det_kine_mup[9];   //[det_n]
   Double_t        det_edep_mun[9];   //[det_n]
   Double_t        det_kine_mun[9];   //[det_n]
   Double_t        det_x_mup[9];   //[det_n]
   Double_t        det_y_mup[9];   //[det_n]
   Double_t        det_z_mup[9];   //[det_n]
   Double_t        det_x_mun[9];   //[det_n]
   Double_t        det_y_mun[9];   //[det_n]
   Double_t        det_z_mun[9];   //[det_n]
   Int_t           det_VrtxPrtParticleID[9];   //[det_n]
   Int_t           save_n;
   Int_t           save_detID[999];   //[save_n]
   Int_t           save_particleID[999];   //[save_n]
   Double_t        save_ke[999];   //[save_n]
   Double_t        save_time[999];   //[save_n]
   Double_t        save_x[999];   //[save_n]
   Double_t        save_y[999];   //[save_n]
   Double_t        save_z[999];   //[save_n]
   Double_t        save_px[999];   //[save_n]
   Double_t        save_py[999];   //[save_n]
   Double_t        save_pz[999];   //[save_n]
   Double_t        save_polx[999];   //[save_n]
   Double_t        save_poly[999];   //[save_n]
   Double_t        save_polz[999];   //[save_n]

   // List of branches
   TBranch        *b_timeToNextEvent;   //!
   TBranch        *b_muTargetMomX;   //!
   TBranch        *b_muTargetMomY;   //!
   TBranch        *b_muTargetMomZ;   //!
   TBranch        *b_mup_n;   //!
   TBranch        *b_mup_TrackID;   //!
   TBranch        *b_mup_GenposX;   //!
   TBranch        *b_mup_GenposY;   //!
   TBranch        *b_mup_GenposZ;   //!
   TBranch        *b_det_n;   //!
   TBranch        *b_det_kine_mup;   //!
   TBranch        *b_det_edep_mun;   //!
   TBranch        *b_det_kine_mun;   //!
   TBranch        *b_det_x_mup;   //!
   TBranch        *b_det_y_mup;   //!
   TBranch        *b_det_z_mup;   //!
   TBranch        *b_det_x_mun;   //!
   TBranch        *b_det_y_mun;   //!
   TBranch        *b_det_z_mun;   //!
   TBranch        *b_det_VrtxPrtParticleID;   //!
   TBranch        *b_save_n;   //!
   TBranch        *b_save_detID;   //!
   TBranch        *b_save_particleID;   //!
   TBranch        *b_save_ke;   //!
   TBranch        *b_save_time;   //!
   TBranch        *b_save_x;   //!
   TBranch        *b_save_y;   //!
   TBranch        *b_save_z;   //!
   TBranch        *b_save_px;   //!
   TBranch        *b_save_py;   //!
   TBranch        *b_save_pz;   //!
   TBranch        *b_save_polx;   //!
   TBranch        *b_save_poly;   //!
   TBranch        *b_save_polz;   //!

   t1(TTree *tree=0);
   virtual ~t1();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef t1_cxx
t1::t1(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("musrSim_0_try.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("musrSim_0_try.root");
      }
      f->GetObject("t1",tree);

   }
   Init(tree);
}

t1::~t1()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t t1::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t t1::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void t1::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("timeToNextEvent", &timeToNextEvent, &b_timeToNextEvent);
   fChain->SetBranchAddress("muTargetMomX", &muTargetMomX, &b_muTargetMomX);
   fChain->SetBranchAddress("muTargetMomY", &muTargetMomY, &b_muTargetMomY);
   fChain->SetBranchAddress("muTargetMomZ", &muTargetMomZ, &b_muTargetMomZ);
   fChain->SetBranchAddress("mup_n", &mup_n, &b_mup_n);
   fChain->SetBranchAddress("mup_TrackID", &mup_TrackID, &b_mup_TrackID);
   fChain->SetBranchAddress("mup_GenposX", &mup_GenposX, &b_mup_GenposX);
   fChain->SetBranchAddress("mup_GenposY", &mup_GenposY, &b_mup_GenposY);
   fChain->SetBranchAddress("mup_GenposZ", &mup_GenposZ, &b_mup_GenposZ);
   fChain->SetBranchAddress("det_n", &det_n, &b_det_n);
   fChain->SetBranchAddress("det_kine_mup", &det_kine_mup, &b_det_kine_mup);
   fChain->SetBranchAddress("det_edep_mun", &det_edep_mun, &b_det_edep_mun);
   fChain->SetBranchAddress("det_kine_mun", &det_kine_mun, &b_det_kine_mun);
   fChain->SetBranchAddress("det_x_mup", &det_x_mup, &b_det_x_mup);
   fChain->SetBranchAddress("det_y_mup", &det_y_mup, &b_det_y_mup);
   fChain->SetBranchAddress("det_z_mup", &det_z_mup, &b_det_z_mup);
   fChain->SetBranchAddress("det_x_mun", &det_x_mun, &b_det_x_mun);
   fChain->SetBranchAddress("det_y_mun", &det_y_mun, &b_det_y_mun);
   fChain->SetBranchAddress("det_z_mun", &det_z_mun, &b_det_z_mun);
   fChain->SetBranchAddress("det_VrtxPrtParticleID", &det_VrtxPrtParticleID, &b_det_VrtxPrtParticleID);
   fChain->SetBranchAddress("save_n", &save_n, &b_save_n);
   fChain->SetBranchAddress("save_detID", save_detID, &b_save_detID);
   fChain->SetBranchAddress("save_particleID", save_particleID, &b_save_particleID);
   fChain->SetBranchAddress("save_ke", save_ke, &b_save_ke);
   fChain->SetBranchAddress("save_time", save_time, &b_save_time);
   fChain->SetBranchAddress("save_x", save_x, &b_save_x);
   fChain->SetBranchAddress("save_y", save_y, &b_save_y);
   fChain->SetBranchAddress("save_z", save_z, &b_save_z);
   fChain->SetBranchAddress("save_px", save_px, &b_save_px);
   fChain->SetBranchAddress("save_py", save_py, &b_save_py);
   fChain->SetBranchAddress("save_pz", save_pz, &b_save_pz);
   fChain->SetBranchAddress("save_polx", save_polx, &b_save_polx);
   fChain->SetBranchAddress("save_poly", save_poly, &b_save_poly);
   fChain->SetBranchAddress("save_polz", save_polz, &b_save_polz);
   Notify();
}

Bool_t t1::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void t1::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t t1::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef t1_cxx
