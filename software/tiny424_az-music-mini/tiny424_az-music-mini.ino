// tiny424
// cpu 5MHz

#include <avr/sleep.h>

// 音ベース周波数
const short base_tone[5][12] = {
  // 0:ド, 1:ド#, 2:レ, 3:レ#, 4:ミ, 5:ファ, 6:ファ#, 7:ソ, 8:ソ#, 9:ラ, 10:ラ#, 11:シ
  {  65,   69,   73,   77,   82,   87,   92,   97,  103,  110,  116,  123},
  { 130,  138,  146,  155,  164,  174,  184,  195,  207,  220,  233,  246},
  { 261,  277,  293,  311,  329,  349,  369,  391,  415,  440,  466,  493},
  { 523,  554,  587,  622,  659,  698,  739,  783,  830,  880,  932,  987},
  {1046, 1108, 1174, 1244, 1318, 1396, 1479, 1567, 1661, 1760, 1864, 1975}
};

// 蛍の光
const char music_hotaru[] = {
  0, 5, 5, 5,
  9, 7, 5, 7, 9, 5, 5, 9, 12, 14,
  14, 12, 9, 9, 5, 7, 5, 7,
  9, 5, 2, 2, 0, 5,
  // -------------------------------
  14, 12, 9, 9, 
  5, 7, 5, 7,
  14, 12, 9, 9, 12, 14,
  14, 12, 9, 9, 5, 7, 5, 7, 9, 5, 2, 2, 5,
  120 
};
// 0:ド, 2:レ, 4:ミ, 5:ファ, 7:ソ, 9:ラ, 11:シ, 12:ド, 14:レ, 16:ミ, 17:ファ, 19:ソ, 21:ラ, 23:シ, 24:ド, 26:レ, 28:ミ, 29:ファ


// ドレミの歌
const char music_doremi[] = {
  0, 2, 4, 0, 4, 0, 4,
  2, 4, 5, 5, 4, 2, 5,
  4, 5, 7, 4, 7, 4, 7,
  5, 7, 9, 9, 7, 5, 9,
  7, 0, 2, 4, 5, 7, 9,
  9, 2, 4, 6, 7, 9, 11,
  11,4, 6, 8, 9,12,
 11,10, 9, 5,11, 7, 12,
  0, 2, 4, 5, 7, 9, 11, 12,
 12,11, 9, 7, 5, 4,  2,
  0,4,4, 4,7,7, 2,5,5,9,11,11,
  120
};

// テトリスのテーマ(コロブチカ)
const char music_tetris[] = {
  16, 11, 12, 14, 12, 11, 9, 9, 12, 16, 14, 12, 11, 11, 12, 14, 16, 12, 9, 9,
  14, 17, 21, 19, 17, 16, 16, 12, 16, 14, 12, 11, 11, 12, 14, 16, 12, 9, 9,
  16, 11, 12, 14, 12, 11, 9, 9, 12, 16, 14, 12, 11, 11, 12, 14, 16, 12, 9, 9,
  14, 17, 21, 19, 17, 16, 16, 12, 16, 14, 12, 11, 11, 12, 14, 16, 12, 9, 9,
  16, 12, 14, 11, 12, 9, 8,    16, 12, 14, 11, 12, 16, 21, 20,
  120
};



// 天国と地獄
const char music_tengoku_zigoku[] = {
  9, 16, 16, 17,
  16, 14, 14, 17,
  19, 23, 26, 23,
  23, 21, 21,
  // ---------------
  23, 14, 14, 23,
  21, 14, 14, 19,
  18, 16, 18, 16,
  18, 16, 18, 16,
  // ---------------
  9, 16, 16, 17,
  16, 14, 14, 17,
  19, 23, 26, 23,
  23, 21, 21,
  // ---------------
  23, 14, 14, 23,
  21, 14, 14, 19,
  18, 16, 18, 16,
  16, 14, 14,
  // ---------------
  // 17, 14, 11, 9,
  29, 26, 23, 21,
  21, 16, 17, 19,
  17,16, 14,
  // 17, 14, 11, 9,
  29, 26, 23, 21,
  19, 21, 23, 24,
  28, 26, 26,
  29, 26, 23, 21,
  21, 16, 17, 19,
  17,16, 14,
  29, 26, 23, 21,
  19, 21, 23, 24,
  26, 21, 24, 21,
  26, 21, 24, 21,
  26, 21, 24, 21,
  26, 21, 24, 21,
  26, 26, 26, 26,
  26, 26, 26, 26,
  26, 26, 26, 26,
  26, 2, 7,
  120 
};
// 0:ド, 2:レ, 4:ミ, 5:ファ, 7:ソ, 9:ラ, 11:シ, 12:ド, 14:レ, 16:ミ, 17:ファ, 19:ソ, 21:ラ, 23:シ, 24:ド, 26:レ, 28:ミ, 29:ファ


