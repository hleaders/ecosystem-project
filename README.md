[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/CQ0jbgGv)
# Course Project
This project aims to demonstrate my knowledge of C++ programming in the form of an animal ecosystem simulator.

# How to run
### To run the program:
- Clone this repository into the editor of your choosing
- Ensure that you have the correct versions of Make (`GNU Make 4.4.1`) and g++ (`g++ (GCC) 13.2.1`) installed on your machine
- Navigate to the `src` directory
- To run the preset sample simulation, enter `make sample` into your terminal and follow the outputted instructions
- To make a custom simulation: 
    - Import your own `{your_map_filename}.txt` and `{your_species_filename}.txt` files into the `input` directory. Make sure your custom map and species files follow the structure of the provided input files.
    - Back in the `src` directory, enter `make clear`, then `make` into your terminal
    - Then, enter `./ecosystem.bin ../input/{your_map_filename}.txt ../input/{your_species_filename}.txt` into your terminal and follow the outputted instructions
# About the project:

While this may not be a masterclass in object-oriented programming, I am pretty proud of it. I made a fair amount of mistakes in planning that came back to bite me in the end, namely overlooking many of the ecosystem rules and making my own and building the code up without many ways to test it, but I never gave up, and I think I have created something passable. 

I think the most notable design choice that I made was storing animals and plants in separate vectors. I did this not because I thought it was the best idea, but because it was the one that I could think through logically. This made it easier for me to handle the issue of plant regrowth after consumption. 

One of the hardest concepts for me to grasp in this class was pointers and memory allocation, and I definitely think that this project helped me get a better understanding of the concept, however I bet there is some malpractice in their usage throughout this project. I also think that my understanding of makefiles and  compilation has increased significantly with this project. Overall, I had a lot of fun with this project and it has been very rewarding to finish it.


This project was brought to you by Diet Coke and a party-sized bag of Peanut Butter M&Ms