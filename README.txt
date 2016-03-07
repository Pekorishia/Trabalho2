////////////////////////NEEDED FILES

-----------------------------SDK Texas Instruments---------------------------------

If don't have the SDK installed in your pc:
SDK Texas Instruments (~2.2Gb) - http://goo.gl/q8zaor
After downloading it, open the linux terminal and go to the directory that you downloaded it. Then type:
$ chmod +x filename
$ ./filename

-----------------------------------QT Designer--------------------------------------

If don't have the QT installed in your pc:
QT Designer - http://www.qt.io/
After downloading it, open the linux terminal and go to the directory that you downloaded it. Then type:
$ chmod +x filename
$ ./filename

------------------------------------QT Libraries ------------------------------------
If you hadn't installed the QT libraries into your BeagleBone Black, enters it by the linux terminal
and type:

$ sudo apt-get install qt5-default

-----------------------------Analog-to-digital converter-----------------------------
Open the linux terminal and enters your BeagleBone. Then type:
$ git clone https://github.com/beagleboard/bb.org-overlays
$ cd ./bb.org-overlays

$./dtc-overlay.sh
$./install.sh


////////////////////////HOW IT WORKS


Create a new QT project as QT Console Application and name it as you wish. 

After creating the project, open the "projectName".pro and change the last config (CONFIG -= app_bundle) to:
CONFIG += c++11

after that, right click into your project file name and go to "Add Existing Directory...".
Then open the directory /DEV/BlackLib/v3_0/BlackGPIO and click on "Start Parsing" and "Okay"

Again, right click into your project file name and go to "Add Existing Files...".
Then open the directory /DEV/BlackLib/v3_0/ and select all these four files:
   -BlackCore.cpp
   -BlackCore.h
   -BlackDef.h
   -BlackErr.h

Go to the link below and copy the "processos.cpp" code to the main.cpp in the project, and download the compila.sh to the project directory.
https://github.com/Pekorishia/Trabalho2

Open the compila.sh and change the "potenciometro" in:
"printf "\n\rCopiando para a BBB (em /home/debian)..."
sshpass -p 'temppwd' scp potenciometro debian@192.168.7.2:~"

to:
"printf "\n\rCopiando para a BBB (em /home/debian)..."
sshpass -p 'temppwd' scp projectName debian@192.168.7.2:~"


Check if the path to /BlackGPIO.h in the main.cpp is the same as in the "projectname".pro
If is different, copy tha path in "projectname".pro and paste it in the main.cpp #include "newpath"

Open the Linux terminal and go to the project directory and type:
$chmod +x compila.sh
$./compila.sh

This will enter the BeagleBone, then type:
./"projectname"

and it will work

/////////////////////////ATENTION!!!

Every time that you are going to execute this project, type these code into your BeagleBone before
executing:
$ sudo sh -c "echo 'BB-ADC' > /sys/devices/platform/bone_capemgr/slots"
