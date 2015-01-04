#include "LoadAndRunCoreClr.h"

#include "mscoree.h"

// Defines a pointer to a function which is the entry point to the managed code.
typedef void (STDMETHODCALLTYPE *ManagedEntryPoint)();

// Loads and runs the core clr with the specified params
bool LoadAndRunCoreClr(CoreClrStartParams* pCoreClrStartupParams)
{
	HRESULT hr = S_OK;
	ICLRRuntimeHost2* pCLRRuntimeHost = nullptr;

	// Load the CoreCRL dll into the process
	HMODULE hCoreCLRModule = ::LoadLibraryExW(pCoreClrStartupParams->CoreClrFilePath.c_str(), NULL, 0);

	if (!hCoreCLRModule)
	{
		printf_s("Could not load CoreCLR from path %S", pCoreClrStartupParams->CoreClrFilePath);
		return 1;
	}

	// Get the "factory" function for the runtime host
	FnGetCLRRuntimeHost pfnGetCLRRuntimeHost = (FnGetCLRRuntimeHost)::GetProcAddress(hCoreCLRModule, "GetCLRRuntimeHost");

	if (!pfnGetCLRRuntimeHost)
	{
		printf_s("Failed to find export GetCLRRuntimeHost\n");
		return false;
	}

	// Create a new instance of the runtime host
	hr = pfnGetCLRRuntimeHost(IID_ICLRRuntimeHost2, (IUnknown**)&pCLRRuntimeHost);

	if (FAILED(hr))
	{
		printf_s("Failed to get IID_ICLRRuntimeHost2 interface\n");
		return false;
	}

	// Set up the startup flags for the clr runtime
	STARTUP_FLAGS dwStartupFlags = (STARTUP_FLAGS)(
		STARTUP_FLAGS::STARTUP_LOADER_OPTIMIZATION_SINGLE_DOMAIN |
		STARTUP_FLAGS::STARTUP_SINGLE_APPDOMAIN |
		STARTUP_FLAGS::STARTUP_SERVER_GC
		);

	hr = pCLRRuntimeHost->SetStartupFlags(dwStartupFlags);

	if (FAILED(hr))
	{
		printf_s("Failed to set startup flags to the clr runtime\n");
		return false;
	}

	// Authenticate with either CORECLR_HOST_AUTHENTICATION_KEY or CORECLR_HOST_AUTHENTICATION_KEY_NONGEN 
	hr = pCLRRuntimeHost->Authenticate(CORECLR_HOST_AUTHENTICATION_KEY);

	if (FAILED(hr))
	{
		printf_s("Failed to Authenticate()\n");
		return false;
	}

	hr = pCLRRuntimeHost->Start();

	if (FAILED(hr))
	{
		printf_s("Failed to Start()\n");
		return false;
	}

	const wchar_t* property_keys[] =
	{
		L"APPBASE",
		L"TRUSTED_PLATFORM_ASSEMBLIES",
		L"APP_PATHS",
	};

	const wchar_t* property_values[] = {
		// APPBASE
		pCoreClrStartupParams->AppBase.c_str(),
		// TRUSTED_PLATFORM_ASSEMBLIES
		pCoreClrStartupParams->FullTrustedAssembliePaths.c_str(),
		// APP_PATHS
		pCoreClrStartupParams->AppPaths.c_str()
	};

	DWORD domainId;
	DWORD appDomainFlags = APPDOMAIN_ENABLE_PLATFORM_SPECIFIC_APPS | APPDOMAIN_ENABLE_PINVOKE_AND_CLASSIC_COMINTEROP;

	int nprops = sizeof(property_keys) / sizeof(wchar_t*);

	hr = pCLRRuntimeHost->CreateAppDomainWithManager(
		pCoreClrStartupParams->EntryPointAssemblyName.c_str(),
		appDomainFlags,
		NULL,
		NULL,
		nprops,
		property_keys,
		property_values,
		&domainId);

	if (FAILED(hr))
	{
		wprintf_s(L"Full trusted assemblies: %S\n", pCoreClrStartupParams->FullTrustedAssembliePaths);
		wprintf_s(L"AppPaths: %S\n", pCoreClrStartupParams->AppPaths);
		printf_s("Failed to create app domain (%d).\n", hr);
		return 1;
	}

	ManagedEntryPoint pManagedEntryPoint;

	// Create a delegate to the managed entry point
	hr = pCLRRuntimeHost->CreateDelegate(
		domainId,
		pCoreClrStartupParams->EntryPointAssemblyName.c_str(),
		pCoreClrStartupParams->EntryPointTypeName.c_str(),
		pCoreClrStartupParams->EntryPointMethodName.c_str(),
		(INT_PTR*)&pManagedEntryPoint);

	if (FAILED(hr))
	{
		printf_s("Failed to create a delegate to the managed entry point: (%d).\n", hr);
		return false;
	}

	// Start the managed entry point
	pManagedEntryPoint();

	// Unload the app domain
	pCLRRuntimeHost->UnloadAppDomain(domainId, true);

	// Stop the runtime host
	pCLRRuntimeHost->Stop();

	return true;
}