lower(daisies, med, wet, yellow).
flower(roses, med, dry, red).
flower(petunias, med, wet, pink).
flower(daffodils, med, wet, yellow).
flower(begonias, tall, wet, white).
flower(snapdragons, tall, dry, red).
flower(marigolds, short, wet, yellow).
flower(gardenias, med, wet, red).
flower(gladiolas, tall, wet, red).
flower(bird_of_paradise, tall, wet, white).
flower(lilies, short, dry, white).
flower(azalea, med, dry, pink).
flower(buttercup, short, dry, yellow).
flower(poppy, med, dry, red).
flower(crocus, med, dry, orange).
flower(carnation, med, wet, white).
flower(tulip, short, wet, red).
flower(orchid, short, wet, white).
flower(chrysanthemum, tall, dry, pink).
flower(dahlia, med, wet, purple).
flower(geranium, short, dry, red).
flower(lavender, short, dry, purple).
flower(iris, tall, dry, purple).
flower(peonies, short, dry, pink).
flower(periwinkle, med, wet, purple).
flower(sunflower, tall, dry, yellow).
flower(violet, short, dry, purple).
flower(zinnia, short, wet, yellow).

plantassign(0, []).
plantassign(N, [H|T]) :-
    N > 0,
    flower(H, _, _, _),  % pick a species name
    N1 is N - 1,
    plantassign(N1, T).


uniquecheck(List) :-
    all_unique(List).

all_unique([]).
all_unique([H|T]) :-
    \+ member(H,T),
    all_unique(T).


colorcheck([]).
colorcheck([_]).
colorcheck([H1,H2|T]) :-
    flower(H1, _, _, C1),
    flower(H2, _, _, C2),
    C1 \= C2,
    colorcheck([H2|T]).


sizecheck([]).
sizecheck([_]).
sizecheck([H1,H2|T]) :-
    flower(H1, S1, _, _),
    flower(H2, S2, _, _),
    size_ok(S1,S2),
    sizecheck([H2|T]).

size_value(short,1).
size_value(med,2).
size_value(tall,3).

size_ok(S1,S2) :-
    size_value(S1,V1),
    size_value(S2,V2),
    Diff is abs(V1 - V2),
    Diff =< 1.


wetcheck(N,List) :-
    N >= 4,
    length(List,N),
    nth1(1,List,F1),    flower(F1,_,dry,_),
    nth1(N,List, FN),   flower(FN,_,dry,_),
    nth1(2,List,F2),    flower(F2,_,wet,_),
    N1 is N-1,
    nth1(N1,List,FN1),  flower(FN1,_,wet,_).


writegarden([]).
writegarden([H|T]) :-
    write(H), write(' '),
    writegarden(T).


gardenplan(N,List) :-
    plantassign(N,List),
    uniquecheck(List),
    colorcheck(List),
    sizecheck(List),
    wetcheck(N,List),
    writegarden(List), nl.
