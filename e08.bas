PRINT "Vote count:"
OPEN "votes.csv" FOR INPUT AS 1
WHILE NOT EOF(1)
INPUT #1, state$, count%
PRINT state$; " provided"; count%; " votes"
WEND
CLOSE #1
PRINT

OPEN "expenses.txt" FROM APPEND AS 2
PRINT #2, "butter", 450
PRINT #2, "cashew", 950
CLOSE #2

PRINT "Alice in Wonderland:"
OPEN "alice.txt" FOR INPUT AS 2
DO WHILE NOT EOF(2)
LINE INPUT #2, line$
PRINT line$
LOOP
CLOSE #2
PRINT
