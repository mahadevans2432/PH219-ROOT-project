
void plot_pT()
{
	TFile *f=new TFile("13TeV_CR0_RHoff.root");
	TTree *tree = (TTree*)f->Get("pytree020");
	Long64_t nentries = (Long64_t)tree->GetEntries();
	 
	Long64_t maxTrack=100000;
   
    Int_t ntrack;
    Double_t pT[maxTrack];


    tree->SetBranchAddress("ntrack",&ntrack);
    tree->SetBranchAddress("pT",&pT);

	TH1D *hpt = new TH1D("hpt","Transverse momentum",100,0.0,5.0);

	for(Int_t i=1; i<nentries; i++){

		tree->GetEntry(i);

		for(Int_t j=0; j<ntrack; j++){
			hpt->Fill(pT[j]);
		}
		
	}
	hpt->Draw();
	hpt->Fit("expo");
	
}
