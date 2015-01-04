#pragma once

// Include common headers
#include "Common.h"

// Parameters required to load and run the core clr
struct CoreClrStartParams
{
	wstring CoreClrFilePath;

	wstring AppBase;

	wstring AppPaths;

	wstring FullTrustedAssembliePaths;

	wstring EntryPointAssemblyName;

	wstring EntryPointTypeName;

	wstring EntryPointMethodName;
};

// Loads and runs the core clr with the specified params
bool LoadAndRunCoreClr(CoreClrStartParams* pCoreClrStartupParams);