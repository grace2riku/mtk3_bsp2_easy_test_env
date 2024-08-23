/*
 * calclogic.cpp
 *
 *  Created on: Aug 23, 2024
 *      Author: k-abe
 */
#include <stdbool.h>  // bool

bool Minus(
    int data1,
    int data2,
    int *ans)
{
    int min = -100;
    *ans = data1 - data2;

    if ((min >= data1) || (min >= data2) || (min >= *ans))
    {
        return false;
    }
    return true;
}
