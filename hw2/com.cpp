#include "gtest/gtest.h"

float commission(int locks, int stocks, int barrels)
{
    int lockprice = 45;
    int stockprice = 30;
    int barrelprice = 25;
    int total = 0;
    float com = 0.0;
    
    if ( locks<1 || locks>70 || stocks<1 || stocks>80 || barrels<1 || barrels>90)
        return -1;
    
    total = locks*lockprice + stocks*stockprice + barrels*barrelprice ;
    
    if ( total <= 1000 )
        com = total * 0.1 ;
    else if( (total > 1000) && (total <= 1800) )
        com = 1000 * 0.1 + (total - 1000 ) * 0.15 ;
    else if(total > 1800 )
        com = 1000 * 0.1 + 800 * 0.15 + (total - 1800) * 0.2 ;
    
    return com;
    
}

TEST(BoundaryValue, commission)
{
    EXPECT_EQ(commission(1,40,40),309);
    EXPECT_EQ(commission(2,40,40),318);
    EXPECT_EQ(commission(69,40,40),921);
    EXPECT_EQ(commission(70,40,40),930);
    EXPECT_EQ(commission(71,40,40),-1);

    EXPECT_EQ(commission(35,1,40),381);
    EXPECT_EQ(commission(35,2,40),387);
    EXPECT_EQ(commission(35,80,40),855);
    EXPECT_EQ(commission(35,81,40),-1);
    
    EXPECT_EQ(commission(35,40,1),420);
    EXPECT_EQ(commission(35,40,2),425);
    EXPECT_EQ(commission(35,40,90),865);
    EXPECT_EQ(commission(35,40,91),-1);
    
    EXPECT_EQ(commission(35,40,40),615);
    
}

TEST(Equivalence, commission)
{
    //weak robust
    EXPECT_EQ(commission(10,10,10), 100);
    EXPECT_EQ(commission(-1,40,45), -1);
    EXPECT_EQ(commission(-2,40,45), -1);
    EXPECT_EQ(commission(71,40,45), -1);
    EXPECT_EQ(commission(35,-1,45), -1);
    EXPECT_EQ(commission(35,81,45), -1);
    EXPECT_EQ(commission(35,40,-1), -1);
    EXPECT_EQ(commission(35,40,91), -1);
    
    //strong robust
    EXPECT_EQ(commission(-2,40,45), -1);
    EXPECT_EQ(commission(35,-1,45), -1);
    EXPECT_EQ(commission(35,40,-2), -1);
    EXPECT_EQ(commission(-2,-1,45), -1);
    EXPECT_EQ(commission(-2,40,-1), -1);
    EXPECT_EQ(commission(35,-1,-1), -1);
    EXPECT_EQ(commission(-2,-1,-1), -1);
    
}

TEST(CommissionPath, C0)
{
  EXPECT_EQ(commission(0, 10, 4), -1);
  EXPECT_EQ(commission(35,1,40),381);
  EXPECT_EQ(commission(35,2,40),387);
  EXPECT_EQ(commission(35,80,40),855);
}

TEST(CommissionPath, C1)
{
  EXPECT_EQ(commission(0, 10, 4), -1);
  EXPECT_EQ(commission(35,1,40),381);
  EXPECT_EQ(commission(35,2,40),387);
  EXPECT_EQ(commission(35,80,40),855);
}

TEST(CommissionPath, C2)
{
  EXPECT_EQ(commission(0, 10, 4), -1);
  EXPECT_EQ(commission(35,1,40),381);
  EXPECT_EQ(commission(35,2,40),387);
  EXPECT_EQ(commission(35,80,40),855);
}

TEST(CommissionPath, MCDC)
{
  EXPECT_EQ(commission(0, 1, 0), -1);
  EXPECT_EQ(commission(0, 1, 91), -1);
  EXPECT_EQ(commission(0, 1, 1), -1);
  EXPECT_EQ(commission(0, 0, 0), -1);
  EXPECT_EQ(commission(0, 0, 91), -1);
  EXPECT_EQ(commission(0, 0, 1), -1);
  EXPECT_EQ(commission(0, 81, 0), -1);
  EXPECT_EQ(commission(0, 81, 91), -1);
  EXPECT_EQ(commission(0, 81, 1), -1);

  EXPECT_EQ(commission(1, 1, 0), -1);
  EXPECT_EQ(commission(1, 1, 91), -1);
  EXPECT_EQ(commission(1, 0, 0), -1);
  EXPECT_EQ(commission(1, 0, 91), -1);
  EXPECT_EQ(commission(1, 0, 1), -1);
  EXPECT_EQ(commission(1, 81, 0), -1);
  EXPECT_EQ(commission(1, 81, 91), -1);
  EXPECT_EQ(commission(1, 81, 1), -1);

  EXPECT_EQ(commission(71, 1, 0), -1);
  EXPECT_EQ(commission(71, 1, 91), -1);
  EXPECT_EQ(commission(71, 1, 1), -1);
  EXPECT_EQ(commission(71, 0, 0), -1);
  EXPECT_EQ(commission(71, 0, 91), -1);
  EXPECT_EQ(commission(71, 0, 1), -1);
  EXPECT_EQ(commission(71, 81, 0), -1);
  EXPECT_EQ(commission(71, 81, 91), -1);
  EXPECT_EQ(commission(71, 81, 1), -1);

  EXPECT_NE(commission(1, 1, 1), -1);


  EXPECT_EQ(commission(35,1,40),381);
  EXPECT_EQ(commission(35,2,40),387);
  EXPECT_EQ(commission(35,80,40),855);
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
