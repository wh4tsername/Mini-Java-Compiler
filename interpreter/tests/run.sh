cd ../ || exit

make

cd tests || exit

number_of_tests=1
for ((i = 1; i <= $number_of_tests; i++))
do
	tail -n +3 test$i.txt > test.txt

	../oberon test.txt > output.txt
	
	head -n 1 test$i.txt | tail -n 1 >> correct_answer.txt

	if cmp -s output.txt correct_answer.txt ; then
 		echo "#test $i OK"
	else
		echo "correct answer: "
		cat correct_answer.txt
		echo "program output: "
		cat output.txt
    	echo "#test $i WA" && break
	fi

	truncate -s 0 correct_answer.txt
done

rm -f test.txt
rm -f output.txt
rm -f correct_answer.txt
