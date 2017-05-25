#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>

#include "key.hpp"
#include "brute.hpp"
//using namespace std;
std::string me;
std::string encrypted;
std::string table_filename;
bool verbose = false;

Brute::Brute(const std::string& filename) {
	T.resize(N);
	std::string buffer;
    std::fstream input(filename.c_str(), std::ios::in);
    for (int i = 0; i < N; i++) {
        std::getline(input, buffer);
        T[i].set_string(buffer); // change this to only last x amount of characters
    }
    input.close();
}

void Brute::decrypt(const std::string& encrypted){
	// your code here
    Key key(encrypted); // Key object for the encrypted string
    char arr[C];
    char encKey[C];
    int i = 0;
    while (i<C){
        arr[i] = 'a';
        encKey[i] = 'a';
        if (i == C-1) {
            encKey[i] = 'b';
        }
        i++;
    }
    Key start(arr);
    Key res(encKey);
    long long dang = std::pow(32,C);
    i=0;
    while (i < dang) {
        if (start.subset_sum(T, false)==key){
            start.showLess();
            std::cout << '\n';
        }
        start += res;
        i++;
    }
}

void usage(const std::string& error_msg="") {
	if (!error_msg.empty()) std::cout << "ERROR: " << error_msg << '\n';
	std::cout << me << ": Brute force cracking of Subset-sum password with " 
		<< B << " bits precision\n"
	    << "USAGE: " << me << " <encrypted> <table file> [options]\n"
		<< "\nArguments:\n"
		<< " <encrypted>:   encrypted password to crack\n"
		<< " <table file>:  name of file containing the table to use\n"
		<< "\nOptions:\n"
		<< " -h|--help:     print this message\n"
		<< " -v|--verbose:  select verbose mode\n\n";
	exit(0);
}

void initialize(int argc, char* argv[]) {
	me = argv[0];
	if (argc < 3) usage("Missing arguments");
	encrypted = argv[1];
	table_filename = argv[2];
	for (int i=3; i<argc; ++i) {
		std::string arg = argv[i];
		if (arg == "-h" || arg == "--help") usage();
		else if (arg == "-v" || arg == "--verbose") verbose = true;
		else usage("Unrecognized argument: " + arg);
	}
}


int main(int argc, char *argv[]){
	
	initialize(argc, argv);
	
	Brute b(table_filename);
    b.decrypt(encrypted);
	
	return 0;
}