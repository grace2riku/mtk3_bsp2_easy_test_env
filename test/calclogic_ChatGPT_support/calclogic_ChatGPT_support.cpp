// テストコードをChatGPTに生成してもらった

#include "CppUTest/TestHarness.h"
#include <limits.h>

extern bool Minus(int data1, int data2, int *ans);

TEST_GROUP(MinusC2CoverageTestGroup)
{
    int ans;

    void setup()
    {
        ans = 0; // テスト実行前にansを初期化
    }

    void teardown()
    {
        // 特に必要な後処理はなし
    }
};

// 各条件の全ての結果をカバーするためのテストケース
// min >= data1 の条件が真の場合
TEST(MinusC2CoverageTestGroup, Minus_MinGreaterThanData1)
{
    CHECK_FALSE(Minus(-100, 50, &ans)); // data1が-100であり、falseを返すことを確認
}

// min >= data1 の条件が偽の場合
TEST(MinusC2CoverageTestGroup, Minus_MinLessThanData1)
{
    CHECK_TRUE(Minus(0, 50, &ans)); // data1がminより大きいため、次の条件に進む
    CHECK_EQUAL(-50, ans); // ansが-50になることを確認
}

// min >= data2 の条件が真の場合
TEST(MinusC2CoverageTestGroup, Minus_MinGreaterThanData2)
{
    CHECK_FALSE(Minus(50, -100, &ans)); // data2が-100であり、falseを返すことを確認
}

// min >= data2 の条件が偽の場合
TEST(MinusC2CoverageTestGroup, Minus_MinLessThanData2)
{
    CHECK_TRUE(Minus(50, 0, &ans)); // data2がminより大きいため、次の条件に進む
    CHECK_EQUAL(50, ans); // ansが50になることを確認
}

// min >= *ans の条件が真の場合
TEST(MinusC2CoverageTestGroup, Minus_MinGreaterThanAns)
{
    CHECK_FALSE(Minus(0, 100, &ans)); // ansが-100であり、falseを返すことを確認
}

// min >= *ans の条件が偽の場合
TEST(MinusC2CoverageTestGroup, Minus_MinLessThanAns)
{
    CHECK_TRUE(Minus(100, 50, &ans)); // ansがminより大きいため、trueを返すことを確認
    CHECK_EQUAL(50, ans); // ansが50になることを確認
}


TEST_GROUP(MinusTestGroup)
{
    int ans;

    void setup()
    {
        ans = 0; // テスト実行前にansを初期化
    }

    void teardown()
    {
        // 特に必要な後処理はなし
    }
};

// data1 と data2 が範囲内で、期待通りの結果が得られるかどうかをテスト
TEST(MinusTestGroup, Minus_ValidInput_WithinBounds)
{
    CHECK_TRUE(Minus(50, 20, &ans)); // 正しい結果が返されることを確認
    CHECK_EQUAL(30, ans); // ansが期待通りの30になっていることを確認
}

// data1, data2, または計算結果がちょうど -100 の場合の挙動を確認
TEST(MinusTestGroup, Minus_BoundaryCondition_ExactMin)
{
    CHECK_FALSE(Minus(-100, 0, &ans)); // data1が-100である場合はfalseを返すことを確認
    CHECK_FALSE(Minus(0, -100, &ans)); // data2が-100である場合もfalseを返すことを確認
    CHECK_FALSE(Minus(-50, 50, &ans)); // ansが-100になる場合もfalseを返すことを確認
}

// data1, data2, または計算結果が -100 未満の場合の挙動を確認
TEST(MinusTestGroup, Minus_BoundaryCondition_BelowMin)
{
    CHECK_FALSE(Minus(-101, 0, &ans)); // data1が-101である場合はfalseを返すことを確認
    CHECK_FALSE(Minus(0, -101, &ans)); // data2が-101である場合もfalseを返すことを確認
    CHECK_FALSE(Minus(-50, 51, &ans)); // ansが-101になる場合もfalseを返すことを確認
}

// data1 または data2 が -100 より大きいが、範囲内のケースをテスト
TEST(MinusTestGroup, Minus_BoundaryCondition_AboveMin)
{
    CHECK_TRUE(Minus(-99, 0, &ans)); // data1が-99であり、正しい結果を返すことを確認
    CHECK_EQUAL(-99, ans); // ansが期待通りの-99になっていることを確認
}

// 同じ値を引いたときの結果が 0 になることを確認
TEST(MinusTestGroup, Minus_SameValues)
{
    CHECK_TRUE(Minus(50, 50, &ans)); // 正しい結果が返されることを確認
    CHECK_EQUAL(0, ans); // ansが期待通りの0になっていることを確認
}

// 正の数同士の引き算が期待通りに動作するか確認
TEST(MinusTestGroup, Minus_LargePositiveDifference)
{
    CHECK_TRUE(Minus(100, 1, &ans)); // 正しい結果が返されることを確認
    CHECK_EQUAL(99, ans); // ansが期待通りの99になっていることを確認
}

// data2 が data1 より大きい場合の計算が正しく行われるか確認
TEST(MinusTestGroup, Minus_LargeNegativeDifference)
{
    CHECK_TRUE(Minus(1, 100, &ans)); // 正しい結果が返されることを確認
    CHECK_EQUAL(-99, ans); // ansが期待通りの-99になっていることを確認
}

// data1 が INT_MAX の場合の挙動をテスト
TEST(MinusTestGroup, Minus_MaxValueInput)
{
    CHECK_TRUE(Minus(INT_MAX, 0, &ans)); // INT_MAXから0を引いた場合、正しい結果を返すことを確認
    CHECK_EQUAL(INT_MAX, ans); // ansがINT_MAXになっていることを確認

    CHECK_TRUE(Minus(INT_MAX, INT_MAX, &ans)); // INT_MAXからINT_MAXを引いた場合、正しい結果を返すことを確認
    CHECK_EQUAL(0, ans); // ansが0になっていることを確認
}

// data1 が INT_MIN の場合に false を返すことを確認
TEST(MinusTestGroup, Minus_MinValueInput)
{
    CHECK_FALSE(Minus(INT_MIN, 0, &ans)); // INT_MINが範囲外であるため、falseを返すことを確認
}

