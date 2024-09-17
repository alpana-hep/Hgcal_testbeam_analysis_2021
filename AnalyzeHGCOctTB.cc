//./analyzeHGCOctTB  file.txt out_tempTest.root sim alpha 20
#define AnalyzeHGCOctTB_cxx
#include <iostream>
#include <vector>
#include <cstring>
#include "AnalyzeHGCOctTB.h"
#include "Math/SMatrix.h"
#include "Math/SVector.h"
#include <math.h>
#include<TF1.h>
using namespace std;

// chip 3022,44,3028
int main(int argc, char* argv[])
{

  if (argc < 6) {
    cerr << "Please give 5 arguments " << "runList " << " " << "outputFileName" << " " << "dataset" <<" " << "configuration" 
	 <<" " << "energy" << endl;
    return -1;
  }
  const char *inputFileList = argv[1];
  const char *outFileName   = argv[2];
  const char *data          = argv[3];
  const char *config          = argv[4];
  const char *energy = argv[5];
  AnalyzeHGCOctTB hgcOctTB(inputFileList, outFileName, data, config, energy);
  cout << "dataset " << data << " " << endl;
  cout << "configuration " << config << " " << endl;
  cout << "energy " << energy << " " << endl;

  hgcOctTB.EventLoop(data,energy);
  return 0;
}

