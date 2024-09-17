# Latest pion analysis code for HgcalTBOct18
In this, Updated ntuples (path for which mentioned in filelist direcotry) are used as the inputs,
The output ntuples that we get are after passing all the cleaning cuts.

This code is same for data and simulation since the input file (updated ntuple) has already taken care of the differences between the data and simulation ntuples.

Downlaod scripts
```
git clone -b pi0FractInfor git@github.com:alpana-hep/Hgcal_testbeam_analysis_2021.git .
make clean
make
```

How to run the script:
```
./analyzeHGCOctTB <file_list> outFileName.root data <configuration> <energy> 
```
<file_list.txt> : contains files to be analyzed (can be found in file_list folder)
<configuration> : alpha (always use alpha for config-1)
<energy> : beam_energy

Example:
```
`./analyzeHGCOctTB file_list/v16_v8/pion100_config1.txt outFileName.root data alpha 100 
```