#include "complete_adder.hpp"

#include <stdio.h>
#include <cmath>
#include <iostream>
#include <fstream>


complete_adder::complete_adder(int nr_of_quaternary_adders, int nr_of_binary_adders, int term_err_rate, int carry_err_rate, int stbl_value_multiplier){
	number_of_quaternary_adders = nr_of_quaternary_adders;
	number_of_binary_adders = nr_of_binary_adders;
	term_error_rate = term_err_rate;
	carry_error_rate = carry_err_rate;
	stable_value_multiplier = stbl_value_multiplier;

	quaternary_adder = new full_adder(4,term_error_rate, carry_error_rate, stable_value_multiplier);
	binary_adder = new full_adder(2,0,0,1);
	quaternary_size = pow(4,number_of_quaternary_adders);
	error_array = new long long int[32];
	for(int i=0; i<32;i++){
		error_array[i]=0;
	}
	error_size_array = new long long int[32];
	for(int i=0; i<32;i++){
		error_size_array[i]=0;
	}
	quaternary_errors=0;
	binary_errors=0;
	nr_of_adds=0;
	incorrect_adds=0;
}

int complete_adder::add(int input1,int input2){
	int i1_temp, i2_temp, starting_bit=1;
	int carry = 0;
	int sum = 0;
	// Variable that tells us how big part of the total integer the 
	// quaternary adders cover.
	int quart_adder_size = pow(4, number_of_quaternary_adders);
	adder_result result;
	
	for(int i = 0; i < number_of_quaternary_adders; i++){
		i1_temp = input1/starting_bit;
		i1_temp = i1_temp % 4;

		i2_temp = input2/starting_bit;
		i2_temp = i2_temp % 4;

		result = quaternary_adder->add(i1_temp, i2_temp, carry);
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
		
		// size of error counter
		int error_size = abs(input1-input2);
		for(int i = 0; i < 32; i++){
			if(error_size >= pow(2,i))
				error_size_array[i]++;
		}
		//quaternary error counter
		if(input1 % quaternary_size != input2 % quaternary_size){
			quaternary_errors++;
		}
		//binary error counter
		if(input1 / quaternary_size != input2 / quaternary_size){
			binary_errors++;
		}
		//bitwise error counter
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
}

void complete_adder::clean_stats(){
		for(int i=0; i<number_of_quaternary_adders+number_of_binary_adders;i++){
		error_array[i]=0;
	}
}



void complete_adder::print_stats(std::string file){

	std::ofstream myfile;
	myfile.open (file);
	myfile << "Nr of QA, Nr of BA, Term error rate, Carry error rate, Stable value rate, Nr of adds, Nr of Incorrect adds, ";
	myfile << "Quartenary side errors, Binary side errors, ";
	myfile << "Bit0, Bit1, Bit2, Bit3, Bit4, Bit5, Bit6, Bit7, Bit8, Bit9, Bit10, Bit11, ";
	myfile << "Bit12, Bit13, Bit14, Bit15, Bit16, Bit17, Bit18, Bit19, Bit20, Bit21, Bit22, ";
	myfile << "Bit23, Bit24, Bit25, Bit26, Bit27, Bit28, Bit29, Bit30, Bit31, ";
	myfile << "Error >= 2^0, Error >= 2^1, Error >= 2^2, Error >= 2^3, Error >= 2^4, Error >= 2^5, Error >= 2^6, ";
	myfile << "Error >= 2^7, Error >= 2^8, Error >= 2^9, Error >= 2^10, Error >= 2^11, Error >= 2^12, ";
	myfile << "Error >= 2^13, Error >= 2^14, Error >= 2^15, Error >= 2^16, Error >= 2^17, Error >= 2^18, ";
	myfile << "Error >= 2^19, Error >= 2^20, Error >= 2^21, Error >= 2^22, Error >= 2^23, Error >= 2^24, ";
	myfile << "Error >= 2^25, Error >= 2^26, Error >= 2^27, Error >= 2^28, Error >= 2^29, Error >= 2^30, ";
	myfile << "Error >= 2^31\n";
	
	myfile << number_of_quaternary_adders << ", " << number_of_binary_adders << ", ";
	myfile << term_error_rate << " ," << carry_error_rate << ", " << stable_value_multiplier << ", " << nr_of_adds << ", ";
	myfile << incorrect_adds << " ," << quaternary_errors << ", " << binary_errors;
	for(int i = 0; i < 32; i++){
		myfile << ", " << error_array[i];
	}
	for(int i = 0; i < 32; i++){
		myfile << ", " << error_size_array[i];
	}
	myfile << "\n";
	
	myfile.close();

	printf("Number of quaternary adders (LSB): %d\n", number_of_quaternary_adders);
	printf("Number of binary adders (MSB): %d\n", number_of_binary_adders);
	printf("Term error rate: 1 in %d \n", term_error_rate);
	printf("Carry error rate: 1 in %d \n", carry_error_rate);
	printf("Stable value rate: %d \n", stable_value_multiplier);
	printf("Total number of adds %lld \n", nr_of_adds);
	printf("Number of incorrect adds %lld \n", incorrect_adds);
	printf("Errors on the quaternary side: %lld\n", quaternary_errors);
	printf("Errors on the binary side: %lld\n", binary_errors);
	for(int i = 0; i < 32; i++){
		printf("Errors on bit %d: %lld\n", i,error_array[i]);
	}
	for(int i = 0; i < 32; i++){
		printf("Errors bigger or equal to 2^%d: %lld\n",i, error_size_array[i]);
	}
}







