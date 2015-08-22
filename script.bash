#!/bin/bash


picker=$1
carrier=$2
worker=$3
visitor=$4
dog=$5
possum=$6
tractor=$7

mkdir -p world/config

rm ugbots_ros/launch/world.launch
rm world/config/robotinstances.inc
rm world/config/peopleinstances.inc
rm world/config/animalinstances.inc

echo  \<launch\> > ugbots_ros/launch/world.launch
echo include \"models\/robots.inc\" > world/config/robotinstances.inc
echo include \"models\/workers.inc\" > world/config/peopleinstances.inc
echo include \"models\/dogs.inc\" > world/config/animalinstances.inc
echo include \"models\/possums.inc\" >> world/config/animalinstances.inc
echo include \"models\/visitors.inc\" >> world/config/peopleinstances.inc

i=0
j=0
w=0
a=0
v=0
d=0
c=0
po=0
t=0
rand=0
rand2=0

while [ $i -lt $picker ];
do

echo \<group ns=\"robot_$i\"\> >> ugbots_ros\/launch\/world.launch
echo \<node pkg=\"ugbots_ros\" name=\"robotnode\" type=\"PICKER\"\/\> >> ugbots_ros\/launch\/world.launch 
echo \<\/group\> >> ugbots_ros\/launch\/world.launch

