#!/usr/bin/env python3
# -*- encoding: utf-8 -*-
'''
@File    :   generator.py
@Time    :   2020/08/12 09:52:50
@Author  :   YFCbingyi 
@Version :   1.0
@Contact :   lighty_chen@163.com
@License :   (C)Copyright 2017-2018, Liugroup-NLPR-CASIA
@Desc    :   None
'''

# here put the import lib
list1 = [x * x for x in range(10)]
print(list1)

# 列表生成式的[] 换成 () 就是生成器
gen1 = (x*x for x in range(10))
print(gen1)
for x in gen1:
    print('x = ',x)
# for x in range(10):
#     print(next(gen1))

def fib(max):
    n,a,b = 0,0,1
    while n < max:
        print(b)
        a,b = b,a+b #a = b, b = a+b
        n = n + 1
    return 'done'
fib(10)

# 如果一个函数定义中包含yield关键字，那么这个函数就不再是一个普通函数，而是一个generator：
def fib1(max):
    n,a,b = 0,0,1
    while n < max:
        yield b
        a,b = b,a+b #a = b, b = a+b
        n = n + 1
    return 'done'

gen2 = fib1(10);
for n in gen2:
    print('fib1 = ',n)


# 杨辉三角
def triangles():
    L = [1]
    while True:
        yield L
        L = [sum(i) for i in zip([0]+L,L+[0])]

L = [1,2,1]
for i in zip([0]+L, L+[0]):
    print('zip ',i)

n = 0
results = []
for t in triangles():
    results.append(t)
    n = n + 1
    if n == 10:
        break

for t in results:
    print(t)

if results == [
    [1],
    [1, 1],
    [1, 2, 1],
    [1, 3, 3, 1],
    [1, 4, 6, 4, 1],
    [1, 5, 10, 10, 5, 1],
    [1, 6, 15, 20, 15, 6, 1],
    [1, 7, 21, 35, 35, 21, 7, 1],
    [1, 8, 28, 56, 70, 56, 28, 8, 1],
    [1, 9, 36, 84, 126, 126, 84, 36, 9, 1]
]:
    print('测试通过!')
else:
    print('测试失败!')