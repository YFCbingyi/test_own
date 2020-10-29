#!/usr/bin/env python3
# -*- encoding: utf-8 -*-
'''
@File    :   filter.py
@Time    :   2020/08/21 16:57:02
@Author  :   YFCbingyi 
@Version :   1.0
@Contact :   lighty_chen@163.com
@License :   (C)Copyright 2017-2018, Liugroup-NLPR-CASIA
@Desc    :   None
'''

# here put the import lib
def is_odd(n):
    return n%2 == 1
list1 = list(filter(is_odd,[1,2,3,4,5,6,7,8,9]))
print(list1)

def not_empty(s):
    return s and s.strip()
list2 = list(filter(not_empty,['A','','C',None]))
print(list2)

list3 = list(range(2,1000));


def is_suchu(l,tar):
    idx = l[0]
    tar.append(idx)
    if len(l) == 1:
        return ''
    def is_zero(n):
        return n % idx != 0
    li = list(filter(is_zero,l[1:]))
    return is_suchu(li,tar);

list4 = list()
is_suchu(list3,list4)
print('2 - 1000 内的素数',list4)