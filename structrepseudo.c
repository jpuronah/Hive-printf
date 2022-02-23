/*
https://csnotes.medium.com/ft-printf-tutorial-42project-f09b6dc1cd0e

	ft_printf is a project that mimics the real printf function.
	Although wide in scope, it’s not a difficult project.

	THINGS TO KEEP IN MIND before starting off:

----Conversions to handle: csdiupxX%----
	
	Flags to handle: 0-.*
	Value to return: length of the printed string (int).

	> man 3 printf
	[..]
	If the 0 and - flags both appear, the 0 flag is ignored. If a precision is 
	given with a numeric conversion (d, i, o, u, x, and X), the 0 flag is 
	ignored.
	[..]

va_list args;
	# declaration

va_start(args, format)	# we initialise it, 
						# passing the name of the variable args and
						# the last known element, in our case format
						# from ft_printf(const char *format,...)

# in our function, every time we encounter a conversion csdipuxX%
# we need to move to that variable (string, char, int etc.) 
# to read its value (see above, ft_print_char)

va_arg(args, int) # every time, we call va_arg()
						# to move to the next variable in memory
						# we pass the name of the variable args and
						# the type of the variable to va_argva_end(args)
						# when we are done, we close this function in 

# this way, see above ft_printf()

Here a quick table for each conversion type:

c = va_arg(args, int)
s = va_arg(args, char *)
d = va_arg(args, int)
i = va_arg(args, int)
u = va_arg(args, unsigned int)
p = va_arg(args, unsigned long)# or 
                               #(unsigned long)va_arg(args, void *);
x = va_arg(args, unsigned int)
X = va_arg(args, unsigned int)

4 — TIPS

*/
