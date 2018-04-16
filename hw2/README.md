# HW2

## Usage

```sh
$ sbcl --script diff.lsp
```

## Goal

+ Implement the `diff` command.
+ Can compare the different text between file1.txt and file2.txt.

## Algorithm

+ LCS

## Architecture

+ In main
  + Call read-file-to-list(filename) twice to get two lists from file1 and 2.
  + Call lcs(l1 l2) to get the LCS positions in two list.
  + Call printdiff(l1pos l2pos l1 l2) to print out diff result.

## Reference

+ [Longest Common Subsequence](http://www.csie.ntnu.edu.tw/~u91029/LongestCommonSubsequence.html)
+ [LISP - File I/O](https://www.tutorialspoint.com/lisp/lisp_file_io.htm)
+ [Lisp make-array](https://www.tutorialspoint.com/lisp/lisp_arrays.htm)
+ [Printing contents of array LISP](https://stackoverflow.com/a/9254931/6734174)
+ [increment or decrement a number](https://stackoverflow.com/a/3736113/6734174)
+ [terminal color output](http://www.lispforum.com/viewtopic.php?f=2&t=420#p2779)
