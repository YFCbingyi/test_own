#!/usr/bin/env python
#coding=utf-8
import sqlite3
conn=sqlite3.connect('./govhall.db', check_same_thread=False)
cu=conn.cursor()
  
#获取表名，保存在tab_name列表
cu.execute("select pos from Facilities where ID = 412")
tab_name=cu.fetchall()
print(tab_name)
  
#获取表的列名（字段名），保存在col_names列表,每个表的字段名集为一个元组
#col_names=[]
#for line in tab_name:
#  cu.execute('pragma table_info({})'.format(line))
#  col_name=cu.fetchall()
#  col_name=[x[1] for x in col_name]
#  col_names.append(col_name)
#  col_name=tuple(col_name)
#print(col_names)
pos = []
for pose in tab_name:
  index = 0
  pose_list = pose[0].split(',')
  pos_tu = []
  #print(pose_list)
  while index < 8:
    #print(index)
    pose_list[index] = int(pose_list[index]) - 305
    pose_list[index + 1] = int(pose_list[index+1]) + 13
    index = index + 2
  #print(pose_list)
  pos.append(pose_list)
print(pos)
p_list = []
for pose in pos:
  pos_string = ''
  for p in pose:
    pos_string += str(p)+','
  p_string = pos_string[:-1]
  #print(p_string)
  p_list.append(p_string)
ID=412
for i in p_list:
  #if ID != 156 and ID != 157 and ID != 167 and ID !=168:
  #print(type(i))
  sql = "update Facilities set pos = " + "'"+i+"'" +" where ID =" + str(ID)
  print(sql,';')
  #cu.execute(sql)
  ID += 1
  while True:
    if ID != 156 and ID != 157 and ID != 167 and ID !=168:
      break
    else:
      ID += 1
    
  
#print(tab_name)

    




