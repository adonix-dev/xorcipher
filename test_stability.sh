#!/bin/sh
ceol=`tput el`
i=1
j=1
number_key=$(wc -l test_bench/keys)
echo Crypted file generation
for file in test_bench/uncrypted/*; do
	cat test_bench/keys | while read -r key; do
		name="$key""()"`basename $file`
		./sources/xorcipher -i $file -o "test_bench/crypted/$name" -k $key > /dev/null
		echo -en "$ceol$j | $i/$number_key | $key\r"
		i=$(( $i + 1 ))
	done
	j=$(( $j + 1 ))
done
test=lol
number_of_crypted_file=`ls -1q test_bench/crypted | wc -l`
for j in `seq 1 3`; do
	i=1
	for file in test_bench/crypted/*; do
		test=`./sources/xorcipher -i $file -m $j`
		if [ $? -ne 0 ]; then
			exit
		fi
		echo -en $ceol"C$j | $i/$number_of_crypted_file\r"
		i=$(( $i + 1 ))
	done
done
echo
