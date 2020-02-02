//
//  main.cpp
//  assignment2
//
//  Created by Justin Chen on 1/21/20.
//  Copyright © 2020 Justin Chen. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "DateTime.hpp"
#include "Calendar.hpp"
#include "Testing.hpp"
//#include "test_dt.hpp"


std::ostream& getOutputStream() {return std::cout;}

int main(int argc, const char * argv[]) {
  ECE141::Testing theTester(getOutputStream());
    //ECE141::DateTime temp(23,1,2020);
    //ECE141::test_dt theTester = ECE141::test_dt(temp);
    //theTester.run_test();
  theTester.runTests();
    /*std::vector<std::array<int,24> >times_unav;
    for (int i =0; i < 30; i++){
        std::array<int,24> temp={0};
        std::cout << &temp<<std::endl;
        times_unav.push_back(temp);
    }
    times_unav[0][3]=4;
    times_unav[20][3]=30;
    std::cout << times_unav[0][3]<<std::endl;
    std::cout << times_unav[40][3]<<std::endl;*/
  return 0;
}
