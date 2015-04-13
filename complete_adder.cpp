#include "complete_adder.hpp"

#include <stdio.h>
#include <cmath>
#include <iostream>
#include <fstream>


complete_adder::complete_adder(int nr_of_quartenary_adders, int nr_of_binary_adders, int term_err_rate, int carry_err_rate, int stbl_value_rate){
	number_of_quartenary_adders = nr_of_quartenary_adders;
	number_of_binary_adders = nr_of_binary_adders;
	term_error_rate = term_err_rate;
	carry_error_rate = carry_err_rate;
	stable_value_rate = stbl_value_rate;

	quartenary_adder = new full_adder(4,term_error_rate, carry_error_rate, stable_value_rate);
	binary_adder = new full_adder(2,0,0,1);
	quartenary_size = pow(4,number_of_quartenary_adders);
	error_array = new long long int(32);
	for(int i=0; i<32;i++){
		error_array[i]=0;
	}
	quartenary_errors=0;
	binary_errors=0;
	nr_of_adds=0;
	incorrect_adds=0;
}

int complete_adder::add(int input1,int input2){
	int i1_temp, i2_temp, starting_bit=1;
	int carry = 0;
	int sum = 0;
	// Variable that tells us how big part of the total integer the 
	// quartenary adders cover.
	int quart_adder_size = pow(4, number_of_quartenary_adders);
	adder_result result;
	
	for(int i = 0; i < number_of_quartenary_adders; i++){
		i1_temp = input1/starting_bit;
		i1_temp = i1_temp % 4;

		i2_temp = input2/starting_bit;
		i2_temp = i2_temp % 4;

		result = quartenary_adder->add(i1_temp, i2_temp, carry);
		carry = result.carry;
		sum = sum+(result.sum*starting_bit);
		starting_bit=starting_bit*4;
	}
	
	for(int i = 0; i <number_of_binary_adders;i++){
		i1_temp = input1/starting_bit;
		i1_temp = i1_temp % 2;

		i2_temp = input2/starting_bit;
		i2_temp = i2_temp % 2;

		result = binary_adder->add(i1_temp, i2_temp, carry);

		carry = result.carry;
		sum = sum+(result.sum*starting_bit);
		starting_bit=starting_bit*2;
	}
	nr_of_adds++;
	compare_results(input1+input2, sum);
	return sum;
}

void complete_adder::compare_results(int input1, int input2){
	int i1_temp, i2_temp, starting_bit=1;

	if(input1 != input2){
		incorrect_adds++;
	}
	
	if(input1 % quartenary_size != input2 % quartenary_size){
		quartenary_errors++;
	}
	if(input1 / quartenary_size != input2 / quartenary_size){
		binary_errors++;
	}
	for(int i = 0; i <32;i++){
		i1_temp = input1/starting_bit;
		i1_temp = i1_temp % 2;

		i2_temp = input2/starting_bit;
		i2_temp = i2_temp % 2;

		if(i1_temp != i2_temp){
			error_array[i]++;
		}
		starting_bit = starting_bit*2;
	}
	
}

void complete_adder::clean_stats(){
		for(int i=0; i<number_of_quartenary_adders+number_of_binary_adders;i++){
		error_array[i]=0;
	}
}



void complete_adder::print_stats(std::string file){

	std::ofstream myfile;
	myfile.open (file);
	myfile << "Nr of QA, Nr of BA, Term error rate, Carry error rate, Stable value rate, Nr of adds, Nr of Incorrect adds, ";
	myfile << "Quartenary side errors, Binary side errors, ";
	myfile << "Bit0, Bit1, Bit2, Bit3, Bit4, Bit5, Bit6, Bit7, Bit8, Bit9, Bit10, Bit11,";
	myfile << "Bit12, Bit13, Bit14, Bit15, Bit16, Bit17, Bit18, Bit19, Bit20, Bit21, Bit22,";
	myfile << "Bit23, Bit24, Bit25, Bit26, Bit27, Bit28, Bit29, Bit30, Bit31\n";
	
	myfile << number_of_quartenary_adders << ", " << number_of_binary_adders << ", ";
	myfile << term_error_rate << " ," << carry_error_rate << ", " << stable_value_rate << ", " << nr_of_adds << ", ";
	myfile << incorrect_adds << " ," << quartenary_errors << ", " << binary_errors;
	for(int i = 0; i < 32; i++){
		myfile << ", " << error_array[i];
	}
	
	myfile.close();

	printf("Number of quartenary adders (LSB): %d\n", number_of_quartenary_adders);
	printf("Number of binary adders (MSB): %d\n", number_of_binary_adders);
	printf("Term error rate: 1 in %d \n", term_error_rate);
	printf("Carry error rate: 1 in %d \n", carry_error_rate);
	printf("Stable value rate: %d \n", stable_value_rate);
	printf("Total number of adds %lld \n", nr_of_adds);
	printf("Number of incorrect adds %lld \n", incorrect_adds);
	printf("Errors on the quartenary side: %lld\n", quartenary_errors);
	printf("Errors on the binary side: %lld\n", binary_errors);
	for(int i = 0; i < 32; i++){
		printf("Errors on bit %d: %lld\n", i,error_array[i]);
	}
}







