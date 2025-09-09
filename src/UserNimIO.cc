// -*- C++ -*-

#include <iostream>
#include <libgen.h>

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
    return EXIT_SUCCESS;
  }

  SlowController sc;
  sc.SetParamFile(argv[kParamFile]);
  sc.SetOutFile("nimio.log");
  sc.SetFPGAModule(new FPGAModule("192.168.10.51"));
  sc.Write(IOM::mid, IOM::NIMOUT1, "IOM::NIMOUT1");
  sc.Write(IOM::mid, IOM::NIMOUT2, "IOM::NIMOUT2");
  sc.Write(IOM::mid, IOM::NIMOUT3, "IOM::NIMOUT3");
  sc.Write(IOM::mid, IOM::NIMOUT4, "IOM::NIMOUT4");

  std::cout << "Successfully finished!" << std::endl;
  return EXIT_SUCCESS;
}
