import sys, os

#energy = int(sys.argv[1])
energy = sys.argv[1]
print energy
# sys.exit(0)

energy_list = {
    "20" : [679,680,681,682,683,684,685,686,687,688,689],
    "50" : [690,691,692,693,694,695,696],
    "80" : range(525,540),
    "100" : range(552,563),
    "120" : range(584,594),
    "200" : range(563,578),
    "250" : range(541,552),
    "300" : range(512,524),
    "420" : [698,699,700,701,702,704,705,708,709,710,712,713,714,715,717,718,721,722]   ##For muons
}
#/home/work/kalpana/public/work/Hgcal_test_beam_2020/Hgcal_TestBeam_Analysis_2021/CMSSW_9_3_0/src/CERN_TB/octTB/data_samples/data_samples/Config1/pion_datasamples/v16_v8/pion20

list_20 = [679,680,681,682,683,684,685,686,687,688,689] 
list_50 = [690,691,692,693,694,695,696]
list_80 = range(525,540) #[525,526,527,528,529,530,]
list_100 = range(552,563) 
list_120 = range(584,594)
list_250 = range(541,552)  
list_300 = range(512,524)  

#muon_list_200 = [698,699,700,701,702,704,705,708,709,710,712,713,714,715,717,718,719,721,722]
#muon_list_200 = [698,699,700,701,702,704,705,708,709,710,712,713,714,715,717,718,721,722]
destination_path = "./v16_v8/pion"+str(energy)
if(int(energy) == 420):
    destination_path = "./v16_v8/muon200"
count = 0
for sample in energy_list[energy]:
    cmd = "hadd -k "+destination_path+"/fulltree_"+str(sample)+".root /eos/cms/store/group/dpg_hgcal/tb_hgcal/2018/cern_h2_october/offline_analysis/ntuples/v16/ntuple_"+str(sample)+".root /eos/cms/store/group/dpg_hgcal/tb_hgcal/2018/cern_h2_october/offline_analysis/AHCAL_ntuples/v8/Run_"+str(sample)+".root"
    print cmd
    os.system(cmd)
    count += 1

print "Added ",count," ntuples successfully"
