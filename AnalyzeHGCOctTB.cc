#define AnalyzeHGCOctTB_cxx
#include "AnalyzeHGCOctTB.h"

#include <TF1.h>
#include <math.h>

#include <cstring>
#include <iostream>
#include <vector>

#include "CLUEAlgo.h"
#include "Math/SMatrix.h"
#include "Math/SVector.h"
#include <assert.h>
using namespace std;

// chip 3022,44,3028

void dumpSoA(const PointsCloud & points) {
  std::cout << "SoA DUMP" << std::endl;
  for (int c = 0 ; c < points.x.size(); ++c) {
    std::cout
      << "id " << c
      << " x = " << points.x[c]
      << " y = " << points.y[c]
      << " z = " << points.z[c]
      << " layer = " << points.layer[c]
      << " energy = " << points.weight[c]
      << " rho = " << points.rho[c]
      << " delta = " << points.delta[c]
      << " isSeed = " << points.isSeed[c]
      << " clusterIdx = " << points.clusterIndex[c]
      << " nearestHigher = " << points.nearestHigher[c]
      << std::endl;
  }
}

int main(int argc, char *argv[])  //, int argvv[])
{
  if (argc < 5) {
    cerr << "Please give 5 arguments "
         << "runList "
         << " "
         << "outputFileName"
         << " "
         << "dataset"
         << " "
         << "configuration"
         << " "
         << "energy" << endl;
    return -1;
  }
  const char *inputFileList = argv[1];
  const char *outFileName = argv[2];
  const char *data = argv[3];
  const char *config = argv[4];
  const char *energy = argv[5];
  AnalyzeHGCOctTB hgcOctTB(inputFileList, outFileName, data, config, energy);
  cout << "dataset " << data << " " << endl;
  cout << "configuration " << config << " " << endl;
  cout << "energy  " << energy << " " << endl;
  // int chi2_method = atoi(energy);
  hgcOctTB.EventLoop(data, energy);
  return 0;
}

