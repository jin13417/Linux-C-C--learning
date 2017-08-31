#!/bin/env python 
#coding:gbk
#coding:utf-8
"利用sys模块导入指定Python文件的路径"
import sys
sys.path.append("./")
"另外一种导入Python文件"
from m import plus

print plus(12,3)

print help(plus)
