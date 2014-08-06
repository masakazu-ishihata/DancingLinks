# Algorithm X

クヌースが考案した exact cover problem の解を効率よく列挙するための手法。


# Dancing Links

クヌースが考案した Algorithm X を効率的に実装するためのデータ構造。

# プログラム

入力は n × m の 0-1 行列であり、1行目に n, m を、以降に各行を書く。  
`test.txt` を上記の行列ファイルとすると以下のように使う。

    cat test.txt | ./algx

出力の各行は入力行列の行の部分集合を表し、１つの解に対応する。  
例えば `test.txt` に対して以下のような出力を得る。

     3 1 0
     3 2
     4 1
     5 0
     6

つまりこの問題に対する exact cover は 5 個存在することが分かる。