echo pickerRobot\(pose [ -48 $((48-$(($i * 5)))) 0 90 ]\ name \"R$i\" color \"red\"\) >> world/config/robotinstances.inc

i=$(($i+1))

done

while [ $j -lt $carrier ];
do

echo \<group ns=\"robot_$i\"\> >> ugbots_ros\/launch\/world.launch
echo \<node pkg=\"ugbots_ros\" name=\"robotnode\" type=\"CARRIER\"\/\> >> ugbots_ros\/launch\/world.launch
echo \<\/group\> >> ugbots_ros\/launch\/world.launch

echo carrierRobot\(pose [ -46 $((48-$(($j*5)))) 0 90 ] name \"R$i\" color \"blue\"\) >> world/config/robotinstances.inc

j=$(($j+1))
i=$(($i+1))

done

while [ $w -lt $worker ];
do

rand=$(( (RANDOM % 97) - 46 )) 

if (($rand>=-12 && $rand<=12));
then
    rand3=$(( (RANDOM % 15) - 49 )) 
    rand4=$(( (RANDOM % 15) + 35 ))
    if [ $(( (RANDOM % 2) + 1 )) -lt "2" ];
    then
        rand2=$rand3
    else
        rand2=$rand4
    fi
else
    rand2=$(( (RANDOM % 99) - 48 )) 
fi

echo \<group ns=\"robot_$i\"\> >> ugbots_ros/launch/world.launch
echo \<node pkg=\"ugbots_ros\" name=\"workernode\" type=\"WORKER\"\/\> >> ugbots_ros/launch/world.launch 
echo \<\/group\> >> ugbots_ros/launch/world.launch

#echo worker\(pose [ 0 $((1+$(($w * 2)))) 0 0 ] name \"W$w\" color \"black\" \) >> world/config/peopleinstances.inc
echo worker\(pose [ $rand $rand2 0 0 ] name \"W$w\" color \"black\" \) >> world/config/peopleinstances.inc
w=$(($w+1))
i=$(($i+1))

done

while [ $v -lt $visitor ];
do

rand=$(( (RANDOM % 97) - 46 )) 

if (($rand>=-12 && $rand<=12));
then
    rand3=$(( (RANDOM % 15) - 49 )) 
    rand4=$(( (RANDOM % 15) + 35 ))
    if [ $(( (RANDOM % 2) + 1 )) -lt "2" ];
    then
        rand2=$rand3
    else
        rand2=$rand4
    fi
else
    rand2=$(( (RANDOM % 99) - 48 )) 
fi

echo \<group ns=\"robot_$i\"\> >> ugbots_ros/launch/world.launch #### WORKER-> VISITOR
echo \<node pkg=\"ugbots_ros\" name=\"visitornode\" type=\"VISITOR\"\/\> >> ugbots_ros/launch/world.launch 
echo \<\/group\> >> ugbots_ros/launch/world.launch

#echo visitor\(pose [ 3.5 $((1+$(($v * 2)))) 0 0 ] name \"V$v\" color \"pink\" \) >> world/config/peopleinstances.inc
echo visitor\(pose [ $rand $rand2 0 0 ] name \"V$v\" color \"pink\" \) >> world/config/peopleinstances.inc
v=$(($v+1))
i=$(($i+1))

done

while [ $d -lt $dog ];
do

rand=$(( (RANDOM % 97) - 46 )) 

if (($rand>=-12 && $rand<=12));
then
    rand3=$(( (RANDOM % 15) - 49 )) 
    rand4=$(( (RANDOM % 15) + 35 ))
    if [ $(( (RANDOM % 2) + 1 )) -lt "2" ];
    then
        rand2=$rand3
    else
        rand2=$rand4
    fi
else
    rand2=$(( (RANDOM % 99) - 48 )) 
fi 

echo \<group ns=\"robot_$i\"\> >> ugbots_ros/launch/world.launch
echo \<node pkg=\"ugbots_ros\" name=\"dognode\" type=\"DOG\"\/\> >> ugbots_ros/launch/world.launch 
echo \<\/group\> >> ugbots_ros/launch/world.launch

#echo dog\( pose [ 0 $((-1-$(($d * 2)))) 0 0 ] name \"D$d\" color \"brown\" \) >> world/config/animalinstances.inc
echo dog\( pose [ $rand $rand2 0 0 ] name \"D$d\" color \"brown\" \) >> world/config/animalinstances.inc
d=$(($d+1))
i=$(($i+1))

done

while [ $po -lt $possum ];
do

rand=$(( (RANDOM % 97) - 46 )) 

if (($rand>=-12 && $rand<=12));
then
    rand3=$(( (RANDOM % 15) - 49 )) 
    rand4=$(( (RANDOM % 15) + 35 ))
    if [ $(( (RANDOM % 2) + 1 )) -lt "2" ];
    then
        rand2=$rand3
    else
        rand2=$rand4
    fi
else
    rand2=$(( (RANDOM % 99) - 48 )) 
fi

echo \<group ns=\"robot_$i\"\> >> ugbots_ros/launch/world.launch #### DOG -> POSSUM
echo \<node pkg=\"ugbots_ros\" name=\"possumnode\" type=\"POSSUM\"\/\> >> ugbots_ros/launch/world.launch 
echo \<\/group\> >> ugbots_ros/launch/world.launch

#echo possum\( pose [ 3.5 $((-1-$(($c * 2)))) 0 0 ] name \"P$po\" color \"purple\" \) >> world/config/animalinstances.inc
echo possum\( pose [ $rand $rand2 0 0 ] name \"P$po\" color \"purple\" \) >> world/config/animalinstances.inc

po=$(($po+1))
i=$(($i+1))

done

: <<'Tractor_Code'
while [ $t -lt $tractor ];
do

echo \<group ns=\"robot_$i\"\> >> ugbots_ros/launch/world.launch
echo \<node pkg=\"ugbots_ros\" name=\"tractornode\" type=\"TRACTOR\"\/\> >> ugbots_ros/launch/world.launch 
echo \<\/group\> >> ugbots_ros/launch/world.launch

echo tractor\( pose [ 0 $((-1-$(($t * 2)))) 0 0 ] name \"T$t\" color \"brown\" \) >> world/config/tractorinstances.inc
t=$(($t+1))
i=$(($i+1))

done
Tractor_Code

echo  \<\/launch\> >> ugbots_ros/launch/world.launch