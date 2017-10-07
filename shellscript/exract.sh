while read a x x x b x; 
do
  [ "$b" == WAM ] && echo ${a#*:}
done < $1

# read the line 
