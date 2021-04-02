# Minishell_42

## What is a shell? :thinking: ## 
  Basically in an operating system there are these two elements:
  <br>
    * The kernel (= kernel): which performs the fundamental functions of 
                    the operating system such as memory management, processes, files ...
  <br>
    * The shell: At its base, a shell is simply a macro processor that executes commands. 
                -The term macro processor means functionality where text and symbols are expanded to create larger expressions.
                -A Unix shell is both a command interpreter and a programming language. 

## This Project Majerly Include :open_file_folder: ##

**Parsing**

        2. The separations
        1. Pipes
        3. Command and arguments
        4. Protections
        5. The <,>, >> redirects
        6. Environment variables
      
**The execution**


    1. Redirects
    2. Env, export, unset
    3. Exit and $?
    4. Pipes / signals / process links 

## Best Ressources ##
    -https://medium.com/@nickolasteixeira/want-to-build-a-simple-shell-heres-how-you-do-it-75890647bae8
    -https://medium.com/dev-genius/lets-build-a-linux-shell-part-i-954c95911501
    -https://medium.com/better-programming/how-bash-works-8424becc12f3
    -https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html
    -https://man7.org/linux/man-pages/dir_all_by_section.html
    -https://unix.stackexchange.com/questions/159513/what-are-the-shells-control-and-redirection-operators
    -https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html
    -https://www.geeksforgeeks.org/pipe-system-call/?ref=rp
    -https://www.geeksforgeeks.org/wait-system-call-c/?ref=rp
    -https://www.geeksforgeeks.org/fork-system-call/?ref=rp
    -http://www-igm.univ-mlv.fr/~dr/NCSPDF/chapitre11.pdf
    -https://www.geeksforgeeks.org/making-linux-shell-c/
    -https://www.quora.com/What-is-the-3rd-parameter-in-the-main-function-char-envp#:~:text=The%20non%2Dportable%2Dbut%2D,As%20always%2C%20I%20recommend%20experimenting
    -https://chrtophe.developpez.com/tutoriels/minisysteme/#L11
    -https://stackoverflow.com/questions/6697753/difference-between-single-and-double-quotes-in-bash
    -https://brennan.io/2015/01/16/write-a-shell-in-c/
    -https://www.youtube.com/watch?v=5BE9qM79fgM
    -https://sites.cs.ucsb.edu/~manish/discussion/week2.pdf
    -https://www.geeksforgeeks.org/chdir-in-c-language-with-examples/ Important
    -https://theswissbay.ch/pdf/Gentoomen%20Library/Programming/Bash/O%27Reilly%20bash%20CookBook.pdf

## To Test ##
     Run : make && ./minshell
