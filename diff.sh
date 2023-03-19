#!/bin/bash
# High Intensity
Color_Off='\033[0m'		  # Reset
IBlack='\033[0;90m'       # Black
IRed='\033[0;91m'         # Red
IGreen='\033[0;92m'       # Green
IYellow='\033[0;93m'      # Yellow
IBlue='\033[0;94m'        # Blue
IPurple='\033[0;95m'      # Purple
ICyan='\033[0;96m'        # Cyan
IWhite='\033[0;97m'       # White

fileFT="traces/ft_test.out"
fileSTD="traces/std_test.out"

timeFT="traces/time/timeFT.out"
timeSTD="traces/time/timeSTL.out"

diffFile="traces/diff/diffValue.out"
diffTime="traces/diff/diffTime.out"

sed -i 's/# define STL 1/# define STL 0/' main.cpp
make
./ft_container ft > $fileFT

sed -i 's/# define STL 0/# define STL 1/' main.cpp
make
./ft_container std > $fileSTD

diff $fileFT $fileSTD > $diffFile

diff $fileFT $fileSTD  | grep microsec > $diffTime



count=1
rm traces/diff/compare.in
touch traces/diff/compare.in
compareFile=traces/diff/compare.in

cat $diffTime | while read -r line;
do
	current=$(echo "$line" | sed 's/[^0-9]*//g')
	if [ $((count % 2)) -eq 1 ]; then
		echo -n "$current " >> $compareFile
	else
		echo "$current" >> $compareFile
	fi
	count=$((count+1))
done < $diffTime

while read -r line;
do
  # Extraire les valeurs numériques des lignes qui commencent par "<" ou ">"
    lhs=$(echo "$line" |  cut -d " " -f1)
	rhs=$(echo "$line" |  cut -d " " -f2)
	#read -r nextline+1
    # Comparer les deux valeurs numériques
   	if [[ $lhs -gt $rhs*20 ]] && [ $lhs -ne 0 ] && [ $rhs -ne 0 ] ; then
   	  echo -e " $IRed Erreur de comparaison entre : FT |$IPurple $lhs ms $Color_Off 	et  STD |$IBlue $rhs ms $Color_Off 	[ ❌ ]"
   	fi
   	echo -e "FT |$IPurple $lhs ms $Color_Off 	et  STD |$IBlue $rhs ms $Color_Off 	[ ✅ ]"
done < $compareFile
# Vérifier si une erreur a été trouvée
if [ $? -eq 0 ]; then
  echo -e "$IGreen None Ft_function is 20 time slower than STL_functions. ✅$Color_Off"
else
  echo -e "$IRed Il y a une erreur dans les valeurs numériques du fichier diff.out. ❌$Color_Off"
fi
