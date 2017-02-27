#!/bin/sh 
echo $1
pid=`ps aux |grep $1 |grep -v grep |grep -v $0|awk '{print $2}'`
echo "$1-->$pid"
while [ 1 ]
do
    pid=`ps aux |grep $1 |grep -v grep |grep -v $0|awk '{print $2}'`
    echo "$1-->$pid"
#    mem=`cat /proc/$pid/status |grep VmRSS`
    #mem=`cat /proc/$pid/statm`
    pmap -x $pid
    sleep 1
done
