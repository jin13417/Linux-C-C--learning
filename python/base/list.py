#!/bin/env python
#coding:utf-8

#列表---可更改数据的内容
list = ["coffee","tea","toast"]

#list 长度
print ("list len is %d" %  (len(list)))

#打印list数值
print ("%s,%s,%s" % (list[0],list[1],list[2]))

#修改list[2]的数值
list[len(list) - 1] = "sausages"
print ("list[2] is %s" % (list[2]))

#list 追加
list.append("waffles")
print ("list[%d] is %s" % (len(list) - 1,list[len(list) - 1]))

#list 一次性追加多个元素
list.extend(["juice","decaf"])

print(list)


