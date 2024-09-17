//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Aug 16 18:22:34 2018 by ROOT version 6.06/01
// from TTree hits/HGC rechits
// found on file: muon_v10.root
//////////////////////////////////////////////////////////

#ifndef HGCNtupleVariables_h
#define HGCNtupleVariables_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TProfile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"

using namespace std;

class HGCNtupleVariables {
public :

   HGCNtupleVariables(TTree * /*tree*/ =0) : fChain(0) { }
   ~HGCNtupleVariables() { }
   void    Init(TTree *tree); 
  //   void    Init(TTree *tree, TTree *tree2, TTree *tree3);
   Bool_t  Notify();
   Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
  std::vector<int> getModuleLocation(int moduleID);
  int getBIN(unsigned int skiroc,unsigned int channel);
  float deltaR(float x1, float y1, float x2, float y2);
  //double shower_comparisons(TProfile* shower, TH1F* hist);
  //double shower_comparisons(TProfile* shower, TH1F* ref_h);
  // TH1F* shower_comparisons(TProfile* shower, TH1F* hist);
  // float find_my_calib(int layer, int en_chan);
  // float find_official_calib(int layer, int en_chan);
  std::vector<float> getLayerPosition(int layer_);
  std::map<int, std::vector<float>> layer_positions;

  std::map<int, std::vector<int>> module_map;
  std::map<int, std::pair<float,float> > align_map;
  std::pair<float,float> dxy_alignment(int layer);
  std::map<std::pair<int,int>, float > noise_map;
  float getNoise(std::pair<int,int> mod_chip);
   double getLeadingKE(vector<double> list);
  // std::map<std::pair<int, int>, float> offical_calib_map;
  // std::map<std::pair<int, int>, float> my_calib_map;
  
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   // TTree          *fChain2;   //!pointer to the analyzed TTree or TChain
   // TTree          *fChain3;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
   // Int_t           fCurrent2; //!current Tree number in a TChain
   // Int_t           fCurrent3; //!current Tree number in a TChain

 //for tree
  TTree* pion_tree;
  UInt_t          pi_event;
  UInt_t          pi_event_orig;
  UInt_t          pi_run;
  Int_t           pi_pdgID;
  Float_t         pi_beamEnergy;
  Float_t         pi_trueBeamEnergy;
  Int_t           pi_NRechits;
  Int_t           pi_NRechits_orig;
  vector<float>   pi_rechit_energy;
  vector<unsigned int> pi_rechit_module;
  vector<unsigned int> pi_rechit_layer;
  vector<unsigned int> pi_rechit_chip;
  vector<unsigned int> pi_rechit_channel;
  vector<unsigned int> pi_rechit_type;
  vector<float>   pi_rechit_x;
  vector<float>   pi_rechit_y;
  vector<float>   *pi_rechit_cogX;
  vector<float>   *pi_rechit_cogY;

  vector<float>   pi_rechit_z;
  vector<short>     pi_rechit_iu;
  vector<short>     pi_rechit_iv;
  vector<short>     pi_rechit_iU;
  vector<short>     pi_rechit_iV;
  vector<float>   pi_rechit_amplitudeHigh;
  vector<float>   pi_rechit_amplitudeLow;
  vector<bool>    pi_rechit_noise_flag;
    Int_t             pi_rechit_shower_start_layer;
  vector<float>   *pi_rechit_energyPerLayer;
  vector<float>   *pi_rechit_nHitsPerLayer;
  
  vector<float> pi_rechitEn_trimAhcal;
  vector<float> pi_comb_rechit_x_trimAhcal;
  vector<float> pi_comb_rechit_y_trimAhcal;
  vector<float> pi_comb_rechit_z_trimAhcal;
  //int pi_comb_NRechits;
  int pi_Nrechit_trimAhcal;
  Int_t           pi_ntracks;
  Float_t         pi_trackChi2_X;
  Float_t         pi_trackChi2_Y;
  Int_t           pi_dwcReferenceType;
  Double_t        pi_m_x;
  Double_t        pi_m_y;
  Double_t        pi_b_x;
  Double_t        pi_b_y;
  vector<float>   *pi_impactX_layer;
  vector<float>   *pi_impactY_layer;


