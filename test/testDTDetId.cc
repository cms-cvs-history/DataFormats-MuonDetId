/**
   \file
   test file for DTDetId

   \author Stefano ARGIRO
   \version $Id: testDTDetId.cc,v 1.1 2005/08/02 15:46:33 argiro Exp $
   \date 27 Jul 2005
*/

static const char CVSId[] = "$Id: testDTDetId.cc,v 1.1 2005/08/02 15:46:33 argiro Exp $";


#include <iostream>

#include <cppunit/extensions/HelperMacros.h>
#include <DataFormats/MuonDetId/interface/DTDetId.h>

class testDTDetId: public CppUnit::TestFixture
{
CPPUNIT_TEST_SUITE(testDTDetId);
CPPUNIT_TEST(testOne);
CPPUNIT_TEST_SUITE_END();

public:
  void setUp(){}
  void tearDown(){}

  void testOne();

};

///registration of the test so that the runner can find it
CPPUNIT_TEST_SUITE_REGISTRATION(testDTDetId);

void testDTDetId::testOne(){

  for (int wheel=DTDetId::minWheelId; wheel<=DTDetId::maxWheelId   ; ++wheel)
    for (unsigned int station=DTDetId::minStationId; 
	 station <= DTDetId::maxStationId ; ++station)
      for (unsigned int sector=DTDetId::minSectorId; 
	   sector<=DTDetId::maxSectorId; ++sector)
	for (unsigned int slayer=DTDetId::minSuperLayerId; 
	     slayer<=DTDetId::maxSuperLayerId; ++slayer)
	  for (unsigned int layer=DTDetId::minLayerId; 
	       layer<=DTDetId::maxLayerId; ++layer)
	    for (unsigned int wire=DTDetId::minWireId; 
		 wire<=DTDetId::maxWireId; ++wire){

	      DTDetId detid(wheel, station, sector, slayer, layer, wire);

	      CPPUNIT_ASSERT(detid.wheel() == wheel);
	      CPPUNIT_ASSERT(detid.station() == station);
	      CPPUNIT_ASSERT(detid.sector() == sector);
	      CPPUNIT_ASSERT(detid.superlayer() == slayer);
	      CPPUNIT_ASSERT(detid.layer() == layer);
	      CPPUNIT_ASSERT(detid.wire() == wire);
	    }
	    


}
