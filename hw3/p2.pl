input_relation(N) :-
    N > 0
    ->read(P),
        read(C),
        assert(parent(P, C)),
        input_relation(N - 1)
    ;read(M),
        input_query(M).

input_query(M) :-
    M > 0
    ->read(A),
        read(B),
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

% lca(A, B, X) :-
%     A == B -> X is A;
%     parent(A, B) -> X is A;
%     parent(B, A) -> X is B;
%     ancestor(X, A),
%     ancestor(X, B).
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
    read(N),
    input_relation(N - 1).

:- initialization(main).
