/**
   \file
   test file for DTSLId

   \author Stefano ARGIRO
   \version $Id: testDTSLId.cc,v 1.5 2005/11/07 16:49:52 namapane Exp $
   \date 27 Jul 2005
*/

#include <cppunit/extensions/HelperMacros.h>
#include <DataFormats/MuonDetId/interface/DTSLId.h>
#include <FWCore/Utilities/interface/Exception.h>

#include <iostream>
using namespace std;

class testDTSLId: public CppUnit::TestFixture
{
CPPUNIT_TEST_SUITE(testDTSLId);
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
CPPUNIT_TEST_SUITE_REGISTRATION(testDTSLId);

void testDTSLId::testOne(){

  for (int wheel=DTSLId::minWheelId; wheel<=DTSLId::maxWheelId; ++wheel)
    for (int station=DTSLId::minStationId; 
	 station <= DTSLId::maxStationId ; ++station)
      for (int sector=DTSLId::minSectorId; 
	   sector<=DTSLId::maxSectorId; ++sector)
	for (int slayer=DTSLId::minSuperLayerId; 
	     slayer<=DTSLId::maxSuperLayerId; ++slayer) {
	      
	      DTSLId detid(wheel, station, sector, slayer);
	      
	      CPPUNIT_ASSERT(detid.wheel() == wheel);
	      CPPUNIT_ASSERT(detid.station() == station);
	      CPPUNIT_ASSERT(detid.sector() == sector);
	      CPPUNIT_ASSERT(detid.superlayer() == slayer);

	      // test constructor from id
	      int myId = detid.rawId();
	      DTSLId anotherId(myId);
	      CPPUNIT_ASSERT(detid==anotherId);
	    }
	    

  
}

void testDTSLId::testFail(){
  
  // contruct using an invalid input index
  try {
    // Invalid superlayer
    DTSLId detid(0,1,1,5);
    CPPUNIT_ASSERT("Failed to throw required exception" == 0);      
    detid.rawId(); // avoid compiler warning
  } catch (cms::Exception& e) {
    // OK
  } catch (...) {
    CPPUNIT_ASSERT("Threw wrong kind of exception" == 0);
  }
  
  // contruct using an invalid input id
  try {
    DTSLId detid(3211);
    CPPUNIT_ASSERT("Failed to throw required exception" == 0);      
    detid.rawId(); // avoid compiler warning
  } catch (cms::Exception& e) {
    // OK
  } catch (...) {
    CPPUNIT_ASSERT("Threw wrong kind of exception" == 0);
  }
}


void testDTSLId::testMemberOperators(){
  // Test equality operator
  DTSLId superlayer1(2,3,8,1);
  DTSLId superlayer2=superlayer1;  

  CPPUNIT_ASSERT(superlayer2==superlayer1);

  DTSLId superlayer(2,3,8,1);
  DTChamberId chamber = superlayer.chamberId();
  
  CPPUNIT_ASSERT(chamber.wheel() == 2);
  CPPUNIT_ASSERT(chamber.station() == 3);
  CPPUNIT_ASSERT(chamber.sector() == 8);

}
