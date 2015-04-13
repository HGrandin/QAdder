#include "complete_adder.hpp"
#include <random>

#define TERM_ERROR_RATE 	(1000000)
#define CARRY_ERROR_RATE 	(10000000)
#define STABLE_VALUE_RATE	(10)
#define QUATERNARY_ADDERS 	(8)
#define BINARY_ADDERS 		(16)
#define FILE_NAME "newResults2.csv"



int main(){
	int i1,i2,i=0;
	int adder_sum, real_sum;
	int incorrect_sum_count = 0;
	complete_adder *adder = new complete_adder(QUATERNARY_ADDERS,BINARY_ADDERS,
		TERM_ERROR_RATE, CARRY_ERROR_RATE, STABLE_VALUE_RATE);
	
	std::default_random_engine generator(time(0));
    std::uniform_int_distribution<int> distribution(0, pow(2,31));
    
	while(1){
		i1 = distribution(generator);
		i2 = distribution(generator);
		real_sum = i1+i2;
		adder_sum = adder->add(i1,i2);

		if(real_sum != adder_sum){
			incorrect_sum_count++;
		}
		i++;
		if(i>=10000000){
			adder->print_stats(FILE_NAME);
			i = 0;
		}
	}
	


	

}


