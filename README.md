# attfeeder
For Quick Attendance!


### Build<br>
g++ src.cpp att.h ui.h att.cpp ui.cpp -o att

=========================<br>

### Run Application<br>
  att -db pt_attendees.txt -csv att.csv<br>
  use -v option for validation of input<br>

=========================<br>

### Commands<br>

#### #UI<br>
  - d \<date>      : set date and switch to DateUI<br>
  - r             : render<br>
  - l             : lists all attendees as in db<br>
  - man           : print manual<br>
  - exit          : exit application

------------------------------------------<br>

#### #DateUI<br>
  - rm \<name>     : unmark attendee by name<br>
  - m             : prints marked attendees for each date<br>
  - count \<ladies> \<gents> : set count<br>
  - clear         : clears all marked entries for current date<br>
  - l             : lists all attendees as in db<br>
  - man           : print manual<br>
  - exit          : switch to (att)<br>

==========================<br>