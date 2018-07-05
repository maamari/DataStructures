#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <stdexcept>
#include <string>

class LengthMismatch : public std::exception{
public:
	LengthMismatch(int len1, int len2);
	std::string what();
private:
	std::string mismatch;
};

#endif
