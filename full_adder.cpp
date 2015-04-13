#include "full_adder.hpp"

#include <cstdlib>
#include <ctime>
#include <assert.h>
#include <stdio.h>
#include <random>


full_adder::full_adder(int size, int term_err_rate, int carry_err_rate, int stbl_value_multiplier){
	assert(size>1);
	term_error_rate = term_err_rate;
	carry_error_rate = carry_err_rate;
	stable_value_multiplier = stbl_value_multiplier;
	base = size;
	generator.seed(time(0));
}

adder_result full_adder::add(int input1, int input2, int carry_in){
	if(input1>=base){
		printf("Base: %d\n", base);
		printf("Input1: %d\n", input1);
	}
	if(input2>=base){
		printf("Base: %d\n", base);
		printf("Input2: %d\n", input2);
	}
	assert(input1<base);
	assert(input2<base);
	adder_result result;
	int random;
	std::uniform_int_distribution<int> fifty_fifty(1, 2);


	//*******************Error for the inputs*****************************
	if(term_error_rate>0){
		input1 = this->add_input_noise(input1);
		input2 = this->add_input_noise(input2);	
	}
	if(carry_error_rate>0){
		std::uniform_int_distribution<int> carry_distribution(1, carry_error_rate);

		//random for the first term.
	    random = carry_distribution(generator);
	    // printf("Random: %d \n",random);
		if(random==1){
			if(carry_in==0){
				carry_in++;
			}
			else{
				carry_in--;
			}
		}

	}


	int sum = input1+input2+carry_in;

	if(sum >= base)
		result.carry = 1;
	else
		result.carry = 0;

	result.sum = sum % base;

	// printf("From full adder, result.sum: %d\n", result.sum);
	// printf("From full adder, result.carry: %d\n", result.carry);

	return result;
}

void full_adder::print_settings(){
	printf("Term error rate: 1 in %d\n",term_error_rate);
	printf("Carry error rate: 1 in %d\n",carry_error_rate);
	printf("Stable value rate: %d\n",stable_value_multiplier);
	printf("Base: %d\n", base);
}


int full_adder::add_input_noise(int input){
	std::uniform_int_distribution<int> term_distribution(1, term_error_rate);
	std::uniform_int_distribution<int> stable_distribution(1, stable_value_multiplier);
	std::uniform_int_distribution<int> fifty_fifty(1, 2);
	if(term_distribution(generator) == 1){
		switch(input){
			case 0 : 
				if(stable_distribution(generator) == 1){
					input++;
				}
				break;
			case 3 : 
				if(stable_distribution(generator) == 1){
					input--;
				}
				break;
			default :
				if(input != 1 and input != 2)
					printf("Error: In full_adder::add_input_noise, case that should never happen.\n");
				if(fifty_fifty(generator) == 1){
					input++;
				}
				else{
					input--;
				}
				break;
		}
	}
	return input;
}
