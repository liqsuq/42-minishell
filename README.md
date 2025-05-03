[English]() | 日本語 | 

<p align="center">
  <picture>
    <img height="400" alt="minishellImage" src="https://github.com/user-attachments/assets/96aab2ee-f9e3-4db8-ac33-61ad4aed5ad8">
  </picture>
</p>

<!--  <hr style="border: none; height: 0.2px; background-color: #ccc;" /> -->

<p align="center">
Minishellは、Bashが備える代表的な機能（コマンド実行やリダイレクト、パイプ、環境変数展開など）を核として、C言語で実装した軽量シェルです。<br>
シェルとして動作するために必要なプロセスの生成と管理、入出力の制御（ファイルディスクリプタ）、シグナルへの対応など、<br>
低レベルなOSの仕組みを幅広く扱いつつ、可能なかぎりBashの挙動に近づけるよう工夫しています。
</p>

<p align="center">
  <img src="https://img.shields.io/badge/-C-213a70.svg?logo=C&style=flat">
  <img src="https://img.shields.io/badge/-Linux-ea5520.svg?logo=linux&style=flat">
</p>

<hr>

## 実装内容

| 機能カテゴリ | 説明 |
|-----------|---------------------------------------------------------------------|
| プロンプト   | 	minish$ というプロンプトを常時表示し、履歴機能（readline）に対応 |
| コマンド実行      | PATH 上のコマンド、または相対/絶対パス指定バイナリを execve(2) で起動 |
| リダイレクト    | `<`, `>`,`>>`, `<<（Here-Document）`をネストも含めて正しく処理 |
| パイプ | 無限長パイプラインを再帰的に展開・実行 |
| 環境変数展開   | `$VAR` と直前コマンド終了値を示す `$?` をトークン単位で展開 |
| ビルドイン     | `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit` |
| シグナル処理   | `Ctrl-C`, `Ctrl-\`, `Ctrl-D` |
| エラー互換 | コマンド未発見(127)・実行権限なし(126)・構文エラー(2) など Bash と同じ終了コードを返却 |

## Makeコマンド一覧
| Make | 実装する内容 |
|-----------|-------------------------------------------------|
| all | 依存するソースコードをコンパイルし、実行ファイルを作成します。通常は $(NAME) ターゲットも含まれます |
| clean | コンパイル時に生成されたオブジェクトファイル（*.o など）を削除します。 |
| fclean | clean の内容に加えて、生成された実行ファイルやライブラリなどもまとめて削除します |
| re | fclean を実行した後、改めて all を実行して再ビルドを行います |


## ビルド方法
```
$ git clone <this repository>
$ cd minishell
$ make #コンパイル
$ ./minishell
minish$ #起動
```
## ディレクトリ構成
```
builtin/    … ビルトインコマンド実装
execute/    … fork/exec とパイプライン管理
expand/     … 変数・パラメータ・クォート展開
misc/       … シグナル・エラー処理・環境変数ユーティリティ
parse/      … 再帰下降パーサ
redirect/   … リダイレクトと heredoc
tokenize/   … 字句解析器
pipeline/   … パイプノード生成／実行
tester.sh   … Bash 互換性テストスクリプト
```
## テスト
tester.sh を実行すると Bash と Minishell の出力差分と終了コード差分を自動比較し、主要機能が互換であるか一括検証できます。
```
$ ./tester.sh
```
## Norminetteへの準拠
このプロジェクトは、42 School Norminetteルール（v3.3.55）に厳密に準拠しています。Norminetteは、42のすべてのCプロジェクトで一貫したコーディングスタイルを強制するものであり、以下のようなルールがあります：

- 関数あたり最大25行
- 1行あたり最大80文字
- ファイルあたり最大5関数
- 特定の変数宣言と命名規則
- 標準ライブラリ関数の使用制限
- 構造化された関数ヘッダーフォーマット
- forループ、switch文、do-whileループの禁止
- インデントにタブの使用が必須

このリポジトリのすべてのコードは、公式の42 Norminette検証ツールでエラーなく合格しています。

## 評価
<img src="https://github.com/user-attachments/assets/765ec3c2-7927-4a92-b718-ec39fc93c64d" alt="grade" style="width:20%;"/>

検証日：〇年〇月〇日

必須部分：〇/100

ボーナス：〇/15

