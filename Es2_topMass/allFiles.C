{

    TFile* fileTopM166 = new TFile("TopMass_m166.root");
    TTree* treeTop166 = (TTree*)fileTopM166->Get("Top");
    Top topAna166(treeTop166);
    topAna166.Loop("outFile_m166.root");
    /*
    TFile* fileTopM168 = new TFile("TopMass_m168.root");
    TTree* treeTop168 = (TTree*)fileTopM168->Get("Top");
    Top topAna168(treeTop168);
    topAna168.Loop("outFile_m168.root");

    TFile* fileTopM170 = new TFile("TopMass_m170.root");
    TTree* treeTop170 = (TTree*)fileTopM170->Get("Top");
    Top topAna170(treeTop170);
    topAna170.Loop("outFile_m170.root");

    TFile* fileTopM172 = new TFile("TopMass_m172.root");
    TTree* treeTop172 = (TTree*)fileTopM172->Get("Top");
    Top topAna172(treeTop172);
    topAna172.Loop("outFile_m172.root");

    TFile* fileTopM174 = new TFile("TopMass_m174.root");
    TTree* treeTop174 = (TTree*)fileTopM174->Get("Top");
    Top topAna174(treeTop174);
    topAna174.Loop("outFile_m174.root");
    

    TFile* fileTopM176 = new TFile("TopMass_m176.root");
    TTree* treeTop176 = (TTree*)fileTopM176->Get("Top");
    Top topAna176(treeTop176);
    topAna176.Loop("outFile_m176.root");

    TFile* fileTopData = new TFile("TopMass_pseudoData.root");
    TTree* treeTopData = (TTree*)fileTopData->Get("Top");
    Top topAnaData(treeTopData);
    topAnaData.Loop("outFile_pseudoData.root");
*/
}