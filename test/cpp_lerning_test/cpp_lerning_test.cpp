/*
 * cpp_lerning_test.cpp
 *
 *  Created on: 2023/07/11
 *      Author: k-abe
 */
#include "CppUTest/TestHarness.h"
#include "default_argument.h"

TEST_GROUP(CppLerningTestGroup)
{

};

// 数値リテラルの桁区切り文字(C++14)
TEST(CppLerningTestGroup, BasicUsageDigitSeparators)
{
	LONGS_EQUAL(1000000, 1'000'000);	// 10進数数値の桁区切り
	LONGS_EQUAL(0xd846, 0b1101'1000'0100'0110);	// 2進数の4桁区切り
}

// 2進数リテラル(C++14)
TEST(CppLerningTestGroup, BasicUsageBinaryLiterals)
{
	LONGS_EQUAL(0x0a, 0b1010);
	LONGS_EQUAL(0x0b, 0b1011);
	LONGS_EQUAL(0x0c, 0b1100);
	LONGS_EQUAL(0x0d, 0b1101);
	LONGS_EQUAL(0x0e, 0b1110);
	LONGS_EQUAL(0x0f, 0b1111);

	// 【0B】の記述でもOK
	LONGS_EQUAL(0x0a, 0B1010);
	LONGS_EQUAL(0x0b, 0B1011);
	LONGS_EQUAL(0x0c, 0B1100);
	LONGS_EQUAL(0x0d, 0B1101);
	LONGS_EQUAL(0x0e, 0B1110);
	LONGS_EQUAL(0x0f, 0B1111);
}

// デフォルト引数を使わない
TEST(CppLerningTestGroup, defaultArgumentNone)
{
	LONGS_EQUAL(7, defargtest_add(3, 4));
}

// 第1引数のみデフォルト引数 -> コンパイルエラー
//TEST(CppLerningTestGroup, defaultArgument_arg1)
//{
//	LONGS_EQUAL(4, defargtest_add(, 3));
//}

// 第2引数のみデフォルト引数
TEST(CppLerningTestGroup, defaultArgument_arg2)
{
	LONGS_EQUAL(2, defargtest_add(0));
}

// 第1, 2引数ともにデフォルト引数
TEST(CppLerningTestGroup, defaultArgument_arg1_2)
{
	LONGS_EQUAL(3, defargtest_add());
}
