#!/usr/bin/env python
# coding=utf-8

import socket

address = ('127.0.0.1',9999)

s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.bind(address)

s.listen(5)

ss,addr = s.accept()

print 'got connected from ',addr
ss.send('byebye')

while True:
    ra = ss.recv(512)
    print ra
    # if ra.index('close'):
    #     break

ss.close()
s.close()
