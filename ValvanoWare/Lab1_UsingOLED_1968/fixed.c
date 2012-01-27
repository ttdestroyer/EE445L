//fixed.c
// Runs on LM3S1968
// Maykei Nguyen
// Kyle O'Brien
// January 24, 2011

#include <stdio.h>
#include "Output.h"
#include "rit128x96x4.h"
#include "fixed.h"



//------------Fixed_uDecOut2------------
// Initializes the output function to display a fixed point
// value with two decimal points
// Input: 32-bit unsigned integer
// Output: 32-bit decimal fixed-point with resolution of 0.01
void Fixed_uDecOut2(unsigned int input){
	int i = input;	   //the input value won't be changed
	int max = 99999;   //given constraint
	int output;		   //output value to display
	int divisor;	   //divisor used
	int base = 10;	   //using decimal system
	int resolution = 2;	//resolution given, number of places after the decimal
	int j; //initialize counter

	//this section handles inputs over given maximum
	if(i > max){
		printf("***.**");
	}
	else{		
			//this section accounts for the integer part of the fixed point	number
			divisor = base;	 //start the divisor with the base value
			for(j = 1; j < resolution; j++){
				//this conditional statement gives the integer value of the desired resolution for division use
				divisor = divisor*base;	
			}
			output = i/divisor;
			printf("%3d", output);	//print the value with three spaces to make display pretty
			printf(".");

			//this section accounts for the decimal part of the fixed point	number
			output = i%divisor;		//divisor remains the same from above
			printf("%02d", output); //this only prints the highest (far left) digit 
			divisor = divisor/base;	//reduce the divisor to move to next decimal place to the right
	}
}

//------------Fixed_uDecOut3------------
// Initializes the output function to display a fixed point
// value with three decimal points
// Input: 32-bit signed integer
// Output: 16-bit signed decimal fixed-point with resolution of 0.001
void Fixed_uDecOut3(signed int input){
	int i = input;	   //the input value won't be changed
	int max = 9999;   //given constraint
	int min = -9999;	//given constraint
	int output;		   //output value to display
	int divisor;	   //divisor used
	int base = 10;	   //using decimal system
	int resolution = 3;	//resolution given, number of places after the decimal
	int j; //initialize counter

	//this section handles inputs not within given constraints
	if(i > max || i < min){
		printf("*.***");
	}
	else{		
			//this section accounts for the integer part of the fixed point	number
			divisor = base;	 //start the divisor with the base value
			for(j = 1; j < resolution; j++){
				//this conditional statement gives the integer value of the desired resolution for division use
				if(j < resolution){
					divisor = divisor*base;	
				}
			}
			output = i/divisor;
			printf("%2d", output);	//print the value with two spaces to make display pretty
			printf(".");

			//this section accounts for the decimal part of the fixed point	number
			
			
			output = i%divisor;		//divisor remains the same from above
			if(output < 0){printf("%03d", -output);}
			else{printf("%03d", output);} //this only prints the highest (far left) digit 
			divisor = divisor/base;	//reduce the divisor to move to next decimal place to the right
	}
}

//------------Fixed_uBinOut------------
// Initializes the output function to display a fixed point
// value with two binary points
// Input: 32-bit unsigned integer
// Output: 32-bit binary fixed-point with resolution of 1/256
void Fixed_uBinOut(unsigned int input){
	long int result;
	int rounding_temp;
	int raise = 0;
	int digit_out = 0;

	if(input == 0){
		printf(" 0.00"); //6chars
		return;
	}
	if(input >= 256000){
		printf("***.**");
		return;
	}

	input = input*1000;
	result = input/256;

	//Round to nearest 10s place
	rounding_temp = result % 10;
	if (rounding_temp >= 5){
		raise = 1;
	}
	result = (result/10)+raise;

	if(result < 100){
		printf(" 00.%d", result);
		return;
	}
	if(result < 100000){
		digit_out = result/100;
		printf(" %02d.",digit_out);
		result = result%(digit_out*100);
		printf("%02d\n", result);
		return;
	}
}