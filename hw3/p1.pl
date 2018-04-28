% :- discontiguous is_prime/1.
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

query_prime(P) :-
    is_prime(P), write('yes'), nl.
query_prime(P) :-
    \+ is_prime(P), write('no'), nl.

p2loop(N, P1, P2) :-
    N >= P1 + P2,
    P2n is P2 + 2,
    \+ p1loop(N, P1, P2n),
    p2loop(N, P1, P2n).
p1loop(N, P1, P2) :-
    N >= P1 + P2,
    P1n is P1 + 2,
    \+ goldbash(N, P1n, P2),
    p1loop(N, P1n, P2).

goldbash(4, 2, 2).
goldbash(N, P1, P2) :-
    N is P1 + P2,
    is_prime(P1),
    is_prime(P2),
    write(P1),
    write(' '),
    write(P2), nl.
goldbash(N, P1, P2) :-
    % N >= P1 + P2,
    p2loop(N, P1, P2),
    write(P1),
    write(' '),
    write(P2), nl.
    % (
    %     P2n is P2 + 2,
    %     goldbash(N, P1, P2n)
    % );(
    %     P1n is P1 + 2,
    %     goldbash(N, P1n, P2)
    % ).
    % (
    %     P1next is P1 + 2,
    %     P2next is P2 + 2,
    %     P1next > 1,
    %     P2next > 1,
    %     N is P1next + P2next,
    %     is_prime(P1next),
    %     is_prime(P2next)
    % );(
    %     P11next is P1 + 2,
    %     goldbash(N, P11next, P2)
    % );
    % (
    %     P22next is P2 + 2,
    %     goldbash(N, P1, P22next)
    % ),
    % write(P1next), nl,
    % write(P2next), nl.

query_goldbash(N, P1, P2) :-
    goldbash(N, P1, P2), write('yes'), nl.
query_goldbash(N, P1, P2) :-
    \+ goldbash(N, P1, P2), write('no'), nl.

main :-
    repeat,
    write('Input: '),
    flush_output,
    read(X),
    write('Output: '),
    flush_output,
    % write(X), nl,
    query_prime(X),
    goldbash(X, 1, 1),
    % write(P1), nl,
    % write(P2), nl,
    flush_output,
    fail.
    % halt.

:- initialization(main).
