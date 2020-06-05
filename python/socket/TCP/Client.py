#!/usr/bin/env python
# coding=utf-8

import socket


address = ('127.0.0.1',9999)

s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.connect(address)

while True:
    a = input("Enter string: ")
    print a
    s.send(str(a))
    # if a.index('close'):
    #     break

s.close()
