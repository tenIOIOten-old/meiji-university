directori=ex10
file=10_2.cpp
cd `dirname $0`
cd compmech/$directori
gcc $file 
if [ "$?" -eq 0 ]
then  
 ./a.out  
fi
