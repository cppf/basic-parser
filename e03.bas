CLS
INPUT "N: ", n%

sum% = 0
FOR i% = 1 TO n%
sum% = sum% + i% ^ 3
NEXT
PRINT "Sigma n^3: "; sum
'n% => n is an INTEGER
