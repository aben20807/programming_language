input_relation(N) :-
    N > 0
    ->read(P),
        read(C),
        assert(is_parent(P, C)),
        input_relation(N - 1)
    ;read(M),
        input_query(M).

input_query(M) :-
    M > 0
    ->read(A),
        read(B),
        query_parent(A, B),
        input_query(M - 1)
    ;main.

query_parent(A, B) :-
    is_parent(A, B)
    ->write('yes'), nl
    ;write('no'), nl.

main :-
    % trace,
    read(N),
    input_relation(N - 1).

:- initialization(main).
