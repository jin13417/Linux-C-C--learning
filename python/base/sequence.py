#!/bin/env python
#coding:utf-8

#序列的其他共有属性
#字典代表一组数据，但它不是序列，因为它没有衣蛾从头至尾的特定顺序

#1、引用最后一个元素

last_names = ["Dogglass","Jefferson","Williams","Frank"]

print ( "last_names len is %d" % (len(last_names)))

#python 提供了一个捷径，可以通过使用数值-1访问一个序列的最后一个元素

len = len(last_names)
print ("last_names[%d] = %s" % ( len -1,last_names[len -1]))
print ("last_names[%d] = %s" % (  -1,last_names[-1]))
print ("last_names[%d] = %s" % ( len -2,last_names[len -2]))
print ("last_names[%d] = %s" % (  -2,last_names[-2]))

#2、序列的范围

#序列分片
slice_me = ("the","next","time","we","meet","drinks","are","on","me")
print  (slice_me[5:9])
slice_me_list = ["the","next","time","we","meet","drinks","are","on","me"]
print  (slice_me_list[5:9])
slice_this_string="the next time we meet drinks are on me"
print (slice_this_string[5:9])

#通过附加序列增长列表
#append 方法是将一个序列附加到另一个序列的末端
slice_me = ("the","next","time","we","meet","drinks","are","on","me")
apartment = []
apartment.append(slice_me)
print ("apartment.append(slice_me) is %s" % (apartment))
#extend 方法将给定序列中的么个元素插入到调用它的列表中
apartment=[]
apartment.extend(slice_me)
print ("apartment.extend(slice_me) is %s" % (apartment))

#使用列表临时存储数据
#为了防止列表变得笨重，可以使用pop方法在处理完列表的一个数据之后
#将其引用从列表中删除。当删除引用之后，它原来在列表的位置将被后续元素
#填上，列表较少的元素个数等于已经弹出的元素个数。
todays_temperatures = [23,32,33,31]
todays_temperatures.append(29)
print ("berfore todays_temperatures is :%s" % (todays_temperatures))
print ("todays_temperatures.pop(1) is %d" % (todays_temperatures.pop(1)))
print ("end todays_temperatures.pop(1) is :%s" % (todays_temperatures))

