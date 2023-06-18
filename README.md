# attfeeder
For Quick Attendance!

### Build
>g++ src.cpp att.h ui.h att.cpp ui.cpp -o att

-----

### Run Application

>att -db \<file_name> -csv \<file_name.csv><br>
  
use -v option for validation of input

---
Input

Under option -db as an ASCII file<br>
Ex: yoga_attendees.txt
```txt
raj shekhar
ram prakash
prem chand
```
Each line contains single name

-----

Output<br>
```csv
name,date1,date2
raj shekhar,0,0
ram prakash,1,0
prem chand,0,1
```
 
------

### Commands

#### #UI
>(att)
  - d \<date>      : set date and switch to DateUI<br>
  - r             : render<br>
  - l             : lists all attendees as in db<br>
  - man           : print manual<br>
  - exit          : exit application<br>
#### #DateUI 
>(\<date>)
  - \<name> : mark attendee by name<br>
  - rm \<name>     : unmark attendee by name<br>
  - m             : prints marked attendees for each date<br>
  - count \<ladies> \<gents> : set count<br>
  - clear         : clears all marked entries for current date<br>
  - l             : lists all attendees as in db<br>
  - man           : print manual<br>
  - exit          : switch to (att)<br>
