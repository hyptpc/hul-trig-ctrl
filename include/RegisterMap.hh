// -*- C++ -*-

#ifndef REGISTER_MAP_HH
#define REGISTER_MAP_HH

#include <string>

static const uint32_t NumOfRegion2 = 6;

//_____________________________________________________________________________
namespace RGN1
{
static const uint32_t mid = 0x1;
enum ELocalAddress
{
  kSEL_TOF = 0x000, // W/R, [23:0], select TOF segment
};
}

//_____________________________________________________________________________
namespace RGN2
{
static const uint32_t mid = 0x2;
enum ELocalAddress
{
  // BEAM
  kDELAY_BH1_BEAM    = 0xa00, // W/R, [7:0], select delay
  kDELAY_BH2_BEAM    = 0xa10, // W/R, [7:0], select delay
  kDELAY_BAC_BEAM    = 0xa20, // W/R, [7:0], select delay
  kDELAY_HTOF_BEAM   = 0xa30, // W/R, [7:0], select delay
  kDELAY_OTHER1_BEAM = 0xa40, // W/R, [7:0], select delay
  kDELAY_OTHER2_BEAM = 0xa50, // W/R, [7:0], select delay
  kWIDTH_BH1_BEAM    = 0xb00, // W/R, [6:0], select width
  kWIDTH_BH2_BEAM    = 0xb10, // W/R, [6:0], select width
  kWIDTH_BAC_BEAM    = 0xb20, // W/R, [6:0], select width
  kWIDTH_HTOF_BEAM   = 0xb30, // W/R, [6:0], select width
  kWIDTH_OTHER1_BEAM = 0xb40, // W/R, [6:0], select width
  kWIDTH_OTHER2_BEAM = 0xb50, // W/R, [6:0], select width
  kBPS_CTRL_BEAM     = 0xc00, // W/R, [5:0], select coin
  kBPS_COIN_BEAM     = 0xc10, // W/R, [5:0], select cion
  // SCAT
  kDELAY_BEAM_SCAT   = 0xd00, // W/R, [7:0], select delay
  kDELAY_PVAC_SCAT   = 0xd10, // W/R, [7:0], select delay
  kDELAY_FAC_SCAT    = 0xd20, // W/R, [7:0], select delay
  kDELAY_TOF_SCAT    = 0xd30, // W/R, [7:0], select delay
  kDELAY_LAC_SCAT    = 0xd40, // W/R, [7:0], select delay
  kDELAY_WC_SCAT     = 0xd50, // W/R, [7:0], select delay
  kDELAY_M2D1_SCAT   = 0xd60, // W/R, [7:0], select delay
  kDELAY_M2D2_SCAT   = 0xd70, // W/R, [7:0], select delay
  kDELAY_M3D_SCAT    = 0xd80, // W/R, [7:0], select delay
  kDELAY_OTHER3_SCAT = 0xd90, // W/R, [7:0], select delay
  kDELAY_OTHER4_SCAT = 0xda0, // W/R, [7:0], select delay
  kWIDTH_BEAM_SCAT   = 0xe00, // W/R, [6:0], select width
  kWIDTH_PVAC_SCAT   = 0xe10, // W/R, [6:0], select width
  kWIDTH_FAC_SCAT    = 0xe20, // W/R, [6:0], select width
  kWIDTH_TOF_SCAT    = 0xe30, // W/R, [6:0], select width
  kWIDTH_LAC_SCAT    = 0xe40, // W/R, [6:0], select width
  kWIDTH_WC_SCAT     = 0xe50, // W/R, [6:0], select width
  kWIDTH_M2D1_SCAT   = 0xe60, // W/R, [6:0], select width
  kWIDTH_M2D2_SCAT   = 0xe70, // W/R, [6:0], select width
  kWIDTH_M3D_SCAT    = 0xe80, // W/R, [6:0], select width
  kWIDTH_OTHER3_SCAT = 0xe90, // W/R, [6:0], select width
  kWIDTH_OTHER4_SCAT = 0xea0, // W/R, [6:0], select width
  kBPS_CTRL_SCAT     = 0xf00, // W/R, [10:0], select coin
  kBPS_COIN_SCAT     = 0xf10, // W/R, [10:0], select cion
};
}

//_____________________________________________________________________________
namespace RGN3
{
static const uint32_t mid = 0x8;
enum ELocalAddress
{
  kPS_R2A    = 0xa00, // W/R, [23:0], select Preset Scale Value(0 ~ 2^24-1)
  kPS_R2B    = 0xa10, // W/R, [23:0], select Preset Scale Value(0 ~ 2^24-1)
  kPS_R2C    = 0xa20, // W/R, [23:0], select Preset Scale Value(0 ~ 2^24-1)
  kPS_R2D    = 0xa30, // W/R, [23:0], select Preset Scale Value(0 ~ 2^24-1)
  kPS_R2E    = 0xa40, // W/R, [23:0], select Preset Scale Value(0 ~ 2^24-1)
  kPS_R2F    = 0xa50, // W/R, [23:0], select Preset Scale Value(0 ~ 2^24-1)
  kGATE_R2A  = 0xb00, // W/R, [23:0], select Preset Scale Value(0 ~ 2^24-1)
  kGATE_R2B  = 0xb10, // W/R, [23:0], select Preset Scale Value(0 ~ 2^24-1)
  kGATE_R2C  = 0xb20, // W/R, [23:0], select Preset Scale Value(0 ~ 2^24-1)
  kGATE_R2D  = 0xb30, // W/R, [23:0], select Preset Scale Value(0 ~ 2^24-1)
  kGATE_R2E  = 0xb40, // W/R, [23:0], select Preset Scale Value(0 ~ 2^24-1)
  kGATE_R2F  = 0xb50, // W/R, [23:0], select Preset Scale Value(0 ~ 2^24-1)
  kSEL_PSOR  = 0xe00, // W/R, [5:0], select trigger ps OR
  kRST_PSCNT = 0xe10, // W/R, [0:0],
};
}

//_____________________________________________________________________________
namespace RGN4
{
static const uint32_t mid = 0x9;
enum ELocalAddress
  {
    kSEL_EXTCLK  = 0x010, // W/R, [0],
    kSEL_RSV2    = 0x020, // W/R, [0],
    kSEL_CLK10M  = 0x030, // W/R, [0],
    kSEL_CLK1M   = 0x040, // W/R, [0],
    kSEL_CLK100k = 0x050, // W/R, [0],
    kSEL_CLK10k  = 0x060, // W/R, [0],
    kSEL_CLK1k   = 0x070, // W/R, [0],
    kGATE        = 0x080, // W/R, [1:0],
  };
}

//_____________________________________________________________________________
namespace IOM
{
static const uint32_t mid = 0xa;
enum ELocalAddress{
  NIMOUT1           = 0x010, // W/R, [5:0],NIMOUT1 select sig
  NIMOUT2           = 0x020, // W/R, [5:0],NIMOUT2 select sig
  NIMOUT3           = 0x030, // W/R, [5:0],NIMOUT3 select sig
  NIMOUT4           = 0x040  // W/R, [5:0],NIMOUT4 select sig
};
};

//_____________________________________________________________________________
namespace BCT
{
static const uint32_t mid = 0xe;
enum ELocalAddress{
  Reset    = 0x000, // W/-, assert reset signal from BCT
  Version  = 0x010, // -/R, [31:0]
  ReConfig = 0x020  // W/-, Reconfig FPGA by SPI
};
static const uint32_t kVersionLen = 4;
}

#endif
