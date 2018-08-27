# HW3

## Environmant
+ language: prolog
+ executable: SWI-Prolog 7.6.4 for Microsoft Windows (64 bit)

## Problem 1
+ Goldbash's conjecture

```bash
$ swipl -q -s p1.pl
Input: 8
Output: 3 5
Input: 4
Output: 2 2
Input: 100
Output: 3 97
^C
```

## Problem 2
+ Lowest Common Ancestor

```bash
$ swipl -q -s p2.pl
```

+ input:

```bash
6    # number of nodes
1 2  # 1 is the parent of 2
2 3  # 2 is the parent of 3
1 4  # 1 is the parent of 4
4 5  # 4 is the parent of 5
4 6  # 4 is the parent of 6
3    # number of queries
3 4  # LCA of 3 and 4
5 6  # LCA of 5 and 6
1 2  # LCA of 1 and 2
^C
```

+ output:
```
1
4
1
```

## Problem 3
+ Reachable

```bash
$ swipl -q -s p3.pl
```

+ input:

```
6 6  # number of nodes and number of edges
1 2  # 1 and 2 are connected
2 3  # 2 and 3 are connected
3 1  # 3 and 1 are connected
4 5  # 4 and 5 are connected
5 6  # 5 and 6 are connected
6 1  # 6 and 1 are connected
2    # numbers of queries
1 3  # 1 and 3 ared connected?
1 5  # 1 and 5 ared connected?
^C
```

+ output:

```
yes
yes
```
