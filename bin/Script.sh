 #!/bin/bash


echo "Début de traitement"
#myArr=("100" "500" "1000" "2000" "3000" "4000" "5000" "10000")
myArr=("1 1 1" "2 4 1" "2 4 2")
myArr1=("proton" "He1+" "He2+")

for idx in ${!myArr[*]}
do
    while [[ $(pgrep -x TPSim | wc -l) -gt 4 ]]
    do
	sleep 10
    done
        #Init
        value=${myArr[$idx]}
        idx_fichier=$(($idx))
        echo Index : $idx / Fichier : $value
        # Creation du fichier a partir du fichier de base (fichier temporaire)
        cp vrml_base.mac base_$idx_fichier_bis.mac
        # Mise en place de la variable
        #sed -e "s/%energy/$value/g" base_$idx_fichier_bis.mac > base_$idx_fichier.mac
	sed -e "s/%ion/$value/g" base_$idx_fichier_bis.mac > base_$idx_fichier.mac
        # Suppression fichier temporaire
        rm base_$idx_fichier_bis.mac
	./TPSim ${myArr1[$idx]}_pinhole_100um_B_0.1T 1000000 base_$idx_fichier.mac &
	sleep 5
	rm base_$idx_fichier.mac
done
echo "Fin de traitement"


