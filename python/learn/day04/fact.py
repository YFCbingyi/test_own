#!/usr/bin/env python3
# coding=utf-8

def fact(number):
    if number==1:
        return 1;
    return number*fact(number-1)

print(fact(5))
