#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>

int main() {
    std::cout << "=== Testing Serialization ===" << std::endl;
    Data originalData(42, "Test Object", 3.14159, true);
    Data* originalPtr = &originalData;
    std::cout << "\nOriginal Data object:" << std::endl;
    originalData.display();
    std::cout << "Original pointer address: " << originalPtr << std::endl;
    std::cout << "\n--- Serialization ---" << std::endl;
    uintptr_t serialized = Serializer::serialize(originalPtr);
    std::cout << "Serialized value: " << serialized << std::endl;
    std::cout << "Serialized value (hex): 0x" << std::hex << serialized << std::dec << std::endl;
    std::cout << "\n--- Deserialization ---" << std::endl;
    Data* deserializedPtr = Serializer::deserialize(serialized);
    std::cout << "Deserialized pointer address: " << deserializedPtr << std::endl;
    std::cout << "\n--- Verification ---" << std::endl;
    std::cout << "Original pointer == Deserialized pointer: " 
              << (originalPtr == deserializedPtr ? "TRUE" : "FALSE") << std::endl;
    std::cout << "\nData accessed through deserialized pointer:" << std::endl;
    deserializedPtr->display();
    std::cout << "\n=== Testing with Dynamic Allocation ===" << std::endl;
    Data* dynamicData = new Data(100, "Dynamic Object", 2.71828, false);
    std::cout << "\nDynamic Data object:" << std::endl;
    dynamicData->display();
    std::cout << "Dynamic pointer address: " << dynamicData << std::endl;
    uintptr_t dynamicSerialized = Serializer::serialize(dynamicData);
    Data* dynamicDeserialized = Serializer::deserialize(dynamicSerialized);
    std::cout << "\nDynamic serialized value: " << dynamicSerialized << std::endl;
    std::cout << "Dynamic deserialized pointer: " << dynamicDeserialized << std::endl;
    std::cout << "Dynamic original == deserialized: " 
              << (dynamicData == dynamicDeserialized ? "TRUE" : "FALSE") << std::endl;
    std::cout << "\nData accessed through dynamic deserialized pointer:" << std::endl;
    dynamicDeserialized->display();
    std::cout << "\n--- Testing Data Modification ---" << std::endl;
    std::cout << "Modifying data through deserialized pointer..." << std::endl;
    dynamicDeserialized->id = 999;
    dynamicDeserialized->name = "Modified";
    dynamicDeserialized->value = 42.0;
    dynamicDeserialized->active = true;
    std::cout << "Original dynamic data after modification:" << std::endl;
    dynamicData->display();
    delete dynamicData;
    std::cout << "\n=== Testing with NULL Pointer ===" << std::endl;
    Data* nullPtr = NULL;
    uintptr_t nullSerialized = Serializer::serialize(nullPtr);
    Data* nullDeserialized = Serializer::deserialize(nullSerialized);
    std::cout << "NULL pointer serialized: " << nullSerialized << std::endl;
    std::cout << "NULL pointer deserialized: " << nullDeserialized << std::endl;
    std::cout << "NULL original == deserialized: " 
              << (nullPtr == nullDeserialized ? "TRUE" : "FALSE") << std::endl;   
    return 0;
}