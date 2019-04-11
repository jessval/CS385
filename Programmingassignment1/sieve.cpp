/*******************************************************************************
 * Name        : sieve.cpp
 * Author      :Jessica Valenzuela
 * Date        :9/17/18
 * Description : Sieve of Eratosthenes
 * Pledge      :I pledge my honor that I have abided by the Stevens Honors System
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {

public:
	// Constructor that uses an initializer list.
	PrimesSieve(int limit) :
			is_prime_ { new bool[limit + 1] }, limit_ { limit } {
		sieve();
	}

	~PrimesSieve() {
		delete[] is_prime_;
	}

	inline int num_primes() const {
		return num_primes_;
	}

	void display_primes() const {
		// Code to display the primes in the format specified in the
		// requirements document.
		cout<< endl;
		        cout << "Number of primes found: " << num_primes() << endl;
		        cout << "Primes up to " << limit_ << ":" << endl;

		const int max_prime_width = num_digits(max_prime_),
				primes_per_row = 80 / (max_prime_width + 1);

		if (num_primes_ <= primes_per_row) {
			for (int i = 2; i <= limit_; i++) {
				if (is_prime_[i]) {
					if (i != max_prime_) {
						cout << i << " ";
					} else {
						cout << i;
					}

				}

			}

		} else {
			int counter = 0;
			for (int j=0; j<= limit_; j++) {
				if (is_prime_[j] == true) {
					int extra_space = (counter == 0) ? 0 : 1;
					cout << setw(max_prime_width + extra_space) << j;
					if(counter == primes_per_row - 1){
						cout << endl;

					}
					counter = (counter + 1) % primes_per_row;

				}
			}
		}
	}

	private:
	// Member variables (fields). Use the trailing _ for these variables.
		bool * const is_prime_;
		const int limit_;
		int num_primes_, max_prime_;

	int count_num_primes() const {
		// Code to count the number of primes found
		int count = 0;
		for(int i = 2; i<=limit_; i++){
			if(is_prime_[i] == true){
				count ++;

			}
		}
		return count;
	}

	int num_digits(int num) const {
		// Write code to determine how many digits are in an integer
		// No strings are needed. Keep dividing by 10.
		int count = 0;
		while(num != 0 ) {
			count ++;
			num = num/10;

		}
		return count;
	}

	void maxprime() {
		for(int i=2; i<=limit_; i++){
			if(is_prime_[i] == true){
				max_prime_ = i;
			}
		}
	}

	void sieve() {
		//finds prime number using Sieve of Erathothenes

		for(int i=2; i<=limit_ ; i++){
			is_prime_[i] = true;
		}
		for(int i=2; i<= sqrt(limit_); i++){
			if(is_prime_[i] == true){
				for(int j = i*i; j<= limit_; j = j+i){
					is_prime_[j] = false;
				}

			}

		}
		num_primes_ = count_num_primes();
		//finds max prime number
		for(int k = limit_; k >= 2; k--){
			if(is_prime_[k]){
				max_prime_ = k;
				break;
			}
		}



	}
}
;

int main() {
	cout << "**************************** " << "Sieve of Eratosthenes"
			<< " ****************************" << endl;
	cout << "Search for primes up to: ";
	string limit_str;
	cin >> limit_str;
	int limit;

	// Use stringstream for conversion. Don't forget to #include <sstream>
	istringstream iss(limit_str);

	// Check for error.
	if (!(iss >> limit)) {
		cerr << "Error: Input is not an integer." << endl;
		return 1;
	}
	if (limit < 2) {
		cerr << "Error: Input must be an integer >= 2." << endl;
		return 1;
	}

	// Code that uses your class to produce the desired output.
	PrimesSieve p(limit);
	p.display_primes();

	return 0;
}
