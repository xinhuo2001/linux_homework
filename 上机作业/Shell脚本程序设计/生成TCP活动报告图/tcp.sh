#默认存储文件
file="tcp.txt"
[ $# = 1 ] && {
	file=$1
}	
echo $file

#创建存储文件
[ ! -r "$file" ] && {
	touch "$file"
}

pre_sum_seg=0

while true
do
    #获取当前时间
    eval `date "+year=%Y; month=%m; day=%d; hour=%H; minute=%M"`
    curTime="$year-$month-$day $hour:$minute"
    echo $curTime
    
    #获取报文数目
    info=`netstat --statistics | awk 'NR>=45 && NR<=46' | sed -e 's/[a-z][a-z]*//g'`
    rec_seg=`echo "$info" | awk 'NR==1 {print $1}'`
    send_seg=`echo "$info" | awk 'NR==2 {print $1}'`
    echo $rec_seg 
    echo $send_seg
    sum_seg=`expr $rec_seg + $send_seg`
    echo $sum_seg
    
    #附加符号
    diff=`expr $sum_seg - $pre_sum_seg`
    echo $diff
    symbal=" "
    if [ $diff -lt -10 ]
    then
    	symbal="-"
    elif [ $diff -gt 10 ]
    then
    	symbal="+"
    else
    	symbal=" "
    fi
	
	#追加文件
    echo "$curTime $rec_seg $send_seg $sum_seg $symbal" >> $file
	pre_sum_seg=`expr $sum_seg`
	echo "追加文件"
	sleep 60 
done
