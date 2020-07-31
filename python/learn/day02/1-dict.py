#!/usr/bin/env python3
# coding=utf-8

dic = {'Marry':95, 'Bob':70, 'Amy':24}
print(dic['Marry'])

if 'Chries' in dic:
    print(dic['Chries'])
else:
    print('chries is not exsit')

dic['Chries'] = 18;
print(dic)

if 'Chries' in dic:
    print(dic['Chries'])


print('Noob is %d' % dic.get('Noob',-1))
