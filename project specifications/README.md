# Course Project

The goal of the course project is to solidify the foundational C++ knowledge obtained in this course by designing and 
implementing a functional, larger-scope software system. The project topic has been chosen to necessitate the use of 
a wide array of language concepts and features we studied/will study.

## Submission Instructions
Push your solution files to your Github project repository. Only commits made before the deadline will be considered.

You will have to compile C++ code to build executables so that you can test your code, but **don't** submit 
these executables (or any object files that might be built). To make things easier, you can use a 
[Gitignore file](https://docs.github.com/en/get-started/getting-started-with-git/ignoring-files) and have it ignore all files with extensions `.o` or `.bin` (and any other extensions you might want to ignore).

Your code must compile. This is a programming class so you're not going to get too many points for code that 
doesn't compile even if you have some logic figured out. So if you have only understood some of the logic, make sure
you make it compile so that you can get points for it.

## Grading

**Your project code is due by midnight (CST), Friday, May 3rd.** This is a hard deadline, so please plan ahead for this.
Note that your Github repo will specify the deadline in UTC so it might look like you have more time, but please don't be misled by this.

Additionally, during finals week you will have to schedule a 10 minute meeting either with the instructor 
or the TA to explain your code. Your grade will be 
dependent on how you do in this meeting. See 
[below](#project-meeting) for more details.

As per the syllabus, **the project constitutes 30% of your total grade** (see also [Extra Credit](#extra-credit)). The project will be graded out of 100 points and 
the grade will be a function of the following criteria:

| Project Evaluation Criteria | Grade Percentage | Explanation | 
| ----------------------------- | --------------------- | -------------- |
| Functional requirements | 70% | Does the delivered software satisfy the project's stated functional requirements? |
| Quality of the final executable | 10% | Absence of errors during the normal execution, as well as graceful handling of error conditions. | 
| Test coverage | 10% | Handling of corner cases. |
| Documentation | 10% | User-facing documentation and developer documentation, including comments in your code.

### Project Meeting
You must schedule a 10 minute meeting with the 
instructor/TA through [this](https://calendly.com/arjunvish/project-meeting) link.
The objective of this meeting is for you to explain your code, your design choices, and answer 
any questions we might have. This will help us understand your code better. This meeting isn't independently graded but 
your project grade will be wieghted on your explanation of your code. The bar to do well in this meeting will 
be set pretty low, but you will have had to put the effort into building your project to reach this bar.

## Project definition

The project objective is to **build an interactive command line program that (crudely) simulates a small terrestrial 
ecosystem** according to the rules below. 

The core notion of the simulator is that of an iteration: a single "step" of the simulation during 
which the ecosystem transforms itself to its next state according to its [rules](#ecosystem-rules) (think 
[Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)).

An ecosystem is defined by two inputs:
  - a rectangular [map of the area](Area-Map.md) that describes the (initial) location of the living organisms 
  (plants and animals) that populate the area;
  - a [list of species](Species.md) populating the ecosystem, together with their characteristics. 

The ecosystem map and the list of species are loaded from the corresponding files provided to the program 
as command line arguments in this order: the path of 
the file containing the map is the first command-line 
argument, and that of the file containing the species list is the second command-line argument.

Running the simulator starts a new simulation session. Within a single simulation session, the user can select to 
run a single iteration, or a "batch" of several iterations at once (e.g. 10 or 100 iterations). After each run, the 
simulator prints the session's current ecosystem state to the console. The user can then choose to continue the 
simulation session (by doing another run), or exit.

### Ecosystem rules

1. During each iteration every organism in the ecosystem gets a chance to perform its living functions (move, 
grow, consume). 
2. Animals move around the ecosystem to find food, but they cannot move over plants or other animals 
(unless they are consuming them). All animals move with the same speed (one block per iteration). They can't move 
diagonally. An animal has to move if it can.
3. Plants remain static and don't spread into new areas.
4. Each living organism has an associated number of "energy points" it gives to the organism that consumes it.
5. Plants don't eat other organisms; herbivores eat only plants; omnivores eat herbivores and plants.
6. Plants that have been eaten regrow in the same location according to their "regrowth coefficient"; for example, a 
plant with a regrowth coefficient of 2 regrows in two iterations. A plant cannot regrow if its location is currently occupied by an animal. Furthermore, a plant can't be consumed in a partially grown state.
7. Animals that have been eaten are removed from the simulation.
8. Each animal has a current energy level as well as a "max" energy level that limits the number of energy points 
they can absorb. All animals start the simulation with a current energy level equal to their "max" level. Each move 
subtracts one point from their current energy level. An animal with zero energy points dies and is removed from the 
simulation. 
9. An animal can consume another organism only if it can add the organism's energy points/energy level to its energy 
level without going over its "max" limit. To consume another organism, the consumer has to move to the organism's 
position.
10. Animals act in their own interest: e.g. if an animal is in danger of being eaten, it'll try to escape; if 
it's running out of energy, it'll seek to replenish it, etc.
11. An animal can see its immediate vicinity (adjacent blocks only), and it can identify predator and prey. It follows 
these rules (in the same order) to determine how to move:
    * If it sees a predator it moves in the opposite  direction, as long as it has at least one unit of energy and space to move.
    * If it sees a prey and it can consume it, it moves to consume the prey.
    * Otherwise, it moves arbitrarily in some direction.

### Compilation and Organization

You don't need to use FastX to code the project but **make sure** your project builds and runs using the versions of 
Make (`GNU Make 4.4.1`) and g++ (`g++ (GCC) 13.2.1`) that are installed in FastX. You can either clone and run your 
repository within FastX to make sure of this, or update your versions to the ones mentioned above. Differences in 
compiler versions lead to weird behaviors sometimes so please ensure compatibility. If your code doesn't compile
with the FastX compiler version, it will be considered as non-compiling (which won't get you too many points).


Your project repo should be organized as follows:
* The `src` directory at the project root (top directory) will contain all source files (.cpp and .h files).
* The `src` directory must contain a `Makefile` so that 
    1.  running `make` in the `src` directory creates the binary `ecosystem.bin` in it. This is the binary that will be 
        called with the input files as command line arguments (your project executable). You will have many .cpp and 
        .h files, and you could, in theory, create one `make` recipe that simply calls `g++` on all these files but 
        this is very inefficient for compilation and will slow down your development. If you change the code in one 
        of your files, running `make` will recompile all your files. The `make` software was made to avoid such 
        repetition. Separate the compilation of all your files so that you avoid unnecessary recompilation;
    2.  running `make clean` removes all object files, binaries, and any other files created as a side-effect of
        compilation;
    3.  running `make sample` will call your binary (`ecosystem.bin` on the input files [map.txt](map.txt) and 
        [species.txt](species.txt)) which are also present in the `input` directory of your project repo.
* The `input` directory at the project root will contain text input files (for maps and species lists). Feel free to add more 
tests there.
* The project root should also contain a `README.md` that specifies how your sources can be built, and usage details for 
your binary. This is a *Markdown* file and you can find some basic Markdown usage instructions 
[here](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet) but don't spend too much time on it. You only 
need very basic Markdown knowledge for your documentation.
* The root will contain also a `DevDocs.md` for developer documentation. Document details about your code organization, design 
decisions and data structures here.


### External Libraries
You don't need to create complicated data structures from scratch, you can reuse the ones from the 
standard library, or other libraries. Otherwise, we want you to use the concepts taught in class. If you are 
going to use any libraries to make any of your tasks easier, 
1. make sure to check with us to see whether it will be okay to use them
2. document clearly which library you're using and what you're using it for.

### Documentation

Write organized, well-documented, and well-commented code. Apart from counting for a percentage of the grade, this will 
help you with your implementation. The individual concepts you need to apply for this project might be straightforward, 
but there will be so many of them that you will need to write a significant amount of code. Useful comments will help you 
when you return to previously written code. 

See also the requirements for `README.md` and `DevDocs.md` files in the [Compilation and Organization](#compilation-and-organization) section.

### Testing

The input map and species list given to you represent one possible ecosystem that you can simulate. 
Make sure you test on maps of other sizes and compositions, with different species lists.
[Here](./map2.txt) is a larger map with the same set 
of species for testing.

### Extra Credit

You will have an opportunity to get 5% of your course grade in extra credit through the project. The specification of extra credit
is intentionally left open-ended. Any feature that enhances some aspect of the project and goes beyond satisfying the project requirements can be considered for extra credit. Please add an `Extra Credit` section in your `README.md` that specifies your 
case for extra credit.
Some ideas:
- Create a script that generates maps based on a list of species and other parameters (specify how to use your script).
- Add features to your implementation to create more 
interesting behaviors of organisms. Be careful with this, 
added features should still comply with project requirements. Best way to do this is to check with us
whether an added feature could give you extra credit, and 
not reduce your grade instead.

### Design and Implementation Choices
The rules constrain many of the choices you have to make, but this is a large project, so many choices are still open. For 
example, we are not telling you what data structures to use and you will have to pick a few to store information. 

Implementation details are also not fully specified. For example, many of the rules address animal movement, but there are 
still choices you have to make to fully implement movement. Many of these are intentional ommisions - we want you to 
think about these design choices.

However, it is possible, as always, that things are unintentionally underspecified. When in doubt, ask questions on Slack 
and during office hours. This project specification is stored in a repository that is separate from your project repo, and 
updates might be made to the specifications as we have discussions about it. [Errata.md](Errata.md) will store any changes 
that are made to the initial project specification so that you can keep track of changes that have been made after the 
project specification was published.

When you are making choices that were not specified, document them clearly. 

## Project Division

As long as you satisfy the specification (and are able to explain your code), you will satisfy the project requirements. In 
this section, we specify incremental goals that you can follow in your implementation. This is just one way of implementing 
your project, and you don't have to follow it. But if you are going to submit something incomplete, it will serve your grade 
better to complete as many of these goals as possible.

### Part 1
1. Define a class hierarchy for organisms, plants, and animals (finding a way to differentiate herbivores and omnivores).
2. Write functions to parse the species file and the map, and create a unique organism object for each organism in the map, 
and store details such as
    * a unique way to identify each organism on the map
    * the species type that it belongs to from the [species file](species.txt) ('a', 'A', .etc.)
    * the type of organism (plant/herbivore/omnivore)
    * other details about it from the species file (this will depend on which type of organism it is)
    * its location on the map
3. Depending on how you store each organism's details, write one or more functions to print them back on to the 
screen, that can be called from `main`. Add commented calls to these functions in `main`.
4. Write a function to print the current state of the map. In this part, you will simply be printing the map that 
is parsed from the input file, but you should be storing the map in a data structure and printing it back from 
the data structure. This function should be callable from `main`. Add a commented call to this function in `main`.
5. Document all your functions. Your documentation should explain:
    * how the function works
    * the line numbers to uncomment to test your function

    Also document the data structures that you use to store and access information about your ecosystem.

### Part 2
Implement animal movement based on the relevant rules. At this stage, consumption doesn't necessarily need to work but 
animals should still be motivated by predator and prey in their surroundings (and by their own energy levels) to move as 
specified by the rules. Also add the interface to be able to iterate through the map to see the animals move.

### Part 3
Implement consumption (and death) of organisms based on the relevant rules.

### Part 4
Implement plant regrowth based on their regrowth coefficient.

### Part 5
Any remaining details not covered by the previous parts should be implemented at this stage. Think also about your front-end requirements if you haven't already.