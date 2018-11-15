#!/bin/bash

folder=$1
#echo $folder

find ./$1/ -depth -name "*\:*" -execdir rename 's/:/_/g' "{}" \;
find ./$1/ -depth -name "* *" -execdir rename 's/ /_/g' "{}" \;

for i in `find $folder/* -maxdepth 0 -type d` 
do
    #echo $i
    ii=`basename $i`
    for j in `find $folder/$ii/* -maxdepth 0 -type d`
    do
        jj=`basename $j`
        list=`ls $folder/$ii/$jj | grep .txt`
        echo ./Average $folder/$ii/$jj $list average_${ii}_${jj}.csv
        ./Average $folder/$ii/$jj $list average_${ii}_${jj}.csv
    done
    echo ""
done

for i in `find $folder/* -maxdepth 0 -type d` 
do
    list=""
    ii=`basename $i`
    for j in `find $folder/$ii/* -maxdepth 0 -type d` 
    do
        jj=`basename $j`
        append=`ls $folder/$ii/$jj/*.csv`
        list="$list $append"
    done
    #echo $list
    echo ./Compare $list $folder/$ii/COLUMN
    ./Compare $list $folder/$ii/COLUMN
done

echo "done"