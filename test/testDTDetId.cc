/**
   \file
   test file for DTDetId

   \author Stefano ARGIRO
   \version $Id: testDTDetId.cc,v 1.2 2005/10/18 17:57:47 namapane Exp $
   \date 27 Jul 2005
*/

#include <cppunit/extensions/HelperMacros.h>
#include <DataFormats/MuonDetId/interface/DTDetId.h>
#include <FWCore/Utilities/interface/Exception.h>

#include <iostream>
using namespace std;

class testDTDetId: public CppUnit::TestFixture
{
CPPUNIT_TEST_SUITE(testDTDetId);
CPPUNIT_TEST(testOne);
CPPUNIT_TEST(testFail);
CPPUNIT_TEST_SUITE_END();

public:
  void setUp(){}
  void tearDown(){}

  void testOne();
  void testFail();
};

///registration of the test so that the runner can find it
CPPUNIT_TEST_SUITE_REGISTRATION(testDTDetId);

void testDTDetId::testOne(){

  for (int wheel=DTDetId::minWheelId; wheel<=DTDetId::maxWheelId; ++wheel)
    for (int station=DTDetId::minStationId; 
	 station <= DTDetId::maxStationId ; ++station)
      for (int sector=DTDetId::minSectorId; 
	   sector<=DTDetId::maxSectorId; ++sector)
	for (int slayer=DTDetId::minSuperLayerId; 
	     slayer<=DTDetId::maxSuperLayerId; ++slayer)
	  for (int layer=DTDetId::minLayerId; 
	       layer<=DTDetId::maxLayerId; ++layer)
	    for (int wire=DTDetId::minWireId; 
		 wire<=DTDetId::maxWireId; ++wire){
	      
	      DTDetId detid(wheel, station, sector, slayer, layer, wire);
	      
	      CPPUNIT_ASSERT(detid.wheel() == wheel);
	      CPPUNIT_ASSERT(detid.station() == station);
	      CPPUNIT_ASSERT(detid.sector() == sector);
	      CPPUNIT_ASSERT(detid.superlayer() == slayer);
	      CPPUNIT_ASSERT(detid.layer() == layer);
	      CPPUNIT_ASSERT(detid.wire() == wire);

	      // test constructor from id
	      int myId = detid.rawId();
	      DTDetId anotherId(myId);
	      CPPUNIT_ASSERT(detid==anotherId);
	    }
	    

  
}

void testDTDetId::testFail(){
  
  // contruct using an invalid input index
  try {
    // Invalid layer
    DTDetId detid(0,1,1,1,7,1);
    CPPUNIT_ASSERT("Failed to throw required exception" == 0);      
    detid.rawId(); // avoid compiler warning
  } catch (cms::Exception& e) {
    // OK
  } catch (...) {
    CPPUNIT_ASSERT("Threw wrong kind of exception" == 0);
  }
  
  // contruct using an invalid input id
  try {
    DTDetId detid(3211);
    CPPUNIT_ASSERT("Failed to throw required exception" == 0);      
    detid.rawId(); // avoid compiler warning
  } catch (cms::Exception& e) {
    // OK
  } catch (...) {
    CPPUNIT_ASSERT("Threw wrong kind of exception" == 0);
  }
}