void AnalyzeHGCOctTB::EventLoop(const char *data, const char *energy) {
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();
  //Long64_t nentries3 = fChain3->GetEntriesFast();
  Long64_t hgc_jentry = 0;

  cout << "nentries " << nentries << endl;
  cout << "Analyzing dataset " << data << " " << endl;

  Long64_t nbytes = 0, nb = 0;
  Long64_t nbytes2 = 0, nb2 = 0;
  Long64_t nbytes3 = 0, nb3 = 0;

  

  int decade = 0;
  int ahc_zeroHit = 0;
 float offset = 159.4; 
  //additional variable
  Long64_t hadronic_int = 0;
  Long64_t hard_hadronic_int = 0;
  Long64_t notFound_hadronic_int = 0;

 int Elist[8] ={20,50,80,100,120,200,250,300};


  bool DEBUG = false;
  //  bool DEBUG = true;
  int TOTAL_ACTIVE_LAYER = -1;
  int EE_LAYER = -1;
  int FH_LAYER = -1;
  int AH_LAYER = -1;
  if(!strcmp(conf_,"alpha") || !strcmp(conf_,"config1")) {
    TOTAL_ACTIVE_LAYER = 79;
    EE_LAYER = 28;
    FH_LAYER = 12;
    AH_LAYER = 39;
  }
  else if(!strcmp(conf_,"bravo") || !strcmp(conf_,"config2")){
    TOTAL_ACTIVE_LAYER = 78;
    EE_LAYER = 28;
    FH_LAYER = 11;
    AH_LAYER = 39;
  }
  else if(!strcmp(conf_,"charlie") || !strcmp(conf_,"config3")) {
    TOTAL_ACTIVE_LAYER = 59;
    EE_LAYER = 8;
    FH_LAYER = 12;
    AH_LAYER = 39;
    
  }
  else {
    cout<<"ERROR: Unknown configuration!!!!"<<endl;
    return;
  }

  //counter
  int nHgc=0, nAhc=0;
  //cout<<energy<<endl;
  char* outFileName = new char[1000];
  sprintf(outFileName,"./skimmed_ntuple_sim_config22_pionAll8Points_combinedHgc_Ahc_v46_patchMIP.root");//skimmed_ntuple_sim_config22_pion%sGeV_combinedHgc_Ahc_v46_patchMIP.root",energy);
  TFile* outfile = TFile::Open(outFileName,"recreate");
  //TTree* pion_tree;
  pion_tree = new TTree("pion_variables_v1","variables for pion analysis v1");
  HGCNtupleVariables::init_piTree();

  
  if(DEBUG) cout<<"DEBUG: Configuration = "<<conf_<<endl;
  if(DEBUG) cout<<"DEBUG: TOTAL_ACTIVE_LAYER = "<<TOTAL_ACTIVE_LAYER<<endl;
  if(DEBUG) cout<<"DEBUG: EE_LAYER = "<<EE_LAYER<<endl;
  if(DEBUG) cout<<"DEBUG: FH_LAYER = "<<FH_LAYER<<endl;
  if(DEBUG) cout<<"DEBUG: AH_LAYER = "<<AH_LAYER<<endl;

  if(DEBUG) cout<<"DEBUG: Entering event Loop"<<endl;
  int counter=0;
  Long64_t jentry;
  //      nentries=10000;
  int ahcal_layer[10]= {43,47,51,55,59,63,67,71,75,79}; 
  for (jentry=0; jentry<nentries;jentry++,hgc_jentry++)
  {
  //  for (jentry=0; jentry<1;jentry++,hgc_jentry++) {
      // ==============print number of events done == == == == == == == =
      double progress = 5.0 * jentry / (1.0 * nentries);
      int k = int (progress);
      if (k > decade)
	cout << 10 * k << " %" << endl;
      decade = k;
    
      // ===============read this entry == == == == == == == == == == ==

      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) { break; cout<<"Breaking"<<endl;}
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      //cout<<"insides the event loop: check1"<<endl;

      ////   MESSAGE ////
      // apparently code is not running beyond this point ///
      pi_event = 0;
      pi_event_orig = 0;
      pi_run = 0;
      pi_pdgID = 0;
      pi_beamEnergy = -1;
      pi_trueBeamEnergy = -1;
      pi_NRechits = 0;
      pi_NRechits_orig = 0;

      pi_rechit_energy.clear();
      pi_rechit_module.clear();
      pi_rechit_layer.clear();
      pi_rechit_chip.clear();
      pi_rechit_channel.clear();
      pi_rechit_type.clear();
      pi_rechit_x.clear();
      pi_rechit_y.clear();
      pi_rechit_z.clear();
      pi_rechit_iu.clear();
      pi_rechit_iv.clear();
      pi_rechit_iU.clear();
      pi_rechit_iV.clear();
      pi_rechit_amplitudeHigh.clear();
      pi_rechit_amplitudeLow.clear();
      pi_rechit_noise_flag.clear();
      pi_rechit_shower_start_layer = -999;
      pi_rechit_energyPerLayer=0;//.clear();
      pi_rechit_nHitsPerLayer=0;//.clear();
      pi_rechit_cogX=0;//.clear();
      pi_rechit_cogY=0;//.clear(); 
      // cout<<"insides the event loop: check1"<<endl;

      pi_ntracks = 0;
      pi_trackChi2_X = -1;
      pi_trackChi2_Y = -1;
      pi_dwcReferenceType = -1;
      pi_m_x = -999;
      pi_m_y = -999;
      pi_b_x = -999;
      pi_b_y = -999;
      pi_impactX_layer=0;//.clear();
      pi_impactY_layer=0;//.clear();
    
      pi_ahc_nHits = 0;
      pi_ahc_nHits_orig = 0;
      pi_ahc_energyPerLayer=0;// .clear();
      pi_ahc_nHitsPerLayer=0;//.clear();
      pi_ahc_hitI.clear();
      pi_ahc_hitJ.clear();
      pi_ahc_hitK.clear();
      pi_ahc_hitEnergy.clear();
      pi_ahc_hitX.clear();
      pi_ahc_hitY.clear();
      pi_ahc_hitZ.clear();
  
      pi_isHGC_AHC_sync = 0;
      pi_isGoodTrack = 0;
      pi_isFHNoisy = 0;
      pi_MuonVeto = 0;
      pi_isInTrackWindow = 0;
      pi_hgc_channel_mask=0;//->clear();
      pi_ahc_channel_mask=0;//->clear();
      pi_pass_noise_thres=0;//->clear();

      pi_energyLostEE = 0;
      pi_energyLostFH = 0;
      pi_energyLostBH = 0;
      pi_energyLostBeam = 0;

      //cout<<"insides the event loop: check2"<<endl;

      //    pion_tree->Fill();
      event_count[0]++;
      pi_event_orig=event;
      pi_ahc_nHits_orig=ahc_nHits;
      pi_NRechits_orig=NRechits;
      pi_isHGC_AHC_sync=isHGC_AHC_sync;
      pi_isGoodTrack = isGoodTrack;
      pi_isFHNoisy = isFHNoisy;
      pi_MuonVeto=MuonVeto;
      pi_isInTrackWindow=isInTrackWindow;
      pi_hgc_channel_mask=hgc_channel_mask;
      pi_ahc_channel_mask=ahc_channel_mask;
      pi_pass_noise_thres=pass_noise_thres;

      pi_leadingHadKE = 0;
    pi_E_genKin = 0;
    pi_nsc_total_KE = 0;
    pi_Allsec_pions = 0;
    pi_Allsec_Kaons = 0;
    pi_Allseckin =0;
    pi_sec_parent_id=0;
   pi_sec_track_id=0;
   pi_sec_process_id=0;
   pi_Allsec_parent_id=0;
   pi_Allsec_track_id= 0;
   pi_Allsec_process_id=0;

    pi_eventHadInt=0;
    pi_foundHadInt=0;
    pi_process=0;
    pi_nsec=0;
    pi_sec_pdgID=0;
    pi_sec_charge=0;
    pi_sec_kin=0;
    pi_sec_x=0;
    pi_sec_y=0;
    pi_sec_z=0;
    pi_Allsec_pdgID=0;
    pi_Allsec_charge=0;
    pi_Allsec_kin=0;
    pi_Allsec_x=0;
    pi_Allsec_y=0;
    pi_Allsec_z=0;
    pi_sec_parent_id=0;
    pi_sec_track_id=0;
    pi_sec_process_id=0;
    pi_Allsec_parent_id=0;
    pi_Allsec_track_id=0;
    pi_Allsec_process_id=0;
    pi_rechitEn_trimAhcal.clear();
    pi_comb_rechit_x_trimAhcal.clear();
    pi_comb_rechit_y_trimAhcal .clear();
    pi_comb_rechit_z_trimAhcal .clear();
    pi_Nrechit_trimAhcal=0;
      event_count[1]++;
      //if(Nrechits_FH_module_42 >80 ||  Nrechits_FH_module_45 > 80){count_fh++; continue;}
      if(isFHNoisy) {count_fh++; continue;}
      event_count[2]++;
       //good track
      bool isGoodTrack = (dwcReferenceType >= 13 && trackChi2_X < 10 && trackChi2_Y < 10);
      if(!isGoodTrack) { count_badtrack++; continue;}
      event_count[3]++;
      
      //muon veto
      if(MuonVeto) continue;
      event_count[4]++;
      if(rechit_shower_start_layer<=2) continue;
      event_count[5]++;
      //if(!isInTrackWindow) continue;
      event_count[6]++;
      h_beamenergy->Fill(beamEnergy);
      h_true_beamenergy->Fill(trueBeamEnergy);
      h_particle->Fill(pdgID);

      //for tree

      //pi_isHGC_AHC_sync = true;
      pi_event = event;
      pi_run = run;
      pi_pdgID = pdgID;
      
      pi_beamEnergy = beamEnergy;
      pi_trueBeamEnergy = trueBeamEnergy;
      //pi_NRechits = NRechits;
      pi_rechit_cogX=rechit_cogX;
      pi_rechit_cogY=rechit_cogY;
      pi_impactX_layer=TrackImpactX_layer;
      pi_impactY_layer=TrackImpactY_layer;
      pi_rechit_energyPerLayer=rechit_energyPerLayer;
      pi_rechit_nHitsPerLayer=rechit_nHitsPerLayer;
      pi_rechit_shower_start_layer=rechit_shower_start_layer;
      pi_ntracks = ntracks;
      pi_trackChi2_X = trackChi2_X;
      pi_trackChi2_Y = trackChi2_Y;
      pi_dwcReferenceType = dwcReferenceType;
      pi_m_x = m_x;
      pi_m_y = m_y;
      pi_b_x = b_x;
      pi_b_y = b_y;


      //pi_ahc_nHits = ahc_nHits;
      pi_ahc_energyPerLayer = ahc_energyPerLayer;
      pi_ahc_nHitsPerLayer = ahc_nHitsPerLayer;
      
      //pion_tree->Fill();

      ////////////////////////////////////////////
      //            HGCAL Part                  //
      ////////////////////////////////////////////
      
      /// Read HGCAL Tree
      int      nrechit_trimAhcal=0;
      if(DEBUG) cout<<"DEBUG: Start Analylizing HGCAL  RecHits!!"<<endl;
      // total_rechits_energy_EE=0;
      // total_rechits_energy_FH=0;
      for( int i = 0 ; i < NRechits; i++)
      	{
      	  int channel = rechit_channel->at(i);
      	  int chip = rechit_chip->at(i);
      	  int en_chan = 1000*chip + channel;
      	  int layer = rechit_layer->at(i);
      	  float energy=rechit_energy->at(i);
	  
  	  if(hgc_channel_mask->at(i)) continue;
  	  if(!pass_noise_thres->at(i))continue;
	  //cout<<rechit_x->at(i)<<"x"<<rechit_y->at(i)<<"y"<<endl;
	  pi_rechit_energy.push_back(energy);
  	  pi_rechit_x.push_back(rechit_x->at(i));
  	  pi_rechit_y.push_back(rechit_y->at(i));
  	  pi_rechit_z.push_back(rechit_z->at(i));
  	  // pi_rechit_iu.push_back(rechit_iu->at(i));
  	  // pi_rechit_iv.push_back(rechit_iv->at(i));
  	  // pi_rechit_iU.push_back(rechit_iU->at(i));
  	  // pi_rechit_iV.push_back(rechit_iV->at(i));
  	  // pi_rechit_amplitudeHigh.push_back(rechit_amplitudeHigh->at(i));
  	  // pi_rechit_amplitudeLow.push_back(rechit_amplitudeLow->at(i));
  	  // pi_rechit_noise_flag.push_back(rechit_noise_flag->at(i));
	  // pi_rechit_module.push_back(rechit_module->at(i));
  	  // //pi_rechit_layer->push_back(rechit_layer->at(i));
  	  // pi_rechit_chip.push_back(rechit_chip->at(i));
  	  // pi_rechit_channel.push_back(rechit_channel->at(i));
  	  // pi_rechit_type.push_back(rechit_type->at(i));
	  pi_rechitEn_trimAhcal.push_back(energy);
	  pi_comb_rechit_x_trimAhcal.push_back(rechit_x->at(i));
	  pi_comb_rechit_y_trimAhcal.push_back(rechit_y->at(i));
	  pi_comb_rechit_z_trimAhcal.push_back(rechit_z->at(i));
	  nHgc++;
	  nrechit_trimAhcal++;
  	  } //Nrechits loop
      //pion_tree->Fill();
      pi_NRechits = nHgc;
      
      // pi_rechit_x->clear();
      // pi_rechit_y->clear();
      // //////////////////////////////////////////
      
      
      // //    cout<<NRechits<<"\t"<<count<<endl;
      
      // ////////////////////////////////////////////
      // //            AHCAL Part                  //
      // ////////////////////////////////////////////
      
      /// Read AHCAL Tree
      if(DEBUG) cout<<"DEBUG: Start Analylizing AHCAL  RecHits!!"<<endl;

      for(int i = 0 ; i < ahc_nHits; i++) {
      	if(ahc_channel_mask->at(i)) continue;
	int count=0;
	int layer = ahc_hitK->at(i)+40;
	for(int i_l=0; i_l<10; i_l++)
	  {
	    // if(count==1)
	    //   break;
	    if(layer ==ahcal_layer[i_l])
	      {
		// pi_ahc_hitI.push_back(ahc_hitI->at(i));
		// pi_ahc_hitJ.push_back(ahc_hitJ->at(i));
		// pi_ahc_hitK.push_back(ahc_hitK->at(i));
		pi_ahc_hitX.push_back(ahc_hitX->at(i));
		pi_ahc_hitY.push_back(ahc_hitY->at(i));
		pi_ahc_hitZ.push_back(ahc_hitZ->at(i));
		pi_ahc_hitEnergy.push_back(ahc_hitEnergy->at(i));
	
		pi_rechitEn_trimAhcal.push_back(ahc_hitEnergy->at(i));
		pi_comb_rechit_x_trimAhcal.push_back(ahc_hitX->at(i));
		pi_comb_rechit_y_trimAhcal.push_back(ahc_hitY->at(i));
		pi_comb_rechit_z_trimAhcal.push_back(ahc_hitZ->at(i)+offset);
		count++;
		nrechit_trimAhcal++;
	      }
	    nAhc++;
	  }
	// pi_ahc_energyPerLayer.push_back(ahc_energyPerLayer->at(i));
  	// pi_ahc_nHitsPerLayer.push_back(ahc_nHitsPerLayer->at(i));
	//	nAhc++;
      }//
      pi_ahc_nHits=nAhc;
      pi_Nrechit_trimAhcal=nrechit_trimAhcal;
      // if(shower_start_index > -1 && foundHadInt) {
      double nsc_total_KE = 0.0;
      vector<double> KE_list;
      double leadingHadKE = 0.0;
      double E_gen_kin = 0.0;
      KE_list.clear();
      double E_gen_kin_thres = 0.0;
      double Allsec_pions =0.0 ;
      double Allsec_kaons =0.0 ;
      double AllsecKin=0.0;
      if(!foundHadInt) notFound_hadronic_int++;
      if(foundHadInt) {
      hadronic_int++;
      for(int i = 0; i < nsec; i++) {
        nsc_total_KE += sec_kin->at(i);
        if(abs(sec_pdgID->at(i)) == 211 && sec_charge->at(i) == -1) KE_list.push_back(sec_kin->at(i));
      }
      leadingHadKE = getLeadingKE(KE_list);
      E_gen_kin = nsc_total_KE - leadingHadKE;
      if(leadingHadKE > 0) {
	if(E_gen_kin > 10 && false) {
	  cout<<jentry<<" NextClosestLayer is \t "<<endl;
	}
	  if(E_gen_kin < E_gen_kin_thres) continue;
	  hard_hadronic_int++;

	  if(jentry < 20 && false) {
	    cout<<jentry<<" : "<<nsec<<" : "<<nsc_total_KE<< " : "<<leadingHadKE<<" : "<<E_gen_kin<<endl;
            }
      }
      }
      if(E_gen_kin>beamEnergy) continue;      
      bool flag=0;
      for(int i =0;i<int(Allsec_pdgID->size());i++)
	{
	  int j	= i-1;
          if(j<0) j=0;
	   flag=1;
          if(i!=0)
	    flag = !((*Allsec_x)[i]==(*Allsec_x)[j] and (*Allsec_y)[i]==(*Allsec_y)[j] and (*Allsec_z)[i]==(*Allsec_z)[j] and (*Allsec_pdgID)[i] ==(*Allsec_pdgID)[j] and (*Allsec_parent_id)[i] == (*Allsec_parent_id)[j]);
	  //	  flag =1; //neutralizing the previous condition
	  //if(flag==1){
	  if((*Allsec_pdgID)[i]==111 and  (*Allsec_process_id)[i]>=121 )//and (*Allsec_process_id)[i]<=151)
	    Allsec_pions+=(*Allsec_kin)[i];
	  if((*Allsec_pdgID)[i]==221 and  (*Allsec_process_id)[i]>=121)// and  (*Allsec_process_id)[i]<=151)
            Allsec_kaons+=(*Allsec_kin)[i];
	  if(((*Allsec_pdgID)[i]==221 || (*Allsec_pdgID)[i]==111 ) && (*Allsec_process_id)[i]>=121)// &&  (*Allsec_process_id)[i]<=151)//(!((*Allsec_x)[i]==(*Allsec_x)[j] and (*Allsec_y)[i]==(*Allsec_y)[j]) and (*Allsec_z)[i]==(*Allsec_z)[j]))
	    {
	    AllsecKin+=(*Allsec_kin)[i];
	    //cout<<((*Allsec_pdgID)[i]==221 || (*Allsec_pdgID)[i]==111 )<<"\t"<<( (*Allsec_process_id)[i]>=121 )<<"\t"<<( flag==1)<<endl;
	    //	    	  cout<<"jentry "<<jentry<<"\t"<<"flag"<<"\t"<<(*Allsec_kin)[i]<<"\t"<<(*Allsec_pdgID)[i]<<"\t"<<(*Allsec_parent_id)[i]<<"\t"<<(*Allsec_process_id)[i]<<endl;//"x "<<(*Allsec_x)[i]<<" y "<<(*Allsec_y)[i]<< " z "<<(*Allsec_z)[i]<<"\t"<<flag<<"\t j "<<j<<endl;
	  // cout<<(*Allsec_kin)[i]<<"\t"<<(*Allsec_pdgID)[i]<<endl;
	    //}
	    }}
      if(Allsec_pions>beamEnergy)
      {counter++;
	  // for(int i =0;i<int(Allsec_pdgID->size());i++)
        // {
	//   //	  cout<<(*Allsec_kin)[i]<<"\t"<<(*Allsec_pdgID)[i]<<"\t"<<(*Allsec_parent_id)[i]<<"\t"<<"x "<<(*Allsec_x)[i]<<" y "<<(*Allsec_y)[i]<< " z "<<(*Allsec_z)[i]<<endl;
        // }
	//   cout<<" AllsecKin "<<AllsecKin<<"\t"<<Allsec_kaons<<"\t"<<Allsec_pions<<"\t"<<leadingHadKE<<"\t"<<nsc_total_KE<<"\t"<<flag<<endl;

	//   if(AllsecKin>beamEnergy)
	cout<<"Alpana- AllsecKin "<<AllsecKin<<"\t"<<Allsec_kaons<<"\t"<<Allsec_pions<<"\t"<<leadingHadKE<<"\t"<<nsc_total_KE<<" nsc "<<nsec<<"\t"<<beamEnergy<<endl;
	    	    continue;
	}
      //       cout<<"AllsecKin "<<AllsecKin<<"\t"<<Allsec_kaons<<"\t"<<Allsec_pions<<endl;

      for(int ien=0;ien<8;ien++)
	{
	  if(beamEnergy==Elist[ien]){
	    h_2D_nsc_correlation[ien]->Fill(E_gen_kin,nsec);
	    h_nsc[ien]->Fill(nsec/beamEnergy);
	    h_seckin[ien]->Fill(nsc_total_KE/beamEnergy);
	    h_had_leading_KE[ien]->Fill(leadingHadKE/beamEnergy);
	    h_gen_kin[ien]->Fill(E_gen_kin/beamEnergy);
	    h_2D_nsc_correlation_frac[ien]->Fill(E_gen_kin/beamEnergy,nsec);
	    h_2D_hlead_sec_frac[ien]->Fill(E_gen_kin/beamEnergy,leadingHadKE/beamEnergy);
	    h_Allsec_kin_kaons[ien]->Fill(Allsec_kaons/beamEnergy);
	    h_Allsec_kin_pions[ien]->Fill(Allsec_pions/beamEnergy);
	    h_Allsec_kin[ien]->Fill(AllsecKin/beamEnergy);
	  }
	}
      pi_eventHadInt=eventHadInt;
    pi_foundHadInt=foundHadInt;
    pi_process=process;
    pi_nsec=nsec;
    pi_sec_pdgID=sec_pdgID;
    pi_sec_charge=sec_charge;
    pi_sec_kin=sec_kin;
    pi_sec_x=sec_x;
    pi_sec_y=sec_y;
    pi_sec_z=sec_z;
    pi_Allsec_pdgID=Allsec_pdgID;
    pi_Allsec_charge=Allsec_charge;
    pi_Allsec_kin=Allsec_kin;
    pi_Allsec_x=Allsec_x;
    pi_Allsec_y=Allsec_y;
    pi_Allsec_z=Allsec_z;
    
    pi_leadingHadKE = leadingHadKE;
    pi_E_genKin = E_gen_kin;
    pi_nsc_total_KE = nsc_total_KE;
    pi_Allsec_pions = Allsec_pions;
    pi_Allsec_Kaons = Allsec_kaons;
    pi_Allseckin =AllsecKin;
      pi_sec_parent_id=sec_parent_id;
   pi_sec_track_id=sec_track_id;
   pi_sec_process_id=sec_process_id;
   pi_Allsec_parent_id=Allsec_parent_id;
   pi_Allsec_track_id=Allsec_track_id;
   pi_Allsec_process_id=Allsec_process_id;

    pion_tree->Fill();
    nAhc =0;
    nHgc=0;
      // h_total_rechitsEenrgy_nocut->Fill(total_rechits_energy_nocut);
      if(DEBUG) cout<<"DEBUG: End of Entry = "<<jentry<<endl;
      if(DEBUG) cout<<"DEBUG: ****************** "<<endl;

      
      //if(DEBUG && jentry > 10) break;
      //      gSystem->Exit(0);
      //      if(jentry > 10) break;
      //pion_tree->Fill();
    } // loop over entries
  

  ///////////////////////////////////////////////////////////
  ///////  E N D     O F     E N T R Y     L O O P     //////
  ///////////////////////////////////////////////////////////
  //  gSystem->Exit(0);
  cout<<"Got Out "<<jentry<<endl;
  cout<<count_fh<<endl;
  cout<<count_badtrack<<endl;
  for(int i =0;i<7;i++)
    {
      cout<<event_count[i]<<endl;
     }
  cout<<counter<<"\t"<<"counter"<<endl;
  outfile->cd();
  pion_tree->Write();
  outfile->Close();
  cout<<"outFile: "<<outFileName<<" written!!"<<endl;
}
