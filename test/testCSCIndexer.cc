/**
   \file
   test unit for CSCIndexer

   \author Vadim Khotilovich
   \version $Id: testCSCIndexer.cc,v 1.1.2.1 2012/05/24 22:10:20 khotilov Exp $
   \date 24 May 2012
*/

static const char CVSId[] = "$Id: testCSCIndexer.cc,v 1.1.2.1 2012/05/24 22:10:20 khotilov Exp $";

#include <cppunit/extensions/HelperMacros.h>
#include <DataFormats/MuonDetId/interface/CSCIndexer.h>
#include <FWCore/Utilities/interface/Exception.h>

#include <iostream>
using namespace std;

class testCSCIndexer: public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(testCSCIndexer);
  
  CPPUNIT_TEST(testChamber);
  CPPUNIT_TEST(testLayer);
  CPPUNIT_TEST(testStripChannel);
  CPPUNIT_TEST(testChip);
  CPPUNIT_TEST(testGasGain);
  //CPPUNIT_TEST(testFail);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp(){}
  void tearDown(){}

  void testChamber();
  void testLayer();
  void testStripChannel();
  void testChip();
  void testGasGain();
  //void testFail();
};

///registration of the test so that the runner can find it
CPPUNIT_TEST_SUITE_REGISTRATION(testCSCIndexer);


void testCSCIndexer::testChamber()
{
  //std::cout << "\ntestCSCIndexer: testChamber starting... " << std::endl;

  CSCIndexer indexer;

  for (CSCIndexer::LongIndexType i = 1; i <= CSCIndexer::MAX_CHAMBER_INDEX; ++i)
  {
    CSCDetId id = indexer.detIdFromChamberIndex(i);
    int ie = id.endcap();
    int is = id.station();
    int ir = id.ring();
    int ic = id.chamber();
    CSCIndexer::IndexType ii = indexer.chamberIndex(id);

    if (i != ii) cout<<" BAD CHAMBER INDEX: "<<i<<" != "<<ii<<" \t   ("<<ie<<" "<<is<<" "<<ir<<" "<<ic<<")"<<endl;
    CPPUNIT_ASSERT(i == ii);   // loop-back index test
    CPPUNIT_ASSERT(ie >= 1 && ie <= 2);
    CPPUNIT_ASSERT(is >= 1 && is <= 4);
    CPPUNIT_ASSERT(ir >= 1 && ir <= indexer.offlineRingsInStation(is));
    CPPUNIT_ASSERT(ic >= 1 && ic <= indexer.chambersInRingOfStation(is, ir));
  }
}


void testCSCIndexer::testLayer()
{
  //std::cout << "\ntestCSCIndexer: testLayer starting... " << std::endl;

  CSCIndexer indexer;

  for (CSCIndexer::LongIndexType i = 1; i <= CSCIndexer::MAX_LAYER_INDEX; ++i)
  {
    CSCDetId id = indexer.detIdFromLayerIndex(i);
    int ie = id.endcap();
    int is = id.station();
    int ir = id.ring();
    int ic = id.chamber();
    int il = id.layer();
    CSCIndexer::IndexType ii = indexer.layerIndex(id);

    if (i != ii) cout<<" BAD LAYER INDEX: "<<i<<" != "<<ii<<" \t   ("<<ie<<" "<<is<<" "<<ir<<" "<<ic<<" "<<il<<")"<<endl;
    CPPUNIT_ASSERT(i == ii);   // loop-back index test
    CPPUNIT_ASSERT(ie >= 1 && ie <= 2);
    CPPUNIT_ASSERT(is >= 1 && is <= 4);
    CPPUNIT_ASSERT(ir >= 1 && ir <= indexer.offlineRingsInStation(is));
    CPPUNIT_ASSERT(ic >= 1 && ic <= indexer.chambersInRingOfStation(is, ir));
    CPPUNIT_ASSERT(il >= 1 && il <= 6);
  }
}