  Int_t           pi_ahc_nHits;
  Int_t           pi_ahc_nHits_orig;
  vector<float>   *pi_ahc_energyPerLayer;
  vector<int>     *pi_ahc_nHitsPerLayer;
  vector<int>     pi_ahc_hitI;
  vector<int>     pi_ahc_hitJ;
  vector<int>     pi_ahc_hitK;
  vector<float>   pi_ahc_hitEnergy;
  vector<float>   pi_ahc_hitX;
  vector<float>   pi_ahc_hitY;
  vector<float>   pi_ahc_hitZ;


  bool pi_isHGC_AHC_sync;
  bool pi_isGoodTrack;
  bool pi_isFHNoisy;
  bool pi_MuonVeto;
  bool pi_isInTrackWindow;
  vector<bool> *pi_hgc_channel_mask;
  vector<bool> *pi_ahc_channel_mask;
  vector<bool> *pi_pass_noise_thres;
  Float_t         pi_energyLostEE;
  Float_t         pi_energyLostFH;
  Float_t         pi_energyLostBH;
  Float_t         pi_energyLostBeam;
     UInt_t          pi_eventHadInt;
   Bool_t          pi_foundHadInt;
   Int_t           pi_process;
   Int_t           pi_nsec;
   vector<double>  *pi_sec_pdgID;
   vector<double>  *pi_sec_charge;
   vector<double>  *pi_sec_kin;
   vector<double>  *pi_sec_x;
   vector<double>  *pi_sec_y;
   vector<double>  *pi_sec_z;
   vector<double>  *pi_Allsec_pdgID;
   vector<double>  *pi_Allsec_charge;
   vector<double>  *pi_Allsec_kin;
   vector<double>  *pi_Allsec_x;
   vector<double>  *pi_Allsec_y;
   vector<double>  *pi_Allsec_z;
  Double_t pi_leadingHadKE;
  Double_t pi_E_genKin;
  Double_t pi_nsc_total_KE;
  Double_t pi_Allsec_pions;
  Double_t pi_Allsec_Kaons;
  Double_t pi_Allseckin;
  int Nrechit_trimAhcal;
  vector<double>  *pi_sec_parent_id;
   vector<double>  *pi_sec_track_id;
   vector<double>  *pi_sec_process_id;
   vector<double>  *pi_Allsec_parent_id;
   vector<double>  *pi_Allsec_track_id;
   vector<double>  *pi_Allsec_process_id;
  

  void init_piTree();
   // Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          event;
   UInt_t          run;
   Int_t           pdgID;
   Float_t         beamEnergy;
   Float_t         trueBeamEnergy;
   Bool_t          isHGC_AHC_sync;
   Bool_t          isGoodTrack;
   Bool_t          isFHNoisy;
   Bool_t          MuonVeto;
   Bool_t          isInTrackWindow;
   vector<bool>    *hgc_channel_mask;
   vector<bool>    *ahc_channel_mask;
   vector<bool>    *pass_noise_thres;
  // UInt_t          event;
   Int_t           NRechits;
   vector<float>   *rechit_energy;
   vector<float>   *rechit_x;
   vector<float>   *rechit_y;
   vector<float>   *rechit_z;
   vector<float>   *rechit_cogX;
   vector<float>   *rechit_cogY;
   vector<short>   *rechit_iu;
   vector<short>   *rechit_iv;
   vector<short>   *rechit_iU;
   vector<short>   *rechit_iV;
   vector<float>   *rechit_amplitudeHigh;
   vector<float>   *rechit_amplitudeLow;
   vector<bool>    *rechit_noise_flag;
   vector<unsigned int> *rechit_module;
   vector<unsigned int> *rechit_layer;
   vector<unsigned int> *rechit_chip;
   vector<unsigned int> *rechit_channel;
   vector<unsigned int> *rechit_type;
   Int_t           rechit_shower_start_layer;
   vector<float>   *rechit_energyPerLayer;
   vector<float>   *rechit_nHitsPerLayer;
   Int_t           ntracks;
   Float_t         trackChi2_X;
   Float_t         trackChi2_Y;
   Int_t           dwcReferenceType;
   Double_t        m_x;
   Double_t        m_y;
   Double_t        b_x;
   Double_t        b_y;
   vector<float>   *TrackImpactX_layer;
   vector<float>   *TrackImpactY_layer;
   Int_t           ahc_nHits;
   vector<float>   *ahc_energyPerLayer;
   vector<int>     *ahc_nHitsPerLayer;
   vector<int>     *ahc_hitI;
   vector<int>     *ahc_hitJ;
   vector<int>     *ahc_hitK;
   vector<float>   *ahc_hitEnergy;
   vector<float>   *ahc_hitX;
   vector<float>   *ahc_hitY;
   vector<float>   *ahc_hitZ;
  //Int_t           ahc_nHits;
   Float_t         energyLostEE;
   Float_t         energyLostFH;
   Float_t         energyLostBH;
   Float_t         energyLostBeam;

