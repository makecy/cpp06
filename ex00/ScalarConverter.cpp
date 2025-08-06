#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) { (void)other; return *this; }
ScalarConverter::~ScalarConverter() {}

bool ScalarConverter::isChar(const std::string& literal) {
    return (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'');
}

bool ScalarConverter::isInt(const std::string& literal) {
    size_t i = 0;

    if (literal[0] == '+' || literal[0] == '-')
        i++;
    if (i == literal.length())
        return false;
    for (; i < literal.length(); i++) {
        if (!isdigit(literal[i]))
            return false;
    }
    
    return true;
}

bool ScalarConverter::isFloat(const std::string& literal) {
    if (isSpecialFloat(literal))
        return true;
    if (literal.length() < 2 || literal[literal.length() - 1] != 'f')
        return false;
    std::string withoutF = literal.substr(0, literal.length() - 1);
    return isDouble(withoutF);
}

bool ScalarConverter::isDouble(const std::string& literal) {
    if (isSpecialDouble(literal))
        return true;
        
    size_t i = 0;
    bool hasDecimalPoint = false;
    if (literal[0] == '+' || literal[0] == '-')
        i++;
    if (i == literal.length())
        return false;
    for (; i < literal.length(); i++) {
        if (literal[i] == '.') {
            if (hasDecimalPoint)
                return false;
            hasDecimalPoint = true;
        } else if (!isdigit(literal[i])) {
            return false;
        }
    }
    return hasDecimalPoint;
}

bool ScalarConverter::isSpecialFloat(const std::string& literal) {
    return (literal == "nanf" || literal == "+inff" || literal == "-inff");
}

bool ScalarConverter::isSpecialDouble(const std::string& literal) {
    return (literal == "nan" || literal == "+inf" || literal == "-inf");
}
ScalarConverter::LiteralType ScalarConverter::detectType(const std::string& literal) {
    if (isChar(literal))
        return CHAR;
    else if (isInt(literal))
        return INT;
    else if (isFloat(literal))
        return FLOAT;
    else if (isDouble(literal))
        return DOUBLE;
    else
        return INVALID;
}
void ScalarConverter::convertFromChar(char value) {
    if (isprint(value))
        std::cout << "char: '" << value << "'" << std::endl;
    else
        std::cout << "char: Non displayable" << std::endl;
    std::cout << "int: " << static_cast<int>(value) << std::endl;
    std::cout << "float: " << static_cast<float>(value) << ".0f" << std::endl;
    std::cout << "double: " << static_cast<double>(value) << ".0" << std::endl;
}

void ScalarConverter::convertFromInt(int value) {
    if (value >= 0 && value <= 127) {
        if (isprint(value))
            std::cout << "char: '" << static_cast<char>(value) << "'" << std::endl;
        else
            std::cout << "char: Non displayable" << std::endl;
    }
	else
        std::cout << "char: impossible" << std::endl;
    std::cout << "int: " << value << std::endl;
    std::cout << "float: " << static_cast<float>(value) << ".0f" << std::endl;
    std::cout << "double: " << static_cast<double>(value) << ".0" << std::endl;
}

void ScalarConverter::convertFromFloat(float value) {
    if (std::isnan(value) || std::isinf(value) || value < 0 || value > 127) {
        std::cout << "char: impossible" << std::endl;
    } else {
        if (isprint(static_cast<char>(value)))
            std::cout << "char: '" << static_cast<char>(value) << "'" << std::endl;
        else
            std::cout << "char: Non displayable" << std::endl;
    }
    
    if (std::isnan(value) || std::isinf(value) || value > std::numeric_limits<int>::max() || value < std::numeric_limits<int>::min()) {
        std::cout << "int: impossible" << std::endl;
    } else {
        std::cout << "int: " << static_cast<int>(value) << std::endl;
    }
    
    if (value == static_cast<int>(value))
        std::cout << "float: " << value << ".0f" << std::endl;
    else
        std::cout << "float: " << value << "f" << std::endl;
    
    if (value == static_cast<int>(value))
        std::cout << "double: " << static_cast<double>(value) << ".0" << std::endl;
    else
        std::cout << "double: " << static_cast<double>(value) << std::endl;
}

void ScalarConverter::convertFromDouble(double value) {
    if (std::isnan(value) || std::isinf(value) || value < 0 || value > 127) {
        std::cout << "char: impossible" << std::endl;
    }
	else {
        if (isprint(static_cast<char>(value)))
            std::cout << "char: '" << static_cast<char>(value) << "'" << std::endl;
        else
            std::cout << "char: Non displayable" << std::endl;
    }
    
    if (std::isnan(value) || std::isinf(value) || value > std::numeric_limits<int>::max() || value < std::numeric_limits<int>::min()) {
        std::cout << "int: impossible" << std::endl;
    } else {
        std::cout << "int: " << static_cast<int>(value) << std::endl;
    }
    
    if (value > std::numeric_limits<float>::max() || value < -std::numeric_limits<float>::max()) {
        std::cout << "float: impossible" << std::endl;
    } else {
        if (value == static_cast<int>(value))
            std::cout << "float: " << static_cast<float>(value) << ".0f" << std::endl;
        else
            std::cout << "float: " << static_cast<float>(value) << "f" << std::endl;
    }

    if (value == static_cast<int>(value))
        std::cout << "double: " << value << ".0" << std::endl;
    else
        std::cout << "double: " << value << std::endl;
}

// Public convert method
void ScalarConverter::convert(const std::string& literal) {
    LiteralType type = detectType(literal);
    
    switch (type) {
        case CHAR:
            convertFromChar(literal[1]);
            break;
        case INT:
            convertFromInt(atoi(literal.c_str()));
            break;
        case FLOAT:
            if (isSpecialFloat(literal)) {
                if (literal == "nanf")
                    convertFromFloat(std::numeric_limits<float>::quiet_NaN());
                else if (literal == "+inff")
                    convertFromFloat(std::numeric_limits<float>::infinity());
                else // "-inff"
                    convertFromFloat(-std::numeric_limits<float>::infinity());
            } else {
                convertFromFloat(atof(literal.c_str()));
            }
            break;
        case DOUBLE:
            if (isSpecialDouble(literal)) {
                if (literal == "nan")
                    convertFromDouble(std::numeric_limits<double>::quiet_NaN());
                else if (literal == "+inf")
                    convertFromDouble(std::numeric_limits<double>::infinity());
                else
                    convertFromDouble(-std::numeric_limits<double>::infinity());
            } else {
                convertFromDouble(atof(literal.c_str()));
            }
            break;
        default:
            std::cout << "Invalid input: Could not determine type." << std::endl;
            break;
    }
}