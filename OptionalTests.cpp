#include <iostream>
#include "OptionalTests.h"
#include "Optional.h"

static void testEmptyConstruction();
static void testConstructionWithNone();
static void testConstructionWithValue();
static void testEqualityComparison();
static void testLessThanComparison();
static void testEmptyDereference();
static void testCopy();
static void testAssign();
static void testConversionToBool();

void runOptionalTests()
{
    std::cout << "=== Optional tests ===" << std::endl;
    testEmptyConstruction();
    testConstructionWithNone();
    testConstructionWithValue();
    testEqualityComparison();
    testLessThanComparison();
    testEmptyDereference();
    testCopy();
    testAssign();
    testConversionToBool();
}

void testEmptyConstruction()
{
    std::cout << "-- testEmptyConstruction" << std::endl;
    Optional<int> optionalInt;
    std::cout << "Int optional is empty: " << optionalInt.isEmpty() << std::endl;
    std::cout << "Int optional output: " << optionalInt << std::endl;
}

void testConstructionWithNone()
{
    std::cout << "-- testConstructionWithNone" << std::endl;
    Optional<int> optionalInt = None;
    Optional<double> optionalDouble = None;

    std::cout << "Int optional is empty: " << optionalInt.isEmpty() << std::endl;
    std::cout << "Double optional is empty: " << optionalDouble.isEmpty() << std::endl;
    std::cout << "Int optional output: " << optionalInt << std::endl;
    std::cout << "Double optional output: " << optionalDouble << std::endl;
}

void testConstructionWithValue()
{
    std::cout << "-- testConstructionWithValue" << std::endl;
    Optional<int> optional = 10;

    std::cout << "Is empty: " << optional.isEmpty() << std::endl;
    std::cout << "Value: " << *optional << std::endl;
    std::cout << "Output: " << optional << std::endl;
}

void testEqualityComparison()
{
    std::cout << "-- testEqualityComparison" << std::endl;

    Optional<int> empty1 = None;
    Optional<int> empty2 = None;
    Optional<int> nonEmpty1 = 10;
    Optional<int> nonEmpty2 = 20;
    Optional<int> nonEmpty3 = 10;

    std::cout << "empty == empty: " << (empty1 == empty2) << std::endl;
    std::cout << "empty == nonEmpty: " << (empty2 == nonEmpty1) << std::endl;
    std::cout << "nonEmpty == empty: " << (nonEmpty1 == empty2) << std::endl;
    std::cout << "nonEmpty == nonEmpty (not-equal): " << (nonEmpty1 == nonEmpty2) << std::endl;
    std::cout << "nonEmpty == nonEmpty (equal) : " << (nonEmpty1 == nonEmpty3) << std::endl;
}

void testLessThanComparison()
{
//    std::cout << "-- testLessThanComparison" << std::endl;

//    Optional<int> empty1 = None;
//    Optional<int> empty2 = None;
//    Optional<int> nonEmpty1 = 10;
//    Optional<int> nonEmpty2 = 20;
//
//    std::cout << "empty < empty: " << (empty1 < empty2) << std::endl;
//    std::cout << "empty < nonEmpty: " << (empty1 < nonEmpty1) << std::endl;
//    std::cout << "nonEmpty < empty: " << (nonEmpty1 < empty1) << std::endl;
//    std::cout << "nonEmpty1 < nonEmpty2: " << (nonEmpty1 < nonEmpty2) << std::endl;
//    std::cout << "nonEmpty2 < nonEmpty1: " << (nonEmpty2 < nonEmpty1) << std::endl;
}

void testEmptyDereference()
{
    std::cout << "-- testEmptyDereference" << std::endl;

    const Optional<int> empty;
    try
    {
        std::cout << empty.value() << std::endl;
    }
    catch(std::logic_error& logicError)
    {
        std::cout << "Exception: " << logicError.what() << std::endl;
    }
}

void testCopy()
{
    std::cout << "-- testCopy" << std::endl;

    Optional<int> empty;
    Optional<int> nonEmpty = 10;

    Optional<int> copyFromEmpty = empty;
    std::cout << "copyFromEmpty = " << copyFromEmpty << std::endl;

    Optional<int> copyFromNonEmpty = nonEmpty;
    std::cout << "copyFromNonEmpty = " << copyFromNonEmpty << std::endl;
}

void testAssign()
{
    std::cout << "-- testAssign" << std::endl;

    Optional<int> empty;
    Optional<int> nonEmpty = 1;

    Optional<int> test1;
    test1 = empty;
    std::cout << "empty = empty => " << test1 << std::endl;

    Optional<int> test2;
    test2 = nonEmpty;
    std::cout << "empty = nonEmpty => " << test2 << std::endl;

    Optional<int> test3 = 4;
    test3 = empty;
    std::cout << "nonEmpty = empty => " << test3 << std::endl;

    Optional<int> test4 = 5;
    test4 = nonEmpty;
    std::cout << "nonEmpty = nonEmpty => " << test4 << std::endl;
}

void testConversionToBool()
{
    std::cout << "-- testConversionToBool" << std::endl;

    Optional<int> empty;
    Optional<int> nonEmpty = 1;

    if (empty)
        std::cout << "Bad. Empty shold be false!" << std::endl;
    else
        std::cout << "Good! Empty should be false" << std::endl;

    if (nonEmpty)
        std::cout << "Good! Empty should be true" << std::endl;
    else
        std::cout << "Bad. Empty should be true!" << std::endl;
}
