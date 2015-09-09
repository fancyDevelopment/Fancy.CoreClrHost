Fancy.CoreClrHost
=================

A host application to start .NET Core Crl with user defined assemblies.

##What is Fancy.CoreClrHost
Fancy.CoreClrHost enables you to start .NET Code (IL) assemblies using the .NET Core Clr runtime. The assembly which you want to run may not have dependencies to assemblies of the full .NET Framework (no directly and also no indirectly references). Use only nuget packages.

## How to use it
Add the [Fancy.CoreClrHost](https://www.nuget.org/packages/Fancy.CoreClrHost/) nuget package and the CoreClr package to your project (currently you can get the CoreClr package from the aspnetvnext package feed located at myget.org. 

Within your project create a static method which takes no arguments and has no return value. This is the entry point into you .NET code.

Compile your project and call Fancy.CoreClrHost.exe with the following command line arguments:

- --CoreClrFolderPath: Path to folder containing coreclr (The contents of the CoreClr nuget package).
- --AppFolderPath: Path to the folder containing your .NET assemblies you wand to execute code from.
- --EntryPointAssemblyName: The name of the assembly containing your entry point.
- --EntryPointTypeName: The name of the type containing the method you want to start.
- --EntryPointMethodName:The name of the method you want to run.

## Example
Imagine we have the follwing .NET Code compiled into an assembly:
```
namespace CoreClrExampleAssembly
{
    public class Program
    {
        public static int Main()
        {
            Console.WriteLine("Hello .NET Core");
            Console.ReadLine();
        }
    }
}
```
Lets assume the compiled code of the example can be found at C:\Dev\CoreClrExampleAssembly.dll and the contents of the CoreClr package at C:\Dev\CoreClr.

To run the main method using CoreClr you have to use the follwing command line.

```
Fancy.CoreClrHost.exe --CoreClrFolderPath:C:\Dev\CoreClr\Runtime\x86\ --AppFolderPath:C:\Dev\ --EntryPointAssemblyName:CoreClrExampleAssembly --EntryPointTypeName:CoreClrExampleAssembly.Program --EntryPointMethodName:Main
```

## Known Issues
- Currently all paths you provide need to be absolute path and need to end with a backslash.
- Debugging with Visual Studio is possible but only if you attach the debugger when the application is already running. Directly starting the application from Visual Studio with the Debugger (F5) is currently not possible.

## Requirements
- If you load the NuGet Package and want to run the executeable you need to have the Visual Studio 2015 (v140) C++ Runtime installed on your machine

### More Information:
To get some background you can also read my blog posts:

[http://www.fancy-development.net/fancy-coreclrhost-published](http://www.fancy-development.net/fancy-coreclrhost-published)
[http://www.fancy-development.net/hosting-net-core-clr-in-your-own-process](http://www.fancy-development.net/hosting-net-core-clr-in-your-own-process)