  UInt_t          eventHadInt;
   Bool_t          foundHadInt;
   Int_t           process;

Int_t           nsec;

   vector<double>  *sec_pdgID;
   vector<double>  *sec_charge;
   vector<double>  *sec_kin;
   vector<double>  *sec_x;
   vector<double>  *sec_y;
   vector<double>  *sec_z;
   vector<double>  *Allsec_pdgID;
   vector<double>  *Allsec_charge;
   vector<double>  *Allsec_kin;
   vector<double>  *Allsec_x;
   vector<double>  *Allsec_y;
   vector<double>  *Allsec_z;
  vector<double>  *sec_parent_id;
   vector<double>  *sec_track_id;
   vector<double>  *sec_process_id;
   vector<double>  *Allsec_parent_id;
   vector<double>  *Allsec_track_id;
   vector<double>  *Allsec_process_id;

  // List of branches
  TBranch        *b_event;   //!                                                                                                                                                      
  TBranch        *b_run;   //!                                                                                                                                                      
   TBranch        *b_pdgID;   //!                                                                                                                                                     
   TBranch        *b_beamEnergy;   //!                                                                                                                                                
   TBranch        *b_trueBeamEnergy;   //!                                                                                                                                            
   TBranch        *b_isHGC_AHC_sync;   //!                                                                                                                                            
   TBranch        *b_isGoodTrack;   //!                                                                                                                                               
   TBranch        *b_isFHNoisy;   //!                                                                                                                                                 
   TBranch        *b_MuonVeto;   //!                                                                                                                                                  
   TBranch        *b_isInTrackWindow;   //!                                                                                                                                           
   TBranch        *b_hgc_channel_mask;   //!                                                                                                                                          
   TBranch        *b_ahc_channel_mask;   //!                                                                                                                                          
   TBranch        *b_pass_noise_thres;   //!                                                                                                                                          
  // TBranch        *b_event;   //!                                                                                                                                                     
   TBranch        *b_NRechits;   //!                                                                                                                                                  
   TBranch        *b_rechit_energy;   //!                                                                                                                                             
   TBranch        *b_rechit_x;   //!                                                                                                                                                  
   TBranch        *b_rechit_y;   //!                                                                                                                                                  
   TBranch        *b_rechit_z;   //!                                                                                                                                                  
   TBranch        *b_rechit_cogX;   //!                                                                                                                                               
   TBranch        *b_rechit_cogY;   //!                                                                                                                                               
   TBranch        *b_rechit_iu;   //!                                                                                                                                                 
   TBranch        *b_rechit_iv;   //!                                                                                                                                                 
   TBranch        *b_rechit_iU;   //!       
   TBranch        *b_rechit_iV;   //!                                                                                                                                                 
   TBranch        *b_rechit_amplitudeHigh;   //!                                                                                                                                      
   TBranch        *b_rechit_amplitudeLow;   //!                                                                                                                                       
   TBranch        *b_rechit_noise_flag;   //!                                                                                                                                         
   TBranch        *b_rechit_module;   //!                                                                                                                                             
   TBranch        *b_rechit_layer;   //!                                                                                                                                              
   TBranch        *b_rechit_chip;   //!                                                                                                                                               
   TBranch        *b_rechit_channel;   //!                                                                                                                                            
   TBranch        *b_rechit_type;   //!                                                                                                                                               
   TBranch        *b_rechit_shower_start_layer;   //!                                                                                                                                 
   TBranch        *b_rechit_energyPerLayer;   //!                                                                                                                                     
   TBranch        *b_rechit_nHitsPerLayer;   //!                                                                                                                                      
   TBranch        *b_ntracks;   //!                                                                                                                                                   
   TBranch        *b_trackChi2_X;   //!                                                                                                                                               
   TBranch        *b_trackChi2_Y;   //!                                                                                                                                               
   TBranch        *b_dwcReferenceType;   //!                                                                                                                                          
   TBranch        *b_m_x;   //!                                                                                                                                                       
   TBranch        *b_m_y;   //!                                                                                                                                                       
   TBranch        *b_b_x;   //!                                                                                                                                                       
   TBranch        *b_b_y;   //!                                                                                                                                                       
   TBranch        *b_TrackImpactX_layer;   //!                                                                                                                                        
   TBranch        *b_TrackImpactY_layer;   //!                                                                                                                                        
   TBranch        *b_ahc_nHits;   //!                                                                                                                                                 
   TBranch        *b_ahc_energyPerLayer;   //!                                                                                                                                        
   TBranch        *b_ahc_nHitsPerLayer;   //!                                                                                                                                         
   TBranch        *b_ahc_hitI;   //!                                                                                                                                                  
   TBranch        *b_ahc_hitJ;   //!                                                                                                                                                  
   TBranch        *b_ahc_hitK;   //!                                                                                                                                                  
   TBranch        *b_ahc_hitEnergy;   //!                                                                                                                                             
   TBranch        *b_ahc_hitX;   //!                                                                                                                                                  
   TBranch        *b_ahc_hitY;   //!                                                                                                                                                  
   TBranch        *b_ahc_hitZ;   //!                                                                                                                                                  
  // TBranch        *b_ahc_nHits;   //!                                                                                                                                                 
   TBranch        *b_energyLostEE;   //!                                                                                                                                              
   TBranch        *b_energyLostFH;   //!                                                                                                                                              
   TBranch        *b_energyLostBH;   //!                                                                                                                                              
   TBranch        *b_energyLostBeam;   //!
   TBranch        *b_eventHadInt;   //!                                                                                                           
   TBranch        *b_foundHadInt;   //!                                                                                                           
   TBranch        *b_process;   //!                                                                                                               
   TBranch        *b_nsec;   //!                                                                                                                  
   TBranch        *b_sec_pdgID;   //!                                                                                                             
   TBranch        *b_sec_charge;   //!                                                                                                            
   TBranch        *b_sec_kin;   //!                                                                                                               
   TBranch        *b_sec_x;   //!                                                                                                                 
   TBranch        *b_sec_y;   //!                                                                                                                 
   TBranch        *b_sec_z;   //!                                                                                                                 
   TBranch        *b_Allsec_pdgID;   //!                                                                                                          
   TBranch        *b_Allsec_charge;   //!                                                                                                         
   TBranch        *b_Allsec_kin;   //!                                                                                                            
   TBranch        *b_Allsec_x;   //!                                                                                                              
   TBranch        *b_Allsec_y;   //!                                                                                                              
   TBranch        *b_Allsec_z;   //!
  TBranch   *b_sec_parent_id;
   TBranch   *b_sec_track_id;
   TBranch   *b_sec_process_id;
   TBranch   *b_Allsec_parent_id;
   TBranch   *b_Allsec_track_id;
   TBranch   *b_Allsec_process_id;
  //  TBranch *b_Nrechit_trimAhcal;

};

