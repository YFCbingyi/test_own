#!/usr/bin/env python3
# coding=utf-8

def hannuo(n,a,b,c):
    if n == 1:
        print(a, '-->', c)
    elif n > 1:
        hannuo(n-1,a,c,b)
        print(a, '-->', c)
        hannuo(n-1,b,a,c)


print('---------1----------')
print(hannuo(1,'A','B','C'))
print('---------2----------')
print(hannuo(2,'A','B','C'))
print('---------3----------')
print(hannuo(3,'A','B','C'))
