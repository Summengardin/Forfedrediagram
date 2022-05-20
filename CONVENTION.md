# Coding convention<br>

### Name styling:

|||
|---|----------------|
| Va camelCase      me | camelCase      |
| Class private member name | _camelCase     |
| Class name | UpperCamelCase |
| Constants | ALL_CAPS       |
| File naming | lower_case.xxx |

### <br><br>Naming:

Variable naming shall be describing and in english. <br>

Use verbs in front of names to describe functionality, example: <br>

* "setName" and "getName"
* "isRoot" or "hasChildren" for booleans

### <br><br>Code style:

Using clang-format base on Microsoft with a few modifications:

``` .clang-format
BasedOnStyle: Microsoft
AllowShortFunctionsOnASingleLine: None
BreakBeforeBraces: Custom
BraceWrapping:
  SplitEmptyFunction: false
  SplitEmptyRecord: false
BreakConstructorInitializers: BeforeComma
MaxEmptyLinesToKeep: 2
```

