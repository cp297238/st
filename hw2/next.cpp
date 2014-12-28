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

TEST(PathTesting, C0) 
{
    EXPECT_STREQ(next(1812, 0, 31).c_str(), "error");
    EXPECT_STREQ(NextDate(1991, 11, 11), "11,12,1991");
    EXPECT_STREQ(NextDate(1991, 7, 31), "8,1,1991");
    EXPECT_STREQ(NextDate(1991, 12, 31), "1,1,1992");
    EXPECT_STREQ(NextDate(1991, 6, 31), "error");
}

TEST(PathTesting, C1) 
{
    EXPECT_STREQ(next(1812, 0, 31).c_str(), "error");
    EXPECT_STREQ(NextDate(1991, 11, 11), "11,12,1991");
    EXPECT_STREQ(NextDate(1991, 7, 31), "8,1,1991");
    EXPECT_STREQ(NextDate(1991, 12, 31), "1,1,1992");
    EXPECT_STREQ(NextDate(1991, 6, 31), "error");
}

TEST(PathTesting, C2) 
{
    EXPECT_STREQ(next(1812, 0, 31).c_str(), "error");
    EXPECT_STREQ(NextDate(1991, 11, 11), "11,12,1991");
    EXPECT_STREQ(NextDate(1991, 7, 31), "8,1,1991");
    EXPECT_STREQ(NextDate(1991, 12, 31), "1,1,1992");
    EXPECT_STREQ(NextDate(1991, 6, 31), "error");
}

TEST(PathTesting, MCDC) 
{
    EXPECT_STREQ("error",NextDate(1811, 1, 1));
    EXPECT_STREQ("error",NextDate(2013, 1, 1));
    EXPECT_STREQ("error",NextDate(1991, 0, 1));
    EXPECT_STREQ("error",NextDate(1991, 13, 1));
    EXPECT_STREQ("error",NextDate(1991, 1, 0));
    EXPECT_STREQ("error",NextDate(1991, 1, 32));

    EXPECT_STREQ("1,2,1991",NextDate(1991, 1, 1));
    EXPECT_STREQ("2,1,1991",NextDate(1991, 1, 31));
    EXPECT_STREQ("error",NextDate(1991, 1, 32));
    EXPECT_STREQ("3,2,1991",NextDate(1991, 3, 1));
    EXPECT_STREQ("4,1,1991",NextDate(1991, 3, 31));
    EXPECT_STREQ("error",NextDate(1991, 3, 32));
    EXPECT_STREQ("5,2,1991",NextDate(1991, 5, 1));
    EXPECT_STREQ("6,1,1991",NextDate(1991, 5, 31));
    EXPECT_STREQ("error",NextDate(1991, 5, 32));
    EXPECT_STREQ("7,2,1991",NextDate(1991, 7, 1));
    EXPECT_STREQ("8,1,1991",NextDate(1991, 7, 31));
    EXPECT_STREQ("error",NextDate(1991, 7, 32));
    EXPECT_STREQ("8,2,1991",NextDate(1991, 8, 1));
    EXPECT_STREQ("9,1,1991",NextDate(1991, 8, 31));
    EXPECT_STREQ("error",NextDate(1991, 8, 32));
    EXPECT_STREQ("10,2,1991",NextDate(1991, 10, 1));
    EXPECT_STREQ("11,1,1991",NextDate(1991, 10, 31));
    EXPECT_STREQ("error",NextDate(1991, 10, 32));

    EXPECT_STREQ("4,2,1991",NextDate(1991, 4, 1));
    EXPECT_STREQ("5,1,1991",NextDate(1991, 4, 30));
    EXPECT_STREQ("error",NextDate(1991, 4, 31));
    EXPECT_STREQ("6,2,1991",NextDate(1991, 6, 1));
    EXPECT_STREQ("7,1,1991",NextDate(1991, 6, 30));
    EXPECT_STREQ("error",NextDate(1991, 6, 31));
    EXPECT_STREQ("9,2,1991",NextDate(1991, 9, 1));
    EXPECT_STREQ("10,1,1991",NextDate(1991, 9, 30));
    EXPECT_STREQ("error",NextDate(1991, 9, 31));
    EXPECT_STREQ("11,2,1991",NextDate(1991, 11, 1));
    EXPECT_STREQ("12,1,1991",NextDate(1991, 11, 30));
    EXPECT_STREQ("error",NextDate(1991, 11, 31));

    EXPECT_STREQ("12,2,1991",NextDate(1991, 12, 1));
    EXPECT_STREQ("1,1,1992",NextDate(1991, 12 , 31));
    EXPECT_STREQ("error",NextDate(1991, 12, 32));
    EXPECT_STREQ("2,2,1991",NextDate(1991, 2, 1));
    EXPECT_STREQ("3,1,1991",NextDate(1991, 2, 28));
    EXPECT_STREQ("2,29,2000",NextDate(2000, 2, 28));
    EXPECT_STREQ("error",NextDate(1991, 2, 29));
    EXPECT_STREQ("3,1,2000",NextDate(2000, 2, 29));
    EXPECT_STREQ("error",NextDate(1991, 2, 30));

}



int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
