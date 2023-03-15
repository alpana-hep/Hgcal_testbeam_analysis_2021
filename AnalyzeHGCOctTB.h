#ifndef AnalyzeHGCOctTB_H
#define AnalyzeHGCOctTB_H
#define RESET "\033[0m"
#define BLACK "\033[30m"              /* Black */
#define RED "\033[31m"                /* Red */
#define GREEN "\033[32m"              /* Green */
#define YELLOW "\033[33m"             /* Yellow */
#define BLUE "\033[34m"               /* Blue */
#define MAGENTA "\033[35m"            /* Magenta */
#define CYAN "\033[36m"               /* Cyan */
#define WHITE "\033[37m"              /* White */
#define BOLDBLACK "\033[1m\033[30m"   /* Bold Black */
#define BOLDRED "\033[1m\033[31m"     /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m"   /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m"  /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m"    /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m"    /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m"   /* Bold White */

#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "HGCNtupleVariables.h"
#include "TDirectory.h"
#include "TF1.h"
#include "TFile.h"
#include "TGraph.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TLorentzVector.h"
#include "TProfile.h"

class AnalyzeHGCOctTB : public HGCNtupleVariables {
 public:
  AnalyzeHGCOctTB(const TString &inputFileList = "foo.txt",
                  const char *outFileName = "histo.root",
                  const char *dataset = "data", const char *config = "alpha",
                  const char *energy = "-1");  //, const char* min_ = "-1",
                                               //const char* max_ ="-1");
  ~AnalyzeHGCOctTB();
  // Bool_t   FillChain(TChain *chain, TChain *chain2, TChain *chain3, const
  // TString &inputFileList);
  Bool_t FillChain(TChain *chain, const TString &inputFileList);
  Long64_t LoadTree(Long64_t entry);
  void EventLoop(const char *, const char *);  //, const char *,const char *);
  void BookHistogram(const char *, const char *, const char *energy);

  void moduleMap_init(const char *);
  void Alignment_Map_Init();
  void Noise_Map_Init();
  void layerPosition_init();
  void Chi2_Weight_Map_Init(
      int chi2_method);  // intialize the weights at different pion energies

  std::vector<bool> *noise_flag;
  TFile *oFile;
  const char *conf_;
  int inEnergy_;
  int event_count[7] = {};
  int count = 0, count_afterCuts = 0;  //,count_nflag=0,count_nchannel=0,count_nchanLayer1=0,
                                       //count_nflag0=0;
  float totalEnergy_inGeV = 0;
  float EnergySum_SSinEE = 0;
  float EnergySum_SSinFH = 0;
  float Esum_rechits_FH = 0;
  float Esum_rechits_EE = 0;
  float Esum_rechits_AH = 0;
  float Esum_rechits_FH_inGeV = 0;
  float Esum_rechits_EE_inGeV = 0;
  float Esum_rechits_AH_inGeV = 0;
  int total_rechits = 0, rechits_EE = 0, rechits_FH = 0, rechits_AH = 0;

  int count_FH = 0, count_fh = 0, count_badtrack = 0;  //,count_adiMask=0;
  int count_FH_afterCuts = 0;
  TH1F *h_beamenergy;
  TH1F *h_particle;

  TH1F *h_true_beamenergy[6];
  //histograms to understand clue algorithm
  TH1F *h_Clusters_X[85][50];
  TH1F *h_Clusters_Y[85][50];
  TH1F *h_Clusters_Z[85][50];
  TH1F *h_Clusters_En[85][50];
  TH2F *h_Clusters_EnvsZ[85][50];
  TH2F *h_Clusters_XvsY[85][50];
  TH1F *h_NClusters[85];
  TH1F *h_NRechits[85];
  TH2F *h_NRechitsVsNClusters[85];
  TH2F *h_NRechitsVsNClusters_perLayer[85][50];
  TH1F *h_NClusters_perLayer[85][50];
  TH1F *h_Nrechits_perClusters[85][50];
  TH2F *h_Nrechits_beforeVsAfter[85];
  TH1F *h_rechits_rho[85][50];
  TH1F *h_rechits_delta[85][50];
  TH1F *h_totalEnClustered[85];
  TH2F *h_totalClustEn_vsTotalFixEn[85];

  
};
#endif

#ifdef AnalyzeHGCOctTB_cxx

