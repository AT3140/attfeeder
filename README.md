# attfeeder
For Quick Attendance!

=========================
Build
g++ src.cpp att.h ui.h att.cpp ui.cpp -o att
.\att -db pt_attendees.txt -csv att.csv
-v option for validation
=========================
Commands
-----------------------------------------
#UI
d <date>: set date and start marking
start: start marking open interface 2 (deprecated)	
r : render into the given csv
exit: exit application
------------------------------------------
#DateUI
rm <name>: unmark attendee
exit: close date and switch to interface 1
l: lists all attendees (validate)
m: print marked attendees for all dates
clear: clears all marked entries in the given date no column for this date is created during rendering if empty
==========================