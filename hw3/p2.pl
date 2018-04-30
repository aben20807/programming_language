input_relation(N) :-
    N > 0
    ->readln([P|Remain]),
        nth0(0, Remain, C),
        assert(parent(P, C)),
        input_relation(N - 1)
    ;readln([M|_]),
        input_query(M).

input_query(M) :-
    M > 0
    ->readln([A|Remain]),
        nth0(0, Remain, B),
        lca(A, B, X),
        write(X), nl,
        input_query(M - 1)
    ;main.

query_parent(A, B) :-
    parent(A, B)
    ->write('yes'), nl
    ;write('no'), nl.

ancestor(A, B) :-
    parent(A, B).
ancestor(A, B) :-
    parent(X, B),
    ancestor(A, X).

lca(A, B, X) :-
    A == B, X is A.
lca(A, B, X) :-
    ancestor(A, B), X is A.
lca(A, B, X) :-
    ancestor(B, A), X is B.
lca(A, B, X) :-
    ancestor(X, A),
    ancestor(X, B).

main :-
    % trace,                % DEBUG
    % read(N),
    readln([N|_]),
    input_relation(N - 1).

:- initialization(main).
