# ------------------------- DATA CONVERTER ------------------------- #

The content:
DataConverter.cpp   ---> main functional block
DataConverter.h
RunControl.cpp      ---> main() block 
cout_msg.h          ---> message commands definition
globals.h           ---> setting the message level (program needs to be compiled after changing the sensivity level!)
input_data_format.h ---> cotains the definition of structure that will hold the data format from input file 
config_file.txt     ---> contains all variables set in Run Time. Changing the config file does not need a compilation of the software.

## ----------------------------- SYSTEM --------------------------- ##
--> This version is dedicated for Windows (tested at Win 10)

## ----------------------- SOFTWARE OVERVIEW ---------------------- ##
--> the binary file (.bin) is loaded and read out. 
--> binary input file contains a data from MIMOSIS1 saved in FIRED format (simply an 2D uint32_t array [504][1024])
--> software opens a ROOT Tree with a proper name containing the info about pulse voltage, thereshold voltage and back bias or saves name just as a noise file (might be set in config_windows)
--> fills the TH2D (ROOT) with data from input arrays and saved the TH2D* in output ROOT Tree

#### ----- Output ----- ####
--> go: MIMOSIS1_DataConverter_win --> output 
--> root proper_tfile_name.root 
--> TBrowser r

#### ----- To do: ----- ####
--> Implement other formats reading (RAW, DEC) when available. Config file has flag defines for that purpose.

## --------------------------- GIT REPO --------------------------- ##
--> project is stored on GitHub on RomaBugiel account 


## --------------------- HOW TO RUN ON WINDOWS -------------------- ##

### ---------------------------- ROOT  --------------------------- ###
--> Installed using .exe
--> $ROOTSYS$ defined for path to ROOT install directory 
--> $ROOTSYS$\thisroot.bat add to PATH
--> Verify if ROOT prompt appears after putting ‘root’ in command line


### ----------------------- VISUAL STUDIO  ----------------------- ###
--> Install Visual Studio 2019 (with the Desktop development with C++)
--> Verify if Developer Command Prompt works fine and has a new version
Tools → Command Line → Developer Command Prompt 
(tested on: “Visual Studio 2019 Developer Command Prompt v16.7.2”)
--> ROOT will work only on 32b version so verify if it is set properly
--> SDK: 10 
at least newset installed worked. But be careful because sometimes the SDK 11 might be installed with VS, although 10 is marked. (Check in Installed Softwares).
-- To verify SDK version:  Project → Properties → Configuration Properties → General → Windows SDK Version (might be switched to another version if installed. Installation might be done using Visual Studio 2019 Installer)

#### --------------------- PROJECT SETTINGS  --------------------- ####
##### C/C++ PROPERTIES: #####

Go to Project Properties
--> General → Additional Include Directories → need to add %ROOTSYS%/include
--> General C/C++ → Language :
        Conformance mode: no
        Treat WChar_t As Built in Type: no
        Force Conformance in For Loop Scope: no
        Remove unreferenced code and data: no
--> Tested for compilation command line (might be verified in Command Line in C/C+++ in Project Properties)

/JMC /MP /GS /analyze- /W3 /Zc:wchar_t- /I"%ROOTSYS%\include" /ZI /Gm- /Od /sdl /Fd"Debug\vc142.pdb" /fp:strict /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_UNICODE" /D "UNICODE" /errorReport:prompt /WX- /Zc:forScope- /RTC1 /Gd /Oy- /MDd /FC /Fa"Debug\" /EHsc /nologo /Fo"Debug\" /Fp"Debug\ComplexProject.pch" /diagnostics:column 

(project name and paths to be changed)

##### LINKER PROPERTIES: #####

--> General → Additional Library Directories → need to add %ROOTSYS%/lib
--> Input → %ROOTSYS%/*.lib (one might specify only needed libs one by one)
--> Also the Command Line can be verified here. The working one at least is: 

OUT:"C:\Users\rbugiel_adm\Desktop\Software\Project3\Debug\Project3.exe" /MANIFEST /NXCOMPAT /PDB:"C:\Users\rbugiel_adm\Desktop\Software\Project3\Debug\Project3.pdb" /DYNAMICBASE "%ROOTSYS%/lib/*.lib" "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib" /DEBUG /MACHINE:X86 /INCREMENTAL /PGD:"C:\Users\rbugiel_adm\Desktop\Software\Project3\Debug\Project3.pgd" /SUBSYSTEM:CONSOLE /MANIFESTUAC:"level='asInvoker' uiAccess='false'" /ManifestFile:"Debug\Project3.exe.intermediate.manifest" /ERRORREPORT:PROMPT /NOLOGO /LIBPATH:"C:\root_v6.22.00\lib" /TLBID:1 

### --------------------- HOW TO COMPILE AND RUN  ----------------------- ###

#### ------------------------------ VS GUI  ---------------------------- ####
--> "Local Windows Debbuger" button

#### ---------------------------- COMMAND LINE ------------------------- ####
--> in VS: Tools → Command Line → Developer Command Prompt (for x86 → 32b)
--> compile: cl /I %ROOTSYS%/include /EHsc /ZW Source.cpp /link %ROOTSYS%\lib\*.lib
--> run source.exe

THIS SHOULD BE UPDATED FOR THE PROJECT !