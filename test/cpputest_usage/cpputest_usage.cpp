/*
 * cpputest_usage.cpp
 *
 *  Created on: 2023/08/23
 *      Author: k-abe
 */
#include "CppUTest/TestHarness.h"

int g_test_shared_val = 100;

TEST_GROUP(CpputestUsageGroup)
{
	// TEST_GROUPの中の変数はTEST_GROUPで共有できる
	int test_group_shared_val = 1;

    void setup()  // setupは各TEST実行の際に呼び出される
    {
    	test_group_shared_val = 2;
    	g_test_shared_val = 101;
    }

    void teardown()
    {

    }
};

TEST_GROUP(CpputestUsageGroup_2)
{
	// TEST_GROUPの中の変数はTEST_GROUPで共有できる
	int test_group_shared_val_2 = 20;

    void setup()  // setupは各TEST実行の際に呼び出される
    {
    	g_test_shared_val = 102;
    }

    void teardown()
    {

    }
};

TEST(CpputestUsageGroup_2, setupGlobalVariableReference)
{
	// CpputestUsageGroup_2ではsetupで102に設定している
	LONGS_EQUAL(102, g_test_shared_val);
}

TEST(CpputestUsageGroup, setupGlobalVariableReference)
{
	// CpputestUsageGroupではsetupで101に設定している
	LONGS_EQUAL(101, g_test_shared_val);
}

IGNORE_TEST(CpputestUsageGroup, setupOtherTestGroupVariableReference)
{
	// 他グループの変数は参照できないため下記はコンパイルエラー
//	LONGS_EQUAL(20, test_group_shared_val_2);
}

TEST(CpputestUsageGroup_2, setup)	// グループ名が異なればテスト名は重複可能
{
	LONGS_EQUAL(20, test_group_shared_val_2);
}

TEST(CpputestUsageGroup, setup)
{
	LONGS_EQUAL(2, test_group_shared_val);
}

