# Concurrent-sorting-using-semaphores
Compilation:
	gcc CSORT.c -o CSORT -lpthread -lrt
Run:
	./CSORT
	
In order to run the code, please
first ensure you have the CSORT.c, Makefile in the same directory.

and then type in the terminal of the following 2 commands in order to compiling and running the program:

	gcc CSORT.c -o CSORT -lpthread -lrt
	./CSORT
	

To change the input array in order to run the program for various test cases, please enter different arrays when the program is asking you for entering the data and that array is of 7 size.


TEST CASE:

   TEST #1 :
		Input:
			Debug mode (y/n)? : n
			Please enter 7 alphabet characters : XAzMWyd
		Output:
			Array before sorting: XAzMWyd
			Array after sorting: admwxyz

 TEST #2:
		Input:
			Debug mode (y/n)? : y
			Please enter 7 alphabet characters : XAzMWyd
	            Output:
			
                       Process 1 swapped array[0] and array[1] with values a and x respectively. 
                       Process 3 swapped array[2] and array[3] with values m and z respectively.
                       Process 1 swapped array[3] and array[4] with values w and z respectively.
                       Process 2 swapped array[4] and array[5] with values y and z respectively.
                       Process 3 swapped array[5] and array[6] with values d and z respectively.
                       Process 2 swapped array[1] and array[2] with values m and x respectively.
                        Process 3 swapped array[2] and array[3] with values w and x respectively.
                        Process 2 swapped array[4] and array[5] with values d and y respectively.
                        Process 1 swapped array[3] and array[4] with values d and x respectively.
                        Process 3 swapped array[2] and array[3] with values d and w respectively.
                        Process 2 swapped array[1] and array[2] with values d and m respectively.
                        Array after sorting: admwxyz

and same for the 'QHtbUSa'
