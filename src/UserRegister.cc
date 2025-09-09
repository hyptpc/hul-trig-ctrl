// -*- C++ -*-

#include <bitset>
#include <iostream>
#include <numeric>
#include <libgen.h>

#include "BitPatternSelector.hh"
#include "DetectorID.hh"
#include "FPGAModule.hh"
#include "RegisterMap.hh"
#include "SlowController.hh"

enum EArgv { kProcess, kParamFile, kArgc };

//_____________________________________________________________________________
int
main(int argc, char* argv[])
{
  if(argc != kArgc){
    std::cout << "Usage " << ::basename(argv[kProcess])
              << " [param file]" << std::endl;
    return 0;
  }

  SlowController sc;
  // sc.SetVerbose();
  sc.SetOutFile("last.log");
  sc.SetParamFile(argv[kParamFile]);
  sc.SetFPGAModule(new FPGAModule("192.168.10.51"));

  { // Region1 ________________________________________________________________
    using namespace RGN1;
    std::bitset<NumOfSegTOF> tof_bit;
    for(int i=0, n=tof_bit.size(); i<n; ++i){
      tof_bit[i] = sc.Get("RGN1::TOF_SEG" + std::to_string(i + 1));
    }
    sc.Write(mid, kSEL_TOF, "RGN1::SEL_TOF",
              tof_bit.to_ulong(), 3);
  }

  { // Region2 ________________________________________________________________
    using namespace RGN2;
    for(int i=0, n=NumOfRegion2; i<n; ++i){
      std::string head("RGN2");
      head += 'A' + i;
      head += "::";
      sc.Write(mid+i, kDELAY_BH1_BEAM, head+"DELAY_BH1_BEAM");
      sc.Write(mid+i, kDELAY_BH2_BEAM, head+"DELAY_BH2_BEAM");
      sc.Write(mid+i, kDELAY_BAC_BEAM, head+"DELAY_BAC_BEAM");
      sc.Write(mid+i, kDELAY_HTOF_BEAM, head+"DELAY_HTOF_BEAM");
      sc.Write(mid+i, kDELAY_OTHER1_BEAM, head+"DELAY_OTHER1_BEAM");
      sc.Write(mid+i, kDELAY_OTHER2_BEAM, head+"DELAY_OTHER2_BEAM");
      sc.Write(mid+i, kWIDTH_BH1_BEAM, head+"WIDTH_BH1_BEAM");
      sc.Write(mid+i, kWIDTH_BH2_BEAM, head+"WIDTH_BH2_BEAM");
      sc.Write(mid+i, kWIDTH_BAC_BEAM, head+"WIDTH_BAC_BEAM");
      sc.Write(mid+i, kWIDTH_HTOF_BEAM, head+"WIDTH_HTOF_BEAM");
      sc.Write(mid+i, kWIDTH_OTHER1_BEAM, head+"WIDTH_OTHER1_BEAM");
      sc.Write(mid+i, kWIDTH_OTHER2_BEAM, head+"WIDTH_OTHER2_BEAM");
      std::vector<int> beam_coin = {
        sc.Get(head+"COIN_BH1"),
        sc.Get(head+"COIN_BH2"),
        sc.Get(head+"COIN_BAC"),
        sc.Get(head+"COIN_HTOF"),
        sc.Get(head+"COIN_OTHER1"),
        sc.Get(head+"COIN_OTHER2")
      };
      sc.Write(mid+i, kBPS_CTRL_BEAM, head+"BPS_CTRL_BEAM",
                BitPatternSelector::Ctrl(beam_coin));
      sc.Write(mid+i, kBPS_COIN_BEAM, head+"BPS_COIN_BEAM",
                BitPatternSelector::Coin(beam_coin));
      sc.Write(mid+i, kDELAY_BEAM_SCAT, head+"DELAY_BEAM_SCAT");
      sc.Write(mid+i, kDELAY_PVAC_SCAT, head+"DELAY_PVAC_SCAT");
      sc.Write(mid+i, kDELAY_FAC_SCAT, head+"DELAY_FAC_SCAT");
      sc.Write(mid+i, kDELAY_TOF_SCAT, head+"DELAY_TOF_SCAT");
      sc.Write(mid+i, kDELAY_LAC_SCAT, head+"DELAY_LAC_SCAT");
      sc.Write(mid+i, kDELAY_WC_SCAT, head+"DELAY_WC_SCAT");
      sc.Write(mid+i, kDELAY_M2D1_SCAT, head+"DELAY_M2D1_SCAT");
      sc.Write(mid+i, kDELAY_M2D2_SCAT, head+"DELAY_M2D2_SCAT");
      sc.Write(mid+i, kDELAY_M3D_SCAT, head+"DELAY_M3D_SCAT");
      sc.Write(mid+i, kDELAY_OTHER3_SCAT, head+"DELAY_OTHER3_SCAT");
      sc.Write(mid+i, kDELAY_OTHER4_SCAT, head+"DELAY_OTHER4_SCAT");
      sc.Write(mid+i, kWIDTH_BEAM_SCAT, head+"WIDTH_BEAM_SCAT");
      sc.Write(mid+i, kWIDTH_PVAC_SCAT, head+"WIDTH_PVAC_SCAT");
      sc.Write(mid+i, kWIDTH_FAC_SCAT, head+"WIDTH_FAC_SCAT");
      sc.Write(mid+i, kWIDTH_TOF_SCAT, head+"WIDTH_TOF_SCAT");
      sc.Write(mid+i, kWIDTH_LAC_SCAT, head+"WIDTH_LAC_SCAT");
      sc.Write(mid+i, kWIDTH_WC_SCAT, head+"WIDTH_WC_SCAT");
      sc.Write(mid+i, kWIDTH_M2D1_SCAT, head+"WIDTH_M2D1_SCAT");
      sc.Write(mid+i, kWIDTH_M2D2_SCAT, head+"WIDTH_M2D2_SCAT");
      sc.Write(mid+i, kWIDTH_M3D_SCAT, head+"WIDTH_M3D_SCAT");
      sc.Write(mid+i, kWIDTH_OTHER3_SCAT, head+"WIDTH_OTHER3_SCAT");
      sc.Write(mid+i, kWIDTH_OTHER4_SCAT, head+"WIDTH_OTHER4_SCAT");
      std::vector<int> scat_coin = {
        sc.Get(head+"COIN_BEAM"),
        sc.Get(head+"COIN_PVAC"),
        sc.Get(head+"COIN_FAC"),
        sc.Get(head+"COIN_TOF"),
        sc.Get(head+"COIN_LAC"),
        sc.Get(head+"COIN_WC"),
        sc.Get(head+"COIN_M2D1"),
        sc.Get(head+"COIN_M2D2"),
        sc.Get(head+"COIN_M3D"),
        sc.Get(head+"COIN_OTHER3"),
        sc.Get(head+"COIN_OTHER4")
      };
      sc.Write(mid+i, kBPS_CTRL_SCAT, head+"BPS_CTRL_SCAT",
                BitPatternSelector::Ctrl(scat_coin), 2);
      sc.Write(mid+i, kBPS_COIN_SCAT, head+"BPS_COIN_SCAT",
                BitPatternSelector::Coin(scat_coin), 2);
    }
  }

  { // Region3 ________________________________________________________________
    using namespace RGN3;
    std::vector<int> psor_ctrl(NumOfRegion2);
    for(int i=0, n=NumOfRegion2; i<n; ++i){
      std::string foot("R2");
      foot += 'A' + i;
      sc.Write(mid, kPS_R2A + 0x010*i, "RGN3::PS_"+foot,
                sc.Get("RGN3::PS_"+foot)-1, 3);
      sc.Write(mid, kGATE_R2A + 0x010*i, "RGN3::GATE_"+foot);
      psor_ctrl[n-i-1] = sc.Get("RGN3::SEL_"+foot);
    }
    sc.Write(mid, kSEL_PSOR, "RGN3::SEL_PSOR",
              BitPatternSelector::Coin(psor_ctrl));
    sc.Write(mid, kRST_PSCNT, "RGN3::RST_PSCNT", 1, 0);
  }

  { // Region4 ________________________________________________________________
    using namespace RGN4;
    sc.Write(mid, kSEL_EXTCLK, "RGN4::SEL_EXTCLK");
    sc.Write(mid, kSEL_RSV2, "RGN4::SEL_RSV2");
    sc.Write(mid, kSEL_CLK10M, "RGN4::SEL_CLK10M");
    sc.Write(mid, kSEL_CLK1M, "RGN4::SEL_CLK1M");
    sc.Write(mid, kSEL_CLK100k, "RGN4::SEL_CLK100k");
    sc.Write(mid, kSEL_CLK10k, "RGN4::SEL_CLK10k");
    sc.Write(mid, kSEL_CLK1k, "RGN4::SEL_CLK1k");
    sc.Write(mid, kGATE, "RGN4::GATE");
  }

  std::cout << "Successfully finished!" << std::endl;
  return EXIT_SUCCESS;
}
