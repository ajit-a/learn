echo "Enter n"
read n
i=1
for i in $(seq 1 $n)
do
	for j in $(seq 1 $i)
	do
		echo -n "*"
	done
	echo ""
done 

for((i=1;i<=n;i++))
do
	echo $i
done
for i in $(eval echo "{1..$n}")
do
	echo $i
done

