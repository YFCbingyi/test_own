#!/usr/bin/env python3
# coding=utf-8


def person(name,age,**kw):
    print('name : ',name,' age : ',age,' other ',kw)

person('chenbingyi',12)
person('chenbingyi',12,city='beijing',jiguan='shanxi')


extra = {'city':'beijing','sex':'man'}
person('cby',89,**extra)

def persons(name,age,**extra):
    if 'city' in extra:
        print('city :',extra['city'])
    if 'sex' in extra:
        print('sex :',extra['sex'])
    print('name : ',name,' age ',age)

persons('cby',12)
persons('lhf',11,city = 'shanghai')
persons('zsb',19,city = 'jiangsu',sex ='man')


print('==================================')

def product(x, y = 1,*argc):
    sum = x*y
    print(argc)
    for n in argc:
        sum = sum*n
    return sum

print(product(5))
print(product(5,6))
print(product(5,6,7))
print(product(5,6,7,8))
