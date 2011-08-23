##################
# Ubuntu > 10.10 #
##################


Requirements
------------

- libxtst library :				sudo apt-get install libxtst-dev
- SFML 1.6 library :				sudo apt-get install libsfml-dev
- OpenNI >= 1.3.2.3 unstable release :		http://www.openni.org/downloadfiles/opennimodules/openni-binaries/20-latest-unstable
- NITE >= 4.1.2 unstable release :		http://www.openni.org/downloadfiles/opennimodules/openni-compliant-middleware-binaries/33-latest-unstable


Possible additional requirements
--------------------------------

- libmono (needed by OpenNI/NITE) :		sudo apt-get install libmono-winforms2.0-cil


Compilation (optional)
----------------------

Notice that binaries have already been generated, so it is not compulsory to re-compile by yourself.

Air project actually contains two projects : 

- NiFingersGenerator	(binary available here https://github.com/DoobleD/Air/tree/master/NiFingersGenerator/bin/linux/)
- Air			(binary available here https://github.com/DoobleD/Air/tree/master/Air/bin/linux/)


The compilation use the cross-compiler cmake to generate a Makefile.
If you don't have cmake : sudo apt-get install cmake

1 - Compile the fingers detection library :			cd NiFingersGenerator && cmake . && make
2 - Compile the Air program (fingers library required) :	cd Air && cmake . && make


Run
----

The Air binary for linux is in the Air/bin/linux directory, or here https://github.com/DoobleD/Air/tree/master/Air/bin/linux/.

Command-line is : ./Air



#############
# Windows 7 #
#############


Installer
---------

An installer is available in installer/windows/, or here : https://github.com/DoobleD/Air/installer/windows/

IMPORTANT: If you use the installer, nothing more is needed.


Requirements (only if no use of the installer)
----------------------------------------------

- SFML 1.6 library, c++ version :		http://www.sfml-dev.org/download.php		
- OpenNI >= 1.3.2.3 unstable release :		http://www.openni.org/downloadfiles/opennimodules/openni-binaries/20-latest-unstable
- NITE >= 4.1.2 unstable release :		http://www.openni.org/downloadfiles/opennimodules/openni-compliant-middleware-binaries/33-latest-unstable

IMPORTANT : SFML libray has to be compiled with Visual Studio 2010, since the latest available version on the website is compiled with VS 2008.
	    To get VS 2010 : http://www.microsoft.com/visualstudio/en-us/products/2010-editions/visual-cpp-express


Compilation (only if no use of the installer)
---------------------------------------------

Compilation use the cross-compiler cmake. Download cmake GUI here : http://www.cmake.org/cmake/resources/software.html

-> Compile the NiFingersGenerator, the fingers detectionlibrary

   1 - Open cmake-gui.exe
   2 - Choose NiFingersGeneretor as both the sources and the binary directory
   3 - Click on 'Configure' button
   4 - Choose Visual Studio 2010 compiler
   5 - Click on 'Generate' button
   6 - Open the Visual Studio solution generated in NiFingersGenerator directory
   7 - Compile with Visual Studio

-> Compile Air program (NiFingersGenerator library required)

   1 - Open cmake-gui.exe
   2 - Choose Air as both the sources and the binary directory
   3 - Click on 'Configure' button
   4 - Choose Visual Studio 2010 compiler
   5 - Click on 'Generate' button
   6 - Open the Visual Studio solution generated in Air directory
   7 - Compile with Visual Studio


Run
---

-> If you used the installer :
   
   - Double click on C:\Program Files\Air\bin\Air.exe or click on Windows -> Programs -> Air -> Air.exe

-> If you compiled the project by yourself :

   - The Air binary for windows is in the Air/bin/windows directory, or here https://github.com/DoobleD/Air/tree/master/Air/bin/windows/
     Double click on Air.exe.