void AnalyzeHGCOctTB::BookHistogram(const char *outFileName, const char *conf,
                                    const char *energy) {
  conf_ = conf;
  oFile = new TFile(outFileName, "recreate");

  int en = atoi(energy);
  float xlow = 0.0;
  float xhigh = en * 100 * 1.5;
  // int xbin = (xhigh-xlow)/6;
  int xbin = 200;  //*0.5*en;
                   ////////// Book histograms here  //////////////
  const char *baseline[6] = {
      "Nocut",       "FH-noisy",    "Good-track", "MuonVeto",
      "pres-shower", "track-impact"};  //,"dPhi_Met","Met_100","Met_250","Met_600","st_300_Met100","pt_st_Met_250","st_300_Met250","nocut"};
  int Elist[85] = {
      10,  14,  18,  22,  26,  30,  34,  38,  42,  46,  50,  54,  58,  62,  66,
      70,  74,  78,  82,  86,  90,  94,  98,  102, 106, 110, 114, 118, 122, 126,
      130, 134, 138, 142, 146, 150, 154, 158, 162, 166, 170, 174, 178, 182, 186,
      190, 194, 198, 202, 206, 210, 214, 218, 222, 226, 230, 234, 238, 242, 246,
      250, 254, 258, 262, 266, 270, 274, 278, 282, 286, 290, 294, 298, 302, 306,
      310, 314, 318, 322, 326, 330, 334, 338, 342, 346};

  char name[100], title[100];
  char hname[1000], hname1[1000], hname1_2d[1000];
  for (int i = 0; i < 6; i++) {
    cout << baseline[i] << endl;
    sprintf(hname, "h_truebeamenergy_after_%s", baseline[i]);
    h_true_beamenergy[i] = new TH1F(hname, hname, 400, 0, 400);
  }

  for(int ien=0;ien<85;ien++)
    {
      sprintf(hname1,"No_ofClusters_TrueEn_%d_to_%d",Elist[ien],Elist[ien]+4);
      h_NClusters[ien] = new TH1F(hname1,"Total number of clusters per event",600,0,3000);
      h_NClusters[ien]->GetXaxis()->SetTitle("NClusters");
      h_NClusters[ien]->GetYaxis()->SetTitle("Entries");
      sprintf(hname1,"No_ofRechits_TrueEn_%d_to_%d",Elist[ien],Elist[ien]+4);
      h_NRechits[ien] = new TH1F(hname1,"Total number of rechits per event",600,0,3000);
      h_NRechits[ien]->GetXaxis()->SetTitle("NRechits");
      h_NRechits[ien]->GetYaxis()->SetTitle("Entries");
      sprintf(hname1,"NRechits_vsNClusters_TrueEn_%d_to_%d",Elist[ien],Elist[ien]+4);
      h_NRechitsVsNClusters[ien] = new TH2F(hname1,"NRechits vs NClusters",600,0,3000,600,0,3000);
      h_NRechitsVsNClusters[ien]->GetXaxis()->SetTitle("NRechits");
      h_NRechitsVsNClusters[ien]->GetYaxis()->SetTitle("NClusters");

      sprintf(hname1,"NRechits_beforeVsAfter_TrueEn_%d_to_%d",Elist[ien],Elist[ien]+4);
      h_Nrechits_beforeVsAfter[ien] = new TH2F(hname1,"NRechits_orig vs NClusters_wCLUE",600,0,3000,600,0,3000);
      h_Nrechits_beforeVsAfter[ien]->GetXaxis()->SetTitle("NRechits_orig");
      h_Nrechits_beforeVsAfter[ien]->GetYaxis()->SetTitle("NClusters_wCLUE");

      sprintf(hname1,"totalClustEn_vsTotalFixEn_TrueEn_%d_to_%d",Elist[ien],Elist[ien]+4);      
      h_totalClustEn_vsTotalFixEn[ien] = new TH2F(hname1,"totalClustEn vs TotalrawEn",500,0,500,500,0,500);
      h_totalClustEn_vsTotalFixEn[ien]->GetXaxis()->SetTitle("Total raw energy (E_{fix})");
      h_totalClustEn_vsTotalFixEn[ien]->GetYaxis()->SetTitle("Total clustered energy (E_{Clus})");
      
      sprintf(hname1,"totalClustEn_TrueEn_%d_to_%d",Elist[ien],Elist[ien]+4);
      h_totalEnClustered[ien] = new TH1F(hname1,"total energy clustered using CLUE",500,0,500);
      h_totalEnClustered[ien]->GetXaxis()->SetTitle("E_{Clus}");
      h_totalEnClustered[ien]->GetYaxis()->SetTitle("Entries");

      for(int il=0;il<50;il++)
	{
	  sprintf(hname,"Layer_%d",il+1);

	  sprintf(hname1,"h_Clusters_X_TrueEn_%d_to_%d_layer_%d",Elist[ien],Elist[ien]+4,il+1);
	  h_Clusters_X[ien][il] = new TH1F(hname1,hname,200,-40,40);
	  h_Clusters_X[ien][il]->GetXaxis()->SetTitle("Clusters_X");
	  h_Clusters_X[ien][il]->GetYaxis()->SetTitle("Entries");

	  sprintf(hname1,"h_Clusters_Y_TrueEn_%d_to_%d_layer_%d",Elist[ien],Elist[ien]+4,il+1);
          h_Clusters_Y[ien][il] = new TH1F(hname1,hname,200,-40,40);
          h_Clusters_Y[ien][il]->GetXaxis()->SetTitle("Clusters_Y");
          h_Clusters_Y[ien][il]->GetYaxis()->SetTitle("Entries");

	  sprintf(hname1,"h_Clusters_Z_TrueEn_%d_to_%d_layer_%d",Elist[ien],Elist[ien]+4,il+1);
          h_Clusters_Z[ien][il] = new TH1F(hname1,hname,200,10,300);
          h_Clusters_Z[ien][il]->GetXaxis()->SetTitle("Clusters_Z");
          h_Clusters_Z[ien][il]->GetYaxis()->SetTitle("Entries");

	  sprintf(hname1,"h_Clusters_En_TrueEn_%d_to_%d_layer_%d",Elist[ien],Elist[ien]+4,il+1);
          h_Clusters_En[ien][il] = new TH1F(hname1,hname,500,0,500);
          h_Clusters_En[ien][il]->GetXaxis()->SetTitle("Clusters_En");
          h_Clusters_En[ien][il]->GetYaxis()->SetTitle("Entries");

	  sprintf(hname1,"h_Clusters_EnvsZ_TrueEn_%d_to_%d_layer_%d",Elist[ien],Elist[ien]+4,il+1);
	  h_Clusters_EnvsZ[ien][il] = new TH2F(hname1,hname,200,10,300,500,0,500);
	  h_Clusters_EnvsZ[ien][il]->GetXaxis()->SetTitle("Cluster Energy");
	  h_Clusters_EnvsZ[ien][il]->GetYaxis()->SetTitle("Clusters Z");

	  sprintf(hname1,"h_Clusters_XvsY_TrueEn_%d_to_%d_layer_%d",Elist[ien],Elist[ien]+4,il+1);
          h_Clusters_XvsY[ien][il] = new TH2F(hname1,hname,200,10,300,500,0,500);
          h_Clusters_XvsY[ien][il]->GetXaxis()->SetTitle("Cluster X");
          h_Clusters_XvsY[ien][il]->GetYaxis()->SetTitle("Clusters Y");

	  sprintf(hname1,"NRechitsVsNClusters_TrueEn_%d_to_%d_layer_%d",Elist[ien],Elist[ien]+4,il+1);
	  h_NRechitsVsNClusters_perLayer[ien][il] = new TH2F(hname1,hname,500,0,1000,500,0,1000);
	  h_NRechitsVsNClusters_perLayer[ien][il]->GetXaxis()->SetTitle("NRechits");
	  h_NRechitsVsNClusters_perLayer[ien][il]->GetYaxis()->SetTitle("NClusters");

	  sprintf(hname1,"h_NClusters_TrueEn_%d_to_%d_layer_%d",Elist[ien],Elist[ien]+4,il+1);
	  sprintf(hname,"Layer_%d",il+1);
	  h_NClusters_perLayer[ien][il] = new TH1F(hname1,hname,500,0,1000);
	  h_NClusters_perLayer[ien][il]->GetXaxis()->SetTitle("NCluster");
          h_NClusters_perLayer[ien][il]->GetYaxis()->SetTitle("Entries");

	  sprintf(hname1,"h_Nrechits_TrueEn_%d_to_%d_layer_%d",Elist[ien],Elist[ien]+4,il+1);
          sprintf(hname,"Layer_%d",il+1);
          h_Nrechits_perClusters[ien][il] = new TH1F(hname1,hname,500,0,1000);
          h_Nrechits_perClusters[ien][il]->GetXaxis()->SetTitle("Nrechit");
          h_Nrechits_perClusters[ien][il]->GetYaxis()->SetTitle("Entries");

	  sprintf(hname1,"h_rho_rechit_TrueEn_%d_to_%d_layer_%d",Elist[ien],Elist[ien]+4,il+1);
          sprintf(hname,"Layer_%d",il+1);
          h_rechits_rho[ien][il] = new TH1F(hname1,hname,500,0,1000);
          h_rechits_rho[ien][il]->GetXaxis()->SetTitle("rho");
          h_rechits_rho[ien][il]->GetYaxis()->SetTitle("Entries");

	  sprintf(hname1,"h_delta_rechit_TrueEn_%d_to_%d_layer_%d",Elist[ien],Elist[ien]+4,il+1);
          sprintf(hname,"Layer_%d",il+1);
          h_rechits_delta[ien][il] = new TH1F(hname1,hname,500,-50,50);
          h_rechits_delta[ien][il]->GetXaxis()->SetTitle("delta");
          h_rechits_delta[ien][il]->GetYaxis()->SetTitle("Entries");
	}
    }
}

