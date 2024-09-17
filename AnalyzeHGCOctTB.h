#ifndef AnalyzeHGCOctTB_H
#define AnalyzeHGCOctTB_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "HGCNtupleVariables.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TGraph.h"
#include "TF1.h"
#include "TFile.h"
#include "TProfile.h"
#include "TLorentzVector.h"
#include "TDirectory.h"

class AnalyzeHGCOctTB : public HGCNtupleVariables{

 public:
  AnalyzeHGCOctTB(const TString &inputFileList="foo.txt", const char *outFileName="histo.root",const char *dataset="data", const char *config="alpha", const char* energy = "-1");
  ~AnalyzeHGCOctTB();
  //Bool_t   FillChain(TChain *chain, TChain *chain2, TChain *chain3, const TString &inputFileList);
   Bool_t   FillChain(TChain *chain, const TString &inputFileList); 
  Long64_t LoadTree(Long64_t entry);
  void     EventLoop(const char *, const char *);
  void     BookHistogram(const char *, const char *, const char* energy);

  void moduleMap_init(const char *);
  void Alignment_Map_Init();
  void Noise_Map_Init();
  void layerPosition_init();
  std::vector<bool> *noise_flag;
  TFile *oFile;
  const char *conf_;  
  int inEnergy_;
  int event_count[7]={};
  int count=0, count_afterCuts =0;//,count_nflag=0,count_nchannel=0,count_nchanLayer1=0, count_nflag0=0;
  int count_FH=0,count_fh=0, count_badtrack=0;//,count_adiMask=0;
  int count_FH_afterCuts=0;
  TH1F* h_beamenergy;
  TH1F* h_particle;
  TH2F* h_2D_nsc_correlation[8];
  TH2F* h_2D_nsc_correlation_frac[8];
  TH2F* h_2D_hlead_sec_frac[8];

  TH2F* h_2D_nsc_correlation_hadNotfound[8];
  TH2F* h_2D_nsc_correlation_frac_hadNotfound[8];
  TH2F* h_2D_hlead_sec_frac_hadNotfound[8];

  TH1F* h_true_beamenergy;
  TH1F* h_nsc[8];
  TH1F* h_seckin[8];
  TH1F* h_had_leading_KE[8];
  TH1F* h_gen_kin[8];
  TH1F* h_Allsec_kin[8];
  TH1F* h_Allsec_kin_kaons[8];
  TH1F* h_Allsec_kin_pions[8];


  

};
#endif

#ifdef AnalyzeHGCOctTB_cxx

