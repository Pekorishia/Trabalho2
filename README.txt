
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

Create a new QT project as QT Console Application and name it as you wish. Just as an example, we
will use here the project name: "trabalho2".

After creating the project, open the "trabalho2".pro and change the last config (CONFIG -= app_bundle) to:
CONFIG += c++11

after that, right click into your project file name and go to "Add Existing Directory...".
Then open the directory /DEV/BlackLib/v3_0/BlackGPIO and click on "Start Parsing" and "Okay"

Again, right click into your project file name and go to "Add Existing Files...".
Then open the directory /DEV/BlackLib/v3_0/ and select all these four files:
   -BlackCore.cpp
   -BlackCore.h
   -BlackDef.h
   -BlackErr.h

/////////////////////////ATENTION!!!
Every time that you are going to execute this project, type these code into your BeagleBone before
executing:
$ sudo sh -c "echo 'BB-ADC' > /sys/devices/platform/bone_capemgr/slots"
