#!/usr/bin/env python3
# -*- encoding: utf-8 -*-
'''
@File    :   list_create.py
@Time    :   2020/08/11 17:51:08
@Author  :   YFCbingyi 
@Version :   1.0
@Contact :   lighty_chen@163.com
@License :   (C)Copyright 2017-2018, Liugroup-NLPR-CASIA
@Desc    :   None
'''
import os

# here put the import lib
#生成list [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
list1 = list(range(1,11))
print(list1)

#生成[1x1, 2x2, 3x3, ..., 10x10]
list2 = []
for x in range(1,11):
    list2.append(x*x)
print(list2)

#使用列表生成式 生成[1x1, 2x2, 3x3, ..., 10x10]
list3 = [x * x for x in range(1,11)]
print(list3)

#for循环后面还可以加上if判断，这样我们就可以筛选出仅偶数的平方：
list4 = [x * x for x in range(1,11) if x%2 == 0]
print(list4)

#还可以使用两层循环，可以生成全排列
list5 = [m+n for m in 'ABC' for n in 'DEF']
print(list5)

#列出当前目录下的所有文件和目录名，可以通过一行代码实现
list6 = [d for d in os.listdir('.')]
print(list6)

#for循环其实可以同时使用两个甚至多个变量，比如dict的items()可以同时迭代key和value：
dir1 = {'x' : 'A', 'y' : 'B', 'z' : 'C'}
for k,v in dir1.items():
    print(k, '=', v)
#因此，列表生成式也可以使用两个变量来生成list
list7 = [k+'='+v for k,v in dir1.items()]
print(list7)

# 最后把一个list中所有的字符串变成小写、大写
list8 = [s.lower() for s in list7]
print(list8)
list9 = [s.upper() for s in list7]
print(list9)

#if .. else && for
list10 = [x if x % 2 == 0 else -x for x in range(1,11)]
print(list10)


## 测试
L1 = ['Hello', 'World', 18, 'Apple', None]
L2 = [x.lower() for x in L1 if isinstance(x,str)]
print(L2)

if L2 == ['hello','world','apple']:
    print('测试通过')
else:
    print('测试失败')