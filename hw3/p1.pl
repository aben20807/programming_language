is_prime(2).
is_prime(3).
is_prime(P) :-
    integer(P),
    P > 3,
    P mod 2 =\= 0,
    \+ has_factor(P, 3).

has_factor(N, F) :-
    N mod F =:= 0.
has_factor(N, F) :-
    F * F < N,
    Fnext is F + 2,
    has_factor(N, Fnext).

goldbash(4, 2, 2).
goldbash(N, P1, P2) :-
    N is P1 + P2,
    is_prime(P1),
    is_prime(P2).

search_goldbash(4, 1, 1) :-
    write('2 2'), nl.
search_goldbash(N, P1, P2) :-
    p2loop(N, P1, P2).

p2loop(N, P1, P2) :-
    P2n is P2 + 2,
    N >= P1 + P2n,
    \+ p1loop(N, P1, P2n),
    p2loop(N, P1, P2n).
p1loop(N, P1, P2) :-
    P1n is P1 + 2,
    P1n =< P2,
    query_goldbash(N, P1n, P2).

query_goldbash(N, P1, P2) :-
    goldbash(N, P1, P2),
    write(P1),
    write(' '),
    write(P2), nl,
    main.
query_goldbash(N, P1, P2) :-
    \+ goldbash(N, P1, P2),
    p1loop(N, P1, P2).

main :-
    repeat,
    write('Input: '),
    flush_output,
    read(X),
    write('Output: '),
    flush_output,
    search_goldbash(X, 1, 1),
    fail.

:- initialization(main).
