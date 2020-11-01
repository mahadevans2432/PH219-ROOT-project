
void kurtosis_skewness()
{
	TFile *f=new TFile("13TeV_CR0_RHoff.root");
	TTree *tree = (TTree*)f->Get("pytree80100");
	Long64_t nentries = (Long64_t)tree->GetEntries();
	cout<<nentries<<endl;
	 
	Long64_t maxTrack=100000;
   
    Int_t ntrack[maxTrack];
    Double_t pT[maxTrack];
    Double_t eta[maxTrack];
    Double_t rap[maxTrack];
    Double_t phi[maxTrack];


    tree->SetBranchAddress("ntrack",&ntrack);
    tree->SetBranchAddress("phi",&phi);
    tree->SetBranchAddress("pT",&pT);
    tree->SetBranchAddress("eta",&eta);
    tree->SetBranchAddress("rap",&rap);

	TH1D *hpt = new TH1D("hpt","Transverse momentum",100,0.0,100.0);

	for(Long64_t i=0; i<nentries; i++) {  // Event loop starts here
		tree->GetEntry(i);
		for(Long64_t j=0; j<ntrack[i]; j++){
			hpt->Fill(pT[j]);
		}
	}

	cout<<"Skewness:"<<hpt->GetSkewness()<<endl;
	cout<<"Kurtosis:"<<hpt->GetKurtosis()<<endl;
	hpt->Draw();
	
}
