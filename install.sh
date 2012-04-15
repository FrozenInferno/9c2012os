#!/bin/sh

#ensure user is the root

user=$(id -u)
case "$user" in
    0) echo "Welcome!";;
    *) echo "You must have root privileges to install this utility";exit;
esac

#Verify that the system has an ATI GPU
VGA=$(lspci | grep VGA)
case "$VGA" in
    *nVidia*) echo "Detected an nVidia Graphics card on the system";;
    *) echo "No nVidia Graphics Card detected on the system. This utility works only on nVidia cards as of now.";exit;
esac

#install lm-sensors to read the temperature values

sensors=$(which nvclock)
case "$sensors" in
    "") echo "Installing nvclock..." ; install=1;;
    *) echo "Found nvclock.."; install=0;;
esac

#identify the installer frontend and install lm sensors
if [ "$install" == 1 ]; then
installer=$(uname -a)
case "$installer" in
    *Ubuntu*) apt-get install nvclock;;
    *Fedora*) yum install nvclock;;
    *) echo "Cannot install nvclock. Please install nvclock manually and run the installer script";;
esac
fi

sensors=$(which glxgears)
case "$sensors" in
    "") echo "Installing mesa-utils..." ; install=1;;
    *) echo "Found mesa-utils.."; install=0;;
esac

#identify the installer frontend and install lm sensors
if [ "$install" == 1 ]; then
installer=$(uname -a)
case "$installer" in
    *Ubuntu*) apt-get install mesa-utils;;
    *Fedora*) yum install mesa-utils;;
    *) echo "Cannot install mesa-utils. Please install mesa_utils manually and run the installer script";;
esac
fi


#check if the clock frequency of the GPU can be set
#canSet=$(aticonfig --odsc=0,0)
#case "$canSet" in
#    "") echo "Your ATI card is capable of being downclocked. Proceeding to build the utility.";;
#    *) echo "Your ATI card cannot be downclocked. The utility will not be installed.";exit;
#esac

#Make the utility
make

#remove temporary files
rm *~
rm *.o
rm *.dat
rm *.tmp

echo "Done building the utility. To run the utility, run sudo ./master"