void AnalyzeHGCOctTB::BookHistogram(const char *outFileName, const char* conf,  const char* energy) {

  conf_ = conf;
  oFile = new TFile(outFileName, "recreate");
  int Elist[8] ={20,50,80,100,120,200,250,300};
  int en = atoi(energy);
  float xlow = 0.0;
  float xhigh = en*100*1.5;
   double y_max = -1.0;
  double x_2D_max = -1.0;
  double xbin = -1.0;
  double y_2D_max = -1.0;
  double mip_x_max = 3000;
  double mip_y_max = 1500;
  double per_layer_xbin =  -1.0;
  double per_layer_xmax =  -1.0;

  double sec_kin_max = 0.0;
  int nsc = 0.0;
  if(!strcmp(energy, "20")) {
    y_max = 100.0;
    x_2D_max = 3000;
    xbin = 300;
    y_2D_max = 1500;
    inEnergy_ = 20;
    per_layer_xbin = inEnergy_*2;
    per_layer_xmax = inEnergy_*30;
    sec_kin_max = inEnergy_*(3.0/2.0);
    nsc = 150;

  }
  else if(!strcmp(energy, "50")) {
    y_max = 150.0;
    /* x_2D_max = 5000; */
    /* x_2D_max = 5000; */
    /* xbin = 500; */
    x_2D_max = 10000;
    xbin = 500;
    y_2D_max = 200;
    inEnergy_ = 50;
    per_layer_xbin = inEnergy_*2;
    per_layer_xmax = inEnergy_*30;

  }
  else if(!strcmp(energy, "80")) {
    y_max = 200.0;
    /* x_2D_max = 8000; */
    /* xbin = 400; */
    x_2D_max = 12000;
    xbin = 300;
    y_2D_max = 3000;
    inEnergy_ = 80;
    per_layer_xbin = inEnergy_*2;
    per_layer_xmax = inEnergy_*30;

  }
  else if(!strcmp(energy, "100")) {
    y_max = 300.0;
    /* x_2D_max = 10000; */
    /* xbin = 500; */
    x_2D_max = 18000;
    xbin = 360;
    y_2D_max = 3000;
    inEnergy_ = 100;
    per_layer_xbin = inEnergy_*2;
    per_layer_xmax = inEnergy_*30;
    sec_kin_max = inEnergy_*(3.0/2.0);
    nsc = 200;

  }
  else if(!strcmp(energy, "120")) {

   y_max = 400.0;
    /* x_2D_max = 12000; */
    /* xbin = 300; */
    x_2D_max = 20000;
    xbin = 400;
    y_2D_max = 3200;
    inEnergy_ = 120;
    per_layer_xbin = inEnergy_*2;
    per_layer_xmax = inEnergy_*30;

  }
  else if(!strcmp(energy, "200")) {
    y_max = 600.0;
    /* x_2D_max = 18000; */
    /* xbin = 360; */
    x_2D_max = 40000;
    xbin = 800;
    y_2D_max = 4800;
    inEnergy_ = 200;
    per_layer_xbin = inEnergy_*2;
    per_layer_xmax = inEnergy_*30;

  }
else if(!strcmp(energy, "300")) {
    y_max = 800.0;
    x_2D_max = 60000;
    /* x_2D_max = 20000; */
    xbin = 1000;
    y_2D_max = 6000;
    inEnergy_ = 300;
    per_layer_xbin = inEnergy_*2;
    per_layer_xmax = inEnergy_*30;

  }
  else if(!strcmp(energy, "420")) {
    y_max = 200.0;
    x_2D_max = 200;
    /* x_2D_max = 20000; */
    xbin = 1000;
    y_2D_max = 6000;
    per_layer_xbin = 400;
    per_layer_xmax = 40;

    inEnergy_ = 420;
  }

  else {
    cout<<"invalid energy!!!"<<endl;
    return;
  }

  //int xbin = (xhigh-xlow)/6;
  //  int xbin = 500;//*0.5*en;
  ////////// Book histograms here  //////////////
  h_beamenergy = new TH1F("h_beamenergy","h_beamenergy",320,0,320);
  h_true_beamenergy = new TH1F("h_true_beamenergy","h_true_beamenergy",350,0,350);
  h_particle = new TH1F("h_particle","h_particle",600,-300,300);
  char* hname = new char[1000];
  for(int ien=0;ien<8;ien++){
    sec_kin_max=0;
    sec_kin_max=Elist[ien]*(3.0/2.0);
    nsc =0;
    nsc= 2*Elist[ien];
    sprintf(hname,"h_2D_nsc_correlation_En_%d",Elist[ien]);
  h_2D_nsc_correlation[ien] = new TH2F(hname,"h_2D_nsc_correlation",sec_kin_max*5,0.0,sec_kin_max,nsc,0.0,nsc);
  h_2D_nsc_correlation[ien]->GetXaxis()->SetTitle("Kinetic energy Sum of Secondaries [GeV] ");
  h_2D_nsc_correlation[ien]->GetYaxis()->SetTitle("# of Generated Secondaries ");
  sprintf(hname,"h_2D_nsc_correlation_frac_En_%d",Elist[ien]);

  h_2D_nsc_correlation_frac[ien] = new TH2F(hname,"h_2D_nsc_correlation_frac",100.0,0.0,1.0,nsc,0.0,nsc);
  h_2D_nsc_correlation_frac[ien]->GetXaxis()->SetTitle("Fractional Kinetic energy Sum of Secondaries");
  h_2D_nsc_correlation_frac[ien]->GetYaxis()->SetTitle("# of Secondaries ");
  sprintf(hname,"h_2D_hlead_sec_frac_En_%d",Elist[ien]);

  h_2D_hlead_sec_frac[ien] = new TH2F(hname,"h_2D_hlead_sec_frac",100.0,0.0,1.0,100.0,0.0,1.0);
  h_2D_hlead_sec_frac[ien]->GetXaxis()->SetTitle("Fractional Kinetic energy Sum of Secondaries ");
  h_2D_hlead_sec_frac[ien]->GetYaxis()->SetTitle("Fractional Kinetic energy of leadind #pi^{-}");

  sprintf(hname,"h_nsc_En_%d",Elist[ien]);
  h_nsc[ien] = new TH1F(hname,"h_nsc",nsc,0.0,nsc);
  sprintf(hname,"h_seckin_En_%d",Elist[ien]);

  h_seckin[ien] = new TH1F(hname,"h_seckin",100,0,1);//sec_kin_max*5,0.0,sec_kin_max);
  sprintf(hname,"h_had_leading_KE_En_%d",Elist[ien]);

  h_had_leading_KE[ien] = new TH1F(hname,"h_had_leading_KE",100,0,1);//sec_kin_max*5,0.0,sec_kin_max);
  sprintf(hname,"h_gen_kin_En_%d",Elist[ien]);

  h_gen_kin[ien] = new TH1F(hname,"h_gen_kin",100,0,1);//sec_kin_max*5,0.0,sec_kin_max);
  sprintf(hname,"h_Allsec_kin_En_%d",Elist[ien]);

  h_Allsec_kin[ien] = new TH1F(hname,"Allsecondary -pi0+k0",100,0,1);//sec_kin_max*5,0.0,sec_kin_max);
  sprintf(hname,"h_Allsec_kin_kaons_En_%d",Elist[ien]);

  h_Allsec_kin_kaons[ien] = new TH1F(hname,"Allsecondary-k0",100,0,1);//sec_kin_max*5,0.0,sec_kin_max);
  sprintf(hname,"h_Allsec_kin_pions_En_%d",Elist[ien]);

  h_Allsec_kin_pions[ien] = new TH1F(hname,"Allsecondary-pi0",100,0,1);//sec_kin_max*5,0.0,sec_kin_max);

  }
    
}

