
void average_pT()
{	
	TFile *f=new TFile("13TeV_CR0_RHoff.root");
	TTree *tree = (TTree*)f->Get("pytree80100");
	Long64_t nentries = (Long64_t)tree->GetEntries();
	 
	Long64_t maxTrack=100000;
   
    Int_t ntrack;
    Double_t pT[maxTrack];


    tree->SetBranchAddress("ntrack",&ntrack);
    tree->SetBranchAddress("pT",&pT);

	TH1D *av_pt = new TH1D("av_pt","Average transverse momentum",100,0.0,2.0);
	TCanvas *c1=new TCanvas();
	c1->SetLogy();

	for(Int_t i=1; i<nentries; i++){

		tree->GetEntry(i);
		Double_t s = 0.0;
		//tree->GetEntry(i);
		for(Int_t j=0; j<ntrack; j++){
			s = s + pT[j];
			//hpt->Fill(pT[j]);
		}
		av_pt->Fill(s/ntrack);
		av_pt->SetLineColor(kBlue);
		
	}
	av_pt->GetXaxis()->SetTitle("Transverse Momentum");
    	av_pt->GetYaxis()->SetTitle("Counts");
	av_pt->Draw();
	av_pt->Fit("gaus");
	av_pt->SetFillColorAlpha(kGreen-10,0.35);
	auto legend = new TLegend(0.1,0.7,0.48,0.9);
   	legend->AddEntry(av_pt,"average pT","f");
   	legend->AddEntry(gaus,"Fit","l");
   	legend->Draw();
   	
}
