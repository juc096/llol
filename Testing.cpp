//
//  Testing.cpp
//  Assignment2
//
//  Created by rick gessner on 1/15/20.
//  Copyright © 2020 rick gessner. All rights reserved.
//

#include "Testing.hpp"
#include "DateTime.hpp"
#include "Task.hpp"
#include "Meeting.hpp"
#include "Calendar.hpp"
#include "DataHelper.hpp"

namespace ECE141 {
   
  bool testDateTime(Testing &aTester) {
    bool theResult=true;

    //add tests here for each method you want to validate!
    aTester.getOutput()
      << "\nTesting DateTime class...\n"
      << "-------------------------\n";

    DateTime theDate1(4,1,1961, 14,15); //rick's birthday
    DateTime theDate2(4,1,1961, 14,15); //rick's birthday
        
    //first -- test operator== (comparison)...
    if(!aTester.assertTrue("operator==", theDate1==theDate2)) {
      theResult=false;
    }

    //now test the copy constructor...
    DateTime theDateCopy(theDate1); //copy construct...
    if(!aTester.assertTrue("ctor(copy)", theDate1==theDateCopy)) {
      theResult=false;
    }
    
    //add other tests here...
      //more test cases in separate class test_dt.cpp
    
    return theResult;
  }

  //-----------------------------------
  //Test all the task methods...
  bool testTask(Testing &aTester) {
      bool theResult = true;
    
    aTester.getOutput()
      << "\nTesting Task class...\n"
      << "-------------------------\n";
      
      std::string ftitle=DataHelper::getFakeTitle();
      std::string fuser1=DataHelper::getFakeUser1();
      DateTime theDate1(4,1,1961, 14,15);
        Task aTask(theDate1, ftitle, fuser1);
        Task aTask1(aTask);
      if(!aTester.assertTrue("ctor(copy)", aTask==aTask1)) {
        theResult=false;
      }
      
      aTask.setTitle("yikes");
      if(!aTester.assertTrue("set title", aTask.getTitle() == "yikes")) {
        theResult=false;
      }
      aTask.setPerson("yikers");
      if(!aTester.assertTrue("set person", aTask.getPerson() == "yikers")) {
        theResult=false;
      }
      if(!aTester.assertTrue("not equal", aTask.getTitle() != aTask1.getTitle())) {
        theResult=false;
      }
      if(!aTester.assertTrue("not equal", aTask.getPerson() != aTask1.getPerson())) {
        theResult=false;
      }
    
      return theResult;
  }

  //-----------------------------------
  //Test all the meeting methods...
  bool testMeeting(Testing &aTester) {
    bool theResult = true;
    aTester.getOutput()
      << "\nTesting Meeting class...\n"
      << "-------------------------\n";
    std::string ftitle=DataHelper::getFakeTitle();
      std::string fuser1=DataHelper::getFakeUser1();
      std::string fuser2=DataHelper::getFakeUser2();
      DateTime theDate1(4,1,1961, 14,15);
        Meeting aMeeting(theDate1, ftitle, fuser1, fuser2);
        Meeting aMeeting1(aMeeting);
      if(!aTester.assertTrue("ctor(copy)", aMeeting==aMeeting1)) {
        theResult=false;
      }
      aMeeting.setTitle("yikes");
      if(!aTester.assertTrue("set title", aMeeting.getTitle() == "yikes")) {
        theResult=false;
      }
      aMeeting.setPerson("yikers",1);
      aMeeting.setPerson("yikers1",2);
      if(!aTester.assertTrue("set person1", aMeeting.getPerson(1) == "yikers")) {
        theResult=false;
      }
      if(!aTester.assertTrue("set person1", aMeeting.getPerson(2) == "yikers1")) {
        theResult=false;
      }
      if(!aTester.assertTrue("not equal", aMeeting.getTitle() != aMeeting1.getTitle())) {
        theResult=false;
      }
      if(!aTester.assertTrue("not equal", aMeeting.getPerson(1) != aMeeting1.getPerson(1))) {
        theResult=false;
      }
      if(!aTester.assertTrue("not equal", aMeeting.getPerson(2) != aMeeting1.getPerson(2))) {
        theResult=false;
      }
    
      return theResult;
      return true;
  }