void AnalyzeHGCOctTB::EventLoop(const char *data, const char *energy) {

  bool NTUPLEOUT = false;
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();
  // Long64_t nentries3 = fChain3->GetEntriesFast();
  Long64_t hgc_jentry = 0;

  cout << "nentries " << nentries << endl;
  cout << "Analyzing dataset " << data << " " << endl;

  Long64_t nbytes = 0, nb = 0;
  Long64_t nbytes2 = 0, nb2 = 0;
  Long64_t nbytes3 = 0, nb3 = 0;

  int decade = 0;
  int ahc_zeroHit = 0;

  bool DEBUG = false;
  //  bool DEBUG = true;
  int TOTAL_ACTIVE_LAYER = -1;
  int EE_LAYER = -1;
  int FH_LAYER = -1;
  int AH_LAYER = -1;
  if (!strcmp(conf_, "alpha") || !strcmp(conf_, "config1")) {
    TOTAL_ACTIVE_LAYER = 79;
    EE_LAYER = 28;
    FH_LAYER = 12;
    AH_LAYER = 39;
  } else if (!strcmp(conf_, "bravo") || !strcmp(conf_, "config2")) {
    TOTAL_ACTIVE_LAYER = 78;
    EE_LAYER = 28;
    FH_LAYER = 11;
    AH_LAYER = 39;
  } else if (!strcmp(conf_, "charlie") || !strcmp(conf_, "config3")) {
    TOTAL_ACTIVE_LAYER = 59;
    EE_LAYER = 8;
    FH_LAYER = 12;
    AH_LAYER = 39;

  } else {
    cout << "ERROR: Unknown configuration!!!!" << endl;
    return;
  }

  // counter
  int nHgc = 0, nAhc = 0, nrechits = 0;
  float offset = 159.4;  // A constant to be added to AHC layer z positions
  // cout<<energy<<endl;
  float FH_AH_relative_scale = 0.4;
  float alpha_ = FH_AH_relative_scale;
  float EE_scale = 94.624;     // MIPs per Ge
  float FH_AH_scale = 12.788;  // MIPs per GeV
  float ee_rescaling = 1.035;
  float fh_rescaling = 1.095;
  float ah_rescaling = 1.095;
  if (!strcmp(data, "data")) {
    ee_rescaling = 1;
    fh_rescaling = 1;
    ah_rescaling = 1;
  }
  cout << data << " rescaling"
       << "\t" << ee_rescaling << "\t" << fh_rescaling << "\t" << ah_rescaling
       << endl;

  int Elist[85] = {
      10,  14,  18,  22,  26,  30,  34,  38,  42,  46,  50,  54,  58,  62,  66,
      70,  74,  78,  82,  86,  90,  94,  98,  102, 106, 110, 114, 118, 122, 126,
      130, 134, 138, 142, 146, 150, 154, 158, 162, 166, 170, 174, 178, 182, 186,
      190, 194, 198, 202, 206, 210, 214, 218, 222, 226, 230, 234, 238, 242, 246,
      250, 254, 258, 262, 266, 270, 274, 278, 282, 286, 290, 294, 298, 302, 306,
      310, 314, 318, 322, 326, 330, 334, 338, 342, 346};

  float comb_z_boundaries[50] = {14., 15., 17., 18., 20., 21., 23., 24.,
    26.,  27.,  29.,   30., 32.,   33., 35.,  36.,  37.5, 38.5,
    40.5, 41., 43.5,  44.5, 47.,   48., 50.,  51.,   53., 54.5,
    65.,  72.,  79.,   86., 92.,   99., 116., 124., 132., 140.,
    146., 154., 170., 180., 190., 200., 210., 220., 232., 242.,
    252., 262.};


  // to select the evnts within 2sigma region

  if (DEBUG) cout << "DEBUG: Configuration = " << conf_ << endl;
  if (DEBUG)
    cout << "DEBUG: TOTAL_ACTIVE_LAYER = " << TOTAL_ACTIVE_LAYER << endl;
  if (DEBUG) cout << "DEBUG: EE_LAYER = " << EE_LAYER << endl;
  if (DEBUG) cout << "DEBUG: FH_LAYER = " << FH_LAYER << endl;
  if (DEBUG) cout << "DEBUG: AH_LAYER = " << AH_LAYER << endl;

  if (DEBUG) cout << "DEBUG: Entering event Loop" << endl;

  Long64_t jentry;

  float lambda[79];
  for (int i = 0; i < 79; i++) {
    lambda[i] = layer_positions[i + 1].at(
        2);  // for nuclear interaction length  & //pi_lambda use -at(3)
    //     cout<<lambda[i]<<endl;
  }
  int ahcal_layer[10] = {43, 47, 51, 55, 59, 63,
                         67, 71, 75, 79};  // selected layers (10 in total) out
                                           // of AHCAL (39 in total)
  char outfile[200];
  sprintf(outfile,"TrueEn_Clue_Clusters_Skimmed_FTFP_%s_33mBeamLine_combinedHgc_Ahc_v46_%dM.root",data,atoi(energy));
  cout<<"creating out file with name"<<"\t"<<outfile<<endl;
  //  TFile *f = new TFile(outfile,"RECREATE");
  TTree clusters_tree("clusters", "clusters");
  // Create a unique PointsCloud object and (re)-use it to fill the output
  // ntuple.
  PointsCloud pcloud;

  // Create a SoA for the output clusters
  ClustersSoA clusters_soa;

  float Esum_allRecHits_inGeV;

  // Create the branches in the output ntuple.
  Float_t beam_Energy;
  Float_t trueBeamEnergy;
  Int_t Event;
  Int_t SSlocation;
  vector<float> *pi_rechitEn_trimAhcal;
  vector<float> *pi_comb_rechit_x_trimAhcal;
  vector<float> *pi_comb_rechit_y_trimAhcal;
  vector<float> *pi_comb_rechit_z_trimAhcal;

  // clusters_tree.Branch("rechits_x", &pcloud.x);
  // clusters_tree.Branch("rechits_y", &pcloud.y);
  // clusters_tree.Branch("rechits_z", &pcloud.z);
  // clusters_tree.Branch("rechits_energy", &pcloud.weight);
  // clusters_tree.Branch("rechits_layer", &pcloud.layer);
  // clusters_tree.Branch("rechits_rho", &pcloud.rho);
  // clusters_tree.Branch("rechits_delta", &pcloud.delta);
  // clusters_tree.Branch("rechits_clusterIndex", &pcloud.clusterIndex);
  // clusters_tree.Branch("all_rechits_energy", &Esum_allRecHits_inGeV, "all_rechits_energy/F");
  // clusters_tree.Branch("clusters_x", &clusters_soa.x);
  // clusters_tree.Branch("clusters_y", &clusters_soa.y);
  // clusters_tree.Branch("clusters_z", &clusters_soa.z);
  // clusters_tree.Branch("clusters_energy", &clusters_soa.energy);
  // clusters_tree.Branch("clusters_layer", &clusters_soa.layer);
  // clusters_tree.Branch("clusters_size", &clusters_soa.size);
  clusters_tree.Branch("trueBeamEnergy",&trueBeamEnergy);
  clusters_tree.Branch("beamEnergy",&beam_Energy);
  // clusters_tree.Branch("rechit_shower_start_layer",&SSlocation);
  clusters_tree.Branch("event",&Event);
  // clusters_tree.Branch("rechitEn_trimAhcal",&pi_rechitEn_trimAhcal);
  // clusters_tree.Branch("comb_rechit_x_trimAhcal",&pi_comb_rechit_x_trimAhcal);
  // clusters_tree.Branch("comb_rechit_y_trimAhcal",&pi_comb_rechit_y_trimAhcal);
  // clusters_tree.Branch("comb_rechit_z_trimAhcal",&pi_comb_rechit_z_trimAhcal);
  if(DEBUG)  
    nentries = 1;    
  // event, rechit trim Ahcal information, SS layer,
  for (jentry = 0; jentry < nentries; jentry++, hgc_jentry++) {

    // Reset PointsCloud
    pcloud.reset();

    // ==============print number of events done == == == == == == == =
    double progress = 10.0 * jentry / (1.0 * nentries);
    int k = int(progress);
    if (k > decade) cout << 10 * k << " %" << endl;
    decade = k;

    // ===============read this entry == == == == == == == == == == ==

    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) {
      break;
      cout << "Breaking" << endl;
    }
    nb = fChain->GetEntry(jentry);
    nbytes += nb;
    // cout<<"insides the event loop: check1"<<endl;

    ////   MESSAGE ////
    // apparently code is not running beyond this point ///
    event_count[0]++;
    Event=0;
    event_count[1]++;
    h_true_beamenergy[4]->Fill(trueBeamEnergy);
    // if (strcmp(data, "data"))
    //   trueBeamEnergy = beamEnergy;
    totalEnergy_inGeV = 0;
    EnergySum_SSinEE = 0;
    EnergySum_SSinFH = 0;
    Esum_rechits_FH = 0;
    Esum_rechits_EE = 0;
    Esum_rechits_AH = 0;
    Esum_rechits_FH_inGeV = 0;
    Esum_rechits_EE_inGeV = 0;
    trueBeamEnergy=0;
    Esum_rechits_AH_inGeV = 0;
    
    ////////////////////////////////////////////
    //            HGCAL Part                  //
    ////////////////////////////////////////////
    trueBeamEnergy = trueBeamEnergy;
    beam_Energy = beamEnergy;
    Event = event;
    // SSlocation = rechit_shower_start_layer;
    // pi_rechitEn_trimAhcal = rechitEn_trimAhcal;
    // pi_comb_rechit_x_trimAhcal=comb_rechit_x_trimAhcal;
    // pi_comb_rechit_y_trimAhcal=comb_rechit_y_trimAhcal;
    // pi_comb_rechit_z_trimAhcal=comb_rechit_z_trimAhcal;
    
    total_rechits = 0;
    rechits_EE = 0;
    rechits_FH = 0;
    rechits_AH = 0;
    int nrechit_trimAhcal = 0;
    /// Read HGCAL + AHCAL (only 10 layers out of 39) combined Tree
    if (DEBUG) cout << "DEBUG: Start Analylizing HGCAL  RecHits!!" << endl;
    float rechitEnergySum_AH = 0.0;
    for (int i = 0; i < rechitEn_trimAhcal->size(); i++) {
      float energy = rechitEn_trimAhcal->at(i);
      if (comb_rechit_z_trimAhcal->at(i) < 54)  // selecting EE rechits
      {
        Esum_rechits_EE += (energy / ee_rescaling);
        rechits_EE++;
      } else if ((comb_rechit_z_trimAhcal->at(i) > 54) &&
                 (comb_rechit_z_trimAhcal->at(i) <
                  154))  // Selecting FH rechits
      {
        Esum_rechits_FH += (energy / fh_rescaling);
      } else if (comb_rechit_z_trimAhcal->at(i) > 154)  // selecting AH rechits
      {
        rechitEnergySum_AH += (energy / ah_rescaling);
      }
    }  // Nrechits loop

    float trueBeamEnergyy = trueBeamEnergy;
    if (!strcmp(data, "data"))
      trueBeamEnergy = beam_Energy;

    h_true_beamenergy[5]->Fill(trueBeamEnergy);
    nrechit_trimAhcal = 0;
    rechits_AH = nAhc;
    total_rechits = nrechits;
    // convert the energy into GeV using detector level calibration
    Esum_rechits_EE_inGeV = 0.0105 * Esum_rechits_EE;
    Esum_rechits_FH_inGeV = 0.0812 * Esum_rechits_FH;  // updated relative
                                                       // weight
    Esum_rechits_AH_inGeV = 0.12508 * rechitEnergySum_AH;
    Esum_allRecHits_inGeV =
        Esum_rechits_AH_inGeV + Esum_rechits_FH_inGeV + Esum_rechits_EE_inGeV;
    if (DEBUG) cout << "DEBUG: End of Entry = " << jentry << endl;
    if (DEBUG) cout << "DEBUG: ****************** " << endl;
    //      cout<<"\t"<<"beforE"<<endl;

    // Compute clusters using CLUE
    std::array<LayerTiles, NLAYERS> tiles;
    constexpr float MIP2GeV[3] = {0.0105, 0.0812, 0.12508};
    constexpr float dc[2] = {1.3f, 3.f * sqrt(2.f) + 0.1};
    constexpr float rhoc[2] = {4.f * MIP2GeV[0], 4.f * MIP2GeV[2]};
    constexpr float outlierDeltaFactor = 2.f;
    pcloud.x = *comb_rechit_x_trimAhcal;
    pcloud.y = *comb_rechit_y_trimAhcal;
    pcloud.z = *comb_rechit_z_trimAhcal;
    pcloud.weight = *rechitEn_trimAhcal;
    updateLayersAndEnergies(pcloud, comb_z_boundaries, MIP2GeV);
    //    pcloud.layer = *rechit_layer;
    pcloud.resizeOutputContainers(comb_rechit_x_trimAhcal->size());
    compute_histogram(tiles, pcloud);
    calculate_density(tiles, pcloud, dc);
    calculate_distanceToHigher(tiles, pcloud, outlierDeltaFactor, dc);
    auto total_clusters = findAndAssign_clusters(pcloud, outlierDeltaFactor, dc, rhoc);
    auto clusters = getClusters(total_clusters, pcloud);
    
    // Fill in the clusters_SoA
    clusters_soa.load(clusters);
    //    clusters_tree.Fill();
    if (DEBUG) {
      dumpSoA(pcloud);
    }

    float total_energy_clustered = 0.f;
    for (auto const & cl : clusters) {
      auto pos = cl.position();
      if (DEBUG) {
        std::cout << std::get<0>(pos) << " "
          << std::get<1>(pos) << " "
          << std::get<2>(pos) << " "
          << cl.energy() << " "
          << std::endl;
      }
      total_energy_clustered += cl.energy();
    }
    int Cluster_Count[51]={};
    int total_Rechits=0;
    int total_RechitsLay[51]={};
    for (int ien=0;ien<85;ien++)
      {
	//if()
	//cout<<jentr<<"\t"<<"inside energy loop"<<trueBeamEnergy<<"\t"<<data<<endl;
	if(trueBeamEnergy>=Elist[ien] && trueBeamEnergy<Elist[ien]+4)
          {
            h_totalEnClustered[ien]->Fill(total_energy_clustered);
	    h_totalClustEn_vsTotalFixEn[ien]->Fill(Esum_allRecHits_inGeV,total_energy_clustered);
	    h_NClusters[ien]->Fill(total_clusters);
	    //cout<<jentry<<"\t"<<"inside energy loop"<<trueBeamEnergy<<endl;

	    for (auto const & cl : clusters) {
	      auto pos = cl.position();
	      h_Clusters_X[ien][cl.layer()]->Fill(std::get<0>(pos));
	      h_Clusters_Y[ien][cl.layer()]->Fill(std::get<1>(pos));
	      h_Clusters_Z[ien][cl.layer()]->Fill(std::get<2>(pos));
	      h_Clusters_En[ien][cl.layer()]->Fill(cl.energy());
	      h_Clusters_EnvsZ[ien][cl.layer()]->Fill(std::get<2>(pos),cl.energy());
	      h_Clusters_XvsY[ien][cl.layer()]->Fill(std::get<0>(pos),std::get<1>(pos));	      
	      h_Nrechits_perClusters[ien][cl.layer()]->Fill(cl.hits().size());
	      Cluster_Count[cl.layer()]++;
	      total_RechitsLay[cl.layer()]+=cl.hits().size();
	      total_Rechits+=cl.hits().size();
	    }

	    for (unsigned int j=1;j<51;j++)
	      {
		h_NClusters_perLayer[ien][j-1]->Fill(Cluster_Count[j]);
		h_NRechitsVsNClusters_perLayer[ien][j-1]->Fill(total_RechitsLay[j],Cluster_Count[j]);
	      }
	    for (unsigned int i = 0; i < pcloud.n; i++) {
	      h_rechits_rho[ien][pcloud.layer[i]]->Fill(pcloud.rho[i]);
	      h_rechits_delta[ien][pcloud.layer[i]]->Fill(pcloud.delta[i]);	      
	    }
	    h_Nrechits_beforeVsAfter[ien]->Fill(pcloud.n,total_Rechits);
	    h_NRechits[ien]->Fill(pcloud.n);
	    h_NRechitsVsNClusters[ien]->Fill(pcloud.n,total_clusters);
	    
	    
          }
      }

    if (DEBUG) {
      std::cout << "Event count " << event_count[0]
                << " True energy: " << trueBeamEnergy
                << " Sum(RecHits_energy): " << Esum_allRecHits_inGeV
                << " Ratio: " << Esum_allRecHits_inGeV / trueBeamEnergy
                << " Clustered Energy: " << total_energy_clustered
                << " Ratio: " << total_energy_clustered / Esum_allRecHits_inGeV
                << " Total number of clusters: " << total_clusters
                << std::endl;
    }

    if (NTUPLEOUT) {
      std::cout << event_count[0]
                << "," << trueBeamEnergy
                << "," << Esum_allRecHits_inGeV
                << "," << Esum_allRecHits_inGeV / trueBeamEnergy
                << "," << total_energy_clustered
                << "," << total_energy_clustered / Esum_allRecHits_inGeV
                << "," << total_clusters
                << std::endl;
    }
  }  // loop over entries
  // f->cd();
  // clusters_tree.Write();

  ///////////////////////////////////////////////////////////
  ///////  E N D     O F     E N T R Y     L O O P     //////
  ///////////////////////////////////////////////////////////
  //  gSystem->Exit(0);
  cout << "Got Out " << jentry << endl;
  //  f->Write();
}
