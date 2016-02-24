/* 
 * File:   main.cpp
 * Author: Sam
 *
 * Created on February 10, 2016, 6:31 PM
 */

#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale>
#include "GPIOClass.h"

using namespace std;

int main ()
{
    char Again;
    string stateinput;
    GPIOClass gpio4("4"); 
    //GPIOClass gpio17("17");

    gpio4.export_gpio(); //Exports GPIO pins for use
    //gpio17.export_gpio();

    cout << "Pins 4 and 17 have been exported" << endl;

    //gpio17.setdir_gpio("in"); //Sets GPIO17 to input
    gpio4.setdir_gpio("out"); //Sets GPIO4 to output

    cout << "GPIO pin 17 and 4 have been set to 'in' and 'out', respectively" << endl;

    while(toupper(Again) != 'N') //The following sets output high and checks the state of the input and output pins
    {
		gpio4.setval_gpio("1"); //Sets output to high
		sleep(1); //Wait one second
		//gpio17.getval_gpio(stateinput);
		//cout << "GPIO17 (input) is ";
		//if(stateinput == "1")
			//cout << "on. " << endl;
		//if(stateinput == "0")
			//cout << "off. " << endl;
			
		sleep(1); //Wait one second
		gpio4.getval_gpio(stateinput);
		cout << "GPIO4 (output) is ";
		if(stateinput == "1")
			cout << "on. " << endl;
		if(stateinput == "0")
			cout << "off. " << endl;
		cout << "Go again? (N for No)" << endl;
		cin >> Again;
    }
    cout << "Unexporting pins..." << endl << "Deallocating memory..." << endl;
    gpio4.unexport_gpio(); 
    //gpio17.unexport_gpio();
    cout << "Exiting in 3 seconds..." << endl;
    sleep(3);
    return 0;
}
