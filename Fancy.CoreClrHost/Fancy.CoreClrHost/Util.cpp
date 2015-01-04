#include "Util.h"

// Function to check the endig of a string
bool HasEnding(wstring const &fullString, wstring const &ending)
{
	if (fullString.length() >= ending.length())
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	else
		return false;
}

// Function to list all files in a specific directory with a specified pattern
vector<wstring> ListFilesInDirectoryByPattern(LPCWSTR directoryName)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = ::FindFirstFile(directoryName, &FindFileData);

	vector<wstring> result;

	result.push_back(wstring(FindFileData.cFileName));

	while (FindNextFile(hFind, &FindFileData))
		result.push_back(wstring(FindFileData.cFileName));

	return result;
}