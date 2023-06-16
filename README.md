# attfeeder
For Quick Attendance!

=========================
Build
  g++ src.cpp att.h ui.h att.cpp ui.cpp -o att
=========================
Run Application
  .\att -db pt_attendees.txt -csv att.csv
  -v option for validation
=========================
Commands
-----------------------------------------
#UI
  d <date>      : set date and switch to DateUI
  r             : render
  l             : lists all attendees as in db
  man           : print manual
  exit          : exit application
------------------------------------------
#DateUI
  rm <name>     : unmark attendee by name
  m             : prints marked attendees for each date
  count <ladies> <gents> : set count
  clear         : clears all marked entries for current date
  l             : lists all attendees as in db
  man           : print manual
  exit          : switch to (att)
==========================