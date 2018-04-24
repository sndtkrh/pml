Axiom [](p->q)->([]p->[]q)
US #0 ~(p/\q)->~q q
Axiom p->(~(p/\q)->~q)
G #2
MP #3 #1
US #0 r q
US #5 ~(p/\q) p
US #6 ~q r
Axiom (a->b)->(b->c)->(a->c)
US #8 []p a
US #9 [](~(p/\q)->~q) b
US #10 []~(p/\q)->[]~q c
MP #4 #11
MP #7 #12
Axiom (a->(b->c))->(a->(~c->~b))
US #14 []p a
US #15 []~(p/\q) b
US #16 []~q c
MP #13 #17
Axiom <>p<->~[]~p
US #19 q p
Axiom (a->b->c)->(d<->b)->(a->d->c)
US #21 []p a
US #22 ~[]~q b
US #23 ~[]~(p/\q) c
US #24 <>q d
MP #18 #25
MP #20 #26
US #19 p/\q p
Axiom (a->b->c)->(d<->c)->(a->b->d)
US #29 []p a
US #30 <>q b
US #31 ~[]~(p/\q) c
US #32 <>(p/\q) d
MP #27 #33
MP #28 #34
Axiom (a->b->c)->((a/\b)->c)
US #36 []p a
US #37 <>q b
US #38 <>(p/\q) c
MP #35 #39
// #40  |- (([]p/\<>q)-><>(p/\q))
