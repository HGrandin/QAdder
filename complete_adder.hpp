#ifndef COMPLETE_ADDER_HPP_76432
#define COMPLETE_ADDER_HPP_76432

#include "full_adder.hpp"


class complete_adder{
	private:
		int number_of_quartenary_adders;
		int number_of_binary_adders;
		int quartenary_size;
		int term_error_rate;
		int carry_error_rate;
		int stable_value_rate;
		full_adder *quartenary_adder;
		full_adder *binary_adder;

		//statistics
		long long int *error_array;
		long long int quartenary_errors;
		long long int binary_errors;
		long long int incorrect_adds;
		long long int nr_of_adds;

		void compare_results(int result1, int result2);

		void clean_stats();
		

	public:

		complete_adder(int nr_of_quartenary_adders, int nr_of_binary_adders
			, int term_err_rate, int carry_err_rate, int stable_value_rate);
		
		int add(int input1, int input2);

		void print_stats(std::string file);
		
};

#endif /* end of include guard: COMPLETE_ADDER_HPP_76432 */