void AnalyzeHGCOctTB::Alignment_Map_Init() {
  /// Alignment map for config 1, it needs to be changed accorfing to
  /// configurations

  char *f_name = new char[200];
  sprintf(f_name, "./config_maps/Alignment_Map.txt");
  std::ifstream in(f_name);
  // int layer;
  if (!in) {
    cout << "ERROR => " << f_name << " Not found" << endl;
    // return;
    exit(0);
  }

  std::pair<float, float> dx_dy;
  std::pair<int, std::pair<float, float>> temp;
  int layer;
  float dx, dy;
  while (in >> layer >> dx >> dy) {
    // run_layer = std::make_pair(run,layer);
    dx_dy = std::make_pair(dx, dy);
    temp = std::make_pair(layer, dx_dy);
    align_map.insert(temp);
  }

  std::cout << "INFO: Alignment MAP initialized successfully!!!" << endl;
}

void AnalyzeHGCOctTB::Noise_Map_Init() {
  // Noise map for config - 1 , needs to be changed accordingly

  char *f_name = new char[200];
  sprintf(f_name, "./config_maps/Noise_Map.txt");
  std::ifstream in(f_name);

  if (!in) {
    cout << "ERROR => " << f_name << " Not found" << endl;
    exit(0);
  }
  std::pair<int, int> mod_chip;
  std::pair<std::pair<int, int>, float> temp;
  int layer, mod_id, mod_pos, chip;
  float noise;
  while (in >> layer >> mod_id >> mod_pos >> chip >> noise) {
    mod_chip = std::make_pair(mod_id, chip);
    temp = std::make_pair(mod_chip, noise);
    noise_map.insert(temp);
  }

  std::cout << "INFO: Noise MAP initialized successfully!!!" << endl;
}