// クシコスポスト
const char music_csikospost[] = {
  23, 17, 23,  23, 19, 23,
  23, 23, 15, 18, 23, 11,
  // -----------------
  28, 16, 18, 19, 23,
  24, 28, 23,
  21, 24, 19, 23,
  18, 23, 19, 18, 16,
  28, 16, 18, 19, 23,
  24, 28, 23,
  // -----------------
  23, 22, 23, 25, 26, 25, 26, 28,
  30, 25, 30, 23, 11,
  16, 19, 23, 21, 24, 28,
  23, 23, 25, 27, 23, 30,
  28, 28, 30, 31, 28, 35,
  16, 19, 23, 21, 24, 28,
  23, 28, 23, 19, 11, 16, 19,
  18, 11, 15, 18, 16, 28,
  
  
  
  
  120
};
// 0:ド, 2:レ, 4:ミ, 5:ファ, 7:ソ, 9:ラ, 11:シ
// 12:ド, 14:レ, 16:ミ, 17:ファ, 19:ソ, 21:ラ, 23:シ
// 24:ド, 26:レ, 28:ミ, 29:ファ, 31:ソ, 33:ラ, 35:シ


// エリーゼのために
const char music_forelise[] = {
  16, 15, 16, 15, 16,
  11, 14, 12, 9,
  // ------------------
  0, 4, 9, 11,
  4, 8, 11, 12,
  // ------------------
  4, 16, 15, 16, 15, 16,
  11, 14, 12, 9,
  // ------------------
  0, 4, 9, 11,
  4, 12, 11, 9,
  // ------------------
  16, 15, 16, 15, 16,
  11, 14, 12, 9,
  // ------------------
  0, 4, 9, 11,
  4, 8, 11, 12,
  // ------------------
  4, 16, 15, 16, 15, 16,
  11, 14, 12, 9,
  // ------------------
  0, 4, 9, 11,
  4, 12, 11, 9,
  // ------------------
  11, 12, 14, 16,
  7, 17, 16, 14,
  5, 16, 14, 12,
  4, 14, 12, 11, 4,
  16, 16, 28,
  120
};

// 0:ド, 2:レ, 4:ミ, 5:ファ, 7:ソ, 9:ラ, 11:シ, 12:ド, 14:レ, 16:ミ, 17:ファ, 19:ソ, 21:ラ, 23:シ, 24:ド, 26:レ, 28:ミ, 29:ファ



const int pin_spk = PIN_PB3;
const int pin_key_0 = PIN_PA3;
const int pin_key_1 = PIN_PA2;
const int pin_key_2 = PIN_PA1;
const int pin_key_3 = PIN_PB2;
const int pin_lsw_0 = PIN_PA4;
const int pin_lsw_1 = PIN_PA6;
const int pin_lsw_2 = PIN_PA5;
const int pin_lsw_3 = PIN_PA7;

int key_stat_0;
int play_seek;
int play_level;
int music_select;
volatile bool change_switch_fl;
int key_last_push;

short get_tone(char gt) {
  if (gt < 12) {
    return base_tone[play_level][gt + 0];
  } else if (gt <= 24) {
    return base_tone[play_level + 1][gt - 12];
  } else if (gt <= 36) {
    return base_tone[play_level + 2][gt - 24];
  }
  return 0;
}

