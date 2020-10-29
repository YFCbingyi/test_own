#!/usr/bin/env python3
# -*- encoding: utf-8 -*-
'''
@File    :   itor.py
@Time    :   2020/08/12 14:34:09
@Author  :   YFCbingyi 
@Version :   1.0
@Contact :   lighty_chen@163.com
@License :   (C)Copyright 2017-2018, Liugroup-NLPR-CASIA
@Desc    :   None
'''

# here put the import lib
from collections.abc import Iterable
from collections.abc import Iterator

# 作用于for循环的对象统称为可迭代对象：Iterable。
print(isinstance([],Iterable))
print(isinstance('ABV',Iterable))
print(isinstance({},Iterable))
print(isinstance((x for x in range(10)),Iterable))

# 可以被next()函数调用并不断返回下一个值的对象称为迭代器：Iterator。
print(isinstance([],Iterator))
print(isinstance('ABV',Iterator))
print(isinstance({},Iterator))
print(isinstance((x for x in range(10)),Iterator))
# 把list、dict、str等Iterable变成Iterator可以使用iter()函数
print(isinstance(iter([]),Iterator))
print(isinstance(iter('ABV'),Iterator))
print(isinstance(iter({}),Iterator))