  //-----------------------------------
  //Test all the calendar methods...
  bool testCalendar(Testing &aTester) {
    
    aTester.getOutput()
      << "\nTesting Calendar class...\n"
      << "-------------------------\n";
    
    const int theMonth = 1;
    const int theYear = 2020;
    ECE141::Calendar theCalendar(theMonth,theYear);
      
    //---------------------------------------------------
    //Add a test for loading of items from file...
    const char * thePath="./items.txt"; //items.txt file?
    std::ifstream theStream(thePath);
    theCalendar.load(theStream);
      
    //---------------------------------------------------
    //test adding fake tasks...
    for(int i=0;i<100;i++) {
      //make a fake (but reasonabale) datetime...
        //std::cout << "hi" <<std::endl;
      DateTime theDT(
        DataHelper::getRandomValue(1, 31), theMonth, theYear,
        DataHelper::getRandomValue(0, 23), DataHelper::getRandomValue(0, 59));
        //std::cout << "hi2" <<std::endl;
        std::string ftitle=DataHelper::getFakeTitle();
        //std::cout<<ftitle<<std::endl;
        
        std::string fuser1=DataHelper::getFakeUser1();
        //std::cout<<fuser1<<std::endl;
      Task *theTask = new Task( theDT, ftitle,fuser1);
        //std::cout << "hi3" <<std::endl;
      theCalendar.addItem(theTask);
        //std::cout << "hi4" <<std::endl;
    }
    
    //now validate that we added 100 tasks
    if(!aTester.assertTrue("addItem(task)", theCalendar.countTasks())) {  //SHOULD  be valid!
      return false;
    }
      
    //---------------------------------------------------
    //test adding fake meetings...
    for(int i=0;i<100;i++) {
      //make a fake (but reasonabale) datetime...
      DateTime theDT(
        DataHelper::getRandomValue(1, 31), theMonth, theYear,
        DataHelper::getRandomValue(0, 23), DataHelper::getRandomValue(0, 59));

      ECE141::Meeting *theMtg = new ECE141::Meeting( theDT, DataHelper::getFakeTitle(), DataHelper::getFakeUser1(), DataHelper::getFakeUser2());
      theCalendar.addItem(theMtg);
    }

    //Validate that we added 100 meetings
    //---------------------------------------------------
    if(!aTester.assertTrue("addItem(meeting)", theCalendar.countMeetings())) {  //SHOULD  be valid!
      return false;
    }

    //---------------------------------------------------
    
    //now output your calendar show() and summary() methods...
    aTester.getOutput() << theCalendar << "\n";
    theCalendar.showSummary(aTester.getOutput());
    
    //return false;
      return true;
  }

  //----------- this is the test controller ---------------
  
  bool Testing::assertTrue(const char *aMessage, bool aValue) {
    static const char* theMsgs[]={"OK\n","FAIL\n"};
    output << "\t" << aMessage << " " << theMsgs[!aValue];
    return aValue;
  }

  bool Testing::assertFalse(const char *aMessage, bool aValue) {
    static const char* theMsgs[]={"OK\n","FAIL\n"};
    output << "\t" << aMessage << " " << theMsgs[aValue];
    return false==aValue;
  }

  bool Testing::fail(const char* aMessage) {
    output << "Failure: " << aMessage << "\n";
    return false;
  }

  bool Testing::succeed(const char* aMessage) {
    output << "Success: " << aMessage << "\n";
    return true;
  }
  
  //This is the main test function...
  bool Testing::runTests() {
    
    if(!testDateTime(*this)) {
      output << "DateTime tests failed\n";
      return false;
    }

    if(!testTask(*this)) {
      output << "Task tests failed (stopping)\n";
      return false;
    }

    if(!testMeeting(*this)) {
      output << "Meeting tests failed  (stopping)\n";
      return false;
    }

    if(!testCalendar(*this)) {
      output << "Calendar tests failed  (stopping)\n";
      return false;
    }

    return true;
  }

}
