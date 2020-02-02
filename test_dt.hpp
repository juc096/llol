//
//  test_dt.hpp
//  ass2
//
//  Created by Justin Chen on 1/27/20.
//  Copyright © 2020 Justin Chen. All rights reserved.
//

#ifndef test_dt_hpp
#define test_dt_hpp

#include <stdio.h>
#include "DateTime.hpp"
#include "Task.hpp"
#include "Meeting.hpp"
#include "Calendar.hpp"
namespace ECE141 {
class test_dt {
public:
    test_dt(const DateTime &aDT = DateTime(), const std::string &aTitle = "lol",
    const std::string &aPerson1 = "loller1", const std::string &aPerson2="loller2");
    ~test_dt() {};
    
    bool test_heap();
    bool test_meeting();
    bool test_task();
    void run_test();
    bool test_parse();
    Meeting* allocate();
    
    void test_obj_slice();
    void some_func(DateTime * temp);
    void test_cal();
protected:
    DateTime dt;
    Task t;
    Meeting m;
    
    
    
    
};
}

#endif /* test_dt_hpp */