void AnalyzeHGCOctTB::moduleMap_init(const char *config) {
  char *f_name = new char[200];

  if (strcmp(config, "alpha") == 0 || strcmp(config, "config1") == 0) {
    sprintf(f_name, "./config_maps/moduleMAP_config1.txt");
    cout << "\n\nINFO: Mapping module configuration ALPHA (oct10-oct17) "
         << endl;
    cout << "INFO: Mapping EE[0]/FH[1]::Layer #[1-40]::Position on Layer[0 for "
            "EE]&[1-7 for FH] consult figure for Daisy structure "
            "configuration!!!"
         << endl;

  } else if (strcmp(config, "bravo") == 0 || strcmp(config, "config2") == 0) {
    sprintf(f_name, "./config_maps/moduleMAP_config2.txt");
    cout << "\n\nINFO: Mapping module configuration BRAVO (17oct-22oct) "
         << endl;
    cout << "INFO: Mapping EE[0]/FH[1]::Layer #[1-40]::Position on Layer[0 for "
            "EE]&[1-7 for FH] consult figure for Daisy structure "
            "configuration!!!"
         << endl;

  } else if (strcmp(config, "charlie") == 0 || strcmp(config, "config3") == 0) {
    sprintf(f_name, "./config_maps/moduleMAP_config3.txt");
    cout << "\n\nINFO: Mapping module configuration CHARLIE (23Oct-4Nov) "
         << endl;
    cout << "INFO: Mapping EE[0]/FH[1]::Layer #[1-40]::Position on Layer[0 for "
            "EE]&[1-7 for FH] consult figure for Daisy structure "
            "configuration!!!"
         << endl;

  } else {
    cout << "\n\nERROR: Incorrect configuration entered " << endl;
    cout << " Allowed configuration :\n alpha = Configuration 1 (10Oct-17Nov) "
            "\n bravo = Configuration 2 (17Oct-22Oct) \n charlie = "
            "Configuration 3 (23Oct-17Nov)"
         << endl;
    return;
  }

  std::ifstream in(f_name);
  if (!in) {
    cout << "ERROR => " << f_name << " Not found" << endl;
    // return;
    exit(0);
  }

  int modID_, part_, layer_, pos_;
  cout << "File name = " << f_name << endl;
  while (in >> modID_ >> part_ >> layer_ >> pos_) {
    std::pair<int, std::vector<int>> temp_pair;
    std::vector<int> temp_vector;
    temp_vector.push_back(part_);
    temp_vector.push_back(layer_);
    temp_vector.push_back(pos_);
    temp_pair = std::make_pair(modID_, temp_vector);
    module_map.insert(temp_pair);
  }

  cout << "INFO: Module Mapping Done!!! " << endl << endl;
}

