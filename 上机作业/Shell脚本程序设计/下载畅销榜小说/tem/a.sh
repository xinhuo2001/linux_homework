# [ `grep -c "a.txt 桃花"` != '0' ] && {
#     echo "存在"
# }

# [ 1 = 1 ] && {
#     echo "存在"
# }

# echo `grep -c "a.txt 桃花"`

if cat a.txt | grep "桃花" > /dev/null
then
    echo "存在"
fi