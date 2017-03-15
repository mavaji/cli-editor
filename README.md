# stringlist
A simple cli editor using an internal linked list data structure.<br>
It comprises of 5 commands:<br> 
* `i <line_number> <text>` for insert a line
* `a <line_number> <text>` for append to a line
* `d <line_number>` for delete a line
* `l <from_line_number> <to_line_number>` for list lines
* `e` for exit

Sample run:
```
Command:~$i 1 first line
Command:~$i 2 second line
Command:~$i 3 third line
Command:~$l 1 3
---------------------------------------------------------------------------
first line
second line
third line
---------------------------------------------------------------------------
Command:~$a 1  some extra text
Command:~$l 1 3
---------------------------------------------------------------------------
first line some extra text
second line
third line
---------------------------------------------------------------------------
Command:~$d 2
Command:~$l 1 2
---------------------------------------------------------------------------
first line some extra text
third line
---------------------------------------------------------------------------
Command:~$e
---------------------------------------------------------------------------
first line some extra text
third line
---------------------------------------------------------------------------
Program Ended!
```