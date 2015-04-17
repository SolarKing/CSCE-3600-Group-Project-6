# CSCE-3600-Group-Project-6
*for SPRING SEMSTER 2015*

This is the repo for the CSCE 3600 Group Project (Group 6)

###Group Members:
Member              | Email
--------------------|-----------
Charles Bido        | *[Email Me](charlesbido@my.unt.edu)*
Sam Epstein         | *[Email Me](snepstein@gmail.com)*
Mayur Kotamraju     | *[Email Me](mayur.kotamraju@gmail.com)*
(TJ) Emanuel Taylor | *[Email Me](ejt0062@unt.edu)*

#Project Overview

For this term project, we are building a trace-driven cache memory simulator. For
those unfamiliar with caches, a cache is a small, hardware-controlled static memory
located close to the main processor. Cache speeds up the overall system performance. Due
to its small capacity, not all data can be stored in cache.

Therefore, selected pieces of information (usually the most-used data) are stored there. The overall
goal for this project is to create a tool that simulates cache memory's behavior using a memory trace.

The trace gives:

1. a memory reference and 
2. whether this memeory reference is being read or written.

With this information, you will simulate the cache's behavior, not the cache itself.

I have split the project into three parts:

1. a Parser module,
2. a simulation core module, and
3. a reporter module

Each module adds more freatures on top of previous ones, so it is imperative that
your team have a working version of previous modules when designing a subsequent module.

Each module has a detail section with implementation details. For each module, you
team must submit a progress report and its source code.

##Two important details to consider
1. **Submission Dates**
  - Your team can find these at the top of this document.
2. **Project Goals:**
  - Create a good teamwork environment.
  - Get familiar with software engineering practices.
  - Work with Object-Oriented programming in C++.
  - Be more knowledgeable in cache technology.

#Background

Here are some resources that can give you a better idea of cache memories:

**Books**

- Computer Organization and Design: The Hardware and Software Interface, Patterson and Hennessy
- Computer Architecture: A quantitative Approach, Patterson and Hennessy
- Advanced COmputer Architecture: Parallelism, Scalability, Programmablilty, Kai Hwang

**Web Pages**

- [Wikipedia](http://en.wikipdia.org/wiki/CPU_cache#Direct-mapped_cache)

**Video**

- [Direct mapping](https://www.youtube.com/watch?v=VePK5TNgQU8) **NEW**
- [Direct mapped cache memory](https://www.youtube.com/watch?v=bTj0vFs8ndI)
- [Memory hierarchy and cache memory lecture](https://www.youtube.com/watch?v=T4VVC3eeZI0)

#Implementation Details

This project will be developed modularly:

- a parser module
- a simulation core module, and
- a reporter module

Each module defines its own classes and methods. The parser module reads memory reference traces.

It is also responsible for reading input parameters into the simulator. The trace must be read from standard input.

The core simulation module is responsible for the simulation itself. This module decides where each memory refrenece should be placed and decides if there is a miss or hit in the cache (see in more detail how the cache works in the background section).

Finally, the reporter module is the one that creates the output for the user with the results of the execution.

In the following section, we describe in detail what exactly needs to be done for each submission part.

In addition, you will be provided with three items:

1. a sample memory trace that is short, about 100 lines
  - we can use this small trace to test our development
2. a big trace so we can check for performance and consistency
3. a template c++ file

## Part 1 - Due on 03/13/2015 11:59 PM

What is wanted for this part of the project is the following items:

- the program should be able to parse the input trace file
- the program should be able to accept the following parameters:
  - `-sizeL1 xx` *The size of the L1 cache in bytes. It should validate a power of 2*
  - `-sizeL2 xx` *The size of the L2 cache in bytes. It should validate a power of 2, and it should be bigger than L1*
  - `-type direct/full` *Identifies the cache type*
  - `-write-policy through/back` *Tells the writing policy*
- The program must display an on-screen report that shows the following information:

**Input:**

```bash
  $>./program -sizeL1 500 -sizeL2 1000 -type direct < trace.tr
```

**Output:**

```bash
  Input Prameters read:
  SizeL1 500
  SizeL2 1000
  Type Direct
    Memory refreneces read from file
    100 Total
    50 Reads
    50 Write
```

##Part 2 - Due on 04/17/2015 11:59 PM

Level1 (L1) cache, the closest cache to the processor, is the smallest but fastest memory. For Part 2 your team needs to implement an L1 cache and simulation. The details of how the cache works are explained on section 2 of this document. What is wanted for this module is:

- Build a direct-map cache implementation.
- Resize the cache memory to the size specified on the input 
parameters.
- Display on the screen the same information as required in Part 1, 
- Add a hit and miss results to the screen report.

Example:

**Input:**

```bash
  $>./program -sizeL1 500 -sizeL2 1000 -type direct < trace.tr
```

**Output:**

```bash
  Input Prameters read:
  SizeL1 500
  SizeL2 1000
  Type Direct
    Memory refreneces read from file
      100 Total
      50 Reads
      50 Write
    Simulation Execution
      70% hits
      30% misses
```

##Part 3 – Due on 05/08/2015 11:59 PM

L2 caches assists L1 caches to store data. For part 3, you need to implement an L2 cache. The explanation of how L2 cache works is detailed on the resources on section 2. What is wanted for this section is:

- Enable  L2  cache memory  simulation.
- Write write-back  and write-trough  policies
- Enable  a full associativity.
- Enable  a replacement policy.
- Display on your Report screen the same information as part 2, plus a hit and miss results for L2 cache.

Example:

**Input:**

```bash
  $>./program -sizeL1 500 -sizeL2 1000 -type direct < trace.tr
```

**Output:**

```bash
  Input Prameters read:
  SizeL1 500
  SizeL2 1000
  Type Direct
    Memory refreneces read from file
      100 Total
      50 Reads
      50 Write
    Simulation Execution
      L1
        70% hits
        30% misses
      L2
        60% hits
        40% misses
```

#Submitting and Grading

###Submitting Your Work

1. Each part of the project will be submitted through BlackBoard on the specified date. 

2. On every submission, the files to upload will contain:
  * Working source code for the corresponding part.
  * The code must compile (not working code wont be graded).
  * The code must be package in a zip file.
  * User Documentation. 
  * Description how to compile your program.
  * Description on how to use your program.
  * List of Features.
  * Maintenance documentation.
  * Block diagram describing the interaction of your components.
  * Description of your classes.
  * Description of your methods.

### Grading Your Work

The work  your  team  submits will  be  graded  as  follows:

Content       | Grade
--------------|-----------
Program       | 80%
Documentation | 20%
