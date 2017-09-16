#!/bin/bash

#Serban Alexandru 341 C5
             
gcc -Wall a.c -lm

stats_counter=15
N=100000000

echo "N = $N"

#le sterge in caz ca exista de la o rulare precedenta
rm -f test.txt
for i in 1024000 512000 256000 128000
do
	
	rm -f "vmstat$i.txt"
	rm -f "mpstat$i.txt"
	rm -f "iostat$i.txt"	
done

for i in 1024000 512000 256000 128000	#ordine descrescatoare ca nu ai drepturi sa maresti stack size
do

	
	
	echo "==================== limit : $i ========================="

	vmstat 1 $stats_counter | grep -v r | tr -s " " | awk '{ print $3, $4, $7, $8, $9, $10, $11, $12, $13, $14, $15, $16 }' >> "vmstat$i.txt"	 &
	mpstat 1 $stats_counter >> "mpstat$i.txt" &	
	iostat 1 $stats_counter >> "iostat$i.txt" &

  	ulimit -s "$i" -v "$i"	
	time ./a.out "$N"
	
	
		
	
	wait 	# astapta toate firele de executie pronite


	awk 'NF' "mpstat$i.txt" | tail -n +3 | head -n -1 | tr -s " " > temp.txt
	cp temp.txt "mpstat$i.txt" 
	rm temp.txt

	grep '^sda' "iostat$i.txt" | tr -s " " > temp.txt
	cp temp.txt "iostat$i.txt"
	rm temp.txt

	echo "==================== done : $i =========================" 
	echo
	echo


	gnuplot -p -e "plot 'vmstat$i.txt' \
   using 3 title 'si' with lines, 'vmstat$i.txt' \
   using 4 title 'so' with lines, 'vmstat$i.txt' \
   using 5 title 'bi' with lines, 'vmstat$i.txt' \
   using 6 title 'bo' with lines, 'vmstat$i.txt' \
   using 7 title 'in' with lines, 'vmstat$i.txt' \
   using 8 title 'cs' with lines, 'vmstat$i.txt' \
   using 9 title 'us' with lines, 'vmstat$i.txt' \
   using 10 title 'sy' with lines, 'vmstat$i.txt' \
   using 11 title 'id' with lines, 'vmstat$i.txt' \
   using 12 title 'wa' with lines"


	 gnuplot -p -e "plot 'mpstat$i.txt' \
	using 4 title '%usr' with lines, 'mpstat$i.txt' \
	using 6 title '%sys' with lines, 'mpstat$i.txt' \
	using 7 title '%iowait' with lines, 'mpstat$i.txt' \
	using 8 title '%irq' with lines, 'mpstat$i.txt' \
	using 9 title '%soft' with lines, 'mpstat$i.txt' \
	using 10 title '%steal' with lines, 'mpstat$i.txt' \
	using 11 title '%guest' with lines, 'mpstat$i.txt' \
	using 13 title '%idle' with lines"

	 gnuplot -p -e "plot 'iostat$i.txt' \
	using 3 title 'kB_read/s' with lines, 'iostat$i.txt' \
	using 4 title 'kB_wrtn/s' with lines"

	


done

rm -f a.out