void AnalyzeHGCOctTB::Alignment_Map_Init() {
  /// Alignment map for config 1, it needs to be changed accorfing to configurations
  
  char* f_name = new char[200];
  sprintf(f_name,"../../Alignment_Map.txt");
  std::ifstream in(f_name);
  //int layer;
  if(!in) {
    cout<<"ERROR => "<<f_name<<" Not found"<<endl;
    //return;
    exit(0);
  }

  std::pair<float,float> dx_dy;
  std::pair<int, std::pair<float,float> > temp;
  int layer;
  float dx,dy;
  while(in>>layer>>dx>>dy) {
    //run_layer = std::make_pair(run,layer);
    dx_dy = std::make_pair(dx,dy);
    temp = std::make_pair(layer,dx_dy);
    align_map.insert(temp);
  }

  std::cout<<"INFO: Alignment MAP initialized successfully!!!"<<endl;
}

void AnalyzeHGCOctTB::Noise_Map_Init() {
  //Noise map for config - 1 , needs to be changed accordingly
  
  char* f_name = new char[200];
  sprintf(f_name,"../../Noise_Map.txt");
  std::ifstream in(f_name);
  
  if(!in) {
    cout<<"ERROR => "<<f_name<<" Not found"<<endl;
    exit(0);
  }
  std::pair<int,int> mod_chip;
  std::pair<std::pair<int,int>, float> temp;
  int layer,mod_id,mod_pos,chip;
  float noise;
  while(in>>layer>>mod_id>>mod_pos>>chip>>noise) {
    mod_chip = std::make_pair(mod_id,chip);
    temp = std::make_pair(mod_chip,noise);
    noise_map.insert(temp);
  }

  std::cout<<"INFO: Noise MAP initialized successfully!!!"<<endl;
}