#endif

#ifdef HGCNtupleVariables_cxx

void HGCNtupleVariables::Init(TTree *tree)//, TTree *tree2, TTree *tree3)
/* void HGCNtupleVariables::Init(TTree *tree) */
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
  hgc_channel_mask = 0;
   ahc_channel_mask = 0;
   pass_noise_thres = 0;
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

    sec_pdgID = 0;
   sec_charge = 0;
   sec_kin = 0;
   sec_x = 0;
   sec_y = 0;
   sec_z = 0;
   Allsec_pdgID = 0;
   Allsec_charge = 0;
   Allsec_kin = 0;
   Allsec_x = 0;
   Allsec_y = 0;
   Allsec_z = 0;
    sec_parent_id=0;
   sec_track_id=0;
   sec_process_id=0;
   Allsec_parent_id=0;
   Allsec_track_id=0;
   Allsec_process_id=0;
//   rechitEn_trimAhcal=0;
//   comb_rechit_x_trimAhcal=0;
//   comb_rechit_y_trimAhcal=0;
//   comb_rechit_z_trimAhcal=0;
// Nrechit_trimAhcal=0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("pdgID", &pdgID, &b_pdgID);
   fChain->SetBranchAddress("beamEnergy", &beamEnergy, &b_beamEnergy);
   fChain->SetBranchAddress("trueBeamEnergy", &trueBeamEnergy, &b_trueBeamEnergy);
   fChain->SetBranchAddress("isHGC_AHC_sync", &isHGC_AHC_sync, &b_isHGC_AHC_sync);
   fChain->SetBranchAddress("isGoodTrack", &isGoodTrack, &b_isGoodTrack);
   fChain->SetBranchAddress("isFHNoisy", &isFHNoisy, &b_isFHNoisy);
   fChain->SetBranchAddress("MuonVeto", &MuonVeto, &b_MuonVeto);
   fChain->SetBranchAddress("isInTrackWindow", &isInTrackWindow, &b_isInTrackWindow);
   fChain->SetBranchAddress("hgc_channel_mask", &hgc_channel_mask, &b_hgc_channel_mask);
   fChain->SetBranchAddress("ahc_channel_mask", &ahc_channel_mask, &b_ahc_channel_mask);
   fChain->SetBranchAddress("pass_noise_thres", &pass_noise_thres, &b_pass_noise_thres);
