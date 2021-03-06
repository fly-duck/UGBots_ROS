define cmd ranger
(
  sensor(
  range [ 0.0 0.0 ] # range
  fov 180       # field of vision
  samples 180   # samples 
  )
  # generic model properties
  color "black"
  size [ 0.00 0.00 0.0 ]
)

define cmdCenter position
(

  size [2 2 13]
  block(
	points 4
	point[0] [0 0.125]
	point[1] [0.125 0.125]
	point[2] [0.125 0.875]
	point[3] [0 0.875]
	z [0 0.3]
  )

  block(
	points 4
	point[0] [0.25 0.125]
	point[1] [0.875 0.125]
	point[2] [0.875 0.875]
	point[3] [0.25 0.875]
	z [0 0.3]
  )

  block(
	points 4
	point[0] [0 0.125]
	point[1] [0.875 0.125]
	point[2] [0.875 0.875]
	point[3] [0 0.875]
	z [0.3 1]
  )

#=================================================================

  #pole 1
  block(
	points 4
	point[0] [0.125 0.125]
	point[1] [0.175 0.125]
	point[2] [0.175 0.175]
	point[3] [0.125 0.175]
	z [1 5]
  )

  #pole 2
  block(
	points 4
	point[0] [0.825 0.125]
	point[1] [0.875 0.125]
	point[2] [0.875 0.175]
	point[3] [0.825 0.175]
	z [1 5]
  )

  #pole 3
  block(
	points 4
	point[0] [0.825 0.825]
	point[1] [0.875 0.825]
	point[2] [0.875 0.875]
	point[3] [0.825 0.875]
	z [1 5]
  )

  #pole 4
  block(
	points 4
	point[0] [0.125 0.825]
	point[1] [0.175 0.825]
	point[2] [0.175 0.875]
	point[3] [0.125 0.875]
	z [1 5]
  )

  #pole-lid
  block(
	points 12
	point[0] [0.175 0.125]
	point[1] [0.175 0.175]
	point[2] [0.125 0.175]
	point[3] [0.125 0.825]
	point[4] [0.175 0.825]
	point[5] [0.175 0.875]
	point[6] [0.825 0.875]
	point[7] [0.825 0.825]
	point[8] [0.875 0.825]
	point[9] [0.875 0.175]
	point[10] [0.825 0.175]
	point[11] [0.825 0.125]
	z [1.4 1.6]
  )

  #pole-lid
  block(
	points 12
	point[0] [0.175 0.125]
	point[1] [0.175 0.175]
	point[2] [0.125 0.175]
	point[3] [0.125 0.825]
	point[4] [0.175 0.825]
	point[5] [0.175 0.875]
	point[6] [0.825 0.875]
	point[7] [0.825 0.825]
	point[8] [0.875 0.825]
	point[9] [0.875 0.175]
	point[10] [0.825 0.175]
	point[11] [0.825 0.125]
	z [2 2.2]
  )

  #pole-lid
  block(
	points 12
	point[0] [0.175 0.125]
	point[1] [0.175 0.175]
	point[2] [0.125 0.175]
	point[3] [0.125 0.825]
	point[4] [0.175 0.825]
	point[5] [0.175 0.875]
	point[6] [0.825 0.875]
	point[7] [0.825 0.825]
	point[8] [0.875 0.825]
	point[9] [0.875 0.175]
	point[10] [0.825 0.175]
	point[11] [0.825 0.125]
	z [2.6 2.8]
  )

  #pole-lid
  block(
	points 12
	point[0] [0.175 0.125]
	point[1] [0.175 0.175]
	point[2] [0.125 0.175]
	point[3] [0.125 0.825]
	point[4] [0.175 0.825]
	point[5] [0.175 0.875]
	point[6] [0.825 0.875]
	point[7] [0.825 0.825]
	point[8] [0.875 0.825]
	point[9] [0.875 0.175]
	point[10] [0.825 0.175]
	point[11] [0.825 0.125]
	z [3.2 3.4]
  )

  #pole-lid
  block(
	points 12
	point[0] [0.175 0.125]
	point[1] [0.175 0.175]
	point[2] [0.125 0.175]
	point[3] [0.125 0.825]
	point[4] [0.175 0.825]
	point[5] [0.175 0.875]
	point[6] [0.825 0.875]
	point[7] [0.825 0.825]
	point[8] [0.875 0.825]
	point[9] [0.875 0.175]
	point[10] [0.825 0.175]
	point[11] [0.825 0.125]
	z [3.8 4]
  )

  #pole-lid
  block(
	points 12
	point[0] [0.175 0.125]
	point[1] [0.175 0.175]
	point[2] [0.125 0.175]
	point[3] [0.125 0.825]
	point[4] [0.175 0.825]
	point[5] [0.175 0.875]
	point[6] [0.825 0.875]
	point[7] [0.825 0.825]
	point[8] [0.875 0.825]
	point[9] [0.875 0.175]
	point[10] [0.825 0.175]
	point[11] [0.825 0.125]
	z [4.4 4.6]
  )

#=========================Middle=======================

  #middle
  block(
	points 4
	point[0] [0 0]
	point[1] [1 0]
	point[2] [1 1]
	point[3] [0 1]
	z [5 5.2]
  )

#============================Big cones===========================

  #cone 1
  block(
	points 4
	point[0] [0 0]
	point[1] [0.1 0]
	point[2] [0.1 0.1]
	point[3] [0 0.1]
	z [5.2 5.8]
  )

  #cone 2
  block(
	points 4
	point[0] [0.9 0]
	point[1] [1 0]
	point[2] [1 0.1]
	point[3] [0.9 0.1]
	z [5.2 5.8]
  )

  #cone 3
  block(
	points 4
	point[0] [0.9 0.9]
	point[1] [1 0.9]
	point[2] [1 1]
	point[3] [0.9 1]
	z [5.2 5.8]
  )

  #cone 4
  block(
	points 4
	point[0] [0 0.9]
	point[1] [0.1 0.9]
	point[2] [0.1 1]
	point[3] [0 1]
	z [5.2 5.8]
  )

#============================small cones=========================

  #cone-wall 1
  block(
	points 4
	point[0] [0.1 0]
	point[1] [0.9 0]
	point[2] [0.9 0.05]
	point[3] [0.1 0.05]
	z [5.2 5.6]
  )

  #cone-wall 2
  block(
	points 4
	point[0] [0.95 0.1]
	point[1] [1 0.1]
	point[2] [1 0.9]
	point[3] [0.95 0.9]
	z [5.2 5.6]
  )

  #cone-wall 3
  block(
	points 4
	point[0] [0.1 0.95]
	point[1] [0.9 0.95]
	point[2] [0.9 1]
	point[3] [0.1 1]
	z [5.2 5.6]
  )

  #cone-wall 4
  block(
	points 4
	point[0] [0 0.1]
	point[1] [0.05 0.1]
	point[2] [0.05 0.9]
	point[3] [0 0.9]
	z [5.2 5.6]
  )

#==========================upper half===============================

  #pole 1
  block(
	points 4
	point[0] [0.125 0.125]
	point[1] [0.175 0.125]
	point[2] [0.175 0.175]
	point[3] [0.125 0.175]
	z [5.2 9.4]
  )

  #pole 2
  block(
	points 4
	point[0] [0.825 0.125]
	point[1] [0.875 0.125]
	point[2] [0.875 0.175]
	point[3] [0.825 0.175]
	z [5.2 9.4]
  )

  #pole 3
  block(
	points 4
	point[0] [0.825 0.825]
	point[1] [0.875 0.825]
	point[2] [0.875 0.875]
	point[3] [0.825 0.875]
	z [5.2 9.4]
  )

  #pole 4
  block(
	points 4
	point[0] [0.125 0.825]
	point[1] [0.175 0.825]
	point[2] [0.175 0.875]
	point[3] [0.125 0.875]
	z [5.2 9.4]
  )

  #pole-lid
  block(
	points 12
	point[0] [0.175 0.125]
	point[1] [0.175 0.175]
	point[2] [0.125 0.175]
	point[3] [0.125 0.825]
	point[4] [0.175 0.825]
	point[5] [0.175 0.875]
	point[6] [0.825 0.875]
	point[7] [0.825 0.825]
	point[8] [0.875 0.825]
	point[9] [0.875 0.175]
	point[10] [0.825 0.175]
	point[11] [0.825 0.125]
	z [5.6 5.8]
  )

  #pole-lid
  block(
	points 12
	point[0] [0.175 0.125]
	point[1] [0.175 0.175]
	point[2] [0.125 0.175]
	point[3] [0.125 0.825]
	point[4] [0.175 0.825]
	point[5] [0.175 0.875]
	point[6] [0.825 0.875]
	point[7] [0.825 0.825]
	point[8] [0.875 0.825]
	point[9] [0.875 0.175]
	point[10] [0.825 0.175]
	point[11] [0.825 0.125]
	z [6.2 6.4]
  )

  #pole-lid
  block(
	points 12
	point[0] [0.175 0.125]
	point[1] [0.175 0.175]
	point[2] [0.125 0.175]
	point[3] [0.125 0.825]
	point[4] [0.175 0.825]
	point[5] [0.175 0.875]
	point[6] [0.825 0.875]
	point[7] [0.825 0.825]
	point[8] [0.875 0.825]
	point[9] [0.875 0.175]
	point[10] [0.825 0.175]
	point[11] [0.825 0.125]
	z [6.8 7]
  )

  #pole-lid
  block(
	points 12
	point[0] [0.175 0.125]
	point[1] [0.175 0.175]
	point[2] [0.125 0.175]
	point[3] [0.125 0.825]
	point[4] [0.175 0.825]
	point[5] [0.175 0.875]
	point[6] [0.825 0.875]
	point[7] [0.825 0.825]
	point[8] [0.875 0.825]
	point[9] [0.875 0.175]
	point[10] [0.825 0.175]
	point[11] [0.825 0.125]
	z [7.4 7.6]
  )

  #pole-lid
  block(
	points 12
	point[0] [0.175 0.125]
	point[1] [0.175 0.175]
	point[2] [0.125 0.175]
	point[3] [0.125 0.825]
	point[4] [0.175 0.825]
	point[5] [0.175 0.875]
	point[6] [0.825 0.875]
	point[7] [0.825 0.825]
	point[8] [0.875 0.825]
	point[9] [0.875 0.175]
	point[10] [0.825 0.175]
	point[11] [0.825 0.125]
	z [8 8.2]
  )

  #pole-lid
  block(
	points 12
	point[0] [0.175 0.125]
	point[1] [0.175 0.175]
	point[2] [0.125 0.175]
	point[3] [0.125 0.825]
	point[4] [0.175 0.825]
	point[5] [0.175 0.875]
	point[6] [0.825 0.875]
	point[7] [0.825 0.825]
	point[8] [0.875 0.825]
	point[9] [0.875 0.175]
	point[10] [0.825 0.175]
	point[11] [0.825 0.125]
	z [8.6 8.8]
  )

  #pole-lid
  block(
	points 12
	point[0] [0.175 0.125]
	point[1] [0.175 0.175]
	point[2] [0.125 0.175]
	point[3] [0.125 0.825]
	point[4] [0.175 0.825]
	point[5] [0.175 0.875]
	point[6] [0.825 0.875]
	point[7] [0.825 0.825]
	point[8] [0.875 0.825]
	point[9] [0.875 0.175]
	point[10] [0.825 0.175]
	point[11] [0.825 0.125]
	z [9.2 9.4]
  )

#=================================top===================================

  #top-bit
  block(
	points 4
	point[0] [0.25 0.5]
	point[1] [0.45 0.5]
	point[2] [0.45 0.7]
	point[3] [0.25 0.7]
	z [9.4 11]
  )

  block(
	points 4
	point[0] [0.55 0.45]
	point[1] [0.75 0.45]
	point[2] [0.75 0.75]
	point[3] [0.55 0.75]
	z [9.4 10.7]
  )

  block(
	points 4
	point[0] [0.3 0.2]
	point[1] [0.6 0.2]
	point[2] [0.6 0.4]
	point[3] [0.3 0.4]
	z [9.4 10.3]
  )

  block(
	points 11
	point[0] [0.825 0.175]
	point[1] [0.875 0.125]
	point[2] [0.875 0.875]
	point[3] [0.125 0.875]
	point[4] [0.125 0.125]
	point[5] [0.875 0.125]
	point[6] [0.825 0.175]
	point[7] [0.175 0.175]
	point[8] [0.175 0.825]
	point[9] [0.825 0.825]
	point[10] [0.825 0.175]
	z [9.4 10]
  )

#================gear 1 ====================

  block(
	points 4
	point[0] [0.875 0.125]
	point[1] [1 0.125]
	point[2] [1 0.20833325]
	point[3] [0.875 0.20833325]
	z [6.6667 7.3333]
  )

  block(
	points 4
	point[0] [0.875 0.20833325]
	point[1] [1 0.20833325]
	point[2] [1 0.2916665]
	point[3] [0.875 0.2916665]
	z [6.3333 7.6667]
  )

  block(
	points 4
	point[0] [0.875 0.2916665]
	point[1] [1 0.2916665]
	point[2] [1 0.458333]
	point[3] [0.875 0.458333]
	z [6 8]
  )

  block(
	points 4
	point[0] [0.875 0.458333]
	point[1] [1 0.458333]
	point[2] [1 0.54166625]
	point[3] [0.875 0.54166625]
	z [6.3333 7.6667]
  )

  block(
	points 4
	point[0] [0.875 0.54166625]
	point[1] [1 0.54166625]
	point[2] [1 0.6249995]
	point[3] [0.875 0.6249995]
	z [6.6667 7.3333]
  )

#======================gear 2=====================

  block(
	points 4
	point[0] [0.125 0.875]
	point[1] [0.20833325 0.875]
	point[2] [0.20833325 1]
	point[3] [0.125 1]
	z [7.6667 8.3333]
  )

  block(
	points 4
	point[0] [0.20833325 0.875]
	point[1] [0.2916665 0.875]
	point[2] [0.2916665 1]
	point[3] [0.20833325 1]
	z [7.3333 8.6667]
  )

  block(
	points 4
	point[0] [0.2916665 0.875]
	point[1] [0.458333 0.875]
	point[2] [0.458333 1]
	point[3] [0.2916665 1]
	z [7 9]
  )

  block(
	points 4
	point[0] [0.458333 0.875]
	point[1] [0.54166625 0.875]
	point[2] [0.54166625 1]
	point[3] [0.458333 1]
	z [7.3333 8.6667]
  )

  block(
	points 4
	point[0] [0.54166625 0.875]
	point[1] [0.6249995 0.875]
	point[2] [0.6249995 1]
	point[3] [0.54166625 1]
	z [7.6667 8.3333]
  )

  cmd(pose [ 0.00 0.000 0 0.000 ])
)
