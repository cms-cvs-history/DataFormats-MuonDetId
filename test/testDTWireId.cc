/**
   \file
   test file for DTWireId

   \author Stefano ARGIRO
   \version $Id: testDTWireId.cc,v 1.5 2005/11/07 16:49:52 namapane Exp $
   \date 27 Jul 2005
*/

#include <cppunit/extensions/HelperMacros.h>
#include <DataFormats/MuonDetId/interface/DTWireId.h>
#include <FWCore/Utilities/interface/Exception.h>

#include <iostream>
using namespace std;

class testDTWireId: public CppUnit::TestFixture
{
CPPUNIT_TEST_SUITE(testDTWireId);
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
CPPUNIT_TEST_SUITE_REGISTRATION(testDTWireId);

void testDTWireId::testOne(){

  for (int wheel=DTWireId::minWheelId; wheel<=DTWireId::maxWheelId; ++wheel)
    for (int station=DTWireId::minStationId; 
	 station <= DTWireId::maxStationId ; ++station)
      for (int sector=DTWireId::minSectorId; 
	   sector<=DTWireId::maxSectorId; ++sector)
	for (int slayer=DTWireId::minSuperLayerId; 
	     slayer<=DTWireId::maxSuperLayerId; ++slayer)
	  for (int layer=DTWireId::minLayerId; 
	       layer<=DTWireId::maxLayerId; ++layer)
	    for (int wire=DTWireId::minWireId; 
		 wire<=DTWireId::maxWireId; ++wire){
	      
	      DTWireId wireId(wheel, station, sector, slayer, layer, wire);
	      
	      CPPUNIT_ASSERT(wireId.wheel() == wheel);
	      CPPUNIT_ASSERT(wireId.station() == station);
	      CPPUNIT_ASSERT(wireId.sector() == sector);
	      CPPUNIT_ASSERT(wireId.superlayer() == slayer);
	      CPPUNIT_ASSERT(wireId.layer() == layer);
	      CPPUNIT_ASSERT(wireId.wire() == wire);

	      // test constructor from id
	      int myId = wireId.rawId();
	      DTWireId anotherId(myId);
	      CPPUNIT_ASSERT(wireId==anotherId);
	    }
	    

  
}

void testDTWireId::testFail(){
  
  // contruct using an invalid input index
  try {
    // Invalid layer
    DTWireId wireId(0,1,1,1,7,1);
    CPPUNIT_ASSERT("Failed to throw required exception" == 0);      
    wireId.rawId(); // avoid compiler warning
  } catch (cms::Exception& e) {
    // OK
  } catch (...) {
    CPPUNIT_ASSERT("Threw wrong kind of exception" == 0);
  }
  
  // contruct using an invalid input index
  try {
    // Invalid wire
    DTWireId wireId(0,1,1,1,1,1000);
    CPPUNIT_ASSERT("Failed to throw required exception" == 0);      
    wireId.rawId(); // avoid compiler warning
  } catch (cms::Exception& e) {
    // OK
  } catch (...) {
    CPPUNIT_ASSERT("Threw wrong kind of exception" == 0);
  }


  // contruct using an invalid input id
  try {
    DTWireId wireId(3211);
    CPPUNIT_ASSERT("Failed to throw required exception" == 0);      
    wireId.rawId(); // avoid compiler warning
  } catch (cms::Exception& e) {
    // OK
  } catch (...) {
    CPPUNIT_ASSERT("Threw wrong kind of exception" == 0);
  }
}


void testDTWireId::testMemberOperators(){
  // Test equality operator
  DTWireId wire1(2,3,8,1,4,5);
  DTWireId wire2=wire1;  

  CPPUNIT_ASSERT(wire2==wire1);

  // Test layerId() method
  DTWireId wire(2,3,8,1,4,32);
  DTLayerId layer=wire.layerId();


  CPPUNIT_ASSERT(layer.wheel() == 2);
  CPPUNIT_ASSERT(layer.station() == 3);
  CPPUNIT_ASSERT(layer.sector() == 8);
  CPPUNIT_ASSERT(layer.superlayer() == 1);
  CPPUNIT_ASSERT(layer.layer() == 4);

}
