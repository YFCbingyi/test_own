#!/usr/bin/env python3
# coding=utf-8

names = ['Alice',"Bob","Ceries"]
for name in names:
    print(name)

sum = 0
for index in [1,2,3,4,5]:
    sum += index
print(sum)

sum = 0
for index in range(101):
    sum += index
print(sum)

sum = 0
num = 100
while num >0:
    sum+=num;
    num-=1;
print(sum)
