//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu May  6 12:22:59 2021 by ROOT version 6.10/05
// from TTree pion_variables_v1/variables for pion analysis v1
// found on file: skimmed_ntuple_data_config22_pion20GeV_HGCv16_AHCv8.root
//////////////////////////////////////////////////////////

#ifndef myclass_h
#define myclass_h

#include <TChain.h>
#include <TFile.h>
#include <TROOT.h>

// Header file for the classes stored in the TTree if any.
#include "vector"

class myclass {
 public:
  TTree *fChain;   //! pointer to the analyzed TTree or TChain
  Int_t fCurrent;  //! current Tree number in a TChain

  // Fixed size dimensions of array or collections stored in the TTree if any.

  // Declaration of leaf types
  UInt_t event;
  UInt_t run;
  Int_t pdgID;
  Float_t beamEnergy;
  Float_t trueBeamEnergy;
  Int_t NRechits;
  vector<float> *rechit_energy;
  vector<float> *rechit_x;
  vector<float> *rechit_y;
  vector<float> *rechit_z;
  vector<float> *rechit_cogX;
  vector<float> *rechit_cogY;
  vector<short> *rechit_iu;
  vector<short> *rechit_iv;
  vector<short> *rechit_iU;
  vector<short> *rechit_iV;
  vector<float> *rechit_amplitudeHigh;
  vector<float> *rechit_amplitudeLow;
  vector<bool> *rechit_noise_flag;
  vector<unsigned int> *rechit_module;
  vector<unsigned int> *rechit_layer;
  vector<unsigned int> *rechit_chip;
  vector<unsigned int> *rechit_channel;
  vector<unsigned int> *rechit_type;
  Int_t rechit_shower_start_layer;
  vector<float> *rechit_energyPerLayer;
  vector<float> *rechit_nHitsPerLayer;
  Int_t ntracks;
  Float_t trackChi2_X;
  Float_t trackChi2_Y;
  Int_t dwcReferenceType;
  Double_t m_x;
  Double_t m_y;
  Double_t b_x;
  Double_t b_y;
  vector<float> *TrackImpactX_layer;
  vector<float> *TrackImpactY_layer;
  Int_t ahc_nHits;
  vector<float> *ahc_energyPerLayer;
  vector<int> *ahc_nHitsPerLayer;
  vector<int> *ahc_hitI;
  vector<int> *ahc_hitJ;
  vector<int> *ahc_hitK;
  vector<float> *ahc_hitEnergy;
  vector<float> *ahc_hitX;
  vector<float> *ahc_hitY;
  vector<float> *ahc_hitZ;
  Float_t energyLostEE;
  Float_t energyLostFH;
  Float_t energyLostBH;
  Float_t energyLostBeam;

  // List of branches
  TBranch *b_event;                      //!
  TBranch *b_run;                        //!
  TBranch *b_pdgID;                      //!
  TBranch *b_beamEnergy;                 //!
  TBranch *b_trueBeamEnergy;             //!
  TBranch *b_NRechits;                   //!
  TBranch *b_rechit_energy;              //!
  TBranch *b_rechit_x;                   //!
  TBranch *b_rechit_y;                   //!
  TBranch *b_rechit_z;                   //!
  TBranch *b_rechit_cogX;                //!
  TBranch *b_rechit_cogY;                //!
  TBranch *b_rechit_iu;                  //!
  TBranch *b_rechit_iv;                  //!
  TBranch *b_rechit_iU;                  //!
  TBranch *b_rechit_iV;                  //!
  TBranch *b_rechit_amplitudeHigh;       //!
  TBranch *b_rechit_amplitudeLow;        //!
  TBranch *b_rechit_noise_flag;          //!
  TBranch *b_rechit_module;              //!
  TBranch *b_rechit_layer;               //!
  TBranch *b_rechit_chip;                //!
  TBranch *b_rechit_channel;             //!
  TBranch *b_rechit_type;                //!
  TBranch *b_rechit_shower_start_layer;  //!
  TBranch *b_rechit_energyPerLayer;      //!
  TBranch *b_rechit_nHitsPerLayer;       //!
  TBranch *b_ntracks;                    //!
  TBranch *b_trackChi2_X;                //!
  TBranch *b_trackChi2_Y;                //!
  TBranch *b_dwcReferenceType;           //!
  TBranch *b_m_x;                        //!
  TBranch *b_m_y;                        //!
  TBranch *b_b_x;                        //!
  TBranch *b_b_y;                        //!
  TBranch *b_TrackImpactX_layer;         //!
  TBranch *b_TrackImpactY_layer;         //!
  TBranch *b_ahc_nHits;                  //!
  TBranch *b_ahc_energyPerLayer;         //!
  TBranch *b_ahc_nHitsPerLayer;          //!
  TBranch *b_ahc_hitI;                   //!
  TBranch *b_ahc_hitJ;                   //!
  TBranch *b_ahc_hitK;                   //!
  TBranch *b_ahc_hitEnergy;              //!
  TBranch *b_ahc_hitX;                   //!
  TBranch *b_ahc_hitY;                   //!
  TBranch *b_ahc_hitZ;                   //!
  TBranch *b_energyLostEE;               //!
  TBranch *b_energyLostFH;               //!
  TBranch *b_energyLostBH;               //!
  TBranch *b_energyLostBeam;             //!

