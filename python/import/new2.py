#!/bin/env python 
#coding:gbk
#coding:utf-8
"利用sys模块导入指定Python文件的路径"
import sys
sys.path.append("./")
"另外一种导入Python文件"
my = __import__("m")

print my.plus(12,3)

print help(my.plus)
