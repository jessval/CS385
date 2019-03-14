/*
 * gcd.cpp
 *
 *  Created on: Aug 31, 2018
 *      Author: Jess
 *      "I pledge my honor that I have abided by the Stevens Honor System" -Jessica Valenzuela
 */

#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

int gcd_iterative(int m, int n){
	if(m == 0){
		return n;
		}
	if (n==0){
		return m;
		}
	if(m==n){
		return m;
		}
	int r;
	while(n != 0){
		r = m%n;
		m=n;
		n=r;
	}
	return m;
}

int gcd_recursive(int m, int n){
	if(m == 0){
			return n;
	}
	if (n==0){
		return m;
	}
	if(m==n){
		return m;
	}
	if(m%n != 0){
		return gcd_recursive(n,m%n);
	}
	return n;
}

int main(int argc, char* const argv[]) {
    int m, n;
    istringstream iss;

    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <integer m> <integer n>"
             << endl;
        return 1;
    }
    iss.str(argv[1]);
    if ( !(iss >> m) ) {
        cerr << "Error: The first argument is not a valid integer."
             << endl;
        return 1;
    }
    iss.clear(); // clear the error code
    iss.str(argv[2]);
    
    if ( !(iss >> n) ) {
        cerr << "Error: The second argument is not a valid integer."
             << endl;
        return 1;
    }

	cout<<"Iterative: " <<"gcd(" << m <<", "<<n<<") = "<< gcd_iterative(abs(m),abs(n))<<endl;
	cout<<"Recursive: " <<"gcd(" <<m<<", "<<n<<") = " << gcd_recursive(abs(m),abs(n))<<endl;

    return 0;
}



