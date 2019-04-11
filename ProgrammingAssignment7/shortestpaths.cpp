/*
 * shortestpath.cpp
 *
 *  Created on: Nov 28, 2018
 *  Author: Jessica Valenzuela and Himanshu Rana
 *  I pledge my honor that I have abided by the Stevens Honor System.
 */

#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;
long num_vertices;
long INF = numeric_limits<long>::max();
long** intermatrix;
long** W;
long** distancemat;

//vertices in the matrix

long len(long num) {
	long digits = 1;
	while (num > 9) {
		num = num / 10;
		digits++;
	}
	return digits;
}
//copy matrix for use in variable
long** copy(long** toCopy) {
	long** returnarray = new long*[num_vertices];
	for (int i = 0; i < num_vertices; i++) {
		returnarray[i] = new long[num_vertices];
		for (int j = 0; j < num_vertices; j++) {
			returnarray[i][j] = toCopy[i][j];
		}
	}
	return returnarray;
}

//output the distance matrix that will have the shortest path using floyds algorithm
long** floydsalgorithm(long** W) {
	distancemat = copy(W);
	intermatrix = new long*[num_vertices];

	for (int i = 0; i < num_vertices; ++i) {
		intermatrix[i] = new long[num_vertices];
		fill(intermatrix[i], intermatrix[i] + num_vertices, INF);
	}
	for (int k = 1; k <= num_vertices; k++) {
		for (int i = 1; i <= num_vertices; i++) {
			for (int j = 1; j <= num_vertices; j++) {
				long path = distancemat[i-1][k-1] + distancemat[k-1][j-1];
				if (path < 0) {
					path = INF;
				}
				if (path < distancemat[i-1][j-1]) {
					distancemat[i-1][j-1] = path;
					intermatrix[i-1][j-1] = k-1;
				}
			}
		}
	}
		return distancemat;
	}

	/**
	 * Displays the matrix on the screen formatted as a table.
	 */
void display_table(long** const matrix, const string &label,
		const bool use_letters = false) {
	cout << label << endl;
	long max_val = 0;
	for (int i = 0; i < num_vertices; i++) {
		for (int j = 0; j < num_vertices; j++) {
			long cell = matrix[i][j];
			if (cell < INF && cell > max_val) {
				max_val = matrix[i][j];
			}
		}
	}
	int max_cell_width = len(max(static_cast<long>(num_vertices), max_val));
	cout << ' ';
	for (int j = 0; j < num_vertices; j++) {
		cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
	}
	cout << endl;
	for (int i = 0; i < num_vertices; i++) {
		cout << static_cast<char>(i + 'A');
		for (int j = 0; j < num_vertices; j++) {
			cout << " " << setw(max_cell_width);
			if (matrix[i][j] == INF) {
				cout << "-";
			} else if (use_letters) {
				cout << static_cast<char>(matrix[i][j] + 'A');
			} else {
				cout << matrix[i][j];
			}
		}
		cout << endl;
	}
	cout << endl;
}

vector<char> pathinfohelper(int i, int j) {
	if (intermatrix[i][j] == INF) {
		vector<char> temp;
		temp.push_back(static_cast<char>(i + 'A'));
		if (i != j) {
			temp.push_back(static_cast<char>(j + 'A'));
		}
		return temp;
	}
	long t = intermatrix[i][j];
	vector<char> a = pathinfohelper(i, t);
	vector<char> b = pathinfohelper(t, j);
	a.insert(a.end(), b.begin() + 1, b.end());
	return a;

}

void pathinfo() {
	//displays path length and path it takes
	for (int i = 1; i <= num_vertices; i++) {
		for (int j = 1; j <= num_vertices; j++) {
			bool pathExists = distancemat[i-1][j-1] != INF;
			cout << static_cast<char>(i-1 + 'A') << " -> "
			<< static_cast<char>(j-1 + 'A') << ", distance: "
			<< (pathExists ? to_string(distancemat[i-1][j-1]) : "infinity")
			<< ", path: ";
			if (pathExists) {
				vector<char> path = pathinfohelper(i-1, j-1);
				cout << path.at(0);
				for (size_t k = 1; k < path.size(); k++) {
					cout << " -> " << path.at(k);
				}
			} else {
				cout << "none";
			}
			cout << endl;
		}
	}
}


int main(int argc, const char *argv[]) {
	// Make sure the right number of command line arguments exist.
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <filename>" << endl;
		return 1;
	}
	// Create an ifstream object.
	ifstream input_file(argv[1]);
	// If it does not exist, print an error message.
	if (!input_file) {
		cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
		return 1;
	}
	// Add read errors to the list of exceptions the ifstream will handle.
	input_file.exceptions(ifstream::badbit);
	string line;
	try {
		unsigned int line_number = 1;
		istringstream iss;
		char start, end;
		int weight;
		// Use getline to read in a line.
		// See http://www.cplusplus.com/reference/string/string/getline/
		while (getline(input_file, line)) {
			iss.str(line);
			if (line_number == 1) {
				if (!(iss >> num_vertices) || num_vertices >= 27
						|| num_vertices <= 0) {
					cerr << "Error: Invalid number of vertices '" << line
					<< "' on line " << line_number << "." << endl;
					return 1;
				}
				W = new long*[num_vertices];
				for (int i = 0; i < num_vertices; ++i) {
					W[i] = new long[num_vertices];
					fill(W[i], W[i] + num_vertices, INF);
				}
				for (int i = 0; i < num_vertices; ++i) {
					W[i][i] = 0;
				}

			} else {
				vector<string> results(istream_iterator<string> {iss},
						istream_iterator<string>());
				if (results.size() != 3) {
					cerr << "Error: Invalid edge data '" << line << "' on line "
					<< line_number << "." << endl;
					return 1;
				}
				iss.clear();
				iss.str(results.at(0));
				if (!(iss >> start) || start < 'A'
						|| start >= ('A' + num_vertices)) {
					cerr << "Error: Starting vertex '" << results.at(0)
					<< "' on line " << line_number
					<< " is not among valid values A-"
					<< static_cast<char>('A' + num_vertices - 1) << "."
					<< endl;
					return 1;
				}
				iss.clear();
				iss.str(results.at(1));
				if (!(iss >> end) || end < 'A' || end >= ('A' + num_vertices)) {
					cerr << "Error: Ending vertex '" << results.at(1)
					<< "' on line " << line_number
					<< " is not among valid values A-"
					<< static_cast<char>('A' + num_vertices - 1) << "."
					<< endl;

					return 1;
				}
				iss.clear();
				iss.str(results.at(2));
				if (!(iss >> weight) || weight <= 0) {
					cerr << "Error: Invalid edge weight '" << results.at(2)
					<< "' on line " << line_number << "." << endl;
					return 1;
				}
				W[start - 'A'][end - 'A'] = weight;
			}
			iss.clear();
			++line_number;
		}
		// Don't forget to close the file.
		input_file.close();
	} catch (const ifstream::failure &f) {
		cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
		return 1;
	}

	display_table(W, "Distance matrix:");
	display_table(floydsalgorithm(W), "Path lengths:");
	display_table(intermatrix, "Intermediate vertices:", true);
	pathinfo();
	return 0;
}
