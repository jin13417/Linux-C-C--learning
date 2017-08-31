#!/bin/env python 
#coding:utf-8
#coding:gbk
s.decode('gbk', 'ignore').encode('utf-8')
"利用sys模块导入指定Python文件的路径"
import sys
sys.path.append("./")
"导入Python文件"
import m

print m.plus(12,3)

print help(m.plus)
