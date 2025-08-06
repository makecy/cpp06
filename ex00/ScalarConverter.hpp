#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>
#include <iostream>
#include <limits>
#include <cmath>
#include <cctype>
#include <cstdlib>

class ScalarConverter {
private:
    	ScalarConverter();
    	ScalarConverter(const ScalarConverter& other);
    	ScalarConverter& operator=(const ScalarConverter& other);
    	~ScalarConverter();

		enum LiteralType {
			CHAR,
			INT,
			FLOAT,
			DOUBLE,
			INVALID
		};

		static LiteralType detectType(const std::string& literal);
		static void convertFromChar(char value);
		static void convertFromInt(int value);
		static void convertFromFloat(float value);
		static void convertFromDouble(double value);
		static bool isChar(const std::string& literal);
		static bool isInt(const std::string& literal);
		static bool isFloat(const std::string& literal);
		static bool isDouble(const std::string& literal);
		static bool isSpecialFloat(const std::string& literal);
		static bool isSpecialDouble(const std::string& literal);

public:
		static void convert(const std::string& literal);
};

#endif