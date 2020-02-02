//
//  test_dt.cpp
//  ass2
//
//  Created by Justin Chen on 1/27/20.
//  Copyright © 2020 Justin Chen. All rights reserved.
//

#include "test_dt.hpp"
#include <iostream>
#include <sstream>
namespace ECE141 {

test_dt::test_dt(const DateTime &aDT, const std::string &aTitle, const std::string &aPerson1, const std::string &aPerson2) : dt(aDT),m(aDT, aTitle,aPerson1,aPerson2), t(aDT, aTitle,aPerson1) {
}

    
bool test_dt::test_meeting() {
    Meeting temp = Meeting(m);
    bool pass = true;
    if (m.getDate() == temp.getDate()) {
    }
    else {
        std::cout << "error;date should be equal" << std::endl;
        pass = false;
    }
    if(m.getPerson(1) != temp.getPerson(1)) {
        std::cout << "error;person1 should be equal" << std::endl;
        pass = false;
    }
    if (m.getTitle() != temp.getTitle()) {
        std::cout << "error;title should be equal" << std::endl;
        pass = false;
    }
    
    temp.setTitle("testing_temp_title");
    if (temp.getTitle() != "testing_temp_title") {
        std::cout << "error;title should be diff" << std::endl;
        pass = false;
    }
    temp.setPerson("testing_temp_person1",1);
    if (m.getPerson(1) == temp.getPerson(1)) {
        std::cout << "error;person1 should be diff" << std::endl;
        pass = false;
    }
    temp.setPerson("testing_temp_person2",2);
    if (m.getPerson(2) == temp.getPerson(2)) {
        std::cout << "error;person2 should be diff" << std::endl;
        pass = false;
    }
    
    return pass;
}
bool test_dt::test_task() {
    Task temp = Task(t);
    bool pass = true;
    if (t.getDate() == temp.getDate()) {
    }
    else {
        std::cout << "error;date should be equal" << std::endl;
        pass = false;
    }
    if(t.getPerson() != temp.getPerson()) {
        std::cout << "error;date should be equal" << std::endl;
        pass = false;
    }
    if (t.getTitle() != temp.getTitle()) {
        std::cout << "error;title should be equal" << std::endl;
        pass = false;
    }
    
    temp.setTitle("testing_temp_title");
    if (temp.getTitle() != "testing_temp_title") {
        std::cout << "error;title should be diff" << std::endl;
        pass = false;
    }
    temp.setPerson("testing_temp_person1");
    if (t.getPerson() == temp.getPerson()) {
        std::cout << "error;person1 should be diff" << std::endl;
        pass = false;
    }
    
    return pass;
}
Meeting* test_dt::allocate() {
    DateTime temp = DateTime(1,2,3,4,5);
    Meeting * re = new Meeting(temp, m.getTitle(),m.getPerson(1), m.getPerson(2));
    return re;
}
bool test_dt:: test_heap() {
    bool pass = true;
    Meeting* temp = allocate();
    if (temp->getDay() != temp->getDate().getDay()) {
        std::cout << "meeting obj's day valu:" <<temp->getDay()<<" meeting obj's reference to its derived base object's day value: " <<temp->getDate().getDay() << std::endl;
        std::cout << "error, should be equal. scope of variable temp went out, temp destroyed" <<std::endl;
        pass = false;
    }
    return pass;
    
}
bool test_dt::test_parse() {
    bool pass = true;
    std::string date = "2020-01-20";
    std::istringstream p(date);
    std::string token;
    while (std::getline(p,token,'-')) {
        std::cout<<std::stoi(token)<<std::endl;
    }
    
    return pass;
}
void test_dt::some_func(DateTime* temp) {
    //temp->what_ami();
    std::cout<<temp<<std::endl;
}

void test_dt::test_obj_slice() {
    //do overwritten operators prevent object slicing if param is ref to base class?
    //DateTime * temp = new DateTime();
    Meeting * m_temp = new Meeting(m);
    //Task * t_temp = new Task(t);
    std::cout << m_temp << std::endl;

    //std::cout << m << std::endl;
    //some_func(m_temp);
    //delete temp;
    delete m_temp;
    //delete t_temp;
    
}

void test_dt::test_cal() {
    const int theMonth = 1;
    const int theYear = 2020;
    ECE141::Calendar theCalendar(theMonth,theYear);
      
    //---------------------------------------------------
    //Add a test for loading of items from file...
    const char * thePath="./items.txt"; //items.txt file?
    std::ifstream theStream(thePath);
    theCalendar.load(theStream);
    
    /*auto mp = theCalendar.get_dowMap();
    for (auto iter = mp.begin(); iter != mp.end(); ++iter) {
        std::cout<< theCalendar.getdowString(iter->first) << std::endl;
    }
    std::cout<<"cal: " <<mp.size()<<std::endl;
    auto vect= theCalendar.getDT_vector("Sunday");
    auto vect1= theCalendar.getDT_vector("Saturday");
    std::cout << vect.size() <<std::endl;
    std::cout << vect1.size() <<std::endl;
    for (auto it = vect.begin(); it != vect.end(); ++it) {
        std::cout << *it << std::endl;
    }*/
    ECE141::Calendar theCalCopy = theCalendar;
    auto tempdt = theCalendar.firstAvailableHour(theCalCopy, 11,13,"Thursday");
    std::cout << tempdt.getHour() <<std::endl;
    std::cout << tempdt.getDay() <<std::endl;
    std::cout<<theCalCopy.get_taskCount() << std::endl;
    std::cout<<theCalendar.get_taskCount() << std::endl;
    Task * t_temp = new Task(t);
    theCalCopy.addItem(t_temp);
    std::cout<<theCalCopy.get_taskCount() << std::endl;
    std::cout<<theCalendar.get_taskCount() << std::endl;
    theCalCopy.show(std::cout);
    theCalCopy.showSummary(std::cout);
}

void test_dt::run_test() {
    if (test_task() && test_meeting() && test_heap() && test_parse()) {
        std::cout << "all pass!" <<std::endl;
        test_obj_slice();
        test_cal();
    }
    else {
        std::cout << "fail" <<std::endl;
    }

}


}
