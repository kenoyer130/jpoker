#ifndef JOUT_H
#define JOUT_H

#define jout Jout()

#define debug Debug()

#include <iostream>
#include <stdio.h>
#include <fstream>

using std::cout;
using std::ofstream;
using std::string;

class Jout {

private:

	string file {"log.txt"};
	ofstream fileoutput;	
	
public:
	
    Jout() {
		
    }

	void init() {
		if( remove(file.c_str()) != 0) {
			cout << "error deleting log file!";
		}
	}
	
    ~Jout() {
        
    }
	
    template<typename T> Jout& operator <<(const T& data) {

		fileoutput.open(file, std::ios_base::app);

		if(fileoutput.is_open()) {
		
			fileoutput << data;
			std::cout << data;

			fileoutput.close();
		} else {
			cout << "error writing to log file!";
		}
		
        return *this;
    }
};

class Debug {

public:
	static int DebugEnabled;
	
    template<typename T> Debug& operator << (const T& data) {

		if(Debug::DebugEnabled == 1) {
			jout << data;
		}

        return *this;
    }
	
	Debug () {

	}
};

#endif /* JOUT_H */
