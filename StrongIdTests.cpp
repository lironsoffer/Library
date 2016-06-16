#include "StrongIdTests.h"
#include "StrongId.h"
#include <string>
#include <iostream>
//
static void testEmptyConstruction();
static void testName();
static void testConstructionWithValue();
static void testEqualityComparison();
static void testLessThanComparison();
static void testEmptyDereference();
static void testCopy();
static void testAssign();


void runStrongIdTests()
{
    std::cout << "=== StrongId tests ===" << std::endl;
    testName();
    testEmptyConstruction();
    testConstructionWithValue();
    testEqualityComparison();
    testLessThanComparison();
    testEmptyDereference();
    testCopy();
    testAssign();
}

class TestProperties
{
public:
    typedef unsigned ValueType;
    static const char* name() { return "TestId"; }
};

typedef StrongId<TestProperties> TestId;

void testName()
{
    std::cout << "-- testName" << std::endl;
    std::cout << TestId::name() << std::endl;
}

void testEmptyConstruction()
{
    std::cout << "-- testEmptyConstruction" << std::endl;

    TestId id;
    std::cout << id << std::endl;
    std::cout << id.isEmpty() << std::endl;
}

void testConstructionWithValue()
{
    std::cout << "-- testConstructionWithValue" << std::endl;

    TestId id(10);
    std::cout << "Value: " << id.value() << std::endl;
    std::cout << "Empty: " << id.isEmpty() << std::endl;
    std::cout << "Output: " << id << std::endl;
}

void testEqualityComparison()
{
    std::cout << "-- testEqualityComparison" << std::endl;

    TestId empty1;
    TestId empty2;
    TestId nonEmpty1(10);
    TestId nonEmpty2(20);
    TestId nonEmpty3(10);

    std::cout << "empty == empty: " << (empty1 == empty2) << std::endl;
    std::cout << "empty == nonEmpty: " << (empty2 == nonEmpty1) << std::endl;
    std::cout << "nonEmpty == empty: " << (nonEmpty1 == empty2) << std::endl;
    std::cout << "nonEmpty == nonEmpty (not-equal): " << (nonEmpty1 == nonEmpty2) << std::endl;
    std::cout << "nonEmpty == nonEmpty (equal) : " << (nonEmpty1 == nonEmpty3) << std::endl;
}

void testLessThanComparison()
{
    std::cout << "-- testLessThanComparison" << std::endl;

    TestId empty1;
    TestId empty2;
    TestId nonEmpty1(10);
    TestId nonEmpty2(20);

    std::cout << "empty < empty: " << (empty1 < empty2) << std::endl;
    std::cout << "empty < nonEmpty: " << (empty1 < nonEmpty1) << std::endl;
    std::cout << "nonEmpty < empty: " << (nonEmpty1 < empty1) << std::endl;
    std::cout << "nonEmpty1 < nonEmpty2: " << (nonEmpty1 < nonEmpty2) << std::endl;
    std::cout << "nonEmpty2 < nonEmpty1: " << (nonEmpty2 < nonEmpty1) << std::endl;
}

void testEmptyDereference()
{
    std::cout << "-- testEmptyDereference" << std::endl;

    const TestId empty;
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

    TestId empty;
    TestId nonEmpty(10);

    TestId copyFromEmpty = empty;
    std::cout << "copyFromEmpty = " << copyFromEmpty << std::endl;

    TestId copyFromNonEmpty = nonEmpty;
    std::cout << "copyFromNonEmpty = " << copyFromNonEmpty << std::endl;
}
//
void testAssign()
{
    std::cout << "-- testAssign" << std::endl;

    TestId empty;
    TestId nonEmpty(1);

    TestId test1;
    test1 = empty;
    std::cout << "empty = empty => " << test1 << std::endl;

    TestId test2;
    test2 = nonEmpty;
    std::cout << "empty = nonEmpty => " << test2 << std::endl;

    TestId test3(4);
    test3 = empty;
    std::cout << "nonEmpty = empty => " << test3 << std::endl;

    TestId test4(5);
    test4 = nonEmpty;
    std::cout << "nonEmpty = nonEmpty => " << test4 << std::endl;
}
