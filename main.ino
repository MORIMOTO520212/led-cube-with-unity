/****************
  2進数で表す数値の例
  B00000000 = 0
  B00000001 = 1
****************/

// LED用シフトレジスタ
const int SER   =  13;
const int RCLK =  12;
const int SRCLK   = 11;

// ダイナミック点灯用シフトレジスタ
const int SER2 = 4;
const int RCLK2 = 3;
const int SRCLK2 = 2;

// 点灯データ 1であれば点灯、0であれば消灯する
byte led[8][8] = {};

// ダイナミック点灯用
byte dinamic_shift[] = {
  B10000000, B01000000, B00100000, B00010000,
  B00001000, B00000100, B00000010, B00000001,
};

//各ピンをアウトプットに設定
void setup() {
  Serial.begin(57600);
  while(!Serial);

  pinMode( SER, OUTPUT );
  pinMode( RCLK, OUTPUT );
  pinMode( SRCLK, OUTPUT );

  pinMode( SER2, OUTPUT );
  pinMode( RCLK2, OUTPUT );
  pinMode( SRCLK2, OUTPUT );

  delay(1000);

  // シフトレジスタ初期化
  digitalWrite(RCLK, LOW);
  for(int i=0; i<8; i++){
    shiftOut(SER, SRCLK, LSBFIRST, B00000000);
  }
  digitalWrite(RCLK, HIGH);
}

char count = 0;
/* メイン処理 */
void loop() {
  update(count);
  blink_cube(count);
  if(count == 7){count = 0;}
  else{count++;}
}

void update(char i){
  digitalWrite(RCLK, LOW);
  for(char j = 0; j < 8; j++){
    shiftOut(SER, SRCLK, MSBFIRST, led[i][j]);
  }
  digitalWrite(RCLK, HIGH);
}

// ダイナミック点灯
void blink_cube(char i){
  digitalWrite(RCLK2, LOW);
  shiftOut(SER2, SRCLK2, LSBFIRST, dinamic_shift[i]);
  digitalWrite(RCLK2, HIGH);
}

// パケットの判別フラグ
char flag = 1;
// 点灯フラグ、0は消灯、1は点灯
byte flick_flag;
// x,y軸の値
byte x,y,z = 0;
// 受信したデータを格納する
byte data;

// 受信したときにトリガーする
void serialEvent() {
  while (Serial.available()) {
    data = (byte)Serial.read();

    // 1バイト目 処理
    if(flag){
      // 点灯消灯判定
      flick_flag = data >> 6;
      y = data & B00000111;

    // 2バイト目 処理
    }else{
      x = data >> 4;
      z = data & B00000111;

      if(flick_flag){ // 点灯処理
          led[y][x] |= round(pow(2,z));

      }else{ // 消灯処理
        led[y][x] &= ~round(pow(2,z));
      }
    }
    flag ^= 1;
  }
}
