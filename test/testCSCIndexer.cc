/**
   \file
   test unit for CSCIndexer

   \author Vadim Khotilovich
   \version $Id: $
   \date 24 May 2012
*/

static const char CVSId[] = "$Id: testCSCDetId.cc,v 1.5 2007/12/10 18:12:52 ptc Exp $";

#include <cppunit/extensions/HelperMacros.h>
#include <DataFormats/MuonDetId/interface/CSCIndexer.h>
#include <FWCore/Utilities/interface/Exception.h>

#include <iostream>
using namespace std;

class testCSCIndexer: public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(testCSCIndexer);
  
  CPPUNIT_TEST(testGasGain);
  //CPPUNIT_TEST(testFail);
  //CPPUNIT_TEST(testStatic);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp(){}
  void tearDown(){}
  void testGasGain();
  //void testFail();
};

///registration of the test so that the runner can find it
CPPUNIT_TEST_SUITE_REGISTRATION(testCSCIndexer);

void testCSCIndexer::testGasGain(){

  //std::cout << "\ntestCSCIndexer: testGasGain starting... " << std::endl;

  CSCIndexer indexer;
  
  for (CSCIndexer::IndexType i=1; i <= 57240; ++i)
  {
    CSCIndexer::GasGainTuple t = indexer.detIdFromGasGainIndex(i);
    CSCDetId id = t.get<0>();
    int ie = id.endcap();
    int is = id.station();
    int ir = id.ring();
    int ic = id.chamber();
    int il = id.layer();
    int hv = t.get<1>();
    int ch = t.get<2>();
    CSCIndexer::IndexType ii = indexer.gasGainIndex(hv, ch, id);

    if (! ( i< 45145 && is == 1 && ir == 4 ) ) // do this check except for unganged me1a indices
    {
      if (i!=ii) cout<<" BAD "<<i<<" \t "<<ii<<" \t   "<<ie<<" "<<is<<" "<<ir<<" "<<ic<<" "<<il<<" "<<hv<<" "<<ch<<endl;
      CPPUNIT_ASSERT(i == ii);
    }
  
    int max_rings = (is==1) ? 4 : 2;

    CPPUNIT_ASSERT(ie >= 1 && ie <= 2);
    CPPUNIT_ASSERT(is >= 1 && is <= 4);
    CPPUNIT_ASSERT(ir >= 1 && ir <= max_rings);
    //if (!(is==1 && ir==1 && ic>36))
    CPPUNIT_ASSERT(ic >= 1 && ic <= indexer.chambersInRingOfStation(is, ir));
    //CPPUNIT_ASSERT(hv >= 1 && hv <= indexer.hvSegmentsPerLayer(is, ir));
    CPPUNIT_ASSERT(ch >= 1 && ch <= indexer.chipsPerLayer(is, ir));
  }

}

/*
void testCSCIndexer::testFail(){
  
  // std::cout << "\ntestCSCIndexer: testFail starting... " << std::endl;

  // construct using an invalid input index
  try {
    // Invalid layer
    CSCDetId detid(3,1,1,1,7);
    CPPUNIT_ASSERT("Failed to throw required exception" == 0); 
    detid.rawId(); // avoid compiler warning
  } catch (cms::Exception& e) {
    //    std::cout << "\ntestCSCDetId: testFail exception caught " << std::endl;
    // OK
  } catch (...) {
    CPPUNIT_ASSERT("Threw wrong kind of exception" == 0);
  }
  
}
*/
