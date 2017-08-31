#!/bin/env python
#coding:utf-8


#字典---以名称索引的分组数据
dict = {}#空字典
print (dict)

dict["a"] = "1"
dict["b"] = "2"

print (dict)

#从字典里获得它所有的键
key=dict.keys()
print (list(key))
#打印键和值
print ("key[%s] : value[%s]" % (key[0],dict.get(key[0])))
#从字典里获得它所有的值
value=dict.values()
print (list(value))

#字典的工作原理是每个键是不同的（不可以有完全相同的两个键）
#但是可以有多个重复的值




