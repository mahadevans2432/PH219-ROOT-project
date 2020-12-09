double Svariance_calc(int fla)
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

    Double_t a1=0.0,a2=0.0;


    tree->SetBranchAddress("ntrack",&ntrack);
    tree->SetBranchAddress("pT",&pT);

	TH1D *av_pt = new TH1D("av_pt","Average transverse momentum",100,0.0,2.0);

	for(Int_t i=1; i<nentries; i++){

		tree->GetEntry(i);
		Double_t Q1 = 0.0;
		Double_t Q2 = 0.0;
		//tree->GetEntry(i);
		for(Int_t j=0; j<ntrack; j++){
			Q1 = Q1 + (pT[j]);
			Q2 = Q2 + (pT[j]*pT[j]);
			//hpt->Fill(pT[j]);
		}
		if (ntrack > 0){
			a1 = a1 + (Q1/ntrack);
		}
		if (ntrack > 1){
			a2 = a2 + ((Q1*Q1) - Q2)/(ntrack*(ntrack-1));
		}
	}
	a1 = a1/nentries;
	a2 = a2/nentries;

	Double_t avp1 = a1;
	Double_t dp1dp2 = a2 - (a1*a1);
	double var = sqrt(dp1dp2)/avp1;
	return var;
	
}

void Svariance(){
	TCanvas *c1 = new TCanvas("c1","Standardized Variance",200,10,700,500);
    c1->SetGrid();
	double values[5];
	Double_t x[5];
	for(int i=1; i<=5; i++){
		values[i-1] = Svariance_calc(i);
		x[i-1] = 20*i-10;
	}
	
	TGraph *gr = new TGraph(5,x,values);
	gr->SetTitle("Two particle correlator");
	gr->SetMarkerColor(4);
	gr->SetLineStyle(4);
    gr->SetMarkerSize(1.5);
    gr->SetMarkerStyle(21);
    gr->GetXaxis()->SetTitle("Multiplicity");
    gr->GetYaxis()->SetTitle("standard deviation/mean");
    // gr->Draw("AP");
    gr->Draw("ALP");
}
