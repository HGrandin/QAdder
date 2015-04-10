#include "full_adder.hpp"
#include <assert.h>
#include <stdio.h>
#include <unistd.h>

#define ITERATIONS (1)
#define ERROR (0)
#define ERROR_IN (10)

int main(){
	int number_of_errors = 0;
	int number_of_adds = 0;
	full_adder *adder = new full_adder(4,ERROR,ERROR_IN);
	printf("(Error rate: %d in %d\n",ERROR, ERROR_IN);
	for(int l = 0;l<ITERATIONS;l++){
		for(int c = 0; c<2; c++){
			for(int i = 0; i<4;i++){
				for(int j = 0; j<4; j++){
					adder_result result = adder->add(i,j,c);
					// printf("Adder sum: %d\n", result.carry*4+result.sum);
					// printf("Real sum: %d\n", i+j+c);
					if(result.carry*4+result.sum != i+j+c){
						number_of_errors++;
					}
					number_of_adds++;
				}
			}
		}
	}
	printf("Number of Adds:   %d\n", number_of_adds);
	printf("Number of Errors: %d\n", number_of_errors);
}