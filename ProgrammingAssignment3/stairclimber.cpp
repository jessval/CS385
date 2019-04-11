/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Jessica Valenzuela
 * Date        : 10/03/2018
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honors System
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
	vector< vector<int> > result,ways ;
	vector<int> way;
	if(num_stairs <= 0){
		ways.push_back(way);
	} else{
		for(int i = 1; i<=3; i++){
			if(num_stairs >= i){
				result = get_ways(num_stairs-i);
				for(unsigned int j = 0; j<result.size(); j++){
					result[j].push_back(i);
					ways.push_back(result[j]);
				}
			}

		}
	}
	return ways;

}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
	int n;
	unsigned int spaces;
	for(unsigned int i = 0; i<ways.size(); i++){
		n = ways.size();
		spaces = 1;
		while(n >= 10) {
			spaces ++;
			n = n/10;
		}
		cout << setw(spaces) << i+1 <<". " << "[";
		for(unsigned int j = ways[i].size() - 1;j>=1; j--){
			cout << ways[i][j] << ", ";
		}
		cout << ways[i][0] << "]" << endl;

	}
}

int main(int argc, char * const argv[]) {
	istringstream iss;
	int limit;
		// Check for error.
	if(argc != 2){
			cout << "Usage: " << argv[0] << " <number of stairs>" << endl;
			return 1;
		}
	iss.str(argv[1]);
	if (!(iss >> limit) || limit < 1) {
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
		}
	vector< vector<int> > ways = get_ways(limit);

	// Code that uses your class to produce the desired output.
	if(limit == 1){
		cout << "1 way to climb 1 stair." << endl;
	} else {
		cout << ways.size() << " ways to climb " << limit <<" stairs." << endl;

	}
		display_ways(ways);
		iss.clear();
		return 0;

}
