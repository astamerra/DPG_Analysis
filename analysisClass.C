#define analysisClass_cxx
#include "analysisClass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

using namespace std;


Int_t getVFAT(Int_t etaP, Int_t chN, Float_t locX){
    switch((chN % 2)){
      case(1): //even chambers == long
	//if((chN % 2) == 0){
        switch(etaP){
            case(1):
                if(locX < -7.08802) { return 7;  break; }
                if(locX >= -7.08802 && locX <=  7.08802) { return 15; break; }
                if(locX >  7.08802) { return 23; break; }
            case(2):
                if(locX < -6.51678) { return 6;  break; }
                if(locX >= -6.51678 && locX <=  6.51678) { return 14; break; }
                if(locX >  6.51678) { return 22; break; }
            case(3):
                if(locX < -5.99395) { return 5;  break; }
                if(locX >= -5.99395 && locX <=  5.99395) { return 13; break; }
                if(locX >  5.99395) { return 21; break; }
            case(4):
                if(locX < -5.51954) { return 4;  break; }
                if(locX >= -5.51954 && locX <=  5.51954) { return 12; break; }
                if(locX >  5.51954) { return 20; break; }
            case(5):
                if(locX < -5.08405) { return 3;  break; }
                if(locX >= -5.08405 && locX <=  5.08405) { return 11; break; }
                if(locX >  5.08405) { return 19; break; }
            case(6):
                if(locX < -4.68748) { return 2;  break; }
                if(locX >= -4.68748 && locX <=  4.68748) { return 10; break; }
                if(locX >  4.68748) { return 18; break; }
            case(7):
                if(locX <  -4.32246) { return 1;  break; }
                if(locX >= -4.32246 && locX <=  4.32246) { return 9; break; }
                if(locX >   4.32246) { return 17; break; }
            case(8):
                if(locX < -3.98899) { return 0;  break; }
                if(locX >= -3.98899 && locX <=  3.98899) { return 8; break; }
                if(locX >  3.98899) { return 16; break; }
      //      default: return -1;
        }
//}//aggiunta per chiudere l'if
//	if((chN % 2) == 1){
        case(0): //odd chambers == short
        switch(etaP){
            case(1):
                if(locX < -6.69383) { return 7;  break; }
                if(locX >= -6.69383 && locX <=  6.69383) { return 15; break; }
                if(locX >  6.69383) { return 23; break; }
            case(2):
                if(locX < -6.20333) { return 6;  break; }
                if(locX >= -6.20333 && locX <=  6.20333) { return 14; break; }
                if(locX >  6.20333) { return 22; break; }
            case(3):
                if(locX < -5.75097) { return 5;  break; }
                if(locX >= -5.75097 && locX <=  5.75098) { return 13; break; }
                if(locX >  5.75097) { return 21; break; }
            case(4):
                if(locX < -5.33676) { return 4;  break; }
                if(locX >= -5.33676 && locX <=  5.33676) { return 12; break; }
                if(locX >  5.33676) { return 20; break; }
            case(5):
                if(locX < -4.95337) { return 3;  break; }
                if(locX >= -4.95337 && locX <=  4.95337) { return 11; break; }
                if(locX >  4.95337) { return 19; break; }
            case(6):
                if(locX < -4.60082) { return 2;  break; }
                if(locX >= -4.60082 && locX <=  4.60082) { return 10; break; }
                if(locX >  4.60082) { return 18; break; }
            case(7):
                if(locX < -4.27397) { return 1;  break; }
                if(locX >= -4.27397 && locX <=  4.27397) { return 9; break; }
                if(locX > -4.27397) { return 17; break; }
            case(8):
                if(locX < -3.97283) { return 0;  break; }
                if(locX >= -3.97283 && locX <=  3.97283) { return 8; break; }
                if(locX > 3.97283) { return 16; break; }
            default: return -1;
        }
   default: return -1;
     }
}




//initialise output minitree
void outTreeInit(TTree *tree_, Int_t &run, Int_t &lumi, Int_t &evt, Int_t cout[2][2][36]){
    tree_->Branch("run", &run);
    tree_->Branch("evt", &evt);
    tree_->Branch("lumi", &lumi);
    tree_->Branch("count", cout, "count[2][2][36]/I");
}

//initialise output minitree
void outTreeLumiInit(TTree *tree_, Int_t &nEvents, Int_t &lumi, Int_t nHits[2][2][36][8][384]){
    tree_->Branch("nEvents", &nEvents);
    tree_->Branch("lumi", &lumi);
    tree_->Branch("nHits", nHits, "nHits[2][2][36][8][384]/I");
}

