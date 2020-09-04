#ifndef _GLOBALS_H_        // include guard 
#define _GLOBALS_H_ 

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <bitset>
#include <vector>
#include <cstdint>
#include <ostream>


//ROOT 
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include "TSystem.h"
#include "TROOT.h"
#include <TEnv.h>
#include <TH2D.h>
#include <TH1D.h>

const int VERBOSITY_LEVEL = 3;

// User can define "win" or "unix"
const std::string SYSTEM_SEL {"win"};

const std::string backslash  {"\\"};
const std::string forwardslash  {"/"};

#endif
