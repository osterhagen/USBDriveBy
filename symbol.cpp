#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cmath>
#include <map>

#include "key.hpp"
#include "symbol.hpp"

std::string me;
std::string encrypted;
std::string table_filename;
bool verbose = false;
std::map <Key, std::string> keyMap;

Symbol::Symbol(const std::string& filename) {
	T.resize(N);
	std::string buffer;
    std::fstream input(filename.c_str(), std::ios::in);
    for (int i = 0; i < N; i++) {
        std::getline(input, buffer);
        T[i].set_string(buffer);
    }
    input.close();

}

void Symbol::decrypt(const std::string& encrypted){
    //std::cout << "Hey";
    Key key(encrypted); // Key object for the encrypted string
    char arr[C]; // make into string
    char encKey[C];
    char ender[C];
    long long i = 0;
    while (i<C){
        arr[i] = 'a';
        encKey[i] = 'a';
        ender[i] = 'a';
        if (i == C/2-1) {
            encKey[i] = 'b';
        }
        if (i == C-1)
            ender[i] = 'b';
        i++;
    }
    Key start(arr);
    Key res(encKey);
    Key end(ender);
    long long dang = std::pow(32,C);
    i=0;
    while (i < dang) {
        Key encrypt = start.subset_sum(T, false);
        std::string out = start.toString();
        keyMap.insert({encrypt, out});
        start += res;
        i++;
    }
    // test the 2nd thing on the hashmap
    for (int j = 0; j < pow(R, C/2); ++j) {
        Key pref = key;
        Key temp2 = end.subset_sum(T,false);
        pref -= temp2;
        if (keyMap.find(pref) != keyMap.end()){
            std::string hey = keyMap.at(pref);
            Key last(hey);
            last += end;
            last.showLess();
        }

    }
}

void usage(const std::string& error_msg="") {
	if (!error_msg.empty()) std::cout << "ERROR: " << error_msg << '\n';
	std::cout << me << ": Symbol table-based cracking of Subset-sum password"
		<< " with " << B << " bits precision\n"
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

    Symbol b(table_filename);
    b.decrypt(encrypted);
	
	return 0;
}
