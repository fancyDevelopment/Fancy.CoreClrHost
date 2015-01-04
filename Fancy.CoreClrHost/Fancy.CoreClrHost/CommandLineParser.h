#pragma once

// Include common headers
#include "Common.h"

// Struct to store the provided argument values from command line
struct CommandLineArgs
{
	wstring CoreClrFolderPath;

	wstring AppFolderPath;

	wstring EntryPointAssemblyName;

	wstring EntryPointTypeName;

	wstring EntryPointMethodName;
};

// Processes the entire command line into the "CommandLineArgs" structure
// Returns true if the processing was successfull; otherwise, false
bool ProcessCommandLine(int argc, _TCHAR* argv[], CommandLineArgs* pCommandLineArgs);

// Processes a single command line argument into the "CommandLineArgs" structure
// Returns true if the processing was successfull; otherwise, false
bool ProcessCommandLineArg(wstring arg, wstring value, CommandLineArgs* pCommandLineArgs);