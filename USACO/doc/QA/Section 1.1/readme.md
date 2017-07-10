FAQ: Why Does The Grader Not Run My Program Correctly?
Please send a "hey, the grader's broken" letter only after you insert debug prints as suggested by the second half of this page. If not, you will just get back a reply saying, "Where are the debug prints?"

My program runs fine on my machine, but not on your grading system. Why is that?

Our grading system is probably running different software than your system, so problems that show up on our system might not show up on yours (and vice-versa, but we don't usually get complaints about those :).

The absolute key point is: Properly-written programs run on many kinds of computers, not just one. It's not the the grader's broken, your program is generally improper in some way.

If the grader disagrees with your computer's output, odds are your computer is being lenient (i.e., your program can subscript out of bounds and that's not a problem for a while) or you have made assumptions about how the input and output work that you have carried through on your computer but they are different from the grading computer's expectations.

It's unlikely the grader is broken (we've been able to fix every program that claims this), but rather your program is probably violating a rule somewhere.

Some of the more common reasons for this to occur:

The grading system limits your data memory to 16 Megabytes. If you are declaring more than 16MB of data, then reduce your usage. The big clue to this as a problem is a runtime under 0.01 seconds.
The grading system limits your stack usage. If you are declaring a lot of stack data (or calling a routine more than 100,000 deep recursively), then reduce your usage. If you think your program might be recursing, insert a print statement to see how 'deep' your recursion is going.
Memory layout differs between machines. Thus, uninitialized variables and array indexing out-of-bounds can, and often do, cause inconsistent behavior. This means that if you declare array named PLANETNAME to have six characters, then PLANETNAME[40] is going to be some memory element far away from what you have properly defined. Side note: input strings can be a bit longer than you might think. Reading in a five-letter word (like 'sheep') from a line in a file might result in seven characters of storage being used: 's', 'h', 'e', 'e', 'p', ' ' (the newline at the end of the line) and '' (the string terminator).
Linux, on which our grading system runs, is much more picky on memory access than Windows. Thus, invalid array indexes and bad pointer dereferences which are allowed on Windows may cause your program to crash under Linux. Alternately, they will corrupt an internal data structure and give the most cryptic error messages like "Can't open /dev/[mumble]".
Extremely rarely, your program declares a variable that is the same name as a system variable (e.g., mmap). The only way to 'discover' this is by reducing your program down to a small segment where the addition of a single declaration causes it to fail. Change the name of that variable :) .
My program runs fine on my machine, but not on your grading system. How can I find where the bug is?

There are a variety of tricks that one can do to discover the bug:

The number one easiest way to identify what's going on is to insert 'debug prints' into your program. If you have, say, four 'main steps', print the intermediate results between each step. At some point, you will see the divergence. Then you can examine the step in question in more detail. It is often at this juncture that a simple index that goes out of bounds -- even if just by one element -- is discovered. Be sure to print to cerr or stderr so your output is not lost if the program terminates prematurely; standard output is buffered and thus not reported in the case of interrupts or signals.
First requirement: print out the input data as you read it to make sure you are reading the input correctly. When this works, comment out the debug prints. This method will catch the popular "wrong input filename" that occurs when your program opens "program.in" but the task name is "ride.in".

Put sanity checks around all array indexing (Pascal does this by default). The assert() (from assert.h) routine is a nice tool for this. assert() fails if the parameter is 0 (false). If this happens, assert will stop the program and print out an error message saying which assert on which line failed. The really nice thing about assert is that you can #define NDEBUG for including assert.h and the assert operations go away, so that you can put a lot of debugging in and not run it when you want the code to be fast. Consider:
     int i, j, quotient;
     i = 8;
     j = 0;
     assert (j != 0);
     quotient = i/j;
or
     int i, j, chessboard[8][8];
     assert (0 <= i);
     assert (0 <= j);
     assert (i < 8);
     assert (j < 8);
Why four statements? Because the compound statement doesn't give you enough data when failure occurs. 
Note that pointers work the same way, you can use the same sort of assert statements to verify validity of pointers.
On the subject of pointers, be sure to check return values of calls to 'system' routines if your program is failing. Often people access the wrong filename, for instance, and fail to check the return value of the 'open' or other call they use.
If your program doesn't crash (i.e., return a segmentation fault, for example), you can add debugging output, which the grading system will return to you. Just print to stdout. Find when the output diverges from the output on your machine and determine what caused the divergence. First debugging output is always something like: cerr << "Program started" << endl;.
If your program does not complete without a 'signal', putting exits at various locations will let you know if it crashes before or after a particular location. Binary searches work quite well to narrow the search down. This is the second big hammer and works great. For example, if you comment out the bottom half of your program and it still crashes, you know the crash occurs in the top half. If it doesn't crash, you know the crash occurs in the bottom half. Of course, as you narraw it down, you may need to partially go through loops partially or stop recursive functions early.
The grading system does limit the amount of output you get back, so you'll probably want to use conditional statements to look at various passes through a loop. Don't be afraid to add extra variables so you can do things like "on the 3,457th pass through this loop, exit."
Be wary of floating point -- just changing the order of floating point operations (as a compiler does) can change floating values. Never compare floating point numbers for equality; use tolerances.
If these aren't good enough to solve your problem, let us know so we can add more of them.
