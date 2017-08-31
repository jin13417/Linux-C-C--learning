#!/bin/env python
#coding:utf-8

#type 打印出数据的类型

print type(1)
print type(1.0)

print type("helloworld")

#虚数 如12j 
a = 12j + 1
print a
print type(a)

# 除法和求余数
print "5 / 3 = %d" % ( 5 / 3)
print "5 %% 3 = %d" %( 5 % 3)

#进制数字打印
print "%d,%o,%x" %(10,10,10)

#查看变量的类型
a = "hello  world"
print a.__class__
#调用变量的方法
print a.split()
