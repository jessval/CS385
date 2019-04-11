/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      :Jessica Valenzuela
 * Version     : 1.0
 * Date        :11/4/2018
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    // TODO
	long x = 0;
	for(int i = 0; i<length-1;++i){
		for(int j = i+1; j<length; ++j){
			if(array[i] > array[j]){
				x += 1;
			}
		}

	}
	return x;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
	int * scratch = new int[length];
	long x;
	x = mergesort(array, &scratch[0], 0, length-1);
	delete[] scratch;
	return x;


}
//Divides input array in two halves, calls itself for the two halves and then merges the two sorted halves.
static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO
	long x = 0;
	int m;
	if(low<high){
		m = (low + high)/2;
		x = mergesort(array, scratch, low, m);
		x += mergesort(array, scratch, m+1, high);
		int lo = low;
		int hi = m+1;
		for(int k=low; k <= high; k++){
			if(lo<=m && (hi>high || array[lo] <= array[hi])){
				scratch[k] = array[lo];
				lo++;
			} else{
				scratch[k] = array[hi];
				hi++;
				x += (m - lo) + 1;
			}
		}
			for(int k=low; k<= high; ++k){
				array[k] = scratch[k];
			}

		}
		return x;
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
	if(argc > 2){
		cerr<< "Usage: " << argv[0] << " [slow]" << endl;
		return 1;
	}
	else if((argc == 2) && strcmp("slow", argv[1]) != 0) {
		cerr<<"Error: Unrecognized option \'" << argv[1] <<"\'.";
		return 1;
	}

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    int size = values.size();
    if(size == 0) {
    	cerr << "Error: Sequence of integers not received.";
    	return 1;
    }
    int *convertvector = &values[0];
    if(argc == 2){
    	cout<<"Number of inversions: "<< count_inversions_slow(convertvector, size) << endl;

    }
    else{
    	cout<< "Number of inversions: " << count_inversions_fast(&values[0], size) << endl;
    }
    return 0;
}
