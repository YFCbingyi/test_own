#!/usr/bin/env python3
# -*- encoding: utf-8 -*-
'''
@File    :   map_reduce.py
@Time    :   2020/08/14 14:15:34
@Author  :   YFCbingyi 
@Version :   1.0
@Contact :   lighty_chen@163.com
@License :   (C)Copyright 2017-2018, Liugroup-NLPR-CASIA
@Desc    :   None
'''
# here put the import lib
from functools import reduce

# map()函数接收两个参数，一个是函数，一个是Iterable，map将传入的函数依次作用到序列的每个元素，并把结果作为新的Iterator返回。
def f(x):
    return x*x

m1 = map(f,[1,2,3,4,5,6,7,8])
print('list ->',list(m1))   

# map()作为高阶函数，事实上它把运算规则抽象了，因此，我们不但可以计算简单的f(x)=x2，还可以计算任意复杂的函数，比如，把这个list所有数字转为字符串：
print('list str -->',list(map(str,[1,2,3,4,5,6,7,8])))

# reduce把一个函数作用在一个序列[x1, x2, x3, ...]上，这个函数必须接收两个参数，reduce把结果继续和序列的下一个元素做累积计算，其效果就是：
# reduc e(f, [x1, x2, x3, x4]) = f(f(f(x1, x2), x3), x4)
# 比方说对一个序列求和，就可以用reduce实现
def add(x,y):
    return x+y
    
i1 = reduce(add,[1,2,3,4,5,6,7])

print('累计和=',i1)

# 序列[1, 3, 5, 7, 9]变换成整数13579，reduce就可以派上用场
def sum1(x,y):
    return x*10 + y
i2 = reduce(sum1,[1,3,5,7,9])
print('计算结果=',i2)

# 如果考虑到字符串str也是一个序列，对上面的例子稍加改动，配合map()，我们就可以写出把str转换为int的函数：
def char2int(x):
    digits = {'0':0,'1':1,'2':2,'3':3,'4':4,'5':5,'6':6,'7':7,'8':8,'9':9}
    return digits[x]

str1 = '12345'
i3 = reduce(sum1,map(char2int,str1))
print(str1,'-->',i3)


# 利用map()函数，把用户输入的不规范的英文名字，变为首字母大写，其他小写的规范名字。
# 输入：['adam', 'LISA', 'barT']，输出：['Adam', 'Lisa', 'Bart']：

def normalize(name):
    str1 = name[:1].upper() + name[1:].lower()
    return str1

# 测试:
L1 = ['adam', 'LISA', 'barT']
L2 = list(map(normalize, L1))
print(L2)

# 请编写一个prod()函数，可以接受一个list并利用reduce()求积：
def prod(L):
    def ji(x,y):
        return x*y
    return reduce(ji,L)

print('3 * 5 * 7 * 9 =', prod([3, 5, 7, 9]))
if prod([3, 5, 7, 9]) == 945:
    print('测试成功!')
else:
    print('测试失败!')


# 利用map和reduce编写一个str2float函数，把字符串'123.456'转换成浮点数123.456：
digitss = {'0':0,'1':1,'2':2,'3':3,'4':4,'5':5,'6':6,'7':7,'8':8,'9':9}
def str2float(s):
    def ji(x,y):
        return x*10 + y
    def str2int(s):
        if s=='.':
            return
        return digitss[s]
    L = list(map(str2int,s))
    n = 0
    for i in L:
        if i == None:
            break;
        n = n + 1
    print(n)
    return reduce(ji,L[:n])

print('str2float(\'123.456\') =', str2float('123.456'))
if abs(str2float('123.456') - 123.456) < 0.00001:
    print('测试成功!')
else:
    print('测试失败!')