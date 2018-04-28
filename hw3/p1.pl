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

search_goldbash(4, 1) :-        % Special case.
    write('2 2'), nl,
    main.
search_goldbash(N, P1) :-       % Faster than increasing both P1 and P2.
    P1n is P1 + 2,              % P1 is count from 3.
    P2 is N - P1n,              % P2 is N - P1.
    query_goldbash(N, P1n, P2).

query_goldbash(N, P1, P2) :-
    goldbash(N, P1, P2),
    write(P1),
    write(' '),
    write(P2), nl,
    main.                       % Go back to main and input next integer.
query_goldbash(N, P1, P2) :-
    \+ goldbash(N, P1, P2),
    search_goldbash(N, P1).     % Keep searching.

main :-
    repeat,
    write('Input: '),
    flush_output,
    read(X),            % input need to use '.' to represent end of integer.
    write('Output: '),
    flush_output,
    search_goldbash(X, 1),
    fail.

:- initialization(main).
