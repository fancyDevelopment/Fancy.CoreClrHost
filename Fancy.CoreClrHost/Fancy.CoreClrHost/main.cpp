#include "main.h"

#include "Util.h"

int _tmain(int argc, _TCHAR* argv[])
{
	// Process the command line args
	CommandLineArgs commanLineArgs;
	if (!ProcessCommandLine(argc, argv, &commanLineArgs))
	{
		printf_s("Could not process the command line args");
		return 1;
	}

	// Create the core clr startup params from the command line args
	CoreClrStartParams coreClrStartupParams;
	if (!FillCoreClrStartParams(&commanLineArgs, &coreClrStartupParams))
	{
		printf_s("Could create the core clr startup params.\n");
		return 1;
	}

	if (!LoadAndRunCoreClr(&coreClrStartupParams))
	{
		printf_s("Error on loading the core clr or running the managed code.\n");
		return 1;
	}

	return 0;
}

// Function to fill the "CoreClrStartParams" structure
bool FillCoreClrStartParams(CommandLineArgs* pCommandLineArgs, CoreClrStartParams* pCoreClrStartParams)
{
	// Create path to core clr
	pCoreClrStartParams->CoreClrFilePath = pCommandLineArgs->CoreClrFolderPath;
	pCoreClrStartParams->CoreClrFilePath.append(L"coreclr.dll");

	// Set up the app base
	pCoreClrStartParams->AppBase = pCommandLineArgs->AppFolderPath;

	// Set up the app paths
	pCoreClrStartParams->AppPaths = pCommandLineArgs->CoreClrFolderPath + L";" + pCommandLineArgs->AppFolderPath;

	// For simplicity we add here all assemblies of the core clr to the list of fully trusted assemblies
	wstring searchPattern = pCommandLineArgs->CoreClrFolderPath;
	searchPattern.append(L"*.dll");
	vector<wstring> files = ListFilesInDirectoryByPattern(searchPattern.c_str());

	// Append the path to the assemblies to the full path to all full trusted assemblies
	wstring fullTrustedAssemblies;

	for (unsigned int i = 0; i < files.size(); i++)
	{
		fullTrustedAssemblies.append(pCommandLineArgs->CoreClrFolderPath);
		fullTrustedAssemblies.append(files[i]);
		fullTrustedAssemblies.append(L";");
	}

	pCoreClrStartParams->FullTrustedAssembliePaths = fullTrustedAssemblies;
	
	// Copy the params regarding the managed entry point
	pCoreClrStartParams->EntryPointAssemblyName = pCommandLineArgs->EntryPointAssemblyName;
	pCoreClrStartParams->EntryPointTypeName = pCommandLineArgs->EntryPointTypeName;
	pCoreClrStartParams->EntryPointMethodName = pCommandLineArgs->EntryPointMethodName;

	return true;
}

