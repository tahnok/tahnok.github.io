
#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

#define OE   9
#define LAT 10
#define CLK 11
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);

const int data_pin = 6; //  SER_OUT (serial data out)
const int shld_pin = 5; // SH/!LD (shift or active low load)
const int clk_pin = 3; //  CLK (the clock that times the shifting)
const int ce_pin = 4; //  !CE (clock enable, active low)

const int data_pin_2 = 48;
const int ce_pin_2 = 46;
const int shld_pin_2 = 47;
const int clk_pin_2 = 49;

byte incoming1;
byte incoming2;
byte incoming3;
byte incoming4;

byte colour1;
byte colour2;


//int start[] = { 0, 1, 0, 0, 1, 0, 1, 0,
//                0, 0, 1, 0, 1, 1, 0, 1,
//                1, 1, 1, 0, 0, 1, 1, 1,
//                0, 1, 0, 1, 1, 0, 0, 1
//              };
int start[32] = {0};

int* row1;
int* row2;

int x = 0;
int y = 0;

void setup() {

  //shift registers for buttons
  Serial.begin(9600);

  // Initialize each digital pin to either output or input
  // We are commanding the shift register with each pin with the exception of the serial
  // data we get back on the data_pin line.
  pinMode(shld_pin, OUTPUT);
  pinMode(ce_pin, OUTPUT);
  pinMode(clk_pin, OUTPUT);
  pinMode(data_pin, INPUT);
  pinMode(shld_pin_2, OUTPUT);
  pinMode(ce_pin_2, OUTPUT);
  pinMode(clk_pin_2, OUTPUT);
  pinMode(data_pin_2, INPUT);

  // Required initial states of these two pins according to the datasheet timing diagram
  digitalWrite(clk_pin, HIGH);
  digitalWrite(shld_pin, HIGH);
  digitalWrite(clk_pin_2, HIGH);
  digitalWrite(shld_pin_2, HIGH);

  read_shift_regs();
  read_color_shift_regs();
  Serial.println("colours: ");
  print_byte(colour1);
  print_byte(colour2);
  Serial.println(transform(colour1));
  Serial.println(transform(colour2));
  fill_starting_row();

  //matrix
  matrix.begin();
  matrix.fillScreen(0);
  row1 = start;
  displayRow(row1);
  row2 = (int*) malloc(sizeof(int) * 32);
}

int i = 0;
int j = 0;
void loop() {

  for (x = 0; x < 64; x++) {
    int* row;
    if (x % 2) {
      apply_rule(row2, row1);
      row = row2;
    } else {
      apply_rule(row1, row2);
      row = row1;
    }
    //    j = (j + 1) % 24;
    //    Serial.print(x);
    //    Serial.print(":  ");
    //    displayRow(row);
    //    Serial.print("row1 ");
    //    displayRow(row1);
    //    Serial.print("row2 ");
    //    displayRow(row2);
    for (y = 0; y < 32; y++) {
      if (row[y]) {
        matrix.drawPixel(x, y, transform(colour1));
      } else {
        matrix.drawPixel(x, y, transform(colour2));
      }

    }
    delay(100);
  }
  for (;;);
}

void apply_rule(int a[32], int b[32]) {
  for (int i = 0; i < 32; i++) {
    if (i == 0 || i == 31) {
      b[i] = a[i] & 1;
    } else {
      if ( (a[i - 1] && a[i] && !a[i + 1]) ||
           (a[i - 1] && !a[i] && a[i + 1]) ||
           (!a[i - 1] && a[i] && a[i + 1]) ||
           (!a[i - 1] && a[i] && !a[i + 1]) ||
           (!a[i - 1] && !a[i] && a[i + 1])
         ) {
        b[i] = 1;
      } else {
        b[i] = 0;
      }
    }

  }
  //  return b;
}


// Input a value 0 to 24 to get a color value.
// The colours are a transition r - g - b - back to r.
uint16_t Wheel(byte WheelPos) {
  if (WheelPos < 8) {
    return matrix.Color333(7 - WheelPos, WheelPos, 0);
  } else if (WheelPos < 16) {
    WheelPos -= 8;
    return matrix.Color333(0, 7 - WheelPos, WheelPos);
  } else {
    WheelPos -= 16;
    return matrix.Color333(0, WheelPos, 7 - WheelPos);
  }
}

byte read_shift_regs()
{
  byte the_shifted = 0;  // An 8 bit number to carry each bit value of A-H

  // Trigger loading the state of the A-H data lines into the shift register
  digitalWrite(shld_pin, LOW);
  delayMicroseconds(5); // Requires a delay here according to the datasheet timing diagram
  digitalWrite(shld_pin, HIGH);
  delayMicroseconds(5);

  // Required initial states of these two pins according to the datasheet timing diagram
  pinMode(clk_pin, OUTPUT);
  pinMode(data_pin, INPUT);
  digitalWrite(clk_pin, HIGH);
  digitalWrite(ce_pin, LOW); // Enable the clock

  // Get the A-H values
  //the_shifted = shiftIn(data_pin, clk_pin, MSBFIRST);
  incoming1 = shiftIn(data_pin, clk_pin, MSBFIRST);
  incoming2 = shiftIn(data_pin, clk_pin, MSBFIRST);
  incoming3 = shiftIn(data_pin, clk_pin, MSBFIRST);
  incoming4 = shiftIn(data_pin, clk_pin, MSBFIRST);
  digitalWrite(ce_pin, HIGH); // Disable the clock

  return the_shifted;

}

byte read_color_shift_regs()
{
  byte the_shifted = 0;  // An 8 bit number to carry each bit value of A-H

  // Trigger loading the state of the A-H data lines into the shift register
  digitalWrite(shld_pin_2, LOW);
  delayMicroseconds(5); // Requires a delay here according to the datasheet timing diagram
  digitalWrite(shld_pin_2, HIGH);
  delayMicroseconds(5);

  // Required initial states of these two pins according to the datasheet timing diagram
  pinMode(clk_pin_2, OUTPUT);
  pinMode(data_pin_2, INPUT);
  digitalWrite(clk_pin_2, HIGH);
  digitalWrite(ce_pin_2, LOW); // Enable the clock

  // Get the A-H values
  //the_shifted = shiftIn(data_pin, clk_pin, MSBFIRST);
  colour1 = shiftIn(data_pin_2, clk_pin_2, MSBFIRST);
  colour2 = shiftIn(data_pin_2, clk_pin_2, MSBFIRST);
  digitalWrite(ce_pin_2, HIGH); // Disable the clock

  return the_shifted;

}

// A function that prints all the 1's and 0's of a byte, so 8 bits +or- 2
void print_byte(byte val)
{
  byte i;
  for (byte i = 0; i <= 7; i++)
  {
    Serial.print(val >> i & 1, BIN); // Magic bit shift, if you care look up the <<, >>, and & operators
  }
  Serial.print("\n"); // Go to the next line, do not collect $200
}

void fill_starting_row() {
  int i = 0;
  byte data;
  for (i = 0; i < 8; i++) {
    data = incoming1 >> i & 1;
    thang(i, data);
    start[i] = data;
  }
  for (i = 8; i < 16; i++) {
    data = incoming2 >> (i - 8) & 1;
    thang(i, data);
    start[i] = data;
  }
  for (i = 16; i < 24; i++) {
    data = !(incoming3 >> (i - 16) & 1);
    thang(i, data);
    start[i] = data;
  }
  for (i = 24; i < 32; i++) {
    data = !(incoming4 >> (i - 24) & 1);
    thang(i, data);
    start[i] = data;
  }
  Serial.print("\n");
}

void thang(int i, byte thing) {
  //  Serial.print(i);
  //  Serial.print(" : ");
  Serial.print(thing, BIN);
  Serial.print(" ");
}

void displayRow(int b[32]) {
  for (int a = 0; a < 32; a++) {
    thang(a, b[a]);
  }
  Serial.print("\n");
}

uint16_t transform(byte input) {
  //    return matrix.Color333(7 - WheelPos, WheelPos, 0);
  switch (input) {
    case 1:
      return Wheel(0);
    case 2:
      return Wheel(3);
    case 4:
      return Wheel(6);
    case 8:
      return Wheel(9);
    case 16:
      return Wheel(12);
    case 32:
      return Wheel(15);
    case 64:
      return Wheel(18);
    case 128:
      return Wheel(21);
    default:
      return Wheel(24);
  }
}
