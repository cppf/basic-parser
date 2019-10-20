'single line if
IF 1 = 1 THEN PRINT "Math wins" ELSE PRINT "Random wins"

'block if
IF 0 = 1 THEN
PRINT "0 = 1"
ELSEIF 1 = 1 THEN
PRINT "1 = 1"
ELSE
PRINT "Neither"
END IF

'for loop
FOR i = 1 TO 10 STEP 2
PRINT i
NEXT

'exit for loop
FOR i = 1 to 10 STEP 2
PRINT i
IF i > 5 THEN EXIT FOR
NEXT

'while loop
i = 1
WHILE i <= 10
PRINT i
i = i + 2
WEND

'do loop (entry control)
i = 12
DO WHILE i <= 10
PRINT i
IF i > 5 THEN EXIT DO
LOOP

'do loop (exit control)
i = 12
DO
PRINT i
LOOP UNTIL i > 10

'ternary condition
i = 12
IF i <= 10 THEN ok = 1 ELSE ok = 0
