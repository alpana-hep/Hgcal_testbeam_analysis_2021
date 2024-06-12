import os,sys,re,fileinput,string,shutil
from datetime import date
count=0
min_count=0
year=["Fall17","Autumn18","Summer16v3"]
number=["2017","2018","2016"]
#sample_tag=["GJets_DR","QCD_Jets","temp","temp","temp","temp","temp","temp"]
sample_tag=["GJets_DR","QCD","ZGJets","ZJets","TTGJets","TTJets-HT","WGJets","WJets","TTJets-inc"]
bkg_samples=["GJets_DR","QCD","ZGJets","ZJets","TTGJets","TTJets-HT","WGJets","WJets","TTJets-inc"]
#bkg_samples=["GJets_DR","QCD"]
count1=0;
for j in range(0,5):
    min_ = j
    max_ = min_+ 1
    # count=i
    # min_count= i+100000 
    condorSubmit = "condor_submit condor_submit/submitCondor_%dM_%dM"%(min_,max_)
    print condorSubmit
    os.system(condorSubmit)

    
    # fname1 = "/home/work/kalpana1/public/Hgcal_TestBeam_Analysis/CMSSW_9_3_0/src/Machinery_CLUE3D_MarcoV0_Nov2022/file_list/FTFP_sim_33mBeamLine_%dto%dM.txt"%(min_,max_)
    # outfname ="/home/work/kalpana1/public/Hgcal_TestBeam_Analysis/CMSSW_9_3_0/src/Machinery_CLUE3D_MarcoV0_Nov2022/out_%d_to_%d.root"%(min_,max_)
    # jobName = "%s_%s"%(min_,max_)
    # #out_tag="%s_%s" %(sample_tag[count1],year[count1])
    # shutil.copyfile("proto_condor_submit",condorSubmit)
    # for line in fileinput.FileInput(condorSubmit, inplace=1):
    #     line=line.replace("min", str(min_))
    #     line=line.replace("max", str(max_))
    #     line=line.replace("outfile", outfname)
    #     line=line.replace("file_list",fname1)
    #     line=line.replace("JOBNAME", jobName)
    #     print line.rstrip()            
    # print condorSubmit
    # # count+=1
    # # count1+=1
