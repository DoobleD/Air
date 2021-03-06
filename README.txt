 ------------------------------------------------------------------------------------------------------------------
|														   |
|							 Air							   |
|														   |
 ------------------------------------------------------------------------------------------------------------------


Website : http://doobled.github.com/Air/

Repository : https://github.com/DoobleD/Air

User guide : https://github.com/DoobleD/Air/tree/master/documentation or click on the "Downloads" button above.

Technical documentation of the two parts of the project :

	NiFingersGenerator :	http://doobled.github.com/Air/NiFingersGenerator/annotated.html
	Air :			http://doobled.github.com/Air/Air/annotated.html

Windows installer : click on the "Downloads" button above. Visual Studio 2010 required to run Air.

Video : click on the "Downloads" button above.


##################
# Ubuntu > 10.10 #
##################


Requirements
------------

- libxtst library :				
	sudo apt-get install libxtst-dev
- SFML 1.6 library :				
	sudo apt-get install libsfml-dev
- OpenNI >= 1.3.2.3 unstable release :		
	http://www.openni.org/downloadfiles/opennimodules/openni-binaries/20-latest-unstable
- NITE >= 4.1.2 unstable release :		
	http://www.openni.org/downloadfiles/opennimodules/openni-compliant-middleware-binaries/33-latest-unstable
- SensorKinect driver for Kinect :		
	https://github.com/avin2/SensorKinect/tree/unstable/Bin

A key may be necessary when installing NITE on linux : 0KOIk2JeIBYClPWVnMoRKn5cdY4=

You may need to disconnect and reconnect your Kinect device after OpenNI/NITE/SensorKinect installation.


Possible additional requirements
--------------------------------

- libmono (needed by OpenNI/NITE) :		sudo apt-get install libmono-winforms2.0-cil


Compilation (optional)
----------------------

Notice that binaries have already been generated, so it is not compulsory to re-compile by yourself.

Air project actually contains two projects : 

- NiFingersGenerator	
	Binary available here https://github.com/DoobleD/Air/tree/master/NiFingersGenerator/bin/linux/
- Air			
	Binary available here https://github.com/DoobleD/Air/tree/master/Air/bin/linux/


The compilation use the cross-compiler cmake to generate a Makefile.
If you don't have cmake : sudo apt-get install cmake

1 - Compile the fingers detection library :			cd NiFingersGenerator && cmake . && make
2 - Compile the Air program (fingers library required) :	cd Air && cmake . && make


Run
----

The Air binary for linux is in the Air/bin/linux directory, 
or here https://github.com/DoobleD/Air/tree/master/Air/bin/linux/.

Command-line is : ./Air



############################
# Windows 7 (32 bits only) #
############################


Installer
---------

A simple installer is available in installer/windows/
or here : https://github.com/DoobleD/Air/ (click on "Downloads" button).

IMPORTANT : Visual Studio 2010 is REQUIRED to run Air. The installer does NOT install it.

The installer automatically installs the other prerequisites indicated in the requirements section below, 
and intalls Air in C:\Program File\Air, by default.
You can also remove Air by running the installer again, and choosing the remove option. 
Removing Air using the installer won't remove the SensorKinect, OpenNI and NITE packages.

IMPORTANT : you'll probably need to reboot your computer after installation, to install the drivers.

Note : the installer was built with a trial version of the "Advanced Installer" tool.

Note : if, during installation, you have messages indication that 
       OpenNI/NITE/SensorKinect did not installed correctly, please ignore them.


Requirements (only if no use of the installer)
----------------------------------------------

- Visual Studio 2010 :
	http://www.microsoft.com/visualstudio/en-us/products/2010-editions/visual-cpp-express
- SFML 1.6 library, c++ version :		
	http://www.sfml-dev.org/download.php
- OpenNI >= 1.3.2.3 unstable release :		
	http://www.openni.org/downloadfiles/opennimodules/openni-binaries/20-latest-unstable
- NITE >= 4.1.2 unstable release :		
	http://www.openni.org/downloadfiles/opennimodules/openni-compliant-middleware-binaries/33-latest-unstable
- SensorKinect driver for Kinect :		
	https://github.com/avin2/SensorKinect/tree/unstable/Bin

IMPORTANT : SFML libray has to be compiled with Visual Studio 2010, 
	    since the latest available version on the website is compiled with VS 2008.

You may need to disconnect and reconnect your Kinect device after OpenNI/NITE/SensorKinect installation.


Compilation
-----------

Compilation use the cross-compiler cmake. 
Download cmake GUI here : http://www.cmake.org/cmake/resources/software.html

-> Compile the NiFingersGenerator, the fingers detectionlibrary

   1 - Open cmake-gui.exe
   2 - Choose NiFingersGeneretor as both the sources and the binary directory
   3 - Click on 'Configure' button
   4 - Choose Visual Studio 2010 compiler
   5 - Click on 'Generate' button
   6 - Open the Visual Studio solution generated in NiFingersGenerator directory
   7 - Compile with Visual Studio, in Release version

-> Compile Air program (NiFingersGenerator library required)

   1 - Open cmake-gui.exe
   2 - Choose Air as both the sources and the binary directory
   3 - Click on 'Configure' button
   4 - Choose Visual Studio 2010 compiler
   5 - Click on 'Generate' button
   6 - Open the Visual Studio solution generated in Air directory
   7 - Compile with Visual Studio, in Release version


Run
---

-> If you used the installer :
   
   - Double click on C:\Program Files\Air\Air.exe 
     or double click on the Air.exe shortcut on desktop
     or click on Windows -> All Programs -> Air -> Air.exe

-> If you compiled the project by yourself :

   - The Air binary for windows is in the Air/bin/windows directory, 
     or here https://github.com/DoobleD/Air/tree/master/Air/bin/windows/
     Double click on Air.exe.
