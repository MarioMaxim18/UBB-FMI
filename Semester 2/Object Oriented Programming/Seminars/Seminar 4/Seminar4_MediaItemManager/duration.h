#pragma once
#include <iostream>
#include <string>
using std::ostream;
using std::string;
//create an association between „ushi” and unsigned short int: everywhere
//where ushi will be found, unsigned short int substituted by the compiler
#define ushi unsigned short int
class Duration final {
private:
	unsigned short int minutes;
	unsigned short int seconds;
public:
	Duration(ushi _minutes = 0, ushi _seconds = 0) : minutes{ _minutes }, seconds{ _seconds } {};
	Duration(string dur_string);
	inline ushi getMinutes() const { return minutes; };
	inline ushi getSeconds() const { return seconds; };
	void setSeconds(ushi _seconds) { seconds = _seconds; };
	void setMinutes(ushi _minutes) { minutes = _minutes; };
	friend ostream& operator<<(ostream& os, const Duration& dur);
	~Duration() = default;
};

