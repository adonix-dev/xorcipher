#!/bin/sh

if [ -d test_bench ]; then
	rm -R test_bench
fi

mkdir test_bench
mkdir test_bench/uncrypted
mkdir test_bench/crypted

text_lenght=20
number_file_type=5
number_of_type=1
file_power=2
file_id=0
wordfile=/usr/share/dict/french
ceol=`tput el`
file_id=0
key_lenght=3
number_key_type=1

echo Key generation
for k in `seq 1 5`; do
	for j in `seq 1 $number_key_type`; do
		head /dev/urandom | LC_ALL=C tr -dc 'A-Za-z0-9,-.:?_{}' | head -c $key_lenght >> test_bench/keys
		echo >> test_bench/keys
		echo -en "$ceol$k/5 | $j/$number_key_type \r"
	done
	key_lenght=$(( $key_lenght + 1 ))
done

# Les fichiers ne sont composé que de mots du dictionnaire, il n'y a pas de ponctuations donc
# le test est pas optimal.
echo Uncrypted file generation
for k in `seq 1 $number_of_type`; do
	for j in `seq 1 $number_file_type`; do
		for i in `seq 1 $text_lenght`; do
			echo -ne `gshuf -n1 dict`" " >> test_bench/uncrypted/$file_id
			echo -en "$ceol$k/$number_of_type | $j/$number_file_type | $i/$text_lenght \r"
		done
		file_id=$(( $file_id + 1 ))
	done
	text_lenght=$(( $text_lenght * $file_power ))
done

echo "Generation done!"
