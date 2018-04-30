input_edge(N) :-
    N > 0
    ->readln([A|Remain]),
        nth0(0, Remain, B),
        assert(edge(A, B)), % Two direction.
        assert(edge(B, A)),
        input_edge(N - 1)
    ;readln([M|_]),
        input_query(M).

input_query(M) :-
    M > 0
    ->readln([A|Remain]),
        nth0(0, Remain, B),
        reachable(A, B),
        input_query(M - 1)
    ;main.

reachable(A, B) :-
    A = B,                  % If A and B are the same node than reachable.
    write('yes'), nl.
reachable(A, B) :-
    walk(A, B, [])
    ->write('yes'),nl
    ;write('no'), nl.

walk(A, B, Path) :-
    edge(A, X),
    \+ memberchk(X, Path),  % Check if visited.
    (B = X
    ;walk(X, B, [A|Path])   % Add A into visited Path.
    ).

main :-
    % trace,                % DEBUG
    readln([N|Remain]),
    nth0(0, Remain, E),
    integer(N),
    input_edge(E).

:- initialization(main).
