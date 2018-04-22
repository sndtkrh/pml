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

## 様相言語
| シンボル | 意味 |
|:-:|:--|
| 英小文字からなる文字列 | 命題変数 |
| `T` | 真を意味する命題定数 |
| `F` | 偽を意味する命題定数 |
| `~` | 否定 |
| `[]` | ボックス |
| `<>` | ダイヤモンド |
| `->` | 含意 |
| `<->` | 論理的同値 |
| `/\` | 論理積 |
| `\/` | 論理和 |
