#!/usr/bin/env python3
# coding=utf-8

classmates = ['alice','jack','rosice']

print(classmates)
print('classmates\'len is ',len(classmates))
print('''classmates[0] %s
classmates[1] %s
classmates[2] %s''' % (classmates[0],classmates[1],classmates[2]))

print('classmates[end] {0}'.format(classmates[-1]))
print('classmates {0} {1} {2}'.format(classmates[-1],classmates[-2],classmates[-3]))

classmates.append('Ammy')
print(classmates)

classmates.insert(1,'tom')
print(classmates)

classmates.pop()
print(classmates)

classmates.pop(2)
print(classmates)

classmates[1] = 'Search'
print(classmates)

print('--------------2-------------')
L = ['Apple',2,True]
print(L)
L[2] = 'Banana'
print(L)
print('-------------3---------------')

tup = (1,2,3)
print(tup)

t = (1,)
print(t)

tuple = ('a','b',['A','B'])
print(tuple)

tuple[2][0] = 'X'
tuple[2][1] = 'Y'

print(tuple)
