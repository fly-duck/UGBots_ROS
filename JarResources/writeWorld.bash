#!/bin/bash
source ~/.bashrc
roscd

picker=$1
carrier=$2
worker=$3
visitor=$4
dog=$5
cat=$6
possum=$7
tractor=$8
kiwitree=$9

mkdir -p world/config

rm ugbots_ros/launch/world.launch
rm world/config/robotinstances.inc
rm world/config/peopleinstances.inc
rm world/config/animalinstances.inc
rm world/config/tractorinstances.inc
rm world/config/treeinstances.inc
rm world/config/beaconinstances.inc

echo  \<launch\> > ugbots_ros/launch/world.launch
echo include \"models\/cmdCenter.inc\" >> world/config/beaconinstances.inc
echo include \"models\/beaconcore.inc\" >> world/config/beaconinstances.inc
echo include \"models\/kiwirow.inc\" >> world/config/treeinstances.inc
echo include \"models\/robots.inc\" >> world/config/robotinstances.inc
echo include \"models\/workers.inc\" >> world/config/peopleinstances.inc
echo include \"models\/dogs.inc\" >> world/config/animalinstances.inc
echo include \"models\/cats.inc\" >> world/config/animalinstances.inc
echo include \"models\/possums.inc\" >> world/config/animalinstances.inc
echo include \"models\/visitors.inc\" >> world/config/peopleinstances.inc
echo include \"models\/tractors.inc\" >> world/config/tractorinstances.inc

number=0
beacon=$(($kiwitree+$kiwitree-1))
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
tree=0
treenum=0
z=0

#Creating Core Unit
echo \<group ns=\"robot_$number\"\> >> ugbots_ros\/launch\/world.launch
echo \<node pkg=\"ugbots_ros\" name=\"core\" type=\"CORE\"\/\> >> ugbots_ros\/launch\/world.launch 
echo \<\/group\> >> ugbots_ros\/launch\/world.launch

