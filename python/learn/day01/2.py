#!/usr/bin/env python3
# coding=utf-8

s = 'ABC'
print(s.encode('ascii'))
c = '中文'
print(c.encode('utf-8'))

se = b'ABC'
sc = b'\xe4\xb8\xad\xe6\x96\x87'
print(se.decode('ascii'))
print(sc.decode('utf-8'))

sceorr = b'\xe4\xb8\xad\xe6'
print(sceorr.decode('utf-8',errors='ignore'))
