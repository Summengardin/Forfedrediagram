# Forfedrediagram
Mappeinnlevering AIS1002 - Forfedretre <br>

* Tillater bare to foreldre

## Description

---
Tool to build your family tree. Build up from scratch or load an existing tree stored in a .JSON-file. <br>

Example .JSON-file:

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
                "age" : 22,
                "isDead" : false
            },
            "treeIdx" : 1,
            "leftIdx": 2,
            "rightIdx": 3
        },
        {
            "data": {
                "birth": "11-03-1968",
                "death": null,
                "firstName": "Mom",
                "lastName": "Mother",
                "age" : null,
                "isDead" : false
            },
            "treeIdx" : 2,
            "leftIdx": null,
            "rightIdx": null
        },
        {
            "data": {
                "birth": "08-02-1965",
                "death": null,
                "firstName": "Dad",
                "middleName": "Daddy",
                "lastName": "Dadsen",
                "age" : null,
                "isDead" : false
            },
            "treeIdx" : 3,
            "leftIdx": null,
            "rightIdx": null
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



