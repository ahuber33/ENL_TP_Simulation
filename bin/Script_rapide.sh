 #!/bin/bash


for (( i=1 ; i<=10 ; i++ ))
do
    while [[ $(pgrep -x TPSim | wc -l) -gt 4 ]]
    do
	sleep 10
    done
    ./TPSim a_${i} 10000 vrml.mac &
    sleep 10
    done
