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
		cout << "Failed to export GPIO" << this->gpionum << endl;
		return -1;
	}
	cout << "export string of "<< this->gpionum << ": " << export_str.c_str() << endl;
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
		cout << "Unable to unexport GPIO" << this->gpionum << endl;
		return -1;
	}
	cout << "unexport string of "<< this->gpionum << ": " << unexport_str.c_str() << endl;
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
		cout << "Unable to set GPIO direction of GPIO" << this->gpionum << endl;
		return -1;
	}
	setdirgpio << dir;
	cout << "setdir string of "<< this->gpionum << ": " << setdir_str.c_str() << endl;
	setdirgpio.close();
	return 0;
}

int GPIOClass::setval_gpio(string val) //Sets pin to high or low state
{
	string setval_str = "/sys/class/gpio/gpio" + this->gpionum + "/value";
	cout << setval_str << endl;
	ofstream setvalgpio(setval_str.c_str());
	if(setvalgpio < 0)
	{
		cout << "Unable to set value of GPIO" << this->gpionum << endl;
		return -1;
	}	
	setvalgpio << val;
	cout << "Setval string of "<< this->gpionum << ": " << setval_str.c_str() << endl;
	setvalgpio.close();
	return 0;
}

int GPIOClass::getval_gpio(string& val) //Reads value of GPIO pin
{
	string getval_str = "/sys/class/gpio/gpio" + this->gpionum + "/value";
	ifstream getvalgpio(getval_str.c_str());
	if(getvalgpio < 0)
	{
		cout << "Unable to get value of GPIO" << this->gpionum << endl;
		return -1;
	}
	
	getvalgpio >> val;
	
	if(val != "0")
		val = "1";
	else
		val = "0";
	cout << "Getval string of "<< this->gpionum << ": " << getval_str.c_str() << endl;
	getvalgpio.close();
	return 0;
}

string GPIOClass::get_gpionum() //Gets GPIO number
{
	return this->gpionum;
}
