#include <string>
#include <iostream>

#include "Student.h"
#include "Room.h"
#include "Date.h"
#include "Reservation.h"
#include "Library.h"

#include "a1-global.cc"

int main() {
    // std::cout << std::endl;
    // std::cout << "Test Case 1.a (different days):" << std::endl;
    // std::cout << "=============================";
    // Date d1(2020, 1, 24, 11, 3);
    // Date d2(2020, 1, 23, 11, 3);
    // testDate(d1, d2, false);

    // std::cout << std::endl;
    // std::cout << "Test Case 1.b (same day, >=3 hours difference):" << std::endl;
    // std::cout << "=============================";
    // Date d3(2021, 10, 1, 3, 3);
    // Date d4(2021, 10, 1, 6, 3);
    // testDate(d3, d4, false);

    // std::cout << std::endl;
    // std::cout << "Test Case 1.c (same day, d1: 1h+1duration, d2: 2h+3duration):" << std::endl;
    // std::cout << "=============================";
    // Date d5(2021, 10, 1, 1, 1);
    // Date d6(2021, 10, 1, 2, 3);
    // testDate(d5, d6, false);

    // std::cout << std::endl;
    // std::cout << "Test Case 1.d (same day, d1: 1h+3duration, d2: 2h+3duration):" << std::endl;
    // std::cout << "=============================";
    // Date d7(2021, 10, 1, 1, 3);
    // Date d8(2021, 10, 1, 2, 3);
    // testDate(d7, d8, true);

    // std::cout << std::endl;
    // std::cout << "Test Case 1.e (equal dates):" << std::endl;
    // std::cout << "=============================";
    // Date d9(2021, 10, 1, 2, 3);
    // Date d10(2021, 10, 1, 2, 3);
    // testDate(d9, d10, true);


    // std::cout << std::endl;
    // std::cout << "Tests for Library:" << std::endl;
    // std::cout << "=============================" << std::endl;
    // Library myLib = Library();
    // Library& myLibRef = myLib;
    // populate(myLibRef);
    // testReservations(myLibRef);

    Room big("bbbbbb", 1, 1, false);
    Room small("aaaaaa", 1, 1, false);
    if (small.lessThan(big)) {
        std::cout << "ok";
    }
}