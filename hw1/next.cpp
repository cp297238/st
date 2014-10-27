#include "gtest/gtest.h"
#include <string>
#include <stdio.h>
using namespace std;


bool leap(int year)
{
    if ( (year%400==0) || ( (year%4==0) && (year%100!=0) ) )
            return true;
    else
        return false;
}

string output(int year, int mon, int day)
{
    char ans[] = "";
    sprintf(ans,"%d,%d,%d", mon, day, year);
    return ans;
}

string next(int year, int mon, int day)
{
    string ans = "";
    if (year<1812 || year>2012 || mon<1 || mon>12 || day<1 || day>31)
    {
        ans+="error";
        return ans;
    }
    else
    {
        switch (mon)
        {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
                if (day<31)
                    day+=1;
                else
                {
                    mon+=1;
                    day=1;
                }
                break;
                
            case 4:
            case 6:
            case 9:
            case 11:
                if (day<30)
                    day+=1;
                else
                {
                    mon+=1;
                    day=1;
                }
                break;
                
            case 12:
                if (day<31)
                    day+=1;
                else
                {
                    mon=1;
                    year+=1;
                    day=1;
                }
                break;
                
            case 2:
                if (day<28)
                    day+=1;
                else
                {
                    if (day==28)
                    {
                        if (leap(year) )
                            day+=1;
                        else
                        {
                            day=1;
                            mon=3;
                        }
                    }
                    else  //day==29
                    {
                        if (leap(year) )
                        {
                            day=1;
                            mon=3;
                        }
                        else
                        {
                            ans+="error";
                            return ans;
                        }
                    }
                }
                break;
        } //switch(mon)
        
        
    }//else
    
    ans = output(year, mon, day);
    
    return ans;
    
    
    
}



TEST(BoundaryValue, next)
{
    //worse-case
    EXPECT_STREQ(next(1812, 1, 1).c_str(), "1,2,1812");
    EXPECT_STREQ(next(1813, 1, 1).c_str(), "1,2,1813");
    EXPECT_STREQ(next(1912, 1, 1).c_str(), "1,2,1912");
    EXPECT_STREQ(next(2011, 1, 1).c_str(), "1,2,2011");
    EXPECT_STREQ(next(2012, 1, 1).c_str(), "1,2,2012");
    
    EXPECT_STREQ(next(1812, 1, 2).c_str(), "1,3,1812");
    EXPECT_STREQ(next(1813, 1, 2).c_str(), "1,3,1813");
    EXPECT_STREQ(next(1912, 1, 2).c_str(), "1,3,1912");
    EXPECT_STREQ(next(2011, 1, 2).c_str(), "1,3,2011");
    EXPECT_STREQ(next(2012, 1, 2).c_str(), "1,3,2012");
    
    EXPECT_STREQ(next(1812, 1, 15).c_str(), "1,16,1812");
    EXPECT_STREQ(next(1813, 1, 15).c_str(), "1,16,1813");
    EXPECT_STREQ(next(1912, 1, 15).c_str(), "1,16,1912");
    EXPECT_STREQ(next(2011, 1, 15).c_str(), "1,16,2011");
    EXPECT_STREQ(next(2012, 1, 15).c_str(), "1,16,2012");
    
    EXPECT_STREQ(next(1812, 1, 30).c_str(), "1,31,1812");
    EXPECT_STREQ(next(1813, 1, 30).c_str(), "1,31,1813");
    EXPECT_STREQ(next(1912, 1, 30).c_str(), "1,31,1912");
    EXPECT_STREQ(next(2011, 1, 30).c_str(), "1,31,2011");
    EXPECT_STREQ(next(2012, 1, 30).c_str(), "1,31,2012");
    
    EXPECT_STREQ(next(1812, 1, 31).c_str(), "2,1,1812");
    EXPECT_STREQ(next(1813, 1, 31).c_str(), "2,1,1813");
    EXPECT_STREQ(next(1912, 1, 31).c_str(), "2,1,1912");
    EXPECT_STREQ(next(2011, 1, 31).c_str(), "2,1,2011");
    EXPECT_STREQ(next(2012, 1, 31).c_str(), "2,1,2012");
    
    
}

TEST(Equivalence,next)
{
    EXPECT_STREQ(next(1912, 6, 15).c_str(), "6,16,1912");
    
    EXPECT_STREQ(next(1912, -1, 15).c_str(), "error");
    EXPECT_STREQ(next(1912, 13, 15).c_str(), "error");
    
    EXPECT_STREQ(next(1912, 6, -1).c_str(), "error");
    EXPECT_STREQ(next(1912, 6, 32).c_str(), "error");
    
    EXPECT_STREQ(next(1811, 6, 15).c_str(), "error");
    EXPECT_STREQ(next(2013, 6, 15).c_str(), "error");
    
    EXPECT_STREQ(next(1912, -1, -1).c_str(), "error");
    EXPECT_STREQ(next(1811, 6, -1).c_str(), "error");
    EXPECT_STREQ(next(1811, -1, 15).c_str(), "error");
    EXPECT_STREQ(next(1811, -1, -1).c_str(), "error");
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