void analysisClass::Loop()
{

//   In a ROOT session, you can do:
//   //      root> .L analysisClass.C
//   //      root> analysisClass t
//   //      root> t.GetEntry(12); // Fill t data members with entry number 12
//   //      root> t.Show();       // Show values of entry 12
//   //      root> t.Show(16);     // Read and show values of entry 16
//   //      root> t.Loop();       // Loop on all entries
//   //
//
//   //     This is the loop skeleton where:
//   //    jentry is the global entry number in the chain
//   //    ientry is the entry number in the current Tree
//   //  Note that the argument to GetEntry must be:
//   //    jentry for TChain::GetEntry
//   //    ientry for TTree::GetEntry and TBranch::GetEntry
//   //
//   //       To read only selected branches, Insert statements like:
//   // METHOD1:
//   //    fChain->SetBranchStatus("*",0);  // disable all branches
//   //    fChain->SetBranchStatus("branchname",1);  // activate branchname
//   // METHOD2: replace line
//   //    fChain->GetEntry(jentry);       //read all branches
//   //by  b_branchname->GetEntry(ientry); //read only this branch


 // Creation of output file & final tree
   TString root_fileName = fileName;
   TFile *fout = new TFile(root_fileName, "RECREATE");
   fout->cd();
   TTree *outTree = new TTree("outputTree","outputTree");
   TTree *outLumiTree = new TTree("outputLumiTree","outputLumiTree");

  // initialize variables
     Int_t run = 0, lumi = 0, evt = 0;
   int counts[2][2][36] = {0};
   int region_index[2] = {-1, +1};
   int layer_index[2] = {1, 2};

   vector<Int_t> lumi_list;
   Int_t nevents = 0;
   Int_t nhits[2][2][36][8][384] = {0};
   Float_t hit_rate[2][2][36][8][384] = {0.};
   Float_t temp_nhits[2][2][36][8][384] = {0.};
   Int_t VFAT_position[384] = {0};
   

//   TFile saving("plots.root","recreate")

/*
   std::vector<TH3F*> myHisto_neg_l1;
   std::vector<TH3F*> myHisto_neg_l2;
   std::vector<TH3F*> myHisto_pos_l1;
   std::vector<TH3F*> myHisto_pos_l2;


  for(int i=0;i<36;i++){
         TH3F *h1 = new TH3F(Form("h_neg_l1_%d",i+1), Form("Hit rate per lumisection, Region = -1, Layer = 1, Chamber = %d", i+1), 8, 0, 9, 384, 0, 385, 100, 0, 0.0006);
           myHisto_neg_l1.push_back(h1);
         TH3F *h2 = new TH3F(Form("h_neg_l2_%d",i+1), Form("Hit rate per lumisection, Region = -1, Layer = 2, Chamber = %d", i+1), 8, 0, 9, 384, 0, 385, 100, 0, 0.0006);
           myHisto_neg_l2.push_back(h2);
         TH3F *h3 = new TH3F(Form("h_pos_l1_%d",i+1), Form("Hit rate per lumisection, Region = +1, Layer = 1, Chamber = %d", i+1), 8, 0, 9, 384, 0, 385, 100, 0, 0.0006);
           myHisto_pos_l1.push_back(h3);
         TH3F *h4 = new TH3F(Form("h_pos_l2_%d",i+1), Form("Hit rate per lumisection, Region = +1, Layer = 2, Chamber = %d", i+1), 8, 0, 9, 384, 0, 385, 100, 0, 0.0006);
           myHisto_pos_l2.push_back(h4);
}*/

   std::vector<TH2F*> myHisto_neg_l1;
   std::vector<TH2F*> myHisto_neg_l2;
   std::vector<TH2F*> myHisto_pos_l1;
   std::vector<TH2F*> myHisto_pos_l2;


  for(int i=0;i<36;i++){
         TH2F *h1 = new TH2F(Form("h_neg_l1_%d",i+1), Form("Hit rate per lumisection, Region = -1, Layer = 1, Chamber = %d", i+1), 384, 0, 385, 100, 0, 0.0006);
           myHisto_neg_l1.push_back(h1);
         TH2F *h2 = new TH2F(Form("h_neg_l2_%d",i+1), Form("Hit rate per lumisection, Region = -1, Layer = 2, Chamber = %d", i+1), 384, 0, 385, 100, 0, 0.0006);
           myHisto_neg_l2.push_back(h2);
         TH2F *h3 = new TH2F(Form("h_pos_l1_%d",i+1), Form("Hit rate per lumisection, Region = +1, Layer = 1, Chamber = %d", i+1), 384, 0, 385, 100, 0, 0.0006);
           myHisto_pos_l1.push_back(h3);
         TH2F *h4 = new TH2F(Form("h_pos_l2_%d",i+1), Form("Hit rate per lumisection, Region = +1, Layer = 2, Chamber = %d", i+1), 384, 0, 385, 100, 0, 0.0006);
           myHisto_pos_l2.push_back(h4);
}


// initialize output minitree
   outTreeInit(outTree, run, lumi, evt, counts);
   outTreeLumiInit(outLumiTree, nevents, lumi, nhits);

   if (fChain == 0) return;

   bool isVerbose = false;
   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
       // if (Cut(ientry) < 0) continue;
       // per lumi analysis
      lumi_list.push_back(event_lumiBlock);
   } 

    //new loop on events for per lumi analysis
       nentries = fChain->GetEntriesFast();
   nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if(isVerbose) cout<<"\n==================\nrun "<<event_runNumber<<" lumi "<<event_lumiBlock<<" evt "<<event_eventNumber<<endl;
      if(isVerbose) cout<<"jentry "<<jentry<<"event_lumiBlock "<<event_lumiBlock<<" lumi_list.at(jentry) "<<lumi_list.at(jentry)<<endl;
      if((jentry < nentries-1) && event_lumiBlock == lumi_list.at(jentry+1)){
          nevents++;
      if(isVerbose) cout<<"n. GEM RecHit = "<<gemRecHit_region->size()<<endl;

      //loop on GEM rechits
      for(int j=0; j<gemRecHit_region->size(); j++){
              if(isVerbose) cout<<j<<" RecHit region|chamber|layer= "<<gemRecHit_region->at(j)<<" | "<<gemRecHit_chamber->at(j)<<" | "<<gemRecHit_layer->at(j)<<endl;
              //loop on endcaps
 	      for(int e=0; e<2; e++){
		//loop on layers
		for(int l=0; l<2 && gemRecHit_region->at(j) == region_index[e]; l++){
			//loop on chambers
	                for(int c=0; c<36 && gemRecHit_layer->at(j) == layer_index[l]; c++){
				//loop on eta
				for(int p=0; p<8 && gemRecHit_chamber->at(j) == c+1; p++){
		                         if(gemRecHit_etaPartition->at(j) == p+1){
					  //loop on strips
				          	for(int s=0; s<384 &&  gemRecHit_chamber->at(j) == c+1; s++){
							for(int cl=0; cl<gemRecHit_cluster_size->size() && gemRecHit_firstClusterStrip->at(j)==s; cl++){
					 			if((gemRecHit_firstClusterStrip->at(j) + gemRecHit_cluster_size->at(j) == s+cl)){
					 				nhits[e][l][c][p][s+cl]++;
                                 					temp_nhits[e][l][c][p][s+cl]=static_cast<float>(nhits[e][l][c][p][s]);
                                	 				float temp_nevents=static_cast<float>(nevents);
				 					hit_rate[e][l][c][p][s+cl] = temp_nhits[e][l][c][p][s+cl] / temp_nevents;
									VFAT_position[s+cl] = getVFAT(gemRecHit_etaPartition->at(j), gemRecHit_chamber->at(j), gemRecHit_loc_x->at(j));
								}
                     			 		}	
                  			  	}
              				}
         			 }
       			}
		}
	    }
	}
      }else{//if(jentry>0 && event_lumiBlock != lumi_list.at(jentry-1)){
          if(isVerbose){
              cout<<"event_lumiBlock "<<event_lumiBlock<<" nEvents="<<nevents;
              cout<<"hits in chamber [1][1][20][1][21] "<<nhits[1][1][20][1][21]<<endl; }
          lumi = event_lumiBlock;
          outLumiTree->Fill();
	TFile saving("plots.root", "recreate");
/*
	        for(int c=0; c<36; c++){
			for(int p=0; p<8; p++){
                		for(int s=0; s<384; s++){
                           		myHisto_neg_l1[c]->Fill(p+1, s, hit_rate[0][0][c][p+1][s]);
           	          		myHisto_neg_l2[c]->Fill(p+1, s, hit_rate[0][1][c][p+1][s]);
                           		myHisto_pos_l1[c]->Fill(p+1, s, hit_rate[1][0][c][p+1][s]);
                           		myHisto_pos_l2[c]->Fill(p+1, s, hit_rate[1][1][c][p+1][s]);
				}
			}
                        myHisto_neg_l1[c]->Draw("COLZ");
                        myHisto_neg_l1[c]->SetYTitle("Strip");
			myHisto_neg_l1[c]->SetXTitle("Eta partition");
                        myHisto_neg_l1[c]->SetZTitle("Hit Rate");
			myHisto_neg_l1[c]->Write();
	
			myHisto_neg_l2[c]->Draw("COLZ");
			myHisto_neg_l2[c]->SetYTitle("Strip");
                        myHisto_neg_l2[c]->SetXTitle("Eta partition");
                        myHisto_neg_l2[c]->SetZTitle("Hit Rate");
                        myHisto_neg_l2[c]->Write();
			
		        myHisto_pos_l1[c]->Draw("COLZ");
			myHisto_pos_l1[c]->SetYTitle("Strip");
                        myHisto_pos_l1[c]->SetXTitle("Eta partition");
                        myHisto_pos_l1[c]->SetZTitle("Hit Rate");
               	        myHisto_pos_l1[c]->Write();

			myHisto_pos_l2[c]->Draw("COLZ");
			myHisto_pos_l2[c]->SetYTitle("Strip");
                        myHisto_pos_l2[c]->SetXTitle("Eta partition");
                        myHisto_pos_l2[c]->SetZTitle("Hit Rate");
                        myHisto_pos_l2[c]->Write();

	        }
        
		saving.Close();*/

                for(int c=0; c<36; c++){
                        for(int p=0; p<8; p++){
                                for(int s=0; s<384; s++){
                                        myHisto_neg_l1[c]->Fill(s, hit_rate[0][0][c][p+1][s]);
                                        myHisto_neg_l2[c]->Fill(s, hit_rate[0][1][c][p+1][s]);
                                        myHisto_pos_l1[c]->Fill(s, hit_rate[1][0][c][p+1][s]);
                                        myHisto_pos_l2[c]->Fill(s, hit_rate[1][1][c][p+1][s]);
                                }
                        }
                        myHisto_neg_l1[c]->Draw("COLZ");
                        myHisto_neg_l1[c]->SetXTitle("Strip");
                        //myHisto_neg_l1[c]->SetXTitle("Eta partition");
                        myHisto_neg_l1[c]->SetYTitle("Hit Rate");
                        myHisto_neg_l1[c]->Write();

                        myHisto_neg_l2[c]->Draw("COLZ");
                        myHisto_neg_l2[c]->SetXTitle("Strip");
                        //myHisto_neg_l2[c]->SetXTitle("Eta partition");
                        myHisto_neg_l2[c]->SetYTitle("Hit Rate");
                        myHisto_neg_l2[c]->Write();

                        myHisto_pos_l1[c]->Draw("COLZ");
                        myHisto_pos_l1[c]->SetXTitle("Strip");
                        //myHisto_pos_l1[c]->SetXTitle("Eta partition");
                        myHisto_pos_l1[c]->SetYTitle("Hit Rate");
                        myHisto_pos_l1[c]->Write();

                        myHisto_pos_l2[c]->Draw("COLZ");
                        myHisto_pos_l2[c]->SetXTitle("Strip");
                        //myHisto_pos_l2[c]->SetXTitle("Eta partition");
                        myHisto_pos_l2[c]->SetYTitle("Hit Rate");
                        myHisto_pos_l2[c]->Write();

                }

                saving.Close();

                                                                                                                                 

	  //reset
	  memset(nhits, 0, sizeof(nhits));
          nevents=0;
      }
   } //loop on events

        double sum[384]={0.};
        double media_hit_rate[384]={0.};
        double stemp[384]={0.};
       //  double den = 144.; 
       double den = 1152.;
        for(int e=0;e<2;e++){
                for(int l=0;l<2;l++){
                        for(int c=0;c<36;c++){
                                for(int p=0;p<8;p++){
					for(int s=0;s<384;s++){
                                        	sum[s]+=hit_rate[e][l][c][p][s];
                        //                stemp[p]=static_cast<double>(sum[p]);
                 			}
            			}
       			}
		}
	}
        for(int s=0;s<384;s++){
                media_hit_rate[s]=sum[s]/den;
                std::cout <<  "Strip" << " " << s << "valore" << " "  << media_hit_rate[s] << std::endl;
        }

        for(int e=0;e<2;e++){
                for(int l=0;l<2;l++){
                        for(int c=0;c<36;c++){
                                for(int p=0;p<8;p++){
					for(int s=0;s<384;s++){
                                        	if(((hit_rate[e][l][c][p][s] - media_hit_rate[s])/media_hit_rate[s]) > 1) {
                                                	std::cout << "Endcap: "<< e << " Layer: " << l << " Chamber: "<< c+1 << " EtaPartition " << p+1 << " Strip: " << s << std::endl;
                                               		// if(e==0)  std::cout << "GE11-M-" << c+1 << "L" << l+1 <<  " VFAT: " << VFAT_position[p] << " Strip: " << p << std::endl; 
					       		// if(e==1)  std::cout << "GE11-P-" << c+1 << "L" << l+1 <<  " VFAT: " << VFAT_position[p] << " Strip: " << p << std::endl;
						}
                                	}
                        	}
                	}
        	}	
	}

	fout->cd();
	//write and close the file
	fout->Write();
	fout->Close();
}
