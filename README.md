# PML
様相論理の証明支援システム

## コンパイルに必要なもの
- CMake
- C++ 14 以降に対応した C++ コンパイラ

## コンパイルとインストール
```bash
$ git clone https://github.com/sndtkrh/pml.git
$ cd ./pml
$ mkdir ./build
$ cd ./build
$ cmake ..
$ make
$ make install
```

## 例
```
$ pml
PML -- A Proof Assistant for Modal Logic
Axioms are :
(<>p<->~[]~p)
([](p->q)->([]p->[]q))
>> Axiom p->p
#0  |- (p->p)
>> G #0
#1  |- [](p->p)
>> Axiom [](p->q)->([]p->[]q)
#2  |- ([](p->q)->([]p->[]q))
>> US #2 p q
#3  |- ([](p->p)->([]p->[]p))
>> MP #1 #3
#4  |- ([]p->[]p)
>> 
```
