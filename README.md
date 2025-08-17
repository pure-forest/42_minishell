## Minishell - A 42 school coding project
Minishell is a project focusing on replicating the main function of a shell (in our case, Bash) built with C and Makefile. This project is co-developed with @boggem, where we split the work into parsing and execution. I took over the responsibility of parsing the she took over the execution part. 


## Setup Instructions
To compile this project, you will need `cc` `build-essentail` and `libreadline` on your linux system. If you don't have them yet, you can install the package by running the following commands:
```
sudo apt-get update
sudo apt-get install build-essential
sudo apt-get install libreadline-dev 
```
After cloning the repository to your computer, you can start by compiling the executable by running `make` in the terminal. The executable will be compiled into the root directory named as `minishell`. Simply execute the binary by `./minishell` and the program will start. You can run all the possible commands the same way like you did with other shell. For exmaple:
```
ls
echo
cat
grep
cd
```
There is a supression file under suppression directory, which is designed to run along with valgrind tool (installing by running `suodo apt-get install valgrind`) to check for memory leak. If you want to check it, you can run with
```
valgrind --leak-check=full --track-fds=yes --show-reachable=yes --suppressions=suppresion/readline.supp ./minishell
```
You can exit the program by either press ctrl+D or type `exit` in the terminal. 

## Reflection
This was a 4-week-long sprint-like intensitive proejct built during my studies in Hive Helsinki. Project goal was to understand how bash behaves behind the scence and how to handle complicated string manipulation. 

The biggest challenge in parsing is to think about all the edge cases among input string especially there are quotes and expansion to be considered. Due to scope limitation and time constrain, the minishell didn't handle all the cases like other shell can handle, for example `cat Makefile ; echo hello` or any unclosed quotes or pipe. But I did get a taste of how does it feel to consider for so many things while still needs to consider for coding norm required by the school. 

Another challenge is team communication. Since it's a project that neither of us had experience with before, we need to stumble and experiment about what to pass to each other in case of data. We had several times that we failed to communicate what is exactly expected after parsing and what is expected to handle in execution. But after some mistakes and trial, we managed to have a mutual agreement on what the struct of the data will look like. 

I am very proud of this project due to the extensive coverage of cases for string processing and the overall orchestration of the code. 