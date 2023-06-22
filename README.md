# LED Cube with Unity
## LED Cube that glows in time with music.

The LED cube itself was created from scratch. We used the game engine Unity to control the lighting, and made it easy to make the LEDs glow through GUI operation.

## LED Cube schematic
<img src="https://github.com/MORIMOTO520212/led-cube-with-unity/blob/main/Album/led_cube_schematic.png?raw=true">


# Usage
1. Open this Unity Project.
2. Set the Port Name to SerialHandler Object. (ex:COM3)
3. Run the Unity.
4. select a music Object and play it in the Timeline Tab.

# 点灯アルゴリズム
・8個のシフトレジスタを使って、1層(64個)の点灯の制御を行う
・ダイナミック点灯という手法を用いて、もう一つシフトレジスタで、高速に1層ごと点灯させる

1. 1層目の点灯パターンを設定
2. 1層目を点灯
3. 2層目の点灯パターンを設定
4. 2層目を点灯
5. これを8層目まで行う
6. 1層目に戻る
7. 上記の繰り返し


# License
LED Cube with Unity is under [MIT license](https://en.wikipedia.org/wiki/MIT_License).