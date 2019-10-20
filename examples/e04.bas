DECLARE FUNCTION isprime%(n AS INTEGER)
DIM n AS INTEGER

CLS
INPUT "N: ", n

IF isprime%(n) = 1 THEN
PRINT n; " is prime"
ELSE
PRINT n; " is not prime"
END IF


FUNCTION isprime%(n as INTEGER)
DIM i as INTEGER

isprime% = 0
FOR i = 2 TO n - 1
IF n MOD i = 0 THEN EXIT FUNCTION
NEXT

isprime% = 1
END FUNCTION
