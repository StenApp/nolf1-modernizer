# No One Lives Forever Modernizer


This repo uses the Modernizer 1.006 patch 4 code to implement the PS2 thiefmissions
## Features

 - Integrated thiefmissions 1-3
 - Converted Thief code breaker and lock picking tools
 - Added Pen dart (PS2 exclusive)
 - Added "Nine years ago.." loading screen
 - Added PS2 music to the Jukebox
 - Decide whether to play PS2 music during all pc levels
 - Create EN/FR/DE CRes.dlls by editing rc files

## Building

Compile it using Visual Studio 2019 (Requires C++ and MFC).

The following build configurations are setup to build: 
 - Debug
 - Release
 - Release EN -->only build CRes.dll in english
 - Release FR -->only build CRes.dll in french
 - Release DE -->only build CRes.dll in german

## Localization

There have been community efforts to localize Modernizer into other languages.

    nolf1-modernizer/NOLF/ClientRes/Lang/XX ; XX= EN, FR, DE

First off modify the string table located in CRes.dll (Client Resource). Use an Texteditor and modify the source code (rc file), save it as ANSI coded. 
You may also attempt to use other programs lie Resource Hacker to modify the string table directly in the dll. 

Secondly there are some additional strings in Jukebox.txt located here: https://github.com/haekb/nolf1-modernizer/blob/master/ASSETS/Attributes/Jukebox.txt) 

Finally compile your new CRes.dll and the modified attribute file into its own rez using LithRez.exe (from the SDK) and make sure it loads after Modernizer.rez.

## D3D and 2048 pixel limit

You can grab a patched d3d.ren, and d3dim700.dll from the ASSETS folder or from a release of NOLF Modernizer.

## DGVoodoo2

I don't recommend using this application. I've fixed the majority of the slowdowns caused by old d3d techniques. And (at least on my machine) DGVoodoo2 would cause dynamic lights to absolutely destroy my framerate!

## License

This code is still bound to the original EULA found in the NO ONE LIVES FOREVER Source Code v1.003. This can be viewed in the readme.txt file.

## BIG Thanks to

- Haekb/Oopsallnaps/JakeB/Heytherecoffee - groundwork of the PS2 formats, levels, models, Godot level viewer and converter, Blender plugin
- cmbasnett+amphos/five-damned-dollarz+... - creating the io_scene_lithtech Blender plugin
- Spookstah - Fixing LTA level files
- burmaraider - DAT-viewer and 32P palettized texture converter
- AkvenJan - DTX-Meta-Transfer
- Tilo4246 - playtesting thief missions
- Monolith for creating this awesome game!
- Lithfaq discord for hoarding lots of usefull informations
- My wife and daughter who supported me always
- Anyone not listed here that had part of the creating process

