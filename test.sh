#!/usr/local/bin/bash
#!/bin/bash
#!/usr/local/bin/bash

LOG=0
VERBOSE=0

while getopts ":lv" opt; do
	case $opt in
		l)
			LOG=1
			;;
		v)
			VERBOSE=1
			;;
		\?)
			echo "Invalid option: -$OPTARG" >&2
			exit
			;;
	esac
done

echo -n -e "\033[93m"
echo "  Building compiler"
echo "============================="
echo -e -n "\033[0m"

if [ ! -f build.sh ]
then
	echo "Error: Missing build.sh script"
	exit 1
fi

./build.sh

if [ ! -f run.sh ]
then
	echo "Error: Missing run.sh script"
	exit 1
fi

RESULTS=()

for DIR_PHASE in programs/*/
do
	PHASE=$(basename $DIR_PHASE)
	PHASE_NUM=${PHASE%-*}
	PHASE_NAME=${PHASE#*-}
	PREV_PHASE_NUM=`expr $PHASE_NUM - 1`
	PREV_PHASE=`ls programs | grep $PREV_PHASE_NUM-`
	PREV_PHASE_NAME=${PREV_PHASE#*-}
	PREV_MODE=${PREV_PHASE_NAME#*+}
	MODE=${PHASE_NAME#*+}
	PHASE_NAME="${PHASE_NAME^}"

	for DIR_TYPE in $DIR_PHASE*/
	do
		TYPE=$(basename $DIR_TYPE)
		TYPE="${TYPE^}"

		if [[ $TYPE == "Valid" ]]
		then
			CONF_STATUS=0
			CONF_OUTPUT="OK"
		else
			CONF_STATUS=1
			CONF_OUTPUT="Error: "
		fi

		if [ "$(ls -A -I ".gitignore" $DIR_TYPE)" ]
		then
			echo -e "\033[93m"
			echo "  $PHASE_NAME $TYPE"
			echo "============================="
			echo -e -n "\033[0m"

			COUNT=0
			COUNT_PASSED=0

			for TEST in $DIR_TYPE*
			do
				((COUNT++))

				PREV_SUCCESS=1

				if [[ $TYPE == 'Invalid' && ! -z $PREV_MODE ]]
				then
					OUTPUT=$(./run.sh $PREV_MODE $TEST 2>&1)
					STATUS=${PIPESTATUS[0]}
					OUTPUT=${OUTPUT#$TEST}

					if [[ $OUTPUT == *"java.lang.NullPointerException"* ]]
					then
						STATUS=-1
					fi

					if [[ $OUTPUT != "OK" || $STATUS != 0 ]]
					then
						PREV_SUCCESS=0
					fi
				fi

				if [[ $PREV_SUCCESS == 1 ]]
				then
					OUTPUT=$(./run.sh $MODE $TEST 2>&1)
					STATUS=${PIPESTATUS[0]}
					OUTPUT=${OUTPUT#$TEST}

					if [[ $OUTPUT == *"java.lang.NullPointerException"* ]]
					then
						STATUS=-1
					fi
					if [[ $OUTPUT == $CONF_OUTPUT* && $STATUS == $CONF_STATUS ]]
					then
						((COUNT_PASSED++))
						if [[ $VERBOSE == 1 ]]
						then
							STATUS_TEXT="pass"
							STATUS_COLOUR="32"
						else
							STATUS_TEXT=""
						fi
					else
						STATUS_TEXT="fail"
						STATUS_COLOUR="31"
					fi
				else
					STATUS_TEXT="failed previous"
					STATUS_COLOUR="31"
				fi

				if [ ! -z "$STATUS_TEXT" ]
				then
					echo
					echo "$TEST: $OUTPUT" | tr -d '\n'
					echo -n -e " \033[0;${STATUS_COLOUR}m[$STATUS_TEXT]\033[0m"
					if [ $LOG -eq 1 ]
					then
						echo "$TEST: $OUTPUT [$STATUS_TEXT]" >> ${PHASE_NAME}_${TYPE}.log
					fi
				fi
			done
			if [ $VERBOSE -eq 1 ]
			then
				if [ $COUNT -gt 0 ]
				then
					echo
				fi
			else
				if [ $COUNT -ne $COUNT_PASSED ]
				then
					echo
				fi
			fi
			echo
			if [ $COUNT -eq $COUNT_PASSED ]
			then
				STATUS_COLOUR="42"
			else
				STATUS_COLOUR="41"
			fi

			echo -e "\e[${STATUS_COLOUR}m# ${PHASE_NAME} ${TYPE}: ${COUNT_PASSED}/${COUNT}\e[49m"
			RESULTS+=("\e[${STATUS_COLOUR}m# ${PHASE_NAME} ${TYPE}: ${COUNT_PASSED}/${COUNT}\e[49m")
		fi
	done
done

echo -e "\033[93m"
echo "  Overall"
echo "============================="
echo -e "\033[0m"

for i in ${!RESULTS[*]}; do
	echo -e ${RESULTS[$i]}
done
