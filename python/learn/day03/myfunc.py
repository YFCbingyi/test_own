#!/usr/bin/env python3
# coding=utf-8

import math

def my_abs(x):
    if not isinstance(x,(int,float)):
        raise TypeError('bad operand type')
    if x>=0:
        return x
    else:
        return -x

def nop():
    pass

def move(x,y,step,angle=0):
    nx = x+step*math.cos(angle)
    ny = y-step*math.sin(angle)
    return nx,ny

def enroll(name,age = 6,city = 'shanxi'):
    print('name:',name)
    print('age:',age)
    print('city',city)


def calc(*number):
    sum = 0;
    for n in number:
        sum += n;
    return sum
