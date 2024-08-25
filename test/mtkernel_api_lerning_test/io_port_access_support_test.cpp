/*
 * io_port_access_support_test.cpp
 *
 *  Created on: 2024/08/23
 *      Author: k-abe
 */
#include "CppUTest/TestHarness.h"
#include <tk/tkernel.h>
#include <tm/tmonitor.h>


TEST_GROUP(IOPortAccessSupportTestGroup)
{
	// TEST_GROUPの中の変数はTEST_GROUPで共有できる

    void setup()  // setupは各TEST実行の際に呼び出される
    {

    }

    void teardown()
    {

    }
};

TEST(IOPortAccessSupportTestGroup, out_w_and_in_w)
{
	// LED LD1を消灯(PB0 = 0)
	out_w(GPIO_ODR(B), (in_w(GPIO_ODR(B)))&~(1<<0));
	CHECK_FALSE(in_w(GPIO_ODR(B)) & (1<<0) );

	// LED LD1を点灯(PB0 = 1)
	out_w(GPIO_ODR(B), (in_w(GPIO_ODR(B))) | (1<<0));
	CHECK(in_w(GPIO_ODR(B)) & (1<<0) );

	// 後始末 LED LD1を消灯
	out_w(GPIO_ODR(B), (in_w(GPIO_ODR(B)))&~(1<<0));
}

TEST(IOPortAccessSupportTestGroup, in_w_B1USER_Button_NotPressed)
{
	// B1 USER buttonを押していないときは0が読める
	CHECK_FALSE( (in_w(GPIO_IDR(C)) & (1<<13)) );
}

IGNORE_TEST(IOPortAccessSupportTestGroup, in_w_B1USER_Button_Pressed)
{
	// B1 USER buttonを押しているときは1が読める
	CHECK_TRUE( (in_w(GPIO_IDR(C)) & (1<<13)) );
}
