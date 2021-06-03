#include "analysisClass.C"
#include <TROOT.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

// ###### INSTRUCTIONS (input options)
// // (after having compiled the code [.L Analysis.cpp])
//
 using namespace std;

 int Analysis_template(){
    TString fileout = "MuDPGNTuple_MWGR3_EXP_run341343.root";
         
    TChain* chain = new TChain("muNtupleProducer/MuDPGTree");
           //AddFile

//     for(int i=1;i<13;i++){
	for(int i=1;i<10;i++){
		chain->Add(Form("/lustre/cms/store/user/gmilella/ExpressCosmics/CRAB3_gem_dpg_ntuple_mwgr3_2021_run341343_express/210507_215122/0000/MuDPGNTuple_MWGR3_2021_EXP_run341343_%d.root", i));	
	}	
           //OutFile
	   chain->Merge(fileout);

           analysisClass class_noise(chain, fileout);
           class_noise.Loop();
                                 
           return 0;
       }
