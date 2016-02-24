#include <fstream>
#include <iostream>
#include <sstream>
#include "GPIOClass.h"


using namespace std;

GPIOClass::GPIOClass() //Default Constructor, default GPIO pin set to 2
{
	this->gpionum = "2";
}

GPIOClass::GPIOClass(string gnum) //Constructor, creates GPIO class as designated by gnum 
{
	this->gpionum = gnum;
}

int GPIOClass::export_gpio() //Exports GPIO to Pi for use
{
	string export_str = "/sys/class/gpio/export";
	ofstream exportgpio(export_str.c_str());
	if(exportgpio < 0)
	{
		return -1;
	}
	exportgpio << this->gpionum;
	exportgpio.close();
	return 0;
}

int GPIOClass::unexport_gpio() //Frees GPIO pin after use
{
	string unexport_str = "/sys/class/gpio/unexport";
	ofstream unexportgpio(unexport_str.c_str());
	if(unexportgpio < 0)
    {
		return -1;
	}
	unexportgpio << this->gpionum;
	unexportgpio.close();
	return 0;
}

int GPIOClass::setdir_gpio(string dir) //Sets pin to input or output
{
	string setdir_str = "/sys/class/gpio/gpio" + this->gpionum + "/direction";
	ofstream setdirgpio(setdir_str.c_str());
	if(setdirgpio < 0)
	{
		return -1;
	}
	setdirgpio << dir;
	setdirgpio.close();
	return 0;
}

int GPIOClass::setval_gpio(string val) //Sets pin to high or low state
{
	string setval_str = "/sys/class/gpio/gpio" + this->gpionum + "/value";
	ofstream setvalgpio(setval_str.c_str());
	if(setvalgpio < 0)
	{
		return -1;
	}	
	setvalgpio << val;
	setvalgpio.close();
	return 0;
}

int GPIOClass::getval_gpio(string& val) //Reads value of GPIO pin
{
	string getval_str = "/sys/class/gpio/gpio" + this->gpionum + "/value";
	ifstream getvalgpio(getval_str.c_str());
	if(getvalgpio < 0)
	{
		return -1;
	}
	
	getvalgpio >> val;
	
	if(val != "0")
		val = "1";
	else
		val = "0";
	getvalgpio.close();
	return 0;
}

string GPIOClass::get_gpionum() //Gets GPIO number
{
	return this->gpionum;
}