//    fChain->SetBranchAddress("event", &event, &b_event);                                                                                                                           
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
   fChain->SetBranchAddress("rechit_amplitudeHigh", &rechit_amplitudeHigh, &b_rechit_amplitudeHigh);
   fChain->SetBranchAddress("rechit_amplitudeLow", &rechit_amplitudeLow, &b_rechit_amplitudeLow);
   fChain->SetBranchAddress("rechit_noise_flag", &rechit_noise_flag, &b_rechit_noise_flag);
   fChain->SetBranchAddress("rechit_module", &rechit_module, &b_rechit_module);
   fChain->SetBranchAddress("rechit_layer", &rechit_layer, &b_rechit_layer);
   fChain->SetBranchAddress("rechit_chip", &rechit_chip, &b_rechit_chip);
   fChain->SetBranchAddress("rechit_channel", &rechit_channel, &b_rechit_channel);
   fChain->SetBranchAddress("rechit_type", &rechit_type, &b_rechit_type);
   fChain->SetBranchAddress("rechit_shower_start_layer", &rechit_shower_start_layer, &b_rechit_shower_start_layer);
   fChain->SetBranchAddress("rechit_energyPerLayer", &rechit_energyPerLayer, &b_rechit_energyPerLayer);
   fChain->SetBranchAddress("rechit_nHitsPerLayer", &rechit_nHitsPerLayer, &b_rechit_nHitsPerLayer);
   fChain->SetBranchAddress("ntracks", &ntracks, &b_ntracks);
   fChain->SetBranchAddress("trackChi2_X", &trackChi2_X, &b_trackChi2_X);
   fChain->SetBranchAddress("trackChi2_Y", &trackChi2_Y, &b_trackChi2_Y);
   fChain->SetBranchAddress("dwcReferenceType", &dwcReferenceType, &b_dwcReferenceType);
   fChain->SetBranchAddress("m_x", &m_x, &b_m_x);
   fChain->SetBranchAddress("m_y", &m_y, &b_m_y);
   fChain->SetBranchAddress("b_x", &b_x, &b_b_x);
   fChain->SetBranchAddress("b_y", &b_y, &b_b_y);
   fChain->SetBranchAddress("TrackImpactX_layer", &TrackImpactX_layer, &b_TrackImpactX_layer);
   fChain->SetBranchAddress("TrackImpactY_layer", &TrackImpactY_layer, &b_TrackImpactY_layer);
   fChain->SetBranchAddress("ahc_nHits", &ahc_nHits, &b_ahc_nHits);
   fChain->SetBranchAddress("ahc_energyPerLayer", &ahc_energyPerLayer, &b_ahc_energyPerLayer);
   fChain->SetBranchAddress("ahc_nHitsPerLayer", &ahc_nHitsPerLayer, &b_ahc_nHitsPerLayer);
   fChain->SetBranchAddress("ahc_hitI", &ahc_hitI, &b_ahc_hitI);
   fChain->SetBranchAddress("ahc_hitJ", &ahc_hitJ, &b_ahc_hitJ);
   fChain->SetBranchAddress("ahc_hitK", &ahc_hitK, &b_ahc_hitK);
   fChain->SetBranchAddress("ahc_hitEnergy", &ahc_hitEnergy, &b_ahc_hitEnergy);
   fChain->SetBranchAddress("ahc_hitX", &ahc_hitX, &b_ahc_hitX);
   fChain->SetBranchAddress("ahc_hitY", &ahc_hitY, &b_ahc_hitY);
   fChain->SetBranchAddress("ahc_hitZ", &ahc_hitZ, &b_ahc_hitZ);
