#ifndef CREATE_H
#define CREATE_H
#define SIZE 13
//#define LENOFID 12
#include"matrix.cpp"
#include <iostream>
#include <vector>
#include <cmath>

// 将数字的每一位分解到一个vector中
std::vector<int> splitDigits(int number) {
    std::vector<int> digits;
    while (number > 0) {
        digits.insert(digits.begin(), number % 10); // 插入到vector的前端
        number /= 10;
    }
    if (digits.empty()) {
        digits.push_back(0); // 处理数字0的情况
    }
    return digits;
}

// 生成符合规则的13x13矩阵
void generateMatrix(const int input[], matrix& mat,int LENOFID) {
    // 填充前12个元素
    for (int i = 0; i < LENOFID; ++i) {
        mat[i / SIZE][i % SIZE]=input[i];
    }

    int index = LENOFID; // 从第13个位置开始填充
    int power = 2;  // 从平方开始

    // 继续填充，直到矩阵被完全填满
    while (index < SIZE * SIZE) {
        for (int i = 0; i < LENOFID && index < SIZE * SIZE; ++i) {
            // 计算当前元素的幂
            int powValue = std::pow(input[i], power);
            // 分解幂的每一位并填充到矩阵中
            std::vector<int> digits = splitDigits(powValue);
            for (int digit : digits) {
                if (index < SIZE * SIZE) {
                    mat[index / SIZE][index % SIZE]=digit;
                    ++index;
                } else {
                    break; // 矩阵已满，退出循环
                }
            }
        }
        ++power; // 增加幂次
    }
}
#endif