# Hitachi Hokudai Labo & Hokkaido University Contest 2019-1 A サンプルプログラム

* これは、Hitachi Hokudai Labo & Hokkaido University Contest 2019-1 A で使われるサンプルプログラムの説明になります。本プログラムを使用することで、ローカル環境でテストケースの作成や解答プログラムの得点計算が行えます。
* 本プログラムの使用は自己責任でお願いいたします。これらのプログラムを使用することで発生したあらゆる損害に関して、北海道大学と日立製作所は補償いたしません。
* 得点計算を行うプログラムは、実際のコンテストで解答プログラムの得点計算を行うプログラムと同一ですが、実際のコンテストで使用するテストケースやシードは非公開となります。このため、これらのプログラムによって計算された得点は、当コンテストの得点を保証するものではありません。

## サンプルプログラムの概要

`scripts` フォルダ内には以下のコードが格納されています。

* `generator.cpp`
    * このプログラムは、解答プログラムを適用するためのテストケースを作成するものです。
* `output_checker.cpp`
    * このプログラムは、解答プログラムから得られた出力の得点計算をするものです。
* `sample_code/sample.cpp`, `sample_code/sample.py`
    * このプログラムは、提出していただく問題の解答のサンプルとなるプログラムです。こちらのコードを参考にしながら解答を作成しても構いません。

## コンパイルについて

以下のようにコンパイルします。

```bash
g++ -std=gnu++11 -o generator generator.cpp
g++ -std=gnu++11 -o output_checker output_checker.cpp
```

* C++11 オプションを指定しない場合、コンパイルができない可能性があります。

## テストケースの生成

`generator.cpp` をコンパイル後、`generator` を実行することで問題文の条件を満たすテストケースを出力できます。ここで、「テストケースのファイル名 [filename]」「ケースタイプ [case-type]」「乱数シード [seed]」を引数に設定します。

```bash
Usage: ./generator [filename] [case-type] [seed]
```

- `<filename>`: 出力されるテストケースの名前を指定します。
- `<case-type>`: グラフのケースの種類を指定します。
    - `1`: 頂点数を 200 から 400 までの間でランダムに指定します。
    - `2`: 頂点数を 400 に固定します。
- `<seed>`: ランダム生成プログラムの実行に必要なシードを指定します。

以下の例では、乱数シード 2048 で生成した、頂点数がランダムのケースが、`testcase.in` のファイル名で保存されます。

```bash
./generator testcase.in 1 2048
```

## 得点計算

`output_checker.cpp` をコンパイル後、`output_checker` を実行することで、テストケースに対する得点計算ができます。ここで、「入力ファイル名 [input-filename]」「出力ファイル名 [output-filename]」を引数に指定します。

```bash
Usage: ./output_checker [input-filename] [output-filename]
```

以下に例を示します。最初に、あなたが作成した解答プログラムを用いて、テストケース `testcase.in` に対する出力結果を `result.out` のファイル名で保存します。ここで、 `result.out` は問題文の条件に沿ったフォーマットで生成ください。次に、下記コマンドを実行し、入力テストケース `testcase.in` に対する出力結果 `result.out` の得点計算を行います。

```bash
./output_checker testcase.in result.out
```

`result.out` が出力フォーマットに違反せず、出力の制約を満たしている場合、このテストケースに対するスコアが出力されます。