//    fChain->SetBranchAddress("ahc_nHits", &ahc_nHits, &b_ahc_nHits);

   //  fChain->SetBranchAddress("rechitEn_trimAhcal",&rechitEn_trimAhcal,&b_rechitEn_trimAhcal);
   // fChain->SetBranchAddress("comb_rechit_x_trimAhcal",&comb_rechit_x_trimAhcal,&b_comb_rechit_x_trimAhcal);
   // fChain->SetBranchAddress("comb_rechit_y_trimAhcal",&comb_rechit_y_trimAhcal,&b_comb_rechit_y_trimAhcal);
   // fChain->SetBranchAddress("comb_rechit_z_trimAhcal",&comb_rechit_z_trimAhcal,&b_comb_rechit_z_trimAhcal);
   // fChain->SetBranchAddress("Nrechit_trimAhcal",&Nrechit_trimAhcal,&b_Nrechit_trimAhcal);
   fChain->SetBranchAddress("energyLostEE", &energyLostEE, &b_energyLostEE);
   fChain->SetBranchAddress("energyLostFH", &energyLostFH, &b_energyLostFH);
   fChain->SetBranchAddress("energyLostBH", &energyLostBH, &b_energyLostBH);
   fChain->SetBranchAddress("energyLostBeam", &energyLostBeam, &b_energyLostBeam);
    fChain->SetBranchAddress("eventHadInt", &eventHadInt, &b_eventHadInt);
   fChain->SetBranchAddress("foundHadInt", &foundHadInt, &b_foundHadInt);
   fChain->SetBranchAddress("process", &process, &b_process);
   fChain->SetBranchAddress("nsec", &nsec, &b_nsec);
   fChain->SetBranchAddress("sec_pdgID", &sec_pdgID, &b_sec_pdgID);
   fChain->SetBranchAddress("sec_charge", &sec_charge, &b_sec_charge);
   fChain->SetBranchAddress("sec_kin", &sec_kin, &b_sec_kin);
   fChain->SetBranchAddress("sec_x", &sec_x, &b_sec_x);
   fChain->SetBranchAddress("sec_y", &sec_y, &b_sec_y);
   fChain->SetBranchAddress("sec_z", &sec_z, &b_sec_z);
   fChain->SetBranchAddress("Allsec_pdgID", &Allsec_pdgID, &b_Allsec_pdgID);
   fChain->SetBranchAddress("Allsec_charge", &Allsec_charge, &b_Allsec_charge);
   fChain->SetBranchAddress("Allsec_kin", &Allsec_kin, &b_Allsec_kin);
   fChain->SetBranchAddress("Allsec_x", &Allsec_x, &b_Allsec_x);
   fChain->SetBranchAddress("Allsec_y", &Allsec_y, &b_Allsec_y);
   fChain->SetBranchAddress("Allsec_z", &Allsec_z, &b_Allsec_z);
    fChain->SetBranchAddress("sec_parent_id", &sec_parent_id, &b_sec_parent_id);
   fChain->SetBranchAddress("sec_track_id", &sec_track_id, &b_sec_track_id);
   fChain->SetBranchAddress("sec_process_id", &sec_process_id, &b_sec_process_id);
   fChain->SetBranchAddress("Allsec_parent_id", &Allsec_parent_id, &b_Allsec_parent_id);
   fChain->SetBranchAddress("Allsec_track_id", &Allsec_track_id, &b_Allsec_track_id);
   fChain->SetBranchAddress("Allsec_process_id", &Allsec_process_id, &b_Allsec_process_id);





   Notify();
}
 //for tree