void testCSCIndexer::testStripChannel()
{
  //std::cout << "\ntestCSCIndexer: testStripChannel starting... " << std::endl;

  CSCIndexer indexer;

  for (CSCIndexer::LongIndexType i = 1; i <= CSCIndexer::MAX_STRIP_CHANNEL_INDEX; ++i)
  {
    std::pair<CSCDetId, CSCIndexer::IndexType> t = indexer.detIdFromStripChannelIndex(i);
    CSCDetId id = t.first;
    int ie = id.endcap();
    int is = id.station();
    int ir = id.ring();
    int ic = id.chamber();
    int il = id.layer();
    int st = t.second;
    CSCIndexer::LongIndexType ii = indexer.stripChannelIndex(id, st);

    if (i != ii) cout<<" BAD STRIPCHANNEL INDEX: "<<i<<" != "<<ii<<" \t   ("<<ie<<" "<<is<<" "<<ir<<" "<<ic<<" "<<il<<") "<<st<<endl;
    CPPUNIT_ASSERT(i == ii);   // loop-back index test
    CPPUNIT_ASSERT(ie >= 1 && ie <= 2);
    CPPUNIT_ASSERT(is >= 1 && is <= 4);
    CPPUNIT_ASSERT(ir >= 1 && ir <= indexer.offlineRingsInStation(is));
    CPPUNIT_ASSERT(ic >= 1 && ic <= indexer.chambersInRingOfStation(is, ir));
    CPPUNIT_ASSERT(il >= 1 && il <= 6);
    CPPUNIT_ASSERT(st >= 1 && st <= indexer.stripChannelsPerLayer(is, ir));
  }
}


void testCSCIndexer::testChip()
{
  //std::cout << "\ntestCSCIndexer: testChip starting... " << std::endl;

  CSCIndexer indexer;

  for (CSCIndexer::IndexType i = 1; i <= CSCIndexer::MAX_CHIP_INDEX; ++i)
  {
    std::pair<CSCDetId, CSCIndexer::IndexType> t = indexer.detIdFromChipIndex(i);
    CSCDetId id = t.first;
    int ie = id.endcap();
    int is = id.station();
    int ir = id.ring();
    int ic = id.chamber();
    int il = id.layer();
    int ch = t.second;
    CSCIndexer::IndexType ii = indexer.chipIndex(id, ch);

    if (i != ii) cout<<" BAD CHIP INDEX: "<<i<<" != "<<ii<<" \t   ("<<ie<<" "<<is<<" "<<ir<<" "<<ic<<" "<<il<<") "<<ch<<endl;
    CPPUNIT_ASSERT(i == ii);   // loop-back index test
    CPPUNIT_ASSERT(ie >= 1 && ie <= 2);
    CPPUNIT_ASSERT(is >= 1 && is <= 4);
    CPPUNIT_ASSERT(ir >= 1 && ir <= indexer.offlineRingsInStation(is));
    CPPUNIT_ASSERT(ic >= 1 && ic <= indexer.chambersInRingOfStation(is, ir));
    CPPUNIT_ASSERT(il >= 1 && il <= 6);
    CPPUNIT_ASSERT(ch >= 1 && ch <= indexer.chipsPerLayer(is, ir));
  }
}


void testCSCIndexer::testGasGain()
{
  //std::cout << "\ntestCSCIndexer: testGasGain starting... " << std::endl;

  CSCIndexer indexer;
  
  for (CSCIndexer::IndexType i = 1; i <= CSCIndexer::MAX_GAS_GAIN_INDEX; ++i)
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

    if (i != ii) cout<<" BAD GASGAIN INDEX: "<<i<<" != "<<ii<<" \t   ("<<ie<<" "<<is<<" "<<ir<<" "<<ic<<" "<<il<<") "<<hv<<" "<<ch<<endl;
    CPPUNIT_ASSERT(i == ii);   // loop-back index test
    CPPUNIT_ASSERT(ie >= 1 && ie <= 2);
    CPPUNIT_ASSERT(is >= 1 && is <= 4);
    CPPUNIT_ASSERT(ir >= 1 && ir <= indexer.offlineRingsInStation(is));
    CPPUNIT_ASSERT(ic >= 1 && ic <= indexer.chambersInRingOfStation(is, ir));
    CPPUNIT_ASSERT(il >= 1 && il <= 6);
    CPPUNIT_ASSERT(hv >= 1 && hv <= indexer.hvSegmentsPerLayer(is, ir));
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
