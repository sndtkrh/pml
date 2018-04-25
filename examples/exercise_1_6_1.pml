Axiom [](p->q)->([]p->[]q)
US #^ ~(p/\q)->~q q
Axiom p->(~(p/\q)->~q)
G #^
MP #^ #1
US #0 r q
US #^ ~(p/\q) p
US #^ ~q r
Axiom (a->b)->(b->c)->(a->c)
US #^ []p a
US #^ [](~(p/\q)->~q) b
US #^ []~(p/\q)->[]~q c
MP #4 #^
MP #7 #^
Axiom (a->(b->c))->(a->(~c->~b))
US #^ []p a
US #^ []~(p/\q) b
US #^ []~q c
MP #13 #^
Axiom <>p<->~[]~p
US #^ q p
Axiom (a->b->c)->(d<->b)->(a->d->c)
US #^ []p a
US #^ ~[]~q b
US #^ ~[]~(p/\q) c
US #^ <>q d
MP #18 #^
MP #20 #^
US #19 p/\q p
Axiom (a->b->c)->(d<->c)->(a->b->d)
US #^ []p a
US #^ <>q b
US #^ ~[]~(p/\q) c
US #^ <>(p/\q) d
MP #27 #^
MP #28 #^
Axiom (a->b->c)->((a/\b)->c)
US #^ []p a
US #^ <>q b
US #^ <>(p/\q) c
MP #35 #^
Name #^ f
