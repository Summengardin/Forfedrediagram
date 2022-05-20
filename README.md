# Ancestor tree

#### Portfolio assessment AIS1002 - Ancester tree

This is the final project by two students taking part of the subject "Object-oriented programming and algorithms" on
NTNU Ålesund during spring 2022

| | |  
|--|--|  
| Group Number | **11** |    
| Candidate Numbers | **10014**,  **10016**|  
| Institution Number | **194** |  
| Subject | **Object-oriented programming and algorithms** |  
| Subject Code | **AIS1002** |

--- This tool to allows a user to generate an ancestor diagram. You can either use the example console application to
build a tree, or use the library to build your own application. The tree is template based, which means you are not
forced to create an ancestor tree of people. Maybe you want to track organize the ancestors of your dog? You can either
build up from scratch or load an existing tree stored in a .JSON-file. <br>

## Limitations

* This tree only allows for two parents, this is by purpose and as of given terms in the assignment
* The tree can save to file but as for now, json is the supported format. Feel free to contribute by making support for
  other file-types
* The date-class is a simple one and has some major limitations. It does not handle leap year, which reduces
  possibilities like calculating days between dates and accounting for 29th of february.
* In the CLI, once you have set a root, you are not change which node is root. You can edit the data of the root node, or remove the node, but not set a new root

## User instructions

Provided in the "src"-folder is a console application providing an example of usage of this tree-library.  
Starting this application you will be presented with a welcome message and the main menu with the following options:

1. **Show full tree**

If there one or more nodes in the tree, this option will print out the tree with indentation to represent relations.  
For people, the output in the tree will be full name followed by the tree index. Example:

```cpp  
Rot Rotesen [1]  
	Mor Morsen [2] 
		Mormor Besta Bestemorsen [5] 
	Far Faren Farsen [3]  
```  

In this tree "Rot Rotesen" is the root node, and has the index 1. Rot's parents are "Mor Morsen" with index 2, and "Far
Farsen" with index 3. "Mor Morsen" har only one registered parent, "Mormor Besta Bestemorsen", who has the index 5.
Dummy-people will only be represented by their index (see "4. remove person" for more info)

2. **Detailed view**

This option gives you the opportunity to get a more detailed view of a person/multiple people. You will be asked for a
search term and the program will find people containing a name with that search-term. This results in three scenarios;

* If the program finds no matching people, you will return to the main menu.
* If the program finds one matching person, you will see a detailed view of that person with all known information.
* If the program finds multiple matching people you will get a detailed view of all the people found. A sorting option
  gives you the opportunity to sort that view by either index in the tree or by first name


3. **Add person**

With this option you will be able to add new person to the tree. You will then enter all attributes for that person,
which are: First name, Middle name, Last name, Gender, Birth, Death. Some keypoints about these attributes:

* First Name and Last Name are mandatory. You will not be able to add a person without those.
* The other attributes are optional and may therefore be left empty
* Birth and Death are of date type and have to be entered in the format [dd-mm-yyyy]
* Neither Birth og Death may be future dates, and you will get a warning if you try to set Death to be before Birth

If the person you are creating is the first person in the tree it will automatically be set as the root person. If not,
the new person has to be parent to existing person in the tree


4. **Remove person**

To remove a person from the tree, you will first need to enter a search-term to find the person you want to remove. If
your search-term is found on among multiple people you will encounter a sub-menu to choose between all the matching
people. If the person you are removing is a leaf-person (has no registered parents) the person will be removed from the
tree together with its placeholder (node). If the person has at least one parent, det person will be replaced by a
Dummy-person (empty person). This will leave people further down that branch intact. Here is an example of this

```cpp  
 Mor Morsen [2]
    [5]
        Oldemor Oldemorsen [8]
        Oldefar Oldingen Oldefarsen [9] 
```  

Here, the person with index 5 have been removed , and are only left as an empty person. Therefore, "Oldemor Oldemorsen"
and "Oldefar Oldingen Oldefarsen" are still reachable.

5. **Edit person**

Like many other menu options in the tree, editing a person begins with entering a search-term to find the person you
want to edit. However, in this menu-option you can both search by name, or index. This lets you edit an empty person (
described in "4. remove person"). And like remove person, edit person will give you either:

* No person was found, which means no person to edit
* Single match will lead you directly to the editing interface
* Multiple matches will lead you to a sub-menu to select between all the matches

When you have selected the person you want to edit, you will go through det same process as when adding person. The only
difference is that now you have the option to enter "-" to leave the attribute unchanged. For example, if a persons
first name is "Anders" and enter "-" for the first name, first name will still be "Anders".

6. **Load tree from .json-file**

This option will let you load and existing tree from a json-file. Json file must be of the right format or you will get
an error. See provided example for correct format or export a tree from this interface using option <7. Save tree to
.json-file>. An example tree-has been provided and you can choose to load this one when you selevt this menu.

7. **Save tree to .json-file**

This option will let you save your new ancestor tree to a .json-file. Enter your desired filename and the tree will be
saved to a "Output"-folder located in the project folder.


---

### Example json-file

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

![UML-diagram](.github/assets/UML_image.png)

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