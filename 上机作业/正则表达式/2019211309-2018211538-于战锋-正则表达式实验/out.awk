/time/ {t=$2}
!/time/ {printf("%s,%s,%s\n",t,$1,$2)}
