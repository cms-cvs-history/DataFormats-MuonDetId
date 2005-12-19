/**
   \file
   test file for DTLayerId

   \author Stefano ARGIRO
   \version $Id: testDTLayerId.cc,v 1.5 2005/11/07 16:49:52 namapane Exp $
   \date 27 Jul 2005
*/

#include <cppunit/extensions/HelperMacros.h>
#include <DataFormats/MuonDetId/interface/DTLayerId.h>
#include <FWCore/Utilities/interface/Exception.h>

#include <iostream>
using namespace std;

class testDTLayerId: public CppUnit::TestFixture
{
CPPUNIT_TEST_SUITE(testDTLayerId);
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
CPPUNIT_TEST_SUITE_REGISTRATION(testDTLayerId);

void testDTLayerId::testOne(){

  for (int wheel=DTLayerId::minWheelId; wheel<=DTLayerId::maxWheelId; ++wheel)
    for (int station=DTLayerId::minStationId; 
	 station <= DTLayerId::maxStationId ; ++station)
      for (int sector=DTLayerId::minSectorId; 
	   sector<=DTLayerId::maxSectorId; ++sector)
	for (int slayer=DTLayerId::minSuperLayerId; 
	     slayer<=DTLayerId::maxSuperLayerId; ++slayer)
	  for (int layer=DTLayerId::minLayerId; 
	       layer<=DTLayerId::maxLayerId; ++layer) {
	      
	      DTLayerId detid(wheel, station, sector, slayer, layer);
	      
	      CPPUNIT_ASSERT(detid.wheel() == wheel);
	      CPPUNIT_ASSERT(detid.station() == station);
	      CPPUNIT_ASSERT(detid.sector() == sector);
	      CPPUNIT_ASSERT(detid.superlayer() == slayer);
	      CPPUNIT_ASSERT(detid.layer() == layer);

	      // test constructor from id
	      int myId = detid.rawId();
	      DTLayerId anotherId(myId);
	      CPPUNIT_ASSERT(detid==anotherId);
	    }
	    

  
}

void testDTLayerId::testFail(){
  
  // contruct using an invalid input index
  try {
    // Invalid layer
    DTLayerId detid(0,1,1,1,7);
    CPPUNIT_ASSERT("Failed to throw required exception" == 0);      
    detid.rawId(); // avoid compiler warning
  } catch (cms::Exception& e) {
    // OK
  } catch (...) {
    CPPUNIT_ASSERT("Threw wrong kind of exception" == 0);
  }
  
  // contruct using an invalid input id
  try {
    DTLayerId detid(3211);
    CPPUNIT_ASSERT("Failed to throw required exception" == 0);      
    detid.rawId(); // avoid compiler warning
  } catch (cms::Exception& e) {
    // OK
  } catch (...) {
    CPPUNIT_ASSERT("Threw wrong kind of exception" == 0);
  }
}


void testDTLayerId::testMemberOperators(){
  // Test equality operator
  DTLayerId layer1(2,3,8,1,4);
  DTLayerId layer2=layer1;  

  CPPUNIT_ASSERT(layer2==layer1);

  DTLayerId layer(2,3,8,1,4);
  DTSLId superlayer = layer.superlayerId();

  CPPUNIT_ASSERT(superlayer.wheel() == 2);
  CPPUNIT_ASSERT(superlayer.station() == 3);
  CPPUNIT_ASSERT(superlayer.sector() == 8);
  CPPUNIT_ASSERT(superlayer.superlayer() == 1);

}