void AnalyzeHGCOctTB::layerPosition_init() {
  // Layer postions for config - 1, needs to be changed accordingly for other
  // configs

  char *f_name = new char[200];
  sprintf(f_name, "./config_maps/config1_lengths.txt");

  std::ifstream in(f_name);
  if (!in) {
    cout << "ERROR => " << f_name << " Not found" << endl;
    exit(0);
  }
  int layer_;
  float cm_, x0, nuc_int_, pi_int_;

  cout << "File name = " << f_name << endl;
  while (in >> layer_ >> cm_ >> x0 >> nuc_int_ >> pi_int_) {
    std::pair<int, std::vector<float>> temp_pair;
    std::vector<float> temp_vector;
    temp_vector.push_back(cm_ / 10.0);
    temp_vector.push_back(x0);
    temp_vector.push_back(nuc_int_);
    temp_vector.push_back(pi_int_);

    temp_pair = std::make_pair(layer_, temp_vector);
    layer_positions.insert(temp_pair);
  }

  cout << "INFO: Layer Position Mapping Done!!! " << endl << endl;
  if (0) {
    for (const auto &kv : layer_positions) {
      std::cout << "Layer " << kv.first << " is at position " << kv.second[0]
                << std::endl;
    }
  }
}

AnalyzeHGCOctTB::AnalyzeHGCOctTB(
    const TString &inputFileList, const char *outFileName, const char *dataset,
    const char *config,
    const char *energy) {  //,const char* min_, const char* max_) {

  TChain *tree = new TChain("pion_variables_v1");
  // TChain *tree2 = new TChain("trackimpactntupler/impactPoints");
  // TChain *tree3 = new TChain("bigtree");

  if (!FillChain(tree, inputFileList)) {
    std::cerr << "Cannot get the tree " << std::endl;
  } else {
    std::cout << "Initiating analysis of dataset " << dataset << std::endl;
  }

  int chi2_method = atoi(energy);
  HGCNtupleVariables::Init(tree);  //, tree2, tree3);
  //  HGCNtupleVariables::init_piTree();
  BookHistogram(outFileName, config, energy);
  moduleMap_init(config);
  Alignment_Map_Init();
  Noise_Map_Init();
  layerPosition_init();
  Chi2_Weight_Map_Init(chi2_method);
}
void AnalyzeHGCOctTB::Chi2_Weight_Map_Init(int chi2_method) {
  char *f_name_EH = new char[2000];
  char *f_name_H = new char[2000];
  char *method = new char[2000];
  bool UseSimWeights = false;

  // switch (chi2_method) {
  //   case 0:
  //     sprintf(method, "%d : rechit energy sum as input to chi2", chi2_method);
  //     break;
  //   case 1:
  //     sprintf(
  //         method,
  //         "%d : detector scale with No offset for H hadrons as input to chi2",
  //         chi2_method);
  //     break;
  //   case 2:
  //     sprintf(method,
  //             "%d : detector scale with offset (0.4 GeV) for H hadrons as "
  //             "input to chi2",
  //             chi2_method);
  //     break;
  //   case 3:
  //     sprintf(method,
  //             "%d : detector scale with offset (0.4 GeV) for H hadrons AND "
  //             "events around the core of beam energy as input to chi2",
  //             chi2_method);
  //     break;
  //   default:
  //     cout << "Incorrect method input use between 0-3" << endl;
  //     exit(0);
  // }
  sprintf(f_name_EH,
          "./txt_maps/chi2_flatEn/sim/"
          "chi2_calibFact_EH_hadrons_flatEn_1_scalMC_2sigma.txt");//          chi2_method);
  sprintf(f_name_H,
          "./txt_maps/chi2_flatEn/sim/"
          "chi2_calibFact_EH_hadrons_flatEn_1_scalMC_2sigma.txt");//,
  //          chi2_method);

  std::ifstream in_EH(f_name_EH);
  std::ifstream in_H(f_name_H);
  if (!in_EH) {
    cout << "ERROR => " << f_name_EH << " Not found" << endl;
    // return;
    exit(0);
  }
  if (!in_H) {
    cout << "ERROR => " << f_name_H << " Not found" << endl;
    // return;
    exit(0);
  }
  int beamEnergy;
  float w1, w2, w3;

  cout << "File name = " << f_name_EH << endl;
  while (in_EH >> beamEnergy >> w1 >> w2 >> w3) {
    std::pair<int, std::vector<float>> temp_pair;
    std::vector<float> temp_vector;
    temp_vector.push_back(w1);
    temp_vector.push_back(w2);
    temp_vector.push_back(w3);

    temp_pair = std::make_pair(beamEnergy, temp_vector);
    chi2_weights_EH.insert(temp_pair);
  }
  cout << BOLDGREEN
       << "INFO: Chi2 calibration Map initialized for EH hadrons!! " << RESET
       << endl;
  beamEnergy = -1.0;
  w1 = -1.0;
  w2 = -1.0;
  w3 = -1.0;

  cout << "File name = " << f_name_H << endl;
  while (in_H >> beamEnergy >> w1 >> w2 >> w3) {
    std::pair<int, std::vector<float>> temp_pair;
    std::vector<float> temp_vector;
    temp_vector.push_back(w1);
    temp_vector.push_back(w2);
    temp_vector.push_back(w3);

    temp_pair = std::make_pair(beamEnergy, temp_vector);
    chi2_weights_H.insert(temp_pair);
  }
  cout << BOLDGREEN << "INFO: Chi2 calibration Map initialized for H hadrons!! "
       << RESET << endl
       << endl;

  cout << BOLDGREEN << "INFO: Chi2 minimization method used =>  " << method
       << RESET << endl
       << endl;
}