  myclass(TTree *tree = 0);
  virtual ~myclass();
  virtual Int_t Cut(Long64_t entry);
  virtual Int_t GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void Init(TTree *tree);
  virtual void Loop();
  virtual Bool_t Notify();
  virtual void Show(Long64_t entry = -1);
};

#endif

#ifdef myclass_cxx
myclass::myclass(TTree *tree) : fChain(0) {
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  if (tree == 0) {
    TFile *f = (TFile *)gROOT->GetListOfFiles()->FindObject(
        "skimmed_ntuple_data_config22_pion20GeV_HGCv16_AHCv8.root");
    if (!f || !f->IsOpen()) {
      f = new TFile("skimmed_ntuple_data_config22_pion20GeV_HGCv16_AHCv8.root");
    }
    f->GetObject("pion_variables_v1", tree);
  }
  Init(tree);
}

myclass::~myclass() {
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t myclass::GetEntry(Long64_t entry) {
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t myclass::LoadTree(Long64_t entry) {
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

void myclass::Init(TTree *tree) {
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set object pointer
  rechit_energy = 0;
  rechit_x = 0;
  rechit_y = 0;
  rechit_z = 0;
  rechit_cogX = 0;
  rechit_cogY = 0;
  rechit_iu = 0;
  rechit_iv = 0;
  rechit_iU = 0;
  rechit_iV = 0;
  rechit_amplitudeHigh = 0;
  rechit_amplitudeLow = 0;
  rechit_noise_flag = 0;
  rechit_module = 0;
  rechit_layer = 0;
  rechit_chip = 0;
  rechit_channel = 0;
  rechit_type = 0;
  rechit_energyPerLayer = 0;
  rechit_nHitsPerLayer = 0;
  TrackImpactX_layer = 0;
  TrackImpactY_layer = 0;
  ahc_energyPerLayer = 0;
  ahc_nHitsPerLayer = 0;
  ahc_hitI = 0;
  ahc_hitJ = 0;
  ahc_hitK = 0;
  ahc_hitEnergy = 0;
  ahc_hitX = 0;
  ahc_hitY = 0;
  ahc_hitZ = 0;
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("event", &event, &b_event);
  fChain->SetBranchAddress("run", &run, &b_run);
  fChain->SetBranchAddress("pdgID", &pdgID, &b_pdgID);
  fChain->SetBranchAddress("beamEnergy", &beamEnergy, &b_beamEnergy);
  fChain->SetBranchAddress("trueBeamEnergy", &trueBeamEnergy,
                           &b_trueBeamEnergy);
  fChain->SetBranchAddress("NRechits", &NRechits, &b_NRechits);
  fChain->SetBranchAddress("rechit_energy", &rechit_energy, &b_rechit_energy);
  fChain->SetBranchAddress("rechit_x", &rechit_x, &b_rechit_x);
  fChain->SetBranchAddress("rechit_y", &rechit_y, &b_rechit_y);
  fChain->SetBranchAddress("rechit_z", &rechit_z, &b_rechit_z);
  fChain->SetBranchAddress("rechit_cogX", &rechit_cogX, &b_rechit_cogX);
  fChain->SetBranchAddress("rechit_cogY", &rechit_cogY, &b_rechit_cogY);
  fChain->SetBranchAddress("rechit_iu", &rechit_iu, &b_rechit_iu);
  fChain->SetBranchAddress("rechit_iv", &rechit_iv, &b_rechit_iv);
  fChain->SetBranchAddress("rechit_iU", &rechit_iU, &b_rechit_iU);
  fChain->SetBranchAddress("rechit_iV", &rechit_iV, &b_rechit_iV);
  fChain->SetBranchAddress("rechit_amplitudeHigh", &rechit_amplitudeHigh,
                           &b_rechit_amplitudeHigh);
  fChain->SetBranchAddress("rechit_amplitudeLow", &rechit_amplitudeLow,
                           &b_rechit_amplitudeLow);
  fChain->SetBranchAddress("rechit_noise_flag", &rechit_noise_flag,
                           &b_rechit_noise_flag);
  fChain->SetBranchAddress("rechit_module", &rechit_module, &b_rechit_module);
  fChain->SetBranchAddress("rechit_layer", &rechit_layer, &b_rechit_layer);
  fChain->SetBranchAddress("rechit_chip", &rechit_chip, &b_rechit_chip);
  fChain->SetBranchAddress("rechit_channel", &rechit_channel,
                           &b_rechit_channel);
  fChain->SetBranchAddress("rechit_type", &rechit_type, &b_rechit_type);
  fChain->SetBranchAddress("rechit_shower_start_layer",
                           &rechit_shower_start_layer,
                           &b_rechit_shower_start_layer);
  fChain->SetBranchAddress("rechit_energyPerLayer", &rechit_energyPerLayer,
                           &b_rechit_energyPerLayer);
  fChain->SetBranchAddress("rechit_nHitsPerLayer", &rechit_nHitsPerLayer,
                           &b_rechit_nHitsPerLayer);
  fChain->SetBranchAddress("ntracks", &ntracks, &b_ntracks);
  fChain->SetBranchAddress("trackChi2_X", &trackChi2_X, &b_trackChi2_X);
  fChain->SetBranchAddress("trackChi2_Y", &trackChi2_Y, &b_trackChi2_Y);
  fChain->SetBranchAddress("dwcReferenceType", &dwcReferenceType,
                           &b_dwcReferenceType);
  fChain->SetBranchAddress("m_x", &m_x, &b_m_x);
  fChain->SetBranchAddress("m_y", &m_y, &b_m_y);
  fChain->SetBranchAddress("b_x", &b_x, &b_b_x);
  fChain->SetBranchAddress("b_y", &b_y, &b_b_y);
  fChain->SetBranchAddress("TrackImpactX_layer", &TrackImpactX_layer,
                           &b_TrackImpactX_layer);
  fChain->SetBranchAddress("TrackImpactY_layer", &TrackImpactY_layer,
                           &b_TrackImpactY_layer);
  fChain->SetBranchAddress("ahc_nHits", &ahc_nHits, &b_ahc_nHits);
  fChain->SetBranchAddress("ahc_energyPerLayer", &ahc_energyPerLayer,
                           &b_ahc_energyPerLayer);
  fChain->SetBranchAddress("ahc_nHitsPerLayer", &ahc_nHitsPerLayer,
                           &b_ahc_nHitsPerLayer);
  fChain->SetBranchAddress("ahc_hitI", &ahc_hitI, &b_ahc_hitI);
  fChain->SetBranchAddress("ahc_hitJ", &ahc_hitJ, &b_ahc_hitJ);
  fChain->SetBranchAddress("ahc_hitK", &ahc_hitK, &b_ahc_hitK);
  fChain->SetBranchAddress("ahc_hitEnergy", &ahc_hitEnergy, &b_ahc_hitEnergy);
  fChain->SetBranchAddress("ahc_hitX", &ahc_hitX, &b_ahc_hitX);
  fChain->SetBranchAddress("ahc_hitY", &ahc_hitY, &b_ahc_hitY);
  fChain->SetBranchAddress("ahc_hitZ", &ahc_hitZ, &b_ahc_hitZ);
  fChain->SetBranchAddress("energyLostEE", &energyLostEE, &b_energyLostEE);
  fChain->SetBranchAddress("energyLostFH", &energyLostFH, &b_energyLostFH);
  fChain->SetBranchAddress("energyLostBH", &energyLostBH, &b_energyLostBH);
  fChain->SetBranchAddress("energyLostBeam", &energyLostBeam,
                           &b_energyLostBeam);
  Notify();
}

Bool_t myclass::Notify() {
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

void myclass::Show(Long64_t entry) {
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}
Int_t myclass::Cut(Long64_t entry) {
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}
#endif  // #ifdef myclass_cxx
