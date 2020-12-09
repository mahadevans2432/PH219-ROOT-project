
void plot_pT()
{
	TFile *f=new TFile("13TeV_CR0_RHoff.root");		
	TTree *tree = (TTree*)f->Get("pytree80100");
	Long64_t nentries = (Long64_t)tree->GetEntries();
	 
	Long64_t maxTrack=100000;
   
    Int_t ntrack;
    Double_t pT[maxTrack], log_pT[maxTrack];


    tree->SetBranchAddress("ntrack",&ntrack);
    tree->SetBranchAddress("pT",&pT);

	TH1D *hpt = new TH1D("hpt","Transverse momentum",100,0.0,5.0);
	TCanvas *c1=new TCanvas();
	c1->SetLogy();

	for(Int_t i=0; i<nentries; i++){

		tree->GetEntry(i);

		for(Int_t j=0; j<ntrack; j++){
			hpt->Fill(pT[j]);
			hpt->SetLineColor(kBlue);
		}
		
	}
	//hpt->SetDrawOption("G");
    	hpt->GetXaxis()->SetTitle("Transverse Momentum");
    	hpt->GetYaxis()->SetTitle("Counts");
	hpt->Draw();
	hpt->Fit("expo");
	hpt->SetFillColorAlpha(kGreen-10,0.35);
	auto legend = new TLegend(0.8,0.7,0.48,0.6);
   	legend->AddEntry(hpt,"pT","f");
   	legend->AddEntry(expo,"Fit","l");
   	legend->Draw();
	
}