void AnalyzeHGCOctTB::moduleMap_init(const char* config) {
  char *f_name = new char[200];

  if(strcmp(config,"alpha")==0 || strcmp(config,"config1")==0) {
    sprintf(f_name,"../../config_maps/moduleMAP_config1.txt");
    cout<<"\n\nINFO: Mapping module configuration ALPHA (oct10-oct17) "<<endl;
    cout<<"INFO: Mapping EE[0]/FH[1]::Layer #[1-40]::Position on Layer[0 for EE]&[1-7 for FH] consult figure for Daisy structure configuration!!!"<<endl;

  }
  else if(strcmp(config,"bravo")==0 || strcmp(config,"config2")==0) {
    sprintf(f_name,"../../config_maps/moduleMAP_config2.txt");
    cout<<"\n\nINFO: Mapping module configuration BRAVO (17oct-22oct) "<<endl;
    cout<<"INFO: Mapping EE[0]/FH[1]::Layer #[1-40]::Position on Layer[0 for EE]&[1-7 for FH] consult figure for Daisy structure configuration!!!"<<endl;

  }
  else if(strcmp(config,"charlie")==0  || strcmp(config,"config3")==0) {
    sprintf(f_name,"../../config_maps/moduleMAP_config3.txt");
    cout<<"\n\nINFO: Mapping module configuration CHARLIE (23Oct-4Nov) "<<endl;
    cout<<"INFO: Mapping EE[0]/FH[1]::Layer #[1-40]::Position on Layer[0 for EE]&[1-7 for FH] consult figure for Daisy structure configuration!!!"<<endl;

  }
  else {
    cout<<"\n\nERROR: Incorrect configuration entered "<<endl;
    cout<<" Allowed configuration :\n alpha = Configuration 1 (10Oct-17Nov) \n bravo = Configuration 2 (17Oct-22Oct) \n charlie = Configuration 3 (23Oct-17Nov)"<<endl;
    return;
    
  }

  std::ifstream in(f_name);
  if(!in) {
    cout<<"ERROR => "<<f_name<<" Not found"<<endl;
    //return;
    exit(0);
  }


  int modID_, part_, layer_, pos_;
  cout<<"File name = "<<f_name<<endl;
  while(in>>modID_>>part_>>layer_>>pos_){
    std::pair<int, std::vector<int>> temp_pair;
    std::vector<int> temp_vector;
    temp_vector.push_back(part_);
    temp_vector.push_back(layer_);
    temp_vector.push_back(pos_);
    temp_pair = std::make_pair(modID_,temp_vector);
    module_map.insert(temp_pair);
  }

  cout<<"INFO: Module Mapping Done!!! "<<endl<<endl;


}


void AnalyzeHGCOctTB::layerPosition_init() {
  // Layer postions for config - 1, needs to be changed accordingly for other configs
  
  char *f_name = new char[200];
  sprintf(f_name,"../../config1_lengths.txt");

  std::ifstream in(f_name);
  if(!in) {
    cout<<"ERROR => "<<f_name<<" Not found"<<endl;
    exit(0);
  }
  int layer_;
  float  cm_, x0, nuc_int_, pi_int_;

  cout<<"File name = "<<f_name<<endl;
  while(in>>layer_>>cm_>>x0>>nuc_int_>>pi_int_){
    std::pair<int, std::vector<float>> temp_pair;
    std::vector<float> temp_vector;
    temp_vector.push_back(cm_/10.0);
    temp_vector.push_back(x0);
    temp_vector.push_back(nuc_int_);
    temp_vector.push_back(pi_int_);

    temp_pair = std::make_pair(layer_,temp_vector);
    layer_positions.insert(temp_pair);
  }

  cout<<"INFO: Layer Position Mapping Done!!! "<<endl<<endl;


}


