#准备目录网页文件用于临时存储
catalog="catalog.txt"
[ ! -r "$catalog" ] && {
    touch "$catalog"
}
#小说总览页面
web_url="https://www.qidian.com/rank/hotsales/"
#获取书本链接
    #获取URL网页文本
    #获取文本第一行
    #将文本根据链接标准 red-btn 进行换行 并进行url变换
    #删除"
    #将第一列数据拿出作为链接
bool_url_list=`wget -q -O - "$web_url" \
| awk 'NR==1 {print $0}' \
| sed -e 's/"red-btn"/\n/g' -e 's/ href="/https:/g' \
| sed -e 's/"//g' \
| awk 'NR > 1 {print $1}'` 
#对每一本书进行下载
for book_url in $bool_url_list
do
    #拼凑目录页网址
    catalog_book_url="$book_url/#Catalog"
    echo $catalog_book_url
    #下载目录页(耗时较长)
    wget -q -O "$catalog" "$catalog_book_url"
    #获取书名
    book_name=`awk 'NR == 7 {print $0}' "$catalog" | sed -e 's/<title>\(.*\)(.*title>$/\1/g'`
    echo $book_name
    book_name="$book_name.txt"
    echo $book_name
    #创建书本文件
    [ ! -r "$book_name" ] && {
        touch $book_name
    } 
    #获取该书本各目录链接
    #简化文本 到list.txt
    tem="list1.txt"
    catalog_s=`cat "$catalog" | grep '<a href="//read.qidian.com/chapter/'`
    echo $catalog_s > "$tem"
    #分割文本到list.txt
    list_name="list_name.txt"
    sed 's/<h2 class="book_name"><a href="/\n/g' "$tem" | sed -e 's/" target.*">/ /g' | sed -e 's/<.*//g' -e 's/章 /章/g' > "$list_name"
    #删除文件第一空行 以及 删除过程文件
    sed -i '1d' "$list_name" && rm "$tem"
    #遍历list2.txt并下载
    cat "$list_name" |
    while read catalog_url  catalog_name
    do
        #已经存在的章节不在下载
        if cat $book_name | grep "$catalog_name"
        then
            echo "PASS"
            continue
        #尚未下载的页面
        else
        catalog_url="https:$catalog_url"
        echo $catalog_url $catalog_name
        content="content.txt"
        # 下载小说网页
        wget -q "$catalog_url" && mv "index.html" "$content"
        # 截取文章内容
        cur_content=`cat "$content" | grep '<p> ' | sed -e 's/<p> */\n/g' -e 's/　//g' | grep -v '^ *$'`
#写入文件
ed $book_name > /dev/null 2>&1 <<TOAST
a
TITLE$catalog_name
$cur_content
.
w
q
TOAST
#写入文件
        fi
    done   
done




