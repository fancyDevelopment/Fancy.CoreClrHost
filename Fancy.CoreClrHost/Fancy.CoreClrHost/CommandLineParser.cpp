#include "CommandLineParser.h"

#include "Util.h"

// Processes the entire command line into the "CommandLineArgs" structure
// Returns true if the processing was successfull; otherwise, false
bool ProcessCommandLine(int argc, _TCHAR* argv[], CommandLineArgs* pCommandLineArgs)
{
	// Iterate through each argument and call the process method for each
	// Start at the second argument, the first ist the application itself
	for (int i = 1; i < argc; i++)
	{
		wstring currentArg = wstring(argv[i]);

		int endOfCommand = currentArg.find_first_of(L':');
		wstring currentArgName = currentArg.substr(0, endOfCommand);
		wstring currentValue = currentArg.substr(endOfCommand + 1, currentArg.length());

		if (!ProcessCommandLineArg(currentArgName, currentValue, pCommandLineArgs))
		{
			return false;
		}
	}

	return true;
}

// Processes a single command line argument into the "CommandLineArgs" structure
// Returns true if the processing was successfull; otherwise, false
bool ProcessCommandLineArg(wstring arg, wstring value, CommandLineArgs* pCommandLineArgs)
{
	// Check for all parameters and add the value into the correct field of the struct.
	if (arg == L"--CoreClrFolderPath")
	{
		if (!HasEnding(value, L"\\"))
		{
			printf_s("Argument --CoreClrFolderPath hat to end with a backslash (\\)", value);
			return false;
		}

		pCommandLineArgs->CoreClrFolderPath = value;
	}
	else if (arg == L"--AppFolderPath")
	{
		if (!HasEnding(value, L"\\"))
		{
			printf_s("Argument --AppFolderPath hat to end with a backslash (\\)", value);
			return false;
		}

		pCommandLineArgs->AppFolderPath = value;
	}
	else if (arg == L"--EntryPointAssemblyName")
	{
		pCommandLineArgs->EntryPointAssemblyName = value;
	}
	else if (arg == L"--EntryPointTypeName")
	{
		pCommandLineArgs->EntryPointTypeName = value;
	}
	else if (arg == L"--EntryPointMethodName")
	{
		pCommandLineArgs->EntryPointMethodName = value;
	}
	else
	{
		printf_s("Unknown argument: %S", arg);
		return false;
	}

	return true;
}