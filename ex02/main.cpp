#include "Functions.hpp"
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>

int main() {
    std::cout << "=== Testing Type Identification ===" << std::endl;
    
    std::cout << "\n--- Testing generate() function ---" << std::endl;
    Base* instances[6];
    
    for (int i = 0; i < 6; i++) {
        std::cout << "Generation " << (i + 1) << ": ";
        instances[i] = generate();
    }
    
    std::cout << "\n--- Testing identify(Base* p) ---" << std::endl;
    for (int i = 0; i < 6; i++) {
        std::cout << "Instance " << (i + 1) << " type: ";
        identify(instances[i]);
    }
    
    std::cout << "\n--- Testing identify(Base& p) ---" << std::endl;
    for (int i = 0; i < 6; i++) {
        std::cout << "Instance " << (i + 1) << " type: ";
        identify(*instances[i]);
    }
    
    std::cout << "\n--- Testing with manually created objects ---" << std::endl;
    
    A manualA;
    B manualB;
    C manualC;
    
    std::cout << "Manual A (pointer): ";
    identify(&manualA);
    std::cout << "Manual A (reference): ";
    identify(manualA);
    
    std::cout << "Manual B (pointer): ";
    identify(&manualB);
    std::cout << "Manual B (reference): ";
    identify(manualB);
    
    std::cout << "Manual C (pointer): ";
    identify(&manualC);
    std::cout << "Manual C (reference): ";
    identify(manualC);

    std::cout << "\n--- Testing with Base pointers ---" << std::endl;
    Base* baseA = new A();
    Base* baseB = new B();
    Base* baseC = new C();
    
    std::cout << "Base* pointing to A: ";
    identify(baseA);
    std::cout << "Base* pointing to B: ";
    identify(baseB);
    std::cout << "Base* pointing to C: ";
    identify(baseC);
    std::cout << "\n--- Testing with NULL pointer ---" << std::endl;
    Base* nullPtr = NULL;
    std::cout << "NULL pointer: ";
    identify(nullPtr);
    std::cout << "\n--- Cleaning up ---" << std::endl;
    for (int i = 0; i < 6; i++) {
        delete instances[i];
    }
    
    delete baseA;
    delete baseB;
    delete baseC;
    
    return 0;
}