void HGCNtupleVariables::init_piTree(){

 
  pion_tree->Branch("event",&pi_event);
  pion_tree->Branch("run",&pi_run);
  pion_tree->Branch("pdgID",&pi_pdgID);
  pion_tree->Branch("beamEnergy",&pi_beamEnergy);
  pion_tree->Branch("trueBeamEnergy",&pi_trueBeamEnergy);


   pion_tree->Branch("isHGC_AHC_sync",&pi_isHGC_AHC_sync);
  pion_tree->Branch("isGoodTrack",&pi_isGoodTrack);
  pion_tree->Branch("isFHNoisy",&pi_isFHNoisy);
  pion_tree->Branch("MuonVeto",&pi_MuonVeto);
  pion_tree->Branch("isInTrackWindow",&pi_isInTrackWindow);
  pion_tree->Branch("hgc_channel_mask",&pi_hgc_channel_mask);
  pion_tree->Branch("ahc_channel_mask",&pi_ahc_channel_mask);
  pion_tree->Branch("pass_noise_thres",&pi_pass_noise_thres);
  pion_tree->Branch("event_orig",&pi_event_orig);
  pion_tree->Branch("NRechits_orig",&pi_NRechits_orig);

  
  pion_tree->Branch("NRechits",&pi_NRechits);
  pion_tree->Branch("rechit_energy",&pi_rechit_energy);
  pion_tree->Branch("rechit_x",&pi_rechit_x);
  pion_tree->Branch("rechit_y",&pi_rechit_y);
  pion_tree->Branch("rechit_z",&pi_rechit_z);
  pion_tree->Branch("rechit_cogX",&pi_rechit_cogX);
  pion_tree->Branch("rechit_cogY",&pi_rechit_cogY);
  pion_tree->Branch("rechit_iu",&pi_rechit_iu);
  pion_tree->Branch("rechit_iv",&pi_rechit_iv);
  pion_tree->Branch("rechit_iU",&pi_rechit_iU);
  pion_tree->Branch("rechit_iV",&pi_rechit_iV);
  pion_tree->Branch("rechit_amplitudeHigh",&pi_rechit_amplitudeHigh);
  pion_tree->Branch("rechit_amplitudeLow",&pi_rechit_amplitudeLow);
  pion_tree->Branch("rechit_noise_flag",&pi_rechit_noise_flag);
  pion_tree->Branch("rechit_module",&pi_rechit_module);
  pion_tree->Branch("rechit_layer",&pi_rechit_layer);
  pion_tree->Branch("rechit_chip",&pi_rechit_chip);
  pion_tree->Branch("rechit_channel",&pi_rechit_channel);
  pion_tree->Branch("rechit_type",&pi_rechit_type);
   pion_tree->Branch("rechit_shower_start_layer",&pi_rechit_shower_start_layer);
  pion_tree->Branch("rechit_energyPerLayer",&pi_rechit_energyPerLayer);
  pion_tree->Branch("rechit_nHitsPerLayer",&pi_rechit_nHitsPerLayer);


  pion_tree->Branch("ntracks",&pi_ntracks);
  pion_tree->Branch("trackChi2_X",&pi_trackChi2_X);
  pion_tree->Branch("trackChi2_Y",&pi_trackChi2_Y);
  pion_tree->Branch("dwcReferenceType",&pi_dwcReferenceType);
  pion_tree->Branch("m_x",&pi_m_x);
  pion_tree->Branch("m_y",&pi_m_y);
  pion_tree->Branch("b_x",&pi_b_x);
  pion_tree->Branch("b_y",&pi_b_y);
  pion_tree->Branch("TrackImpactX_layer",&pi_impactX_layer);
  pion_tree->Branch("TrackImpactY_layer",&pi_impactY_layer);

  pion_tree->Branch("ahc_nHits",&pi_ahc_nHits);
  pion_tree->Branch("ahc_nHits_orig",&pi_ahc_nHits_orig);
  pion_tree->Branch("ahc_energyPerLayer",&pi_ahc_energyPerLayer);
  pion_tree->Branch("ahc_nHitsPerLayer",&pi_ahc_nHitsPerLayer);
  pion_tree->Branch("ahc_hitI",&pi_ahc_hitI);
  pion_tree->Branch("ahc_hitJ",&pi_ahc_hitJ);
  pion_tree->Branch("ahc_hitK",&pi_ahc_hitK);
  pion_tree->Branch("ahc_hitEnergy",&pi_ahc_hitEnergy);
  pion_tree->Branch("ahc_hitX",&pi_ahc_hitX);
  pion_tree->Branch("ahc_hitY",&pi_ahc_hitY);
  pion_tree->Branch("ahc_hitZ",&pi_ahc_hitZ);
  //  pion_tree->Branch("ahc_nHits",&pi_ahc_nHits);
  

  pion_tree->Branch("energyLostEE",&pi_energyLostEE);
  pion_tree->Branch("energyLostFH",&pi_energyLostFH);
  pion_tree->Branch("energyLostBH",&pi_energyLostBH);
  pion_tree->Branch("energyLostBeam",&pi_energyLostBeam);
  pion_tree->Branch("rechitEn_trimAhcal",&pi_rechitEn_trimAhcal);
  pion_tree->Branch("comb_rechit_x_trimAhcal",&pi_comb_rechit_x_trimAhcal);
  
  pion_tree->Branch("comb_rechit_y_trimAhcal",&pi_comb_rechit_y_trimAhcal);
  pion_tree->Branch("comb_rechit_z_trimAhcal",&pi_comb_rechit_z_trimAhcal);
  pion_tree->Branch("comb_rechit_z_trimAhcal",&pi_comb_rechit_z_trimAhcal);
  pion_tree->Branch("Nrechit_trimAhcal",&pi_Nrechit_trimAhcal);
  
   pion_tree->Branch("eventHadInt", &eventHadInt);
   pion_tree->Branch("foundHadInt", &foundHadInt);
   pion_tree->Branch("process", &process);
   pion_tree->Branch("nsec", &nsec);
   pion_tree->Branch("sec_pdgID", &sec_pdgID);
   pion_tree->Branch("sec_charge", &sec_charge);
   pion_tree->Branch("sec_kin", &sec_kin);
   pion_tree->Branch("sec_x", &sec_x);
   pion_tree->Branch("sec_y", &sec_y);
   pion_tree->Branch("sec_z", &sec_z);
   pion_tree->Branch("Allsec_pdgID", &Allsec_pdgID);
   pion_tree->Branch("Allsec_charge", &Allsec_charge);
   pion_tree->Branch("Allsec_kin", &Allsec_kin);
   pion_tree->Branch("Allsec_x", &Allsec_x);
   pion_tree->Branch("Allsec_y", &Allsec_y);
   pion_tree->Branch("Allsec_z", &Allsec_z);

   pion_tree->Branch("leadingHadKE", &pi_leadingHadKE);
   pion_tree->Branch("E_genKin",&pi_E_genKin);
   pion_tree->Branch("nsc_total_KE",&pi_nsc_total_KE);
   pion_tree->Branch("Allsec_pions",&pi_Allsec_pions);
   pion_tree->Branch("Allsec_Kaons",&pi_Allsec_Kaons);
   pion_tree->Branch("Allsec_kin",&pi_Allsec_kin);
 pion_tree->Branch("sec_parent_id",&sec_parent_id);
   pion_tree->Branch("sec_process_id",&sec_process_id);
   pion_tree->Branch("sec_track_id",&sec_track_id);
   pion_tree->Branch("Allsec_parent_id",&Allsec_parent_id);
   pion_tree->Branch("Allsec_process_id",&Allsec_process_id);
   pion_tree->Branch("Allsec_track_id",&Allsec_track_id);


   

 }
Bool_t HGCNtupleVariables::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef HGCNtupleVariables_cxx
