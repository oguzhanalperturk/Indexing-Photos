# Indexing-Photos
This assignment is about binary search tree ADT, in particular AVL Tree. This program creates an index of a given list of photos. 
I am given a list of photos in an external text file called “photos.txt”. In this text file, there are some real photos extracted from the google photos database. 
This file includes the following information: 
-name of the photo
-dimension of the photo
-size of the photo
-name of the city that the photo has been taken 
-name of the country that the photo has been taken
-year that the photo has been taken.
Each part is separated by a "," character. 
I processed this file, and generated an AVL tree based on the country name. If there is  more than one photo with the same country, they should then be stored together in the same  node. Based on this data representation, I wrote a program that provides some functionalities to the user.
