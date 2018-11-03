// Set FFFC-FFFD to FFE0 (little endian):
// 111111111111100 -> 11100000
// 111111111111101 -> 11111111
//
// Program at FFE0:
//lda #$E0
//sta $00
//lda #$FF
//sta $01
//jmp ($0000)
//
// ea a9 e0 8d 00 00 a9 ff 8d 01 00 6c 00 00
// a9 e0 85 00 a9 ff 85 01 6c 00 00 
//1111 1111 1110 0000 -> 1010 1001
//1111 1111 1110 0001 -> 1110 0000
//1111 1111 1110 0010 -> 1000 0101
//1111 1111 1110 0011 -> 0000 0000
//1111 1111 1110 0100 -> 1010 1001
//1111 1111 1110 0101 -> 1111 1111
//1111 1111 1110 0110 -> 1000 0101
//1111 1111 1110 0111 -> 0000 0001
//1111 1111 1110 1000 -> 0110 1100
//1111 1111 1110 1001 -> 0000 0000
//1111 1111 1110 1010 -> 0000 0000

int ser0 = 2; // rightmost
int ser1 = 3;
int ser2 = 4;

int rclk = 5; // yellow
int sclk = 6; // orange

int ce = 10;
int oe = 11;
int we = 12;

void setup() {
  pinMode(ser0, OUTPUT);
  pinMode(ser1, OUTPUT);
  pinMode(ser2, OUTPUT);
  
  pinMode(rclk, OUTPUT);
  pinMode(sclk, OUTPUT);

  pinMode(ce, OUTPUT);
  pinMode(oe, OUTPUT);
  pinMode(we, OUTPUT);

  // Disable chip.
  digitalWrite(we, HIGH);
  digitalWrite(ce, HIGH);
  digitalWrite(oe, HIGH);
  delay(10);

  Serial.begin(9600);
}

void loop(){
  delay(5000);

  // Starting address of program.
  write("111111111111100", "11100000");
  write("111111111111101", "11111111");

  // Program.
  write("111111111100000", "10101001");
  write("111111111100001", "11100000");
  write("111111111100010", "10000101");
  write("111111111100011", "00000000"); 
  write("111111111100100", "10101001");
  write("111111111100101", "11111111");
  write("111111111100110", "10000101");
  write("111111111100111", "00000001");
  write("111111111101000", "11101010");
  write("111111111101001", "01101100");
  write("111111111101010", "00000000");
  write("111111111101011", "00000000");

  Serial.println("Done writing.");

}

void write(String addr, String data) {
  // From datasheet:
  // A low pulse on the WE or CE input with CE or WE low (respectively) and OE high initiates a write cycle. The address is latched on the falling edge of CE or WE,
  // whichever occurs last. The data is latched by the first rising edge of CE or WE.
  
  digitalWrite(we, HIGH);
  digitalWrite(ce, HIGH);
  digitalWrite(oe, HIGH);
  delay(10);

  digitalWrite(rclk, 0);
  delay(10);

  // Data, address low, address high.
  writeBit(data.charAt(0), addr.charAt(7), '0');
  writeBit(data.charAt(1), addr.charAt(8), addr.charAt(0));
  writeBit(data.charAt(2), addr.charAt(9), addr.charAt(1));
  writeBit(data.charAt(3), addr.charAt(10), addr.charAt(2));
  writeBit(data.charAt(4), addr.charAt(11), addr.charAt(3));
  writeBit(data.charAt(5), addr.charAt(12), addr.charAt(4));
  writeBit(data.charAt(6), addr.charAt(13), addr.charAt(5));
  writeBit(data.charAt(7), addr.charAt(14),addr.charAt(6));

  digitalWrite(rclk, 1);

  delay(10);

  digitalWrite(ce, LOW);
  delay(10);

  digitalWrite(we, LOW);
  delay(10);
  
  digitalWrite(we, HIGH);
  digitalWrite(ce, HIGH);
  delay(100);
}

void writeBit(char val0, char val1, char val2) {
  digitalWrite(sclk, 0);
  delay(1);

  digitalWrite(ser0, charToDigital(val0));
  digitalWrite(ser1, charToDigital(val1));
  digitalWrite(ser2, charToDigital(val2));
  delay(1);  
  
  digitalWrite(sclk, 1);
  delay(1);
  digitalWrite(sclk, 0);
  delay(1);
}

int charToDigital(char val) {
  if (val == '1') {
    return 1;
  }

  return 0;
}

