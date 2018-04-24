# PML -- Proof Assistant for Modal Logic

これは様相論理の証明支援システムです．

## コンパイルに必要なもの

- CMake
- C++ 14 以降に対応した C++ コンパイラ

g++ 5 以上でコンパイルできることを確認しています．

## コンパイルとインストール

Linux と Mac では以下の方法でインストールできます．

```bash
$ git clone https://github.com/sndtkrh/pml.git
$ cd ./pml
$ mkdir ./build
$ cd ./build
$ cmake ..
$ make
$ make install
```

## 様相言語

| シンボル | 読み方 |
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

## 推論規則

| 規則 | 構文 | 操作 |
|:-:|:-:|:-|
| modus ponens | `MP #n #m` | 既に証明されている n 番目の論理式 φ と m 番目の論理式 φ→ψ から ψ を得る |
| uniform substitution | `US #n φ p` | 既に証明されている n 番目の論理式の命題変数 p に論理式 φ を一様代入したものを得る |
| generalization | `G #n` | 既に証明されている n 番目の論理式 φ から □φ を得る |


## 例

例えば □p∧□q→□(p∧q) の証明は以下のように行います．
`>>` の後に続く文字列がユーザの入力です．
この証明は [1] を参考にしました．

```
$ pml
PML -- A Proof Assistant for Modal Logic
Axioms are :
(<>p<->~[]~p)
([]p<->~<>~p)
([](p->q)->([]p->[]q))
>> Axiom p->(q->(p/\q))
#0  |- (p->(q->(p/\q)))
>> G #0
#1  |- [](p->(q->(p/\q)))
>> Axiom [](p->q)->([]p->[]q)
#2  |- ([](p->q)->([]p->[]q))
>> US #2 q->(p/\q) q
#3  |- ([](p->(q->(p/\q)))->([]p->[](q->(p/\q))))
>> MP #1 #3
#4  |- ([]p->[](q->(p/\q)))
>> US #2 r q
#5  |- ([](p->r)->([]p->[]r))
>> US #5 q p
#6  |- ([](q->r)->([]q->[]r))
>> US #6 p/\q r
#7  |- ([](q->(p/\q))->([]q->[](p/\q)))
>> Axiom (a->b)->(b->c)->(a->c)
#8  |- ((a->b)->((b->c)->(a->c)))
>> US #8 []p a
#9  |- (([]p->b)->((b->c)->([]p->c)))
>> US #9 [](q->(p/\q)) b  
#10  |- (([]p->[](q->(p/\q)))->(([](q->(p/\q))->c)->([]p->c)))
>> US #10 []q->[](p/\q) c
#11  |- (([]p->[](q->(p/\q)))->(([](q->(p/\q))->([]q->[](p/\q)))->([]p->([]q->[](p/\q)))))
>> MP #4 #11
#12  |- (([](q->(p/\q))->([]q->[](p/\q)))->([]p->([]q->[](p/\q))))
>> MP #7 #12
#13  |- ([]p->([]q->[](p/\q)))
>> Axiom (a->(b->c))->((a/\b)->c)
#14  |- ((a->(b->c))->((a/\b)->c))
>> US #14 []p a
#15  |- (([]p->(b->c))->(([]p/\b)->c))
>> US #15 []q b
#16  |- (([]p->([]q->c))->(([]p/\[]q)->c))
>> US #16 [](p/\q) c
#17  |- (([]p->([]q->[](p/\q)))->(([]p/\[]q)->[](p/\q)))
>> MP #13 #17
#18  |- (([]p/\[]q)->[](p/\q))
>> Q
```

## 参考文献

1. Patrick Blackburn, Maarten de Rijke and Yde Venema, Modal Logic, Cambridge University Press, 2002

## License
