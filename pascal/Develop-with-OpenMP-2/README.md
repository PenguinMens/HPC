# Develop-with-OpenMP
Exercises for the OpenMP HPC course.

## Contents
This repository contains several demos and exercises, in c, c++ and fortran.
The c++ examples are stand alone as they showcase using classes with OpenMP,
which do not exist in c (though one can use structs) and fortran (at least earlier
standards). The directories are

 - **Gauss_demo**: showing Gaussian elimination with serial and omp versions along with profiling results.
 - **Workbench**: shows several examples, numbered 1 to n.
 - **Solutions**: OpenMP solutions to the examples

## Updating the code
For your own clarity, we suggest you use git version control.
This allows you to keep track of changes. For a tutorial on git
see https://git-scm.com/docs/gittutorial

We recommend making your own local branch to track the changes
you make.
```
git checkout -b ${user}/myfirstbranch
```

You can then make changes and commit them with
```
git add ${your_list_of_updated_files}
git commit -m "Your message"
```

## Examples
The examples in the workbench showcase updating a simple serial program
**pi-serial.c**. For each example, we suggest you copy the serial version in
Example 1 to the later examples directory, naming the source code as pi-omp.c
pi-omp.f90

The *Makefile* in each directory should compile the code with the appropriate
directives 

## Slides
Slides for the HPC course can be found at ...
