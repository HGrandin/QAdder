#include "full_adder.hpp"

#include <cstdlib>
#include <ctime>
#include <assert.h>
#include <stdio.h>
#include <random>


full_adder::full_adder(int size, int term_err_rate, int carry_err_rate, int sum_err_rate){
	assert(size>1);
	term_error_rate = term_err_rate;
	carry_error_rate = carry_err_rate;
	sum_error_rate = sum_err_rate;
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
		std::uniform_int_distribution<int> term_distribution(1, term_error_rate);

		//random for the first term.
		random = term_distribution(generator);
	    // printf("Random: %d \n",random);

	    
		if(random==1){
			if(base == 2){
				printf("Error in binary: This should never happen!\n");
			}
			if(fifty_fifty(generator) == 1){
				if(input1<3){
					input1++;
				}
			}
			else{
				if(input1>0){
					input1--;
				}
			}
		}

		//random for the second term.
	    random = term_distribution(generator);
	    // printf("Random: %d \n",random);

	    
		if(random==1){
			if(base == 2){
				printf("Error in binary: This should never happen!\n");
			}
			if(fifty_fifty(generator) == 1){
				if(input2<3){
					input2++;
				}
			}
			else{
				if(input2>0){
					input2--;
				}
			}
		}
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
	
	



	if(sum_error_rate>0){
	    std::uniform_int_distribution<int> sum_distribution(1, sum_error_rate);

	    int random = sum_distribution(generator);
	    // printf("Random: %d \n",random);

		if(1==random){
			if(base == 2){
				printf("Error in binary: This should never happen!\n");
			}
			if(sum==0){
				sum++;
			}
			else{
				if(fifty_fifty(generator) == 1){
					sum++;
				}
				else{
					sum--;
				}
			}
		}
	}

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
	printf("Sum error rate: 1 in %d\n",sum_error_rate);
	printf("Base: %d\n", base);
}


double full_adder::add_noise(int input){
	switch(input){
		case 0 : 
			//do stuff
			break;
		case 1 : 
			//do stuff
			break;
		case 2 : 
			//do stuff
			break;
		case 3 : 
			//do stuff
			break;
		default : 
			printf("Error: In full_adder::add_noise, case that should never happen.\n");
			break;
	}
	return 0;
}
