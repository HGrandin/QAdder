#ifndef COMPLETE_ADDER_HPP_76432
#define COMPLETE_ADDER_HPP_76432

#include "full_adder.hpp"


class complete_adder{
	private:
		int number_of_quaternary_adders;
		int number_of_binary_adders;
		int quaternary_size;
		int term_error_rate;
		int carry_error_rate;
		int stable_value_rate;
		full_adder *quaternary_adder;
		full_adder *binary_adder;

		//statistics
		long long int *error_array;
		long long int *error_size_array;
		long long int quaternary_errors;
		long long int binary_errors;
		long long int incorrect_adds;
		long long int nr_of_adds;

		void compare_results(int result1, int result2);

		void clean_stats();
		

	public:
		// The chance of error is : 	1 in X	if X>0
		//								0 		if X=0 
		// The stable_value_rate is how much more stable 0 and 3 are in QA
		complete_adder(int nr_of_quaternary_adders, int nr_of_binary_adders
			, int term_err_rate, int carry_err_rate, int stable_value_rate);
		
		//adds input 1 and 2 with simulated error added.
		int add(int input1, int input2);

		//prints the stats of the adder into a file named as the input string file,
		// as well as in the terminal
		void print_stats(std::string file);
		
};

#endif /* end of include guard: COMPLETE_ADDER_HPP_76432 */