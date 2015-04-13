#ifndef FULL_ADDER_HPP_23876
#define FULL_ADDER_HPP_23876

#include <random>

struct adder_result{
	int sum;
	int carry;
};

class full_adder{
	private:
		std::default_random_engine generator;

		// decides if the adder is of base 2 or base 4
		int base;

		//The error rate of the inputs in the adder
		int term_error_rate;

		//The error rate of the carry input in the adder
		int carry_error_rate;

		//How much more stable the 0 and 3 are in a Quartenary Adder
		int stable_value_multiplier;

		// a quartenary specific function that adds noise to the input
		int add_input_noise(int input);

	public:
		// where size is the number of values the input can have,
		// The chance of error is : 	1 in X	if X>0
		//								0 		if X=0 
		// The stable_value_multiplier is how much more stable 0 and 3 are in QA
		full_adder(int size, int term_err_rate, int carry_err_rate, int stable_value_multiplier);

		void print_settings();

		adder_result add(int input1, int input2, int carry_in);

		

};

#endif /* end of include guard: FULL_ADDER_HPP_23876 */