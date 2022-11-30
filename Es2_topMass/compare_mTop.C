#include "TCanvas.h"
#include "TFile.h"
#include "TGraph.h"
#include "TH1F.h"
#include "TLegend.h"
#include "TGraphErrors.h"

void compare_mTop() {
    // Retrieval of all the mass plots after the kinematic fit for the MC with known mTop
    TFile *f176 = TFile::Open("outFile_m176.root");
    TH1F *h176 = (TH1F *)f176->Get("h_mt");
    h176->SetName("mt176");
    h176->SetLineWidth(2);
    h176->SetLineColor(kBlack);

    TFile *f174 = TFile::Open("outFile_m174.root");
    TH1F *h174 = (TH1F *)f174->Get("h_mt");
    h174->SetName("mt174");
    h174->SetLineWidth(2);
    h174->SetLineColor(kGreen);

    TFile *f172 = TFile::Open("outFile_m172.root");
    TH1F *h172 = (TH1F *)f172->Get("h_mt");
    h172->SetName("mt172");
    h172->SetLineWidth(2);
    h172->SetLineColor(kBlue);

    TFile *f170 = TFile::Open("outFile_m170.root");
    TH1F *h170 = (TH1F *)f170->Get("h_mt");
    h170->SetName("mt170");
    h170->SetLineWidth(2);
    h170->SetLineColor(kRed);

    TFile *f168 = TFile::Open("outFile_m168.root");
    TH1F *h168 = (TH1F *)f168->Get("h_mt");
    h168->SetName("mt168");
    h168->SetLineWidth(2);
    h168->SetLineColor(kOrange);

    TFile *f166 = TFile::Open("outFile_m166.root");
    TH1F *h166 = (TH1F *)f166->Get("h_mt");
    h166->SetName("mt166");
    h166->SetLineWidth(2);
    h166->SetLineColor(kMagenta);

    // Retrieval of mass  after the kinematic fit for pseudodata of unknown mTop
    TFile *f_pseudoData = TFile::Open("outFile_pseudoData.root");
    TH1F *h_pseudoData = (TH1F *)f_pseudoData->Get("h_mt");
    h_pseudoData->SetName("mt_pseudoData");
    h_pseudoData->SetLineWidth(3);
    h_pseudoData->SetLineStyle(2);

    // Drawing templates with different colors for visual comparison
    TCanvas *c = new TCanvas("c", "c");
    h_pseudoData->Draw("e0");
    h166->Draw("sames");
    h168->Draw("sames");
    h170->Draw("sames");
    h172->Draw("sames");
    h174->Draw("sames");
    h176->Draw("sames");

    // Statistical comparison with chi2
    TGraphErrors *mTop_chi2 = new TGraphErrors();

    // Old TGraph
    //mTop_chi2->SetPoint(0, 166, h_pseudoData->Chi2Test(h166, "UUPCHI2OFUF"));
    //mTop_chi2->SetPoint(1, 168, h_pseudoData->Chi2Test(h168, "UUPCHI2OFUF"));
    //mTop_chi2->SetPoint(2, 170, h_pseudoData->Chi2Test(h170, "UUPCHI2OFUF"));
    //mTop_chi2->SetPoint(3, 172, h_pseudoData->Chi2Test(h172, "UUPCHI2OFUF"));
    //mTop_chi2->SetPoint(4, 174, h_pseudoData->Chi2Test(h174, "UUPCHI2OFUF"));
    //mTop_chi2->SetPoint(5, 176, h_pseudoData->Chi2Test(h176, "UUPCHI2OFUF"));

    // Filling graph with y errors (does not change the result at all but I wanted to try...)
    // variance of a chi^2 is 2*ndf
    double chi2;
    int ndf,igood;
    h_pseudoData->Chi2TestX(h166,chi2,ndf,igood,"UUPOFUF");
    mTop_chi2->SetPoint(0, 166, chi2);
    mTop_chi2->SetPointError(0, 0, sqrt(2*ndf));

    h_pseudoData->Chi2TestX(h168,chi2,ndf,igood, "UUPOFUF");
    mTop_chi2->SetPoint(1, 168, chi2);
    mTop_chi2->SetPointError(1, 0, sqrt(2*ndf));

    h_pseudoData->Chi2TestX(h170,chi2,ndf,igood, "UUPOFUF");
    mTop_chi2->SetPoint(2, 170, chi2);
    mTop_chi2->SetPointError(2, 0, sqrt(2*ndf));

    h_pseudoData->Chi2TestX(h172,chi2,ndf,igood, "UUPOFUF");
    mTop_chi2->SetPoint(3, 172, chi2);
    mTop_chi2->SetPointError(3, 0, sqrt(2*ndf));

    h_pseudoData->Chi2TestX(h174,chi2,ndf,igood, "UUPOFUF");
    mTop_chi2->SetPoint(4, 174, chi2);
    mTop_chi2->SetPointError(4, 0, sqrt(2*ndf));

    h_pseudoData->Chi2TestX(h176,chi2,ndf,igood, "UUPOFUF");
    mTop_chi2->SetPoint(5, 176, chi2);
    mTop_chi2->SetPointError(5, 0, sqrt(2*ndf));

    TCanvas *chi2_cv = new TCanvas("chi2_cv", "chi2_cv");
    mTop_chi2->Draw("A*");

    TF1 *f = new TF1("f","[0]+[1]*x+[2]*x^2");
    mTop_chi2->Fit("f");

    // retrieving fit parameters
    double b = f->GetParameter(1);
    double a = f->GetParameter(2);
    double eb = f->GetParError(1);
    double ea = f->GetParError(2);

    // finding x-coordinate of the parabola's vertex
    double m_top_final = -b/(2*a);

    //Evaluating error at 68% CL
    // Getting the chi2 minimum value
    double chi2Min = f->Eval(m_top_final);
    // incrementing it by 1
    chi2Min += 1;

    //solving parabola intersection with y = chi2min + 1
    // ax^2 + bx + c = chi2+1
    // ax^2 + bx + c' = 0 with c'= c-chi2-1
    double cPrime = f->GetParameter(0) - chi2Min;
    // Discriminant
    double D = pow(b,2) - 4*a*cPrime;
    D = sqrt(D);
    // Solutions
    double x1 = (-b-D)/(2*a);
    double x2 = (-b+D)/(2*a);

    //calculating left and right CL intervals
    // should be identical since the parabola is symmetric
    double eDx = x2-m_top_final;
    double eSx = m_top_final-x1;
    std::cout << "------------------------------" << std::endl;
    std::cout << "Estimated mt with 68% CL error:\n";
    if (eDx != eSx)
        std::cout << "Estimated top mass: (" << m_top_final << " + " << eDx << " - " << eSx << ") GeV;" << std::endl;
    else
        std::cout << "Estimated top mass: (" << m_top_final << " +- " << eDx << ") GeV;" << std::endl;

    std::string title = "Fitted quark top mass: (" + std::to_string(m_top_final) + " +- " + std::to_string(eDx) + ")GeV";
    mTop_chi2->SetTitle(title.c_str());
    // Drawing the 68% CL interval's extremes
    mTop_chi2->SetMarkerStyle(3);
    mTop_chi2->SetPoint(6,x1,chi2Min);
    mTop_chi2->SetPoint(7,x2,chi2Min);

    // evaluating the error on the top mass from the fitter errors
    // mtop = -b/2a -> (eMtop/mtop)^2 = (ea/a)^2 + (eb/b)^2
    double em_top_final = m_top_final*(sqrt(pow(ea/a,2)+pow(eb/b,2)));

    std::cout << "------------------------------" << std::endl;
    std::cout << "Estimated mt with fitter error:\n";
    std::cout << "Estimated top mass: (" << m_top_final << "+-" << em_top_final<< ") GeV;" << std::endl;
    std::cout << "------------------------------" << std::endl;
}