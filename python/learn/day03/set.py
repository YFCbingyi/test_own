#!/usr/bin/env python3
# coding=utf-8

s = set([1,2,3])
print(s)
s = set([1,2,3,3,3,4,5,2,2])
print(s)
s.add(4)
print(s)
s.remove(5)
print(s)
s.add(6)
print(s)

s2 = set([2,4,7,8,9])
print(s|s2)
print(s&s2)


