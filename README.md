# LEX22

This lab exercise builds off the code in an earlier lab exercise. The bugs engineered into the code for that exercise have been removed.

In this exercise you will experiment with the code to restructure it in various ways to better understand the impact this has on the efficiency of the code and the quality of the performance informationreported by the tools.

You will now run through steps, each containing several tasks.  Put answers to questions into the [LEX22 response form](https://docs.google.com/forms/d/e/1FAIpQLSeRgeHM3rPsqYMW5nuUV4GoPAGXd0LYD7fZbcHhd8HMOhP3TA/viewform?usp=sf_link).

## Resources
[gprof documentation](https://sourceware.org/binutils/docs/gprof/)

[gcov documentation](https://gcc.gnu.org/onlinedocs/gcc/Gcov.html)

[callgrind documentation](https://www.valgrind.org/docs/manual/cl-manual.html)

[Stanford CS107 callgrind page](https://web.stanford.edu/class/archive/cs/cs107/cs107.1194/resources/callgrind)

## Step 1
Make a subdirectory named `step1`, and move the output files created along the way into this subdirectory.  Before proceeding to step 2 be sure to add/commit/push these files to the remote repo on GitHub.

### gprof and gcov
Run `make andRunPerformance`.  Copy the output files produced by gprof and gcov into lthe `step1` subdirectory, *before proceeding on to run callgrind*.  This is important, as `make andRunCallGrind` invokes `make clean` and will remove these output files.  If you accidentally remove them you will need to re-create them.

Answer the questions [gprof 1] and [gcov 1] in the response form.

### callgrind
Run `make andRunCallGrind`.  Run callgrind_annotate to produce output files as indicated in the the questions [callgrind 1a] and [callgrind 1b] in the response form.  Answer these questions, and then copy the output files produced by callgrind_annotate into lthe `step1` subdirectory.

### hotspots
Answer [hotspots 1] in the response form.



## Step 2
Make a subdirectory named `step2`, and move the output files created along the way into this subdirectory.  Before proceeding to step 3 be sure to add/commit/push these files to the remote repo on GitHub.

Now we are going to refactor the code so that the hotspots are isolated in separate functions. To refactor code is to change the design of the code in a way that preserves functionality.

** In past semesters students had to perform these code transformations on their own, and this took far more time than I intended, and distracted from the main point of this LEX: to run the tools and explore what they can tell us about program performance.  This semester we'll see how things go with the code transformations being provided to you.

To do this step, first open the counts.c file.  Find the code that is delimited by the two lines `// >>>> TASK STEP 11.1` and `// <<<< TASK STEP 11.1`. Refactor so that the code between these lines is put into its own function and replaced by the function call `shiftBuffer(buffer, size-1);`. The function shiftBuffer should be defined this way:
```c
void shiftBuffer(char * buffer, int size) {
  for (int j=0; j<size; j++) {
    buffer[j] = buffer[j+1];
  }
}
```

Find the code that is delimited by the two lines `// >>>> TASK STEP 11.2` and `// <<<< TASK STEP 11.2`. Refactor so that the code between these lines is put into its own function and replaced by the function call and assignment `ch = lowerCase(ch);`.  The function lowerCase should be defined this way:
```c
char lowerCase(char ch) {
    if ('A' <= ch && ch <= 'Z') {
      ch = ch - 'A' + 'a';
    }
    return ch;
}
```

Run `make andRunTests`.  All the tests should pass. If they do not you probably did not get the refactoring correct. Fix the problem before continuing.

### tools

#### gprof and gcov
Run `make andRunPerformance`.  Copy the output files produced by gprof and gcov into lthe `step2` subdirectory, *before proceeding on to run callgrind*.

#### callgrind
Run `make andRunCallGrind`.  Run callgrind_annotate to produce the two output files like you did in step 1.  Answer these questions, and then copy the output files produced by callgrind_annotate into lthe `step2` subdirectory.

Answer questions [tools 2a], [tools 2b], and [tools 2c] in the response form.

### hotspots
Answer [hotspots 2] in the response form.

### refactoring
Answer [refactoring 2] in the response form.



## Step 3
Make a subdirectory named `step3`, and move the output files created along the way into this subdirectory.  Before proceeding to step 4 be sure to add/commit/push these files to the remote repo on GitHub.

Modify the shiftBuffer function so that rather than just shift the buffer one position and then return, it repeatedly shifts the buffer one position until a space is shifted into position 0, or until the entire buffer has been shifted (i.e. there was no space in buffer past position 0 to start with).  If there was no space, then the buffer should be cleared in the same way that happens when a match is found.

There are a few modifications we need to make to the code to make this work.  First, we need to modify the ```shiftBuffer``` function so it repeatedly shifts until the whole buffer has been shifted, or a space has been shifted into postition 0; here's one way (there are surely others):

```c
int shiftBuffer(char * buffer, int size) {                                                                                                                            
  int shiftSize = 0;
  for (; shiftSize < size; shiftSize++) {                                                                                                                             
    for (int j=0; j<=size; j++) {                                                                                                                                     
      buffer[j] = buffer[j+1];                                                                                                                                        
    }                                                                                                                                                                 
    if (buffer[0] == ' ') {                                                                                                                                           
      break;                                                                                                                                                          
    }                                                                                                                                                                 
  }                                                                                                                                                                   
}                                                                                                                                                                     
```

Also, in the ```countWord``` function we need to ensure that the variable ```k``` is properly updated, and that we incorporate the last character read from the file into the right spot in the buffer:

```c
      else {
        // >>>> TASK STEP 11.1                                                                                                                                        
        shiftBuffer(buffer, size-1);
        // <<<< TASK STEP 11.1                                                                                                                                        
        for (int i=0; i<size; i++) {
          if (buffer[i]=='\0') {
            k = i;
            break;
          }
        }
        buffer[k++] = ch;
      }
```


Run `make andRunTests`.  All the tests should pass. If they do not you probably did not get the code changes correct. Fix the problem before continuing.

### tools

#### gprof and gcov
Run `make andRunPerformance`.  Copy the output files produced by gprof and gcov into the `step3` subdirectory, *before proceeding on to run callgrind*.

#### callgrind
Run `make andRunCallGrind`.  Run callgrind_annotate to produce the two output files like you did in step 1.  Answer these questions, and then copy the output files produced by callgrind_annotate into lthe `step3` subdirectory.

### hotspots
Answer [hotspots 3] in the response form.

### impact
Answer [impact 3] in the response form.

## Step 4
Make a subdirectory named `step4`, and move the output files created along the way into this subdirectory.  Before proceeding to step 5 be sure to add/commit/push these files to the remote repo on GitHub.

Modify the ```shiftBuffer``` function so that rather always shifting by one, the shift is done in one shot. Do this by finding the offset to the next space in the buffer, or if there isn't one, to the end of the buffer (or call ```clearBuffer```).

Here's one way to change the ```shiftBuffer``` function:

```c
void shiftBuffer(char * buffer, int size) {
  int shiftSize = 1;
  // determine how much we need to shift the buffer by
  for (; shiftSize < size; shiftSize++) {                                                                                                                             
    if (buffer[shiftSize] == ' ') {                                                                                                                                   
      break;                                                                                                                                                          
    }                                                                                                                                                                 
  }
  // shift the buffer
  for (int j=0; j<=size-shiftSize+1; j++) {                                                                                                                           
    buffer[j] = buffer[j+shiftSize];                                                                                                                                  
  }                                                                                                                                                                   
}                                                                                                                                                                     
```

Run `make andRunTests`.  All the tests should pass. If they do not you probably did not get the code changes correct. Fix the problem before continuing.

### tools

#### gprof and gcov
Run `make andRunPerformance`.  Copy the output files produced by gprof and gcov into the `step4` subdirectory, *before proceeding on to run callgrind*.

#### callgrind
Run `make andRunCallGrind`.  Run callgrind_annotate to produce the two output files like you did in step 1.  Answer these questions, and then copy the output files produced by callgrind_annotate into lthe `step4` subdirectory.

### hotspots
Answer [hotspots 4] in the response form.

### impact
Answer [impact 4] in the response form.

## Step 5
Answer the three reflection questions, [Reflection 5a], [Reflection 5b], and [Reflection 5c], in the response form.

# Wrapping up
Ensure that you have added, committed, and pushed your files to the remote repo on GitHub.

Also give your feedback on the [LEX 22 Feedback Form](https://docs.google.com/forms/d/e/1FAIpQLScYPszsg-tygGhAqocCJWK7Z5ZEOY1gzdTFKC90VjnmcGK4gg/viewform?usp=sf_link).
