# code for TB alignment corrections Hgcal_testbeam_analysis

##HGCAL_analysis_code
##Latest pion analysis code for OctTB2018


git clone -b chi2_optimization git@github.com:alpana-hep/Hgcal_testbeam_analysis_2021.git .

##How to run the script

make
./analyzeHGCOctTB <file_list> outFileName.root <dataset> <configuration> <chi2-method> min_ max_ 

<file_list.txt> : contains files to be analyzed (can be found in file_list folder)
<configuration> : alpha (always use alpha for config-1)
<chi2-method> : 0,1,2,3
	      case 0 : rechit energy sum as input to chi2",
	      case 1 : detector scale with No offset for H hadrons as input to chi2",
              case 2 : detector scale with offset (0.4 GeV) for H hadrons as input to chi2",
  	      case 3 : detector scale with offset (0.4 GeV) for H hadrons AND events around the core of beam energy as input to chi2",

alwyas use chi2 method -case-1

<min_> & <max_> : put these to random numbers (not being used right now - In general these two can be used to set the limit on total number of events for which you need to run your event loop.)
Example:
`./analyzeHGCOctTB file_list/v16_v8/pion100_config1.txt outFileName.root data alpha 1 0 1
How to run the script for sim:

./analyzeHGCOctTB file_list/v16_v8/<sim_file.txt> outFileName.root sim alpha 1 0	1



Descrition of scripts:

AnalyzeHGCOctTB.cc : Main analysis code
AnalyzeHGCOctTB.h : Initialize histos here
HGCNtupleVariables.h: Tree variable initialization
Others are helping classes
