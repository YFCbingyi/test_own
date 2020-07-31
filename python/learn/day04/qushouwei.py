#!/usr/bin/env python3
# coding=utf-8

def qushouwei(s):
    a = 0;
    while s[a] == ' ':
        a = a+1
    b = -1;
    while s[b] == ' ':
        b = b-1
    return s[a:b+1]

print(qushouwei('  hello '))
