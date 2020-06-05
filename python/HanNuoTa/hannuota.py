#!/usr/bin/env python
# coding=utf-8

def HanNuoTa(n,x,y,z):
    if n!=0:
        HanNuoTa(n-1,x,z,y)
        print('%c->%c'%(x,y))
        HanNuoTa(n-1,z,y,x)


HanNuoTa(3,'A','B','c')
    