AnalyzeHGCOctTB::AnalyzeHGCOctTB(const TString &inputFileList, const char *outFileName, const char* dataset, const char* config, const char* energy) {

  TChain *tree = new TChain("pion_variables");
  // TChain *tree2 = new TChain("trackimpactntupler/impactPoints");
  // TChain *tree3 = new TChain("bigtree");


  if( ! FillChain(tree, inputFileList) ) {
    std::cerr << "Cannot get the tree " << std::endl;
  } else {
    std::cout << "Initiating analysis of dataset " << dataset << std::endl;
  }


  HGCNtupleVariables::Init(tree);//, tree2, tree3);
  //  HGCNtupleVariables::init_piTree();
  BookHistogram(outFileName, config, energy);
  moduleMap_init(config);
  Alignment_Map_Init();
  Noise_Map_Init();
  layerPosition_init();
  
}
Bool_t AnalyzeHGCOctTB::FillChain(TChain *chain,  const TString &inputFileList) {//TChain *chain2, TChain *chain3, const TString &inputFileList) {

  ifstream infile(inputFileList, ifstream::in);
  std::string buffer;

  if(!infile.is_open()) {
    std::cerr << "** ERROR: Can't open '" << inputFileList << "' for input" << std::endl;
    return kFALSE;
  }

  std::cout << "TreeUtilities : FillChain " << std::endl;
  while(1) {
    infile >> buffer;
    if(!infile.good()) break;
    //std::cout << "Adding tree from " << buffer.c_str() << std::endl;                                                              
    chain->Add(buffer.c_str());
    // chain2->Add(buffer.c_str());
    // chain3->Add(buffer.c_str());

  }
  std::cout << "No. of Entries in chain  : " << chain->GetEntries() << std::endl;
  // std::cout << "No. of Entries in chain2 : " << chain2->GetEntries() << std::endl;
  // std::cout << "No. of Entries in chain3 : " << chain3->GetEntries() << std::endl;

  return kTRUE;
}

Long64_t AnalyzeHGCOctTB::LoadTree(Long64_t entry) {
  // Set the environment to read one entry                                                                                          
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (!fChain->InheritsFrom(TChain::Class()))  return centry;
  TChain *chain = (TChain*)fChain;
  if (chain->GetTreeNumber() != fCurrent) {
    fCurrent = chain->GetTreeNumber();
    //    Notify();
  }

  // if (!fChain2) return -5;
  // Long64_t centry2 = fChain2->LoadTree(entry);
  // if (centry2 < 0) return centry2;
  // if (!fChain2->InheritsFrom(TChain::Class()))  return centry2;
  // TChain *chain2 = (TChain*)fChain2;
  // if (chain2->GetTreeNumber() != fCurrent) {
  //   fCurrent = chain->GetTreeNumber();
  //   //    Notify();
  // }

  // if (!fChain3) return -5;
  // Long64_t centry3 = fChain3->LoadTree(entry);
  // if (centry3 < 0) return centry3;
  // if (!fChain3->InheritsFrom(TChain::Class()))  return centry3;
  // TChain *chain3 = (TChain*)fChain3;
  // if (chain3->GetTreeNumber() != fCurrent) {
  //   fCurrent = chain->GetTreeNumber();
  //   //    Notify();
  // }
  
  //if (centry==centry2)
  return centry;
  // cout<<"centry = "<<centry<<endl;
  // if(centry>0)
  //   return centry;
  // else return -1;
}

AnalyzeHGCOctTB::~AnalyzeHGCOctTB() { 

  // if (!fChain || !fChain2) return;
  // delete fChain->GetCurrentFile();
  // delete fChain2->GetCurrentFile();
  // oFile->cd();
  // oFile->Write();
  // oFile->Close();


  if (!fChain) return;
  delete fChain->GetCurrentFile();
  oFile->cd();
  oFile->Write();
  oFile->Close();

}

#endif

/*  LocalWords:  Nrechit EE R1 FH GetXaxis SetTitle Sumw2 TH2F reg3 NRechits
 */
/*  LocalWords:  GetYaxis SetTitleOffset
 */
