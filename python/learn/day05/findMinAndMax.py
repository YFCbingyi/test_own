#!/usr/bin/env python3
# coding=utf-8

def findMinAndMax(L):
    if len(L) > 0:
        min = L[0]
        max = L[0]
        print(min,"--",max)
        for value in L:
            if min > value:
                min = value
            if max < value:
                max = value

        return (min,max)
    else:
        return (None,None)


#测试
if findMinAndMax([]) != (None,None):
    print('测试失败')
elif findMinAndMax([7]) != (7,7):
    print('测试失败')
elif findMinAndMax([7,1]) != (1,7):
    print('测试失败')
elif findMinAndMax([7,1,3,9,5]) != (1,9):
    print('测试失败')
else:
    print('测试成功')
