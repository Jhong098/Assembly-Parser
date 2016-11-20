# This program computes y[i] = m*x[i] + b
# for i = 0 to 9, m = 5, b = 2
# x[] = -4 to +5 in steps of 1

Code:	 1000

# Initialize data values
	SDi 	0, 2000			# i = 0
	SDi	5, 2001			# m = 5
	SDi	2, 2002			# b = 2
	SDi	-4, 2003		# x[0] = -4
	SDi	-3, 2004		# x[1] = -3
	SDi	-2, 2005		# x[2] = -2
	SDi	-1, 2006		# x[3] = -1
	SDi	0,  2007		# x[4] = 0
	SDi	1,  2008		# x[5] = 1
	SDi	2,  2009		# x[6] = 2
	SDi	3,  2010		# x[7] = 3
	SDi	4,  2011		# x[8] = 4
	SDi	5,  2012		# x[9] = 5

# Code to loop over x values and compute y = mx+b

	LD	2000, R2		# Load the loop index
	LD	2001, R3		# Load m
	LD	2002, R4		# Load b
	LDi	2003, R5		# Base address of x[]
	LDi	2013, R6		# Base address of y[]
StartOfLoop1:
	SUBi	R2, 9, R1		# Compute i - 9
	JGZ	R1, [EndOfLoop1]	# If i > 9, exit loop
	LD	R5, R1			# Load x[i]
	MUL	R3, R1, R1		# Multiply by m
	ADD	R4, R1, R1		# Add b
	SD	R1, R6			# Store result in y[i]
	ADDi	R5, 1, R5		# Increment x array address
	ADDi	R6, 1, R6		# Increment y array address
	ADDi	R2, 1, R2		# Increment loop index
	JMP	[StartOfLoop1]	

EndOfLoop1:	

# Data starts here
Data: 2000			# i: 2000
				# m: 2001
				# b: 2002
				# x[]: 2003 to 2012
				# y[]: 2013 to 2022