void setup() {
  pinMode(pin_spk, OUTPUT);
  pinMode(pin_key_0, INPUT_PULLUP);
  pinMode(pin_key_1, INPUT_PULLUP);
  pinMode(pin_key_2, INPUT_PULLUP);
  pinMode(pin_key_3, INPUT_PULLUP);
  pinMode(pin_lsw_0, INPUT_PULLUP);
  pinMode(pin_lsw_1, INPUT_PULLUP);
  pinMode(pin_lsw_2, INPUT_PULLUP);
  pinMode(pin_lsw_3, INPUT_PULLUP);
  key_stat_0 = 0;
  play_seek = 0;
  play_level = 2;
  music_select = 0;
  change_switch_fl = true;
  key_last_push = -1;
  attachInterrupt(digitalPinToInterrupt(pin_lsw_0), change_select_switch, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pin_lsw_1), change_select_switch, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pin_lsw_2), change_select_switch, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pin_lsw_3), change_select_switch, CHANGE);

}

int key_check() {
  int key_read = 0;
  int push_status = 0;
  key_read |= !digitalRead(pin_key_0);
  key_read |= !digitalRead(pin_key_1) << 1;
  key_read |= !digitalRead(pin_key_2) << 2;
  key_read |= !digitalRead(pin_key_3) << 3;
  if ((!(key_stat_0 & 0x01) && (key_read & 0x01))) { key_last_push = 0; push_status = 0x10; }
  if ((!(key_stat_0 & 0x02) && (key_read & 0x02))) { key_last_push = 1; push_status = 0x10; }
  if ((!(key_stat_0 & 0x04) && (key_read & 0x04))) { key_last_push = 2; push_status = 0x10; }
  if ((!(key_stat_0 & 0x08) && (key_read & 0x08))) { key_last_push = 3; push_status = 0x10; }
  if (key_stat_0 && !key_read) { key_last_push = -1; push_status = 0x10; }
  key_stat_0 = key_read;
  return (key_stat_0 | push_status);
}

char get_music_tone() {
    // 0:ド, 2:レ, 4:ミ, 5:ファ, 7:ソ, 9:ラ, 11:シ, 12:ド, 14:レ, 16:ミ, 17:ファ, 19:ソ, 21:ラ
  // ドレミファ
  if (music_select == 0) {
    if (key_last_push == 0) return 0;
      else if (key_last_push == 1) return 2;
      else if (key_last_push == 2) return 4;
      else if (key_last_push == 3) return 5;
      else return 0;
  }
  // ソラシド
  if (music_select == 1) {
    if (key_last_push == 0) return 7;
      else if (key_last_push == 1) return 9;
      else if (key_last_push == 2) return 11;
      else if (key_last_push == 3) return 12;
      else return 0;
  }
  // ドレミファ
  if (music_select == 2) {
    if (key_last_push == 0) return 12;
      else if (key_last_push == 1) return 14;
      else if (key_last_push == 2) return 16;
      else if (key_last_push == 3) return 17;
      else return 0;
  }
  // ソラシド
  if (music_select == 3) {
    if (key_last_push == 0) return 19;
      else if (key_last_push == 1) return 21;
      else if (key_last_push == 2) return 23;
      else if (key_last_push == 3) return 24;
      else return 0;
  }
  if (music_select == 4) return music_tetris[play_seek];
  if (music_select == 5) return music_doremi[play_seek];
  if (music_select == 6) return music_forelise[play_seek];
  if (music_select == 7) return music_tengoku_zigoku[play_seek];
  if (music_select == 8) return music_csikospost[play_seek];
  if (music_select == 9) return music_hotaru[play_seek];
  return music_tetris[play_seek];
}

void change_select_switch() {
  change_switch_fl = true;
}

void change_music() {
  int sw_read = 0;
  sw_read |= !digitalRead(pin_lsw_0);
  sw_read |= !digitalRead(pin_lsw_1) << 1;
  sw_read |= !digitalRead(pin_lsw_2) << 2;
  sw_read |= !digitalRead(pin_lsw_3) << 3;
  play_seek = 0;
  music_select = sw_read;
  change_switch_fl = false;
  if (music_select == 7) {
    play_level = 1;
  } else {
    play_level = 2;
  }
}

void loop() {
  int key_0 = key_check();
  if (key_0 & 0x10) {
    if (!(key_0 & 0x0F)) {
      noTone(pin_spk);
    } else {
      tone(pin_spk, get_tone(get_music_tone()));
      play_seek++;
      if (get_music_tone() >= 100) play_seek = 0;
    }
  }
  if (change_switch_fl) change_music();
  delay(20);  

}
