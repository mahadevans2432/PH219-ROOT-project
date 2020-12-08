
double GGamma_pT_calc(int fla)
{
	TFile *f=new TFile("13TeV_CR0_RHoff.root");
	TTree *tree = (TTree*)f->Get("pytree");
	if (fla==1){tree = (TTree*)f->Get("pytree020");}
	else if (fla==2){tree = (TTree*)f->Get("pytree2040");}
	else if (fla==3){tree = (TTree*)f->Get("pytree4060");}
	else if (fla==4){tree = (TTree*)f->Get("pytree6080");}
	else {tree = (TTree*)f->Get("pytree80100");}

	
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
		if (ntrack > 0){
			a1 = a1 + (Q1/ntrack);
		}
		if (ntrack > 1){
			a2 = a2 + ((Q1*Q1) - Q2)/(ntrack*(ntrack-1));
		}
		if (ntrack > 2){
			a3 = a3 + ((Q1*Q1*Q1)-(3*Q2*Q1)+(2*Q3))/(ntrack*(ntrack-1)*(ntrack-2));
		}
	}
	a1 = a1/nentries;
	a2 = a2/nentries;
	a3 = a3/nentries;

	Double_t avp1 = a1;
	Double_t dp1dp2dp3 = a3 - (3*a2*a1) + (2*a1*a1*a1);
	Double_t dp1dp2 = a2 - (a1*a1);
	double GGamma = (dp1dp2dp3*avp1)/(dp1dp2*dp1dp2);
	return GGamma;
	
}

void GGamma_pT(){
	TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);
    c1->SetGrid();
	double values[5];
	Double_t x[5];
	for(int i=1; i<=5; i++){
		values[i-1] = GGamma_pT_calc(i);
		x[i-1] = 20*i;
	}
	
	TGraph *gr = new TGraph(5,x,values);
	gr->SetTitle("Intensive skewness");
    gr->GetXaxis()->SetTitle("Multiplicity");
    gr->GetYaxis()->SetTitle("Gamma_pT");
    gr->Draw();
}