Bool_t AnalyzeHGCOctTB::FillChain(
    TChain *chain,
    const TString &inputFileList) {  // TChain *chain2, TChain *chain3, const
                                     // TString &inputFileList) {

  ifstream infile(inputFileList, ifstream::in);
  std::string buffer;

  if (!infile.is_open()) {
    std::cerr << "** ERROR: Can't open '" << inputFileList << "' for input"
              << std::endl;
    return kFALSE;
  }

  std::cout << "TreeUtilities : FillChain " << std::endl;
  while (1) {
    infile >> buffer;
    if (!infile.good()) break;
    // std::cout << "Adding tree from " << buffer.c_str() << std::endl;
    chain->Add(buffer.c_str());
    // chain2->Add(buffer.c_str());
    // chain3->Add(buffer.c_str());
  }
  std::cout << "No. of Entries in chain  : " << chain->GetEntries()
            << std::endl;
  // std::cout << "No. of Entries in chain2 : " << chain2->GetEntries() <<
  // std::endl; std::cout << "No. of Entries in chain3 : " <<
  // chain3->GetEntries() << std::endl;

  return kTRUE;
}

Long64_t AnalyzeHGCOctTB::LoadTree(Long64_t entry) {
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (!fChain->InheritsFrom(TChain::Class())) return centry;
  TChain *chain = (TChain *)fChain;
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

  // if (centry==centry2)
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
