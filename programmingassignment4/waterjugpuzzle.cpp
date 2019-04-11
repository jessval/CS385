/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Authors     : Himanshu Rana(hrana2) and Jessica Valenzuela(jvalenzu)
 * Date        : 10/19/18
 * Description : ???
 * Pledge      : "I pledge my honor that I have abided by the Stevens Honor System" - Himanshu Rana and Jessica Valenzuela
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// Struct to represent state of water in the jugs.
int capA;
int capB;
int capC;

struct State {
	int a, b, c;
	vector<string> directions;

	State(int _a, int _b, int _c) : a(_a), b(_b), c(_c) { }

	// String representation of state in tuple form.
	string to_string() {
		ostringstream oss;
		oss << "(" << a << ", " << b << ", " << c << ")";
		return oss.str();
	}
};

State Pouring(int A, int B, int C){
	int newA;
	int newB;
	int newC;
	//Check if combination has already been done
	bool**checked = new bool * [capA + 1];
	for(int i = 0; i<= capA; i++){
		checked[i] = new bool[capB + 1];
		fill(checked[i], checked[i] + capB + 1,false);
	}


	//Pouring C to A
	if(C !=0 && A<capA){
		newA=A+C;
		if(newA>capA){
			newA=capA;
		}
		newC = C - (newA - A);
	}
	//Pouring B to A
	if(B !=0 && A<capA){
		newA=A+B;
		if(newA>capA){
			newA=capA;
		}
		newB=B-(newA-A);
	}


	//Pouring from C to B
	if(C !=0 && B < capB){
		newB=B+C;
		if(newB>capB){
			newB=capB;
		}
		newC=C-(newB-B);
	}
	//Pouring from A to B
	if(A !=0 && B<capB){
		newB=B+A;
		if(newB>capB){
			newB=capB;
		}
		newA = A-(newB-B);
	}
	//Pouring from B to C
	if(B !=0 && C<capC){
		newC=C+B;
		if(newC>capC){
			newC=capC;
		}
		newB=B-(newC-C);
	}
	//Pouring from A to C
	if(A !=0 && C<capC){
			newC=C+A;
			if(newC>capC){
				newC=capC;
			}
			newA = A-(newC-C);
		}

	return State(newA, newB, newC);

}

int main(int argc, char * const argv[]) {
	if(argc!=7){
		cout<<"Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" <<endl;
		return 0;
	}
	for(int i = 1; i<=6; i++){
		istringstream iss(argv[i]);
		int number;
		if(!(iss >> number) || number < 0 || (i == 3 && number == 0)) {
			if(i<=3){
				if(i==1){
					cout<<"Error: Invalid capacity '" << argv[i] <<"' for jug A."<<endl;
					return 0;

				}
				if(i==2){
					cout<<"Error: Invalid capacity '" << argv[i] <<"' for jug B."<<endl;
					return 0;

				}
				if(i==3){
					cout<<"Error: Invalid capacity '" << argv[i] <<"' for jug C."<<endl;
					return 0;

				}
			}
			else{
				if(i==4){
					cout<<"Error: Invalid goal '" << argv[i] <<"' for jug A."<<endl;
					return 0;

				}

				if(i==5){
					cout<<"Error: Invalid goal '" << argv[i] <<"' for jug B."<<endl;
					return 0;

				}
				if(i==6){
					cout<<"Error: Invalid goal '" << argv[i] <<"' for jug C."<<endl;
					return 0;

				}
			}
		}

	}

	for (int i = 1, j = 4; i <= 3 && j <= 6; i++, j++) {
			int temp_i, temp_j;
			istringstream iss_i(argv[i]);
			iss_i >> temp_i;
			istringstream iss_j(argv[j]);
			iss_j >> temp_j;
			if ((temp_j > temp_i) && i == 1) {
				cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
				return 1;
			}
			if ((temp_j > temp_i) && i == 2) {
				cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
				return 1;
			}
			if ((temp_j > temp_i) && i == 3) {
				cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
				return 1;
			}
		}


	State s(0, 0, 8);
	cout << s.to_string() << endl;
	s.a += 3;
	s.c -= 3;
	cout << s.to_string() << endl;
	return 0;

}
