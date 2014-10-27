//
//  main.cpp
//  hw1
//
//  Created by tzuyu on 2014/10/25.
//  Copyright (c) 2014年 tzuyu. All rights reserved.
//

#include "gtest/gtest.h"


int checkTriangle(int a, int b, int c)
{
    int error, Equil, Isos, Uneq;
    error = 0; //錯誤
    Equil = 1; //全等三角形
    Isos = 2;  //等腰三角形
    Uneq = 3;  //三角形
    if ( a<1 || a>200 || b<1 || b>200 || c<1 || c>200 )
        return error;
    else
    {
        if ( ( (a+b)<=c) || ((b+c)<=a) || ((a+c)<=b) )
            return error;
        else if (a==b && a==c)
            return Equil;
        else if ( (a==b && b!=c) || (a==c && a!=b) || (b==c && a!=b) )
            return Isos;
        else
            return Uneq;
    }
    
}

TEST(BoundaryValue, triangle)
{
    //Normal
    EXPECT_EQ(2, checkTriangle(1, 100, 100));
    EXPECT_EQ(2, checkTriangle(2, 100, 100));
    EXPECT_EQ(2, checkTriangle(199, 100, 100));
    EXPECT_EQ(0, checkTriangle(200, 100, 100));
    EXPECT_EQ(2, checkTriangle(100, 1, 100));
    EXPECT_EQ(2, checkTriangle(100, 2, 100));
    EXPECT_EQ(2, checkTriangle(100, 199, 100));
    EXPECT_EQ(0, checkTriangle(100, 200, 100));
    EXPECT_EQ(2, checkTriangle(100, 100, 1));
    EXPECT_EQ(2, checkTriangle(100, 100, 2));
    EXPECT_EQ(2, checkTriangle(100, 100, 199));
    EXPECT_EQ(0, checkTriangle(100, 100, 200));
    EXPECT_EQ(1, checkTriangle(100, 100, 100));
    //Robust
    EXPECT_EQ(0, checkTriangle(0, 100, 100));
    EXPECT_EQ(0, checkTriangle(-1, 100, 100));
    EXPECT_EQ(0, checkTriangle(201, 100, 100));
    EXPECT_EQ(0, checkTriangle(202, 100, 100));
    EXPECT_EQ(0, checkTriangle(100, 0, 100));
    EXPECT_EQ(0, checkTriangle(100, -1, 100));
    EXPECT_EQ(0, checkTriangle(100, 201, 100));
    EXPECT_EQ(0, checkTriangle(100, 202, 100));
    EXPECT_EQ(0, checkTriangle(100, 100, 0));
    EXPECT_EQ(0, checkTriangle(100, 100, -1));
    EXPECT_EQ(0, checkTriangle(100, 100, 201));
    EXPECT_EQ(0, checkTriangle(100, 100, 202));
}


TEST(EquivalenceClass, triangle)
{
    //Weak
    EXPECT_EQ(1, checkTriangle(5, 5, 5));
    EXPECT_EQ(2, checkTriangle(2, 2, 3));
    EXPECT_EQ(3, checkTriangle(3, 4, 5));
    EXPECT_EQ(0, checkTriangle(4, 1, 2));
    EXPECT_EQ(0, checkTriangle(-1, 5, 5));
    EXPECT_EQ(0, checkTriangle(5, -1, 5));
    EXPECT_EQ(0, checkTriangle(5, 5, -1));
    EXPECT_EQ(0, checkTriangle(-1, -1, 5));
    EXPECT_EQ(0, checkTriangle(5, -1, -1));
    EXPECT_EQ(0, checkTriangle(-1, -5, -1));
    EXPECT_EQ(0, checkTriangle(-1, -1, -1));
    EXPECT_EQ(0, checkTriangle(201, 5, 5));
    EXPECT_EQ(0, checkTriangle(5, 5, 201));
    
}

TEST(EquivalenceClass, WeakRobust)
{
    EXPECT_EQ(0, checkTriangle(201, 50, 50));
    EXPECT_EQ(0, checkTriangle(0, 50, 50));
    EXPECT_EQ(0, checkTriangle(50, 201, 50));
    EXPECT_EQ(0, checkTriangle(50, 0, 50));
    EXPECT_EQ(0, checkTriangle(50, 50, 201));
    EXPECT_EQ(0, checkTriangle(50, 50, 0));
    EXPECT_EQ(0, checkTriangle(60, 50, 5));
}



int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}