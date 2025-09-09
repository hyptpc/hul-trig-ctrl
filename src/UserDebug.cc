// -*- C++ -*-

#include <iostream>
#include <string>

#include "FPGAModule.hh"
#include "RegisterMap.hh"

//_____________________________________________________________________________
int
main(int argc, char* argv[])
{
  FPGAModule module("192.168.10.51");
  int v = module.ReadModule(BCT::mid, BCT::Version, BCT::kVersionLen);
  std::cout << std::hex << v << std::endl;
  return 0;
}
