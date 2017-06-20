directori=ex8
file=8_2.cpp
cd `dirname $0`
cd compmech/$directori
gcc $file
if [ "$?" -eq 0 ]
then  
 ./a.out
fi
