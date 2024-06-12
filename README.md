# Code setup for testing Clue algorithm

### Descrition of scripts:
AnalyzeHGCOctTB.cc : Main analysis code AnalyzeHGCOctTB.h : Initialize histos here HGCNtupleVariables.h: Tree variable initialization Others are helping classes


Clue algorithm specific classes - Cluster.h CLUEAlgo.h LayerTiles.h LayerTilesConstants.h PointsCloud.h
All runlist text files are under filelist directory

```
git clone -b ClueAlgorithm git@github.com:alpana-hep/Hgcal_testbeam_analysis_2021.git .
maket
```

Example to run code -
```
./analyzeHGCOctTB <file_list> outFileName.root <dataset : data or sim> <configuration - alpha> <energy = -1 for all energies >
```
or 
```
./analyzeHGCOctTB file_list/pion_data_50GeV.txt outFileName.root data alpha 50~
```

<file_list.txt> : contains path of files to be analyzed (can be found in file_list folder)
alpha (always use alpha for config-1)
energy of the pions

To submit condor jobs, use makeCondorSubmit.py create submission script and driver_submitjobs.py submit these on condor
```
cd condor_jobs/
python makeCondorSubmit.py
python driver_submitjobs.py
```