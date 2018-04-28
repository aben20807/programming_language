:- discontiguous is_prime/1.
is_prime(2).
is_prime(3).
is_prime(P) :-
    integer(P), P > 3,
    P mod 2 =\= 0,
    \+ has_factor(P, 3).
is_p(P) :-
    is_prime(P), write('yes'), nl.
is_p(P) :-
    \+ is_prime(P), write('no'), nl.

has_factor(N, L) :-
    N mod L =:= 0.
has_factor(N, L) :-
    L * L < N,
    L2 is L + 2,
    has_factor(N, L2).

main :-
    write('Input: '),
    flush_output,
    read(X),
    write('Output: '),
    flush_output,
    is_p(X),
    flush_output,
    halt.

:- initialization(main).
