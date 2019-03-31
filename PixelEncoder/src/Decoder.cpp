// Pixel Decoder
// Anthony McIntyre, July 2018
// Decodes binary file to pixels for consistency checking

#include "Decoder.h"

int Decoder::decodeRoc32(uint32_t line, int count) {
    int hits = 0;
    uint32_t buf = 0;
    uint32_t bits = 32 / count;
    for(uint32_t i = 0; i < count; i++) {
        buf = line << (i * bits);
        buf >>= (count * bits) - bits;
        hits += (int)buf;
    }
    return hits;
}

int Decoder::decodeRoc64(uint64_t line, int count) {
    int hits = 0;
    uint64_t buf = 0;
    uint64_t bits = 64 / count;
    for(uint64_t i = 0; i < count; i++) {
        buf = line << (i * bits);
        buf >>= (count * bits) - bits;
        hits += (int)buf;
    }
    return hits;
}

int Decoder::open(std::string filename, int chanBase) {
    std::ifstream file(filename.c_str(), std::ios::binary | std::ios::in | std::ios::ate);
    const int FILESIZE = 8388612;
    int blocksize = (FILESIZE - 4) / 16;
    if ((int)file.tellg() != FILESIZE)
        return 0;
    file.seekg(0);
    uint32_t headerBuffer;
    uint32_t header;
    uint32_t line32;
    uint64_t line64;
    int hits;
    file.read((char*)&headerBuffer, 4);
    for (int i = 0; i < 16; i++) {
        header = headerBuffer << (i * 2);
        header >>= (30);
        int chanID = chanBase + i;
        std::cout << "Processing channel " << chanID << '\n';
        switch (header) {
            case 0:
                for (int j = 0; j < blocksize / 4; j) {
                    line32 = 0;
                    hits = 0;
                    file.read( (char*) &line32, 4);
                    hits = decodeRoc32(line32, 2);
                    hitmap[chanID].push_back(hits);
                    if (hits > maxhits) {maxhits = hits;}
                }
                break;
            case 1:
                for (int j = 0; j < blocksize / 4; j++) {
                    line32 = 0;
                    hits = 0;
                    file.read( (char*) &line32, 4);
                    hits = decodeRoc32(line32, 4);
                    hitmap[chanID].push_back(hits);
                    if (hits > maxhits) {maxhits = hits;}
                }
                break;
            case 2:
                for (int j = 0; j < blocksize / 4; j++) {
                    line32 = 0;
                    hits = 0;
                    file.read( (char*) &line32, 4);
                    hits = decodeRoc32(line32, 8);
                    hitmap[chanID].push_back(hits);
                    if (hits > maxhits) {maxhits = hits;}
                }
                break;
            case 3:
                for (int j = 0; j < blocksize / 8; j++) {
                    line64 = 0;
                    hits = 0;
                    file.read( (char*) &line64, 8);
                    hits = decodeRoc64(line64, 8);
                    hitmap[chanID].push_back(hits);
                    if (hits > maxhits) {maxhits = hits;}
                }
                break;
            default:
                std::cout<<"Error: Incorrect header format.\n";
        }
    }
    file.close();
    return 1;
}

void Decoder::graph(std::string path) {
    std::cout << "Highest hits in a channel: " << maxhits << '\n';
    gStyle->SetPalette(55);
    TH2D* hFEDChan = new TH2D("Binary", "Hits per Channel in Binary Files;Channel;Number of Hits",
                         48, 1., 49., ((float)maxhits * 1.5),
                         -0.5, ((float)maxhits * 1.5) - 0.5);
    hFEDChan->SetOption("COLZ");
    for (auto const& chan : hitmap) {
        for (int hits : chan.second) {
            hFEDChan->Fill(chan.first, hits);
        }
    }
    TCanvas* canvas = new TCanvas("canvas");
    hFEDChan->Draw();
    std::string filename = path + "histogram_binary.pdf";
    
    TString cmsText = "CMS";
    int cmsTextFont = 61;
    float cmsTextSize = 0.50;
    TString extraText = "Preliminary";
    int extraTextFont = 52;
    float extraOverCmsTextSize  = 0.76;
    float extraTextSize = extraOverCmsTextSize*cmsTextSize;
    float H = canvas->GetWh();
    float W = canvas->GetWw();
    float l = canvas->GetLeftMargin();
    float t = canvas->GetTopMargin();
    float r = canvas->GetRightMargin();
    float b = canvas->GetBottomMargin();
    float relExtraDY = 3.5;
    float align_ = 23.0;
    float posX_ = 8.0;
    float posY_ = H - 10.5;
    TLatex latex;
    latex.SetTextFont(cmsTextFont);
    latex.SetTextSize(cmsTextSize*t);
    latex.SetTextAlign(align_);
    latex.DrawLatex(posX_, posY_, cmsText);
    latex.SetTextFont(extraTextFont);
    latex.SetTextAlign(align_);
    latex.SetTextSize(extraTextSize*t);
    latex.DrawLatex(posX_+2, posY_- relExtraDY*cmsTextSize*b, extraText);
    
    canvas->Print(filename.c_str());
}

