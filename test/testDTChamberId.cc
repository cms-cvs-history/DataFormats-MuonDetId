/**
   \file
   test file for DTChamberId

   \author Stefano ARGIRO
   \version $Id: testDTChamberId.cc,v 1.5 2005/11/07 16:49:52 namapane Exp $
   \date 27 Jul 2005
*/

#include <cppunit/extensions/HelperMacros.h>
#include <DataFormats/MuonDetId/interface/DTChamberId.h>
#include <FWCore/Utilities/interface/Exception.h>

#include <iostream>
using namespace std;

class testDTChamberId: public CppUnit::TestFixture
{
CPPUNIT_TEST_SUITE(testDTChamberId);
CPPUNIT_TEST(testOne);
CPPUNIT_TEST(testFail);
CPPUNIT_TEST(testMemberOperators);
CPPUNIT_TEST_SUITE_END();

public:
  void setUp(){}
  void tearDown(){}

  void testOne();
  void testFail();
  void testMemberOperators();
};

///registration of the test so that the runner can find it
CPPUNIT_TEST_SUITE_REGISTRATION(testDTChamberId);

void testDTChamberId::testOne(){

  for (int wheel=DTChamberId::minWheelId; wheel<=DTChamberId::maxWheelId; ++wheel)
    for (int station=DTChamberId::minStationId; 
	 station <= DTChamberId::maxStationId ; ++station)
      for (int sector=DTChamberId::minSectorId; 
	   sector<=DTChamberId::maxSectorId; ++sector) {
	      
	      DTChamberId detid(wheel, station, sector);
	      
	      CPPUNIT_ASSERT(detid.wheel() == wheel);
	      CPPUNIT_ASSERT(detid.station() == station);
	      CPPUNIT_ASSERT(detid.sector() == sector);

	      // test constructor from id
	      int myId = detid.rawId();
	      DTChamberId anotherId(myId);
	      CPPUNIT_ASSERT(detid==anotherId);
	    }
	    

  
}

void testDTChamberId::testFail(){
  
  // contruct using an invalid input index
  try {
    // Invalid sector
    DTChamberId detid(0,1,15);
    CPPUNIT_ASSERT("Failed to throw required exception" == 0);      
    detid.rawId(); // avoid compiler warning
  } catch (cms::Exception& e) {
    // OK
  } catch (...) {
    CPPUNIT_ASSERT("Threw wrong kind of exception" == 0);
  }
  
  // contruct using an invalid input id
  try {
    DTChamberId detid(3211);
    CPPUNIT_ASSERT("Failed to throw required exception" == 0);      
    detid.rawId(); // avoid compiler warning
  } catch (cms::Exception& e) {
    // OK
  } catch (...) {
    CPPUNIT_ASSERT("Threw wrong kind of exception" == 0);
  }
}


void testDTChamberId::testMemberOperators(){
  // Test equality operator
  DTChamberId chamber1(2,3,8);
  DTChamberId chamber2=chamber1;  

  CPPUNIT_ASSERT(chamber2==chamber1);


}
