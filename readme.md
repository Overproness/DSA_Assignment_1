# DSA Assignment 1

## Task 1

### Approach

1. Circular Linked List (optional): A linked list where each process (node) links to the next. The last process points back to the first. Technically we could have accomplished this task even without a circular linked list cause we have the start and the end nodes of the list stored in the LinkedList Class.
2. Process Removal: If a process's remaining_time becomes zero, it is removed from the linked list. We could've just added a condition to just ignore the ones that had zero time left but we didn't
3. Dynamic Process Addition: New processes can be added while the scheduler is running, simulating real-world scenarios. I did the optional Task as well.
4. Output: After every cycle, the scheduler displays the process ID and the remaining time for each process. We didn't quite copy the output showed by Sir in the document but we made it close enough

### Assumptions

So we just kinda assumed the amount of time_per_process_per_cycle. We could have input in from the user. But it doesn't make that much of a difference.

### Challenges in Task 1:

It was mid-difficulty. So nothing really challenging.

## Task 2

### Approach

1. Linked List Storage: The 1024-bit number is split into smaller 32-bit integers, with each node storing one of these segments of the big number.
2. Primality Test: Implemented a primality test (Miller-Rabin test) that operates across multiple nodes, ensuring the entire number is tested for primality.
3. Smaller Primes: Used smaller prime numbers to perform preliminary checks, improving the efficiency of the primality test.

### Assumptions

We used 32 32-bit integers (cause 32 x 32 = 1024). I think it would've been better to use u_int64_t implementation but I ASSUMED that we were not doing bit manipulation so I opted for simple unsigned int. And a 32-bit number is just an int. So we used unsigned int cause we don't need the negative numbers. We didn't complex algos to generate random numbers. We just used rand() function to generate 32 bit-chunks of random numbers. And then applied the simple implementation of Miler-Rabin Primality Test on it.

### Challenges faced in Task 2:

There were a lot of challenges.

1. Even the simplest implementation for 1024 bit-number involved the use of u_int64_t or u_int32_t, but we didn't need that so I had to figure that out myself. That we could just make use of simple int cause it takes 32 bits in 32 bit OSs.
2. There was no implementation of Miler Rabin primality test online that used linked list. So that was a problem.
