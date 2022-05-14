# M5ATOMでmini四駆を動かす

とりあえずモータドライバを配した基板を用意して、m5atomでミニ四駆を駆動してみようと思う

## 基板

## ファームウェア

- pwm

ピンG23でモータをPWMする。
[こちら](http://blog.robotakao.jp/blog-entry-388.html)を参考にする
よくわからんので[公式](https://github.com/m5stack/m5-docs/blob/master/docs/ja/api/gpio.md)も見てみる

ledcSetup関数で使うchの設定して、それのchをledcAttachPin関数でアタッチする。で、出来上がり。

- i2c(センサ)

i2cを使ってセンサ値を読み取る

秋月の[公式](https://akizukidenshi.com/catalog/g/gK-13010)のサンプルを動かす（ここでハードの間違いに気づく）

[こちら](https://shikarunochi.matrix.jp/?p=3859)を参考に
https://garchiving.com/how-to-bmx055-with-sample/
