# Hgcal_testbeam_analysis_2021

HGCAL_analysis_code Latest pion analysis code for OctTB2018

git clone -b updated_chi2Optimization2022 git@github.com:alpana-hep/Hgcal_testbeam_analysis_2021.git . How to run the script

make

./analyzeHGCOctTB <file_list> outFileName.root <file_list.txt> : contains path of files to be analyzed (can be found in file_list folder) : alpha (always use alpha for config-1) : energy of the pions

Example: `./analyzeHGCOctTB file_list/pion_data_50GeV.txt outFileName.root data alpha 50

How to run the script for sim:

./analyzeHGCOctTB file_list/<sim_file.txt> outFileName.root sim alpha 50

Descrition of scripts:

AnalyzeHGCOctTB.cc : Main analysis code AnalyzeHGCOctTB.h : Initialize histos here HGCNtupleVariables.h: Tree variable initialization Others are helping classes