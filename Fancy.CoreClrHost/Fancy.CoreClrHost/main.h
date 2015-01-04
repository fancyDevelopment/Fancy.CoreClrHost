#pragma once

// Include common headers
#include "Common.h"

// Include required headers from application 
#include "CommandLineParser.h"
#include "LoadAndRunCoreClr.h"

// Function to fill the "CoreClrStartParams" structure
bool FillCoreClrStartParams(CommandLineArgs* pCommandLineArgs, CoreClrStartParams* pCoreClrStartParams);