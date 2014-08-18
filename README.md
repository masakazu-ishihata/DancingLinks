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




## sudoku.{c, h}

#### new / free

    sudoku *sudoku_new(FILE *_fp);

数独問題を読み込み、sudoku インスタンスを生成する。

    void sudoku_free(sudoku *_s);

数独インスタンス _s を free する。

#### solve

    void sudoku_solve(sudoku *_s);

数独インスタンス _s を解く。  
内部で ECP を解いている。  
ECP への変換は new の時点で行われている。

#### show

    void sudoku_show_problem(FILE *_fp, sudoku *_s);
    void sudoku_show_answer(FILE *_fp, sudoku *_s);

数独インスタンスの問題、解答を表示する。


--------------------------------------------------------------------------------

# 使い方

入力は 9 × 9 の 0-9 行列であり、数独の問題に対応する。  
`test.txt` を上記の行列ファイルとすると以下のように使う。

    cat test.txt | ./sudoku

例えば `test.txt` に対して以下のような出力を得る。


    Problem
      0  0  3  0  0  9  0  8  1
      0  0  0  2  0  0  0  6  0
      5  0  0  0  1  0  7  0  0
      8  9  0  0  0  0  0  0  0
      0  0  5  6  0  1  2  0  0
      0  0  0  0  0  0  0  3  7
      0  0  9  0  2  0  0  0  8
      0  7  0  0  0  4  0  0  0
      2  5  0  8  0  0  6  0  0

    Answer
      6  2  3  5  7  9  4  8  1
      9  1  7  2  4  8  5  6  3
      5  8  4  3  1  6  7  9  2
      8  9  2  4  3  7  1  5  6
      7  3  5  6  8  1  2  4  9
      1  4  6  9  5  2  8  3  7
      4  6  9  7  2  5  3  1  8
      3  7  8  1  6  4  9  2  5
      2  5  1  8  9  3  6  7  4
