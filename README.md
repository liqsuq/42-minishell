<!-- [English]() | 日本語 | -->

<p align="center">
  <picture>
    <img height="300" alt="minishellImage" src="https://github.com/user-attachments/assets/96aab2ee-f9e3-4db8-ac33-61ad4aed5ad8">
  </picture>
</p>

<!--  <hr style="border: none; height: 0.2px; background-color: #ccc;" /> -->

<p align="center">
Minishellは、Bashが備える代表的な機能（コマンド実行・リダイレクト・パイプ・環境変数展開など）を核として、C言語で実装した軽量シェルです。<br>
シェルとして動作するために必要なプロセスの生成と管理、入出力の制御、シグナルへの対応など、低レベルなOSの仕組みを幅広く扱いつつ、可能なかぎりBashの挙動に近づけるよう工夫しています。
</p>

<p align="center">
  <a href="https://github.com/liqsuq/42-minishell/wiki">🐚 ER図・構成の理解に役立つWikiはこちら</a>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/-C-213a70.svg?logo=C&style=flat">
  <img src="https://img.shields.io/badge/-Linux-ea5520.svg?logo=linux&style=flat">
</p>

<hr>

## 実装内容

| 機能カテゴリ | 説明 |
|-----------|---------------------------------------------------------------------|
| プロンプト   | 	プロンプト(minish$)を常時表示し、履歴機能（readline）に対応 |
| コマンド実行      | PATH上のコマンド、または相対/絶対パスで指定した実行ファイルを execve(2) で起動 |
| リダイレクト    | `<`・`>`・`>>`・`<<`(ヒアドキュメント)をネストも含めて正しく処理 |
| パイプ | 無限長パイプラインを再帰的に展開・実行 |
| 変数展開   | 環境変数と直前コマンド終了値を示す `$?` を展開 |
| ビルトイン関数     | `echo`・`cd`・`pwd`・`export`・`unset`・`env`・`exit` |
| シグナル処理   | `Ctrl-C`・`Ctrl-\`・`Ctrl-D` |
| エラー互換 | コマンド未発見(127)・実行権限なし(126)・構文エラー(2) など Bash と同じ終了コードを返却 |

## Makeターゲット一覧
| ターゲット | 概要 |
|-----------|-------------------------------------------------|
| all | 依存するソースコードをコンパイルし、実行ファイルを作成します |
| clean | コンパイル時に生成されたオブジェクトファイル（*.o など）を削除します |
| fclean | clean の内容に加えて生成された実行ファイルやライブラリなども削除します |
| re | fclean を実行後 all を実行して再ビルドを行います |

## ビルド方法
```
$ git clone <this repository>
$ cd 42-minishell
$ make
$ ./minishell
minish$
```

## ディレクトリ構成
| ディレクトリ | 概要 |
|------------|----------------------------------|
| builtin/   | ビルトインコマンド実装 |
| execute/   | コマンド実行とプロセス管理 |
| expand/    | 変数・パラメータ・クォート展開 |
| misc/      | シグナル・環境変数・ユーティリティ |
| parse/     | 構文解析 |
| redirect/  | リダイレクトとヒアドキュメント |
| tokenize/  | 字句解析 |
| pipeline/  | パイプライン実装 |
| tester.sh  | テストスクリプト |

## コーディング規約
このリポジトリではNorminette (v3.3.58)を採用しています。
[Norminette](https://github.com/42School/norminette)
はC言語プロジェクトで一貫したスタイルを強制するためのツールです。主なルールの一例は以下のとおりです。

- 1関数につき最大25行
- 1行あたり最大80文字
- 1ファイルあたり最大5関数
- 定められた形式の関数ヘッダ
- 変数宣言・命名に関する厳密な規定
- インデントはタブを用いて揃えること
- `for`・`switch`・`do-while`などの使用禁止
  
## テスト
コンパイル後`tester.sh`を実行すると Bash と Minishell の出力差分と終了コード差分を自動比較し、主要機能が互換であるか一括検証できます。
<p align="left">
  <img src="https://github.com/user-attachments/assets/acb01f2c-5a10-4465-86d0-332571e75438" height="500">
</p>

## 評価

検証日：〇年〇月〇日

必須部分：〇/100

ボーナス：〇/15

