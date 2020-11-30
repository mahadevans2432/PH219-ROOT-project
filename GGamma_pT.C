
void GGamma_pT()
{
	TFile *f=new TFile("13TeV_CR0_RHoff.root");
	TTree *tree = (TTree*)f->Get("pytree80100");
	Long64_t nentries = (Long64_t)tree->GetEntries();
	 
	Long64_t maxTrack=100000;
   
    Int_t ntrack;
    Double_t pT[maxTrack];

    Double_t a1=0.0,a2=0.0,a3=0.0;


    tree->SetBranchAddress("ntrack",&ntrack);
    tree->SetBranchAddress("pT",&pT);

	TH1D *av_pt = new TH1D("av_pt","Average transverse momentum",100,0.0,2.0);

	for(Int_t i=1; i<nentries; i++){

		tree->GetEntry(i);
		Double_t Q1 = 0.0;
		Double_t Q2 = 0.0;
		Double_t Q3 = 0.0;
		//tree->GetEntry(i);
		for(Int_t j=0; j<ntrack; j++){
			Q1 = Q1 + (pT[j]);
			Q2 = Q2 + (pT[j]*pT[j]);
			Q3 = Q3 + (pT[j]*pT[j]*pT[j]);
			//hpt->Fill(pT[j]);
		}
		if (ntrack > 2){
			a1 = a1 + Q1/ntrack;
			a2 = a2 + ((Q1*Q1) - Q2)/(ntrack*(ntrack-1));
			a3 = a3 + ((Q1*Q1*Q1)-(3*Q2*Q1)+(2*Q3))/(ntrack*(ntrack-1)*(ntrack-2));
		}
	}
	a1 = a1/nentries;
	a2 = a2/nentries;
	a3 = a3/nentries;

	Double_t avp1 = a1;
	Double_t dp1dp2dp3 = a3 - (3*a2*a1) + (2*a1*a1*a1);
	Double_t dp1dp2 = a2 - (a1*a1);
	Double_t GGamma = (dp1dp2dp3*avp1)/(dp1dp2*dp1dp2);
	cout<<GGamma<<endl;
	
}
