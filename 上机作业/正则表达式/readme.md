### 网址
https://www.aqistudy.cn/

### 网页数据展示

![image-20220325173329189](https://raw.githubusercontent.com/xinhuo2001/image1/main/image-20220325173329189.png)

### 数据处理

#### 筛选城市

```sh
#编辑data.awk文件 获得关键数据 时间+城市+浓度
/dateSpan&quot/ {print $0} #时间
/title=&quot;/ && !/title=&quot;&quot;/ {print $0} #地点+浓度
```

#### 去除冗余字符

```sh
sed -e 's/<span title=&quot;/\n/g' #分行
sed -e '/具体监测点/d' #删除第一行无关数据
```

#### 获取关键信息地点+浓度

```sh
sed -e 's/^.*>\(.*\)<[/]span>.*datagrid-cell-c2-pm2_5&quot;>[0-9][0-9]*.*$/\1/g'
```

#### 提取时间

```sh
sed -e 's/^.*>.*<[/]span>$/time \1/'
```

#### 格式化输出

```sh
#out.awk
/time/ {t=$2} 3获取时间
/!time/ {printf("%s,%s,%s",t,$1,$2)} #格式化输出
```

#### 总语句

```sh
cat data.html | awk -f data.awk | sed 's/<span title=&quot;/\n/g' | sed -e '/具体监测点/d' | sed -e 's/^.*>\(.*\)<[/]span>.*datagrid-cell-c2-pm2_5&quot;>\([0-9][0-9]*\).*$/\1 \2/g' | sed -e 's/^.*>\(.*\)<[/]span>$/time \1/' | awk -f out.awk > out.csv
```

#### csv效果

![image-20220325172920055](https://raw.githubusercontent.com/xinhuo2001/image1/main/image-20220325172920055.png)
