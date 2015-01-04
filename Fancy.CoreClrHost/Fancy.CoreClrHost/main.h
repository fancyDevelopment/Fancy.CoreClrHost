#pragma once

// Include the windows sdk version.
#include <SDKDDKVer.h>

// Windows Headers
// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// Include common header files
#include <stdio.h>
#include <tchar.h>

// Include common stuff required from standard template library
#include <vector>
#include <string>

using namespace std;


// Include application headers
