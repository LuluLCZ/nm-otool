#!bin/sh
for file in $(ls -1 /tmp/tests/**/*)
do
echo $file
./ft_nm $file
done 