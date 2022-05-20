
# Ancestor tree

#### Portfolio assessment AIS1002 - Ancester tree
This is the final project by two students taking part of the subject "Object-oriented programming and algorithms" on NTNU Ålesund during spring 2022

|  |  |
|--|--|
| Group Number | **11** |  
| Candidate Numbers	 | **10014**,  **10016**|
| Institution Number | **194** |
| Subject | **Object-oriented programming and algorithms** |
| Subject Code	| **AIS1002** |



---  
This tool to allows a user to generate an ancestor diagram. You can either use the example console application to build  a tree, or use the library to build your own application. The tree is template based, which means you are not forced to  create an ancestor tree of people. Maybe you want to track organize the ancestors of your dog? You can either build up  from scratch or load an existing tree stored in a .JSON-file. <br>

## Limitations
* This tree only allows for two parents, this is by purpose and as of given terms in the assignment
* The tree can save to file but as for now, json is the supported format. Feel free to contribute by making support for other file-types
* The date-class is a very simple one and has some major limitations. It does not handle leap year, which reduces possibilities like calculating days between dates and accounting for 29th of february.

## User instructions
Provided in the "src"-folder is a console application provding an example of usage of this tree-library.
Starting this application you will be presented with a welcome message and the main menu with the following options:

1. **Show tree**
   If there one or more nodes in the tree, this option will print out the tree with indentation to represent relations.
   The output in the tree is decided by the type of nodes stored in tree, but will always show a node index. For people, the output will be full name (+ the node index). Example:
```cpp
Rot Rotesen [1]
       Mor Morsen [2]
           Mormor Besta Bestemorsen [5]
                   Oldemor Oldemorsen [8]
                   Oldefar Oldingen Oldefarsen [9]
           Bestefar Bestefarsen [4]
   Far Faren Farsen [3]
           Farfar Farfarsen [6]
           Farmor Farmorsen [7]
```

3. List item

As mentioned, you are able to load and save the tree to a json-file. Here is an example of what that would look like:

``` json  
 {  
 "nodes": [  
 {  
 "data": {  
 "birth": "22-06-1999",  
 "death": null,  
 "firstName": "Me",  
 "middleName": "Myself",  
 "lastName": "Fatherson",  
 "isAlive" : false  
 },  
 "treeIndex" : 1,  
 "leftIndex": 2,  
 "rightIndex": 3,  
 "isRoot": true  
 },  
 {  
 "data": {  
 "birth": "11-03-1968",  
 "death": null,  
 "firstName": "Mom",  
 "lastName": "Mother",  
 "age" : null,  
 "isAlive" : false  
 },  
 "treeIndex" : 2,  
 "leftIndex": null,  
 "rightIndex": null,  
 "isRoot": false  
 },  
 {  
 "data": {  
 "birth": "08-02-1965",  
 "death": null,  
 "firstName": "Dad",  
 "middleName": "Daddy",  
 "lastName": "Dadsen",  
 "age" : null,  
 "isAlive" : false  
 },  
 "treeIndex" : 3,  
 "leftIndex": null,  
 "rightIndex": null  
 // No "isRoot" property means isRoot = false  
 },  
    
 ],  
 "tree": {  
 "settings": {  
 "globalIndent": 8  
 }  
 }  
}  
  
```  

## UML


## Credits

### Json-library
Licensed under the MIT License <http://opensource.org/licenses/MIT>.
SPDX-License-Identifier: MIT
Copyright (c) 2013-2022 Niels Lohmann <http://nlohmann.me>.

JSON for Modern C++
version 3.10.5  
https://github.com/nlohmann/json

### Menu-class

The menu-class is self-written but highly inspired by:  
["Menu Class - Example of Modern C++ STL features"](https://www.cppstories.com/2018/07/menu-cpp17-example/)

### Github Actions and Catch2 Testing

The setup of GitHub actions and Catch2-testing would not be possible without an example:
["Markaren - Pathfinding"](https://github.com/AIS1002-OOP/Pathfinding)

