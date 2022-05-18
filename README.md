# Ancestor tree
Mappeinnlevering AIS1002 - Forfedretre <br>
Gruppe 11 <br>
Kandidat 10014 og 10016

This tool to allows a user to generate an ancestor diagram. 
You can either use the example console application to build a tree, or 
use the library to build your own application. 
The tree is template based, which means you are not forced to create an ancestor tree of people. 
Maybe you want to track organize the ancestors of your dog?
You can either build up from scratch or load an existing tree stored in a .JSON-file. <br>

## Limitations
* This tree only allows for two parents
## User instructions

---

As mentioned, you are able to load and save the tree to a json-file. 
Here is an example of what that would look like:


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




## Credits

---
### Json-library
Licensed under the MIT License <http://opensource.org/licenses/MIT>. <br>
SPDX-License-Identifier: MIT <br>
Copyright (c) 2013-2022 Niels Lohmann <http://nlohmann.me>. 

JSON for Modern C++ <br>
version 3.10.5 <br>
https://github.com/nlohmann/json <br><br>

### Menu-class
The menu-class is self-written but highly inspired by: <br> 
["Menu Class - Example of Modern C++ STL features"](https://www.cppstories.com/2018/07/menu-cpp17-example/) <br><br>


### Github Actions and Catch2 Testing
The setup of GitHub actions and Catch2-testing would not be possible without an example: <br> 
["Markaren - Pathfinding"](https://github.com/AIS1002-OOP/Pathfinding) <br>



