[ax]: http://en.wikipedia.org/wiki/Knuth's_Algorithm_X "Knuth's Algorithm X - Wikipedia, the free encyclopedia"
[dl]: http://en.wikipedia.org/wiki/Dancing_Links "Dancing Links - Wikipedia, the free encyclopedia"
[ec]: http://en.wikipedia.org/wiki/Exact_cover "Exact cover - Wikipedia, the free encyclopedia"

--------------------------------------------------------------------------------
# 概要

## [Exact Cover Problem][ec]

Exact Cover Problem (ECP) とは集合 S の部分集合族 E ⊆ 2^S が与えられたとき、  
族 E より S の要素 e ∈ S がちょうど1回ずつ登場するような部分族 C ⊆ E を見つける問題である。  
つまり C は a,b ∈ C (a ∩ b = {}) かつ ∪{a | a ∈ C} = S を満たす。  
このような C を S の exact cover と呼ぶ。

## [Algorithm X][ax]

クヌースが考案した [exact cover problem][ec] の解を効率よく列挙するための手法。


## [Dancing Links][dl]

クヌースが考案した [Algorithm X][ax] を効率的に実装するためのデータ構造。


--------------------------------------------------------------------------------


# 実装

## dancinglinnks.{c, h}

データ構造 [Dancing Links][dl] の実装。  
見どころはクヌースが感動したという、双方向リストからの  
データの削除と復元の容易さ。

## algorithmx.{c, h}

データ構造 [Dancing Links][dl] を利用した [Algorithm X][ax] の実装。

## methods

#### new / free

    ecp *ecp_new(int _n, int _m, int **_A);

_n 列 _m 行の 0-1 行列 _A に対する exact cover problem (ECP) を生成する。

    void ecp_free(ecp *_a);

ECP _a を free する。

#### show

    void ecp_show_problem(FILE *_fp, ecp *_a);

ECP _a の問題を表示する。

    void ecp_show_solution(FILE *_fp, ecp *_a);

ECP _a の探索により見つかった解を表示する。

#### solve

    int ecp_solve(ecp *_a, int _max);

ECP _a の解を最大 _max 個列挙する。  

## 使い方

入力は n × m の 0-1 行列であり、1行目に n, m を、以降に各行を書く。  
`test.txt` を上記の行列ファイルとすると以下のように使う。

    cat test.txt | ./ecp

出力の各行は入力行列の行の部分集合を表し、１つの解に対応する。  
例えば `test.txt` に対して以下のような出力を得る。

       1   1   0   1   0   0   0
       0   0   1   1   0   0   0
       0   1   0   0   1   0   0
       1   0   0   0   0   1   0
       0   0   0   0   0   0   1

つまりこの問題に対する exact cover は 5 個存在することが分かる。
