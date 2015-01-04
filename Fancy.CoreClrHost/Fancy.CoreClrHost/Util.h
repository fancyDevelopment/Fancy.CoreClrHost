#pragma once

// Include common headers
#include "Common.h"

// Function to check the endig of a string
bool HasEnding(wstring const &fullString, wstring const &ending);

// Function to list all files in a specific directory with a specified pattern
vector<wstring> ListFilesInDirectoryByPattern(LPCWSTR directoryName);