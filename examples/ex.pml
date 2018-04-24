Axiom p->(q->(p/\q))
G #0
Axiom [](p->q)->([]p->[]q)
US #2 q->(p/\q) q
MP #1 #3
US #2 r q
US #5 q p
US #6 p/\q r
Axiom (a->b)->(b->c)->(a->c)
US #8 []p a
US #9 [](q->(p/\q)) b
US #10 []q->[](p/\q) c
MP #4 #11
MP #7 #12
Axiom (a->(b->c))->((a/\b)->c)
US #14 []p a
US #15 []q b
US #16 [](p/\q) c
MP #13 #17
