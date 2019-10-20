DECLARE SUB printlines(n AS INTEGER)
DECLARE FUNCTION countspaces%(s AS STRING)
DECLARE FUNCTION factorial%(n AS INTEGER)

CLS
PRINT "Printing 3 empty lines"
printlines 3

name$ = "harry kumar potter"
PRINT "Spaces in "; name$; ": "; countspaces%(name$)

'a recursive function
num% = 6
PRINT "Factorial of"; n; ": "; factorial%(num%)


SUB printlines(n AS INTEGER)
FOR i% = 1 TO n
PRINT
NEXT
END SUB

FUNCTION countspaces%(s AS STRING)
count% = 0
FOR i% = 1 TO LEN(s)
IF MID$(s, i%, 1) = " " THEN count% = count% + 1
NEXT
countspaces% = count%
END FUNCTION

FUNCTION factorial%(n AS INTEGER)
factorial% = 1
IF n <= 1 THEN EXIT FUNCTION
factorial% = n * factorial%(n - 1)
END FUNCTION