echo cmdCenter\( pose [ 40 40 0 0 ] origin [ 0 0 0 270 ] name \"core\" color \"DimGrey\" \) >> world/config/beaconinstances.inc

number=$(($number+1))

#generating kiwifruit rows

if (( $kiwitree % 2 )); then
    echo rows \(pose [ 0 -35 -1.002 0 ]\) >> world/config/treeinstances.inc
    treenum=$(($treenum+1))
    tree=$(($tree+1))
    while [ $tree -lt $kiwitree ];
    do
        left=$(echo "scale=2; 0-$treenum*3.5" | bc)
        right=$(echo "scale=2; 0+$treenum*3.5" | bc)
        echo rows \(pose [ $left -35 -1.002 0 ]\) >> world/config/treeinstances.inc
        echo rows \(pose [ $right -35 -1.002 0 ]\) >> world/config/treeinstances.inc

        bleft=$(echo "scale=2; -1.75-$z*3.5" | bc)
        bright=$(echo "scale=2; 1.75+$z*3.5" | bc)
        
        echo \<group ns=\"robot_$number\"\> >> ugbots_ros\/launch\/world.launch
		echo \<node pkg=\"ugbots_ros\" name=\"beacon\" type=\"BEACON\"\/\> >> ugbots_ros\/launch\/world.launch 
		echo \<\/group\> >> ugbots_ros\/launch\/world.launch
        echo point\( pose [ $bleft 38 0 0 ] name \"robot_$number\" color \"yellow\" \) >> world/config/beaconinstances.inc
        number=$(($number+1))
        
        echo \<group ns=\"robot_$number\"\> >> ugbots_ros\/launch\/world.launch
		echo \<node pkg=\"ugbots_ros\" name=\"beacon\" type=\"BEACON\"\/\> >> ugbots_ros\/launch\/world.launch 
		echo \<\/group\> >> ugbots_ros\/launch\/world.launch
        echo point\( pose [ $bright 38 0 0 ] name \"robot_$number\" color \"yellow\" \) >> world/config/beaconinstances.inc
        number=$(($number+1))
        
        echo \<group ns=\"robot_$number\"\> >> ugbots_ros\/launch\/world.launch
		echo \<node pkg=\"ugbots_ros\" name=\"beacon\" type=\"BEACON\"\/\> >> ugbots_ros\/launch\/world.launch 
		echo \<\/group\> >> ugbots_ros\/launch\/world.launch
        echo point\( pose [ $bleft -38 0 0 ] name \"robot_$number\" color \"yellow\" \) >> world/config/beaconinstances.inc
        number=$(($number+1))
        
        echo \<group ns=\"robot_$number\"\> >> ugbots_ros\/launch\/world.launch
		echo \<node pkg=\"ugbots_ros\" name=\"beacon\" type=\"BEACON\"\/\> >> ugbots_ros\/launch\/world.launch 
		echo \<\/group\> >> ugbots_ros\/launch\/world.launch
        echo point\( pose [ $bright -38 0 0 ] name \"robot_$number\" color \"yellow\" \) >> world/config/beaconinstances.inc
        number=$(($number+1))
        
        tree=$(($tree+2))
        treenum=$(($treenum+1))
        z=$(($z+1))
    done
elif ! (( $kiwitree % 2 )); then
    while [ $tree -lt $kiwitree ];
    do
        left=$(echo "scale=2; -1.75-$treenum*3.5" | bc)
        right=$(echo "scale=2; 1.75+$treenum*3.5" | bc)

        echo rows \(pose [ $left -35 -1.002 0 ]\) >> world/config/treeinstances.inc
        echo rows \(pose [ $right -35 -1.002 0 ]\) >> world/config/treeinstances.inc
	

        bleft=$(echo "scale=2; 0-$z*3.5" | bc)
        bright=$(echo "scale=2; 0+$z*3.5" | bc)
	
	if !(($tree==0)); then
        echo \<group ns=\"robot_$number\"\> >> ugbots_ros\/launch\/world.launch
		echo \<node pkg=\"ugbots_ros\" name=\"beacon\" type=\"BEACON\"\/\> >> ugbots_ros\/launch\/world.launch 
		echo \<\/group\> >> ugbots_ros\/launch\/world.launch
        echo point\( pose [ $bleft 38 0 0 ] name \"robot_$number\" color \"yellow\" \) >> world/config/beaconinstances.inc
        number=$(($number+1))
	fi

        echo \<group ns=\"robot_$number\"\> >> ugbots_ros\/launch\/world.launch
		echo \<node pkg=\"ugbots_ros\" name=\"beacon\" type=\"BEACON\"\/\> >> ugbots_ros\/launch\/world.launch 
		echo \<\/group\> >> ugbots_ros\/launch\/world.launch
        echo point\( pose [ $bright 38 0 0 ] name \"robot_$number\" color \"yellow\" \) >> world/config/beaconinstances.inc
        number=$(($number+1))

	if !(($tree==0)); then
        echo \<group ns=\"robot_$number\"\> >> ugbots_ros\/launch\/world.launch
		echo \<node pkg=\"ugbots_ros\" name=\"beacon\" type=\"BEACON\"\/\> >> ugbots_ros\/launch\/world.launch 
		echo \<\/group\> >> ugbots_ros\/launch\/world.launch
        echo point\( pose [ $bleft -38 0 0 ] name \"robot_$number\" color \"yellow\" \) >> world/config/beaconinstances.inc
        number=$(($number+1))
	fi

        echo \<group ns=\"robot_$number\"\> >> ugbots_ros\/launch\/world.launch
		echo \<node pkg=\"ugbots_ros\" name=\"beacon\" type=\"BEACON\"\/\> >> ugbots_ros\/launch\/world.launch 
		echo \<\/group\> >> ugbots_ros\/launch\/world.launch
        echo point\( pose [ $bright -38 0 0 ] name \"robot_$number\" color \"yellow\" \) >> world/config/beaconinstances.inc
	number=$(($number+1))
     
	tree=$(($tree+2))
        treenum=$(($treenum+1))
        z=$(($z+1))
    done
fi

#creating picker robots
temp=0

while [ $i -lt $picker ];
do

echo \<group ns=\"robot_$number\"\> >> ugbots_ros\/launch\/world.launch
echo \<node pkg=\"ugbots_ros\" name=\"robotnode\" type=\"PICKER\"\/\> >> ugbots_ros\/launch\/world.launch 
echo \<\/group\> >> ugbots_ros\/launch\/world.launch


if !(($i%2)); then
	temp=$(($temp+1))
fi

posx=$((-40 + (( $(($i%2)) * 8 )) ))
posy=$((-50 + $(($temp * 4))))
echo pickerRobot\(pose [ $posx $posy 0 0 ]\ name \"P$i\" color \"red\"\) >> world/config/robotinstances.inc

i=$(($i+1))
number=$(($number+1))

done

#creating carrier robots
while [ $j -lt $carrier ];
do

echo \<group ns=\"robot_$number\"\> >> ugbots_ros\/launch\/world.launch
echo \<node pkg=\"ugbots_ros\" name=\"robotnode\" type=\"CARRIER\"\/\> >> ugbots_ros\/launch\/world.launch
echo \<\/group\> >> ugbots_ros\/launch\/world.launch

echo carrierRobot\(pose [ $((25 + (($j*5)))) -15 0 270 ] name \"C$j\" color \"blue\"\) >> world/config/robotinstances.inc

j=$(($j+1))
number=$(($number+1))

done

#creating worker nodes
while [ $w -lt $worker ];
do

rand=55
rand2=-40

echo \<group ns=\"robot_$number\"\> >> ugbots_ros/launch/world.launch
echo \<node pkg=\"ugbots_ros\" name=\"workernode\" type=\"WORKER\"\/\> >> ugbots_ros/launch/world.launch 
echo \<\/group\> >> ugbots_ros/launch/world.launch

echo worker\(pose [ $rand $rand2 0 270 ] origin [ 0 0 0 90 ] name \"W$w\"\) >> world/config/peopleinstances.inc
w=$(($w+1))
number=$(($number+1))

done

visitorx=58
visitory=-47.5

#creating visitor nodes
while [ $v -lt $visitor ];
do

rand=$visitorx
rand2=$visitory

echo \<group ns=\"robot_$number\"\> >> ugbots_ros/launch/world.launch 
echo \<node pkg=\"ugbots_ros\" name=\"visitornode\" type=\"VISITOR\"\/\> >> ugbots_ros/launch/world.launch 
echo \<\/group\> >> ugbots_ros/launch/world.launch

echo visitor\(pose [ $rand $rand2 0 180 ] origin [ 0 0 0 90 ] name \"V$v\" \) >> world/config/peopleinstances.inc
v=$(($v+1))
number=$(($number+1))
visitorx=$(($rand+5))

done

#creating dogs
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

echo \<group ns=\"robot_$number\"\> >> ugbots_ros/launch/world.launch
echo \<node pkg=\"ugbots_ros\" name=\"dognode\" type=\"DOG\"\/\> >> ugbots_ros/launch/world.launch 
echo \<\/group\> >> ugbots_ros/launch/world.launch

echo dog\( pose [ $rand $rand2 0 0 ] origin [ 0 0 0 270 ] name \"D$d\" \) >> world/config/animalinstances.inc
d=$(($d+1))
number=$(($number+1))

done

#creating cat
while [ $c -lt $cat ];
do

rand=$(( (RANDOM % 80) - 40 )) 

echo \<group ns=\"robot_$number\"\> >> ugbots_ros/launch/world.launch
echo \<node pkg=\"ugbots_ros\" name=\"catnode\" type=\"CAT\"\/\> >> ugbots_ros/launch/world.launch 
echo \<\/group\> >> ugbots_ros/launch/world.launch

echo cats\( pose [ $rand 47 0 0 ] origin [ 0 0 0 270 ] name \"C$c\" \) >> world/config/animalinstances.inc
c=$(($c+1))
number=$(($number+1))

done

#creating possums
while [ $po -lt $possum ];
do

echo \<group ns=\"robot_$number\"\> >> ugbots_ros/launch/world.launch 
echo \<node pkg=\"ugbots_ros\" name=\"possumnode\" type=\"POSSUM\"\/\> >> ugbots_ros/launch/world.launch 
echo \<\/group\> >> ugbots_ros/launch/world.launch

possumStart=$(echo "scale=2; $bleft-1.75" | bc)

index=$(( (RANDOM % 28) -14))

yPos=$(echo "scale=2; $index*2.5 -1.25"| bc)

echo possum\( pose [ $left $yPos 0 0 ] origin [ 0 0 0 270 ] name \"PO$po\" color \"wheat4\" \) >> world/config/animalinstances.inc

po=$(($po+1))
number=$(($number+1))

done

#creating tractors
while [ $t -lt $tractor ];
do
echo \<group ns=\"robot_$number\"\> >> ugbots_ros/launch/world.launch
echo \<node pkg=\"ugbots_ros\" name=\"tractornode\" type=\"TRACTOR\"\/\> >> ugbots_ros/launch/world.launch 
echo \<\/group\> >> ugbots_ros/launch/world.launch

echo tractor\( pose [ -45 0 0 0 ] origin [ 0 0 0 270] name \"T$t\" \) >> world/config/tractorinstances.inc

t=$(($t+1))
number=$(($number+1))

done

echo  \<\/launch\> >> ugbots_ros/launch/world.launch
