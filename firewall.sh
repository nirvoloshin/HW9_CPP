#!/bin/bash

while read line 
do
	# removing whitespaces and comments
	line=`echo "$line" |sed 's/[[:space:]]//g' | sed 's/#.*//g'`
	# ignoring blank lines
	if [[ "$line" == "" ]]; then
		continue
	fi
	# spliting the full rule into subrules  
	readarray -d , -t subrule <<< "$line"
	first_rule=1
	# going over each subrule
	for (( n=0; n < ${#subrule[*]}; n++ ))
	do
		# checking each sub string if it's a rule and and check which packets 
		# stand in all the sub rules
		if [[ "${subrule[n]}" =~ "src-ip" 
			|| "${subrule[n]}" =~ "dst-ip" 
			|| "${subrule[n]}" =~ "src-port" 
			|| "${subrule[n]}" =~ "dst-port" ]] ;then

			if (( first_rule == 1 )); then 
				./firewall.exe "${subrule[n]}"< $1 > packet_rule.txt
				first_rule=0
			else
				./firewall.exe "${subrule[n]}" < packet_rule.txt > tmp_file.txt
				cat tmp_file.txt > packet_rule.txt
			fi
		fi
		if (( n==${#subrule[*]}-1 )); then
				cat packet_rule.txt >> combine_packet_rule.txt 
		fi
	done
done

rm tmp_file.txt
rm packet_rule.txt
# all the packets that uphold at least one of the rules will be emitted 
# into the standart output
sort combine_packet_rule.txt |uniq |sed 's/[[:space:]]//g'
rm combine_packet_rule.txt
