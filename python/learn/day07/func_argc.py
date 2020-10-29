#!/usr/bin/env python3
# -*- encoding: utf-8 -*-
'''
@File    :   func_argc.py
@Time    :   2020/08/12 17:23:20
@Author  :   YFCbingyi 
@Version :   1.0
@Contact :   lighty_chen@163.com
@License :   (C)Copyright 2017-2018, Liugroup-NLPR-CASIA
@Desc    :   None
'''

# here put the import lib

# 通常情况下，求和的函数是这样定义的
def calc_sum(*args):
    ax = 0;
    for n in args:
        ax = ax + n;
    return ax;

iv1 = calc_sum(1,2,3,4,12);
print(iv1)

# 但是，如果不需要立刻求和，而是在后面的代码中，根据需要再计算怎么办？可以不返回求和的结果，而是返回求和的函数
def calc_sum2(*args):
    def sum():
        ax = 0
        for n in args:
            ax = ax + n
        return ax
    return sum

f1 = calc_sum2(1,2,3,4,5)
f2 = calc_sum2(4,5,6,7,8)
iv2 = f1() 
print(iv2)
print(f2())

#利用闭包返回一个计数器函数，每次调用它返回递增整数：
# def createCounter():
#     ax = [0]
#     def counter():
#         ax[0] += 1
#         return ax[0]
#     return counter

def createCounter():
    ax = 0;
    def counter():
        nonlocal ax
        ax += 1
        return ax
    return counter

# 测试:
counterA = createCounter()
print(counterA(), counterA(), counterA(), counterA(), counterA()) # 1 2 3 4 5
counterB = createCounter()
if [counterB(), counterB(), counterB(), counterB()] == [1, 2, 3, 4]:
    print('测试通过!')
else:
    print('测试失败!')

