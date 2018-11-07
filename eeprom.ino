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

  // Starting address of program (write to FFFC-FFFD).
  // little endian
  write("111111111111100", "00000000");
  write("111111111111101", "10000000");

  // Program.  Leave MSB off address in ROM to write to.
  write("000000000000000", "00100000");
  write("000000000000001", "00011101");
  write("000000000000010", "10000000");
  write("000000000000011", "00100000");
  write("000000000000100", "00110010");
  write("000000000000101", "10000000");
  write("000000000000110", "10101001");
  write("000000000000111", "10000000");
  write("000000000001000", "00100000");
  write("000000000001001", "00100011");
  write("000000000001010", "10000000");
  write("000000000001011", "10101001");
  write("000000000001100", "01010000");
  write("000000000001101", "00100000");
  write("000000000001110", "00100011");
  write("000000000001111", "10000000");
  write("000000000010000", "00100000");
  write("000000000010001", "00011101");
  write("000000000010010", "10000000");
  write("000000000010011", "10101001");
  write("000000000010100", "01001000");
  write("000000000010101", "00100000");
  write("000000000010110", "00100011");
  write("000000000010111", "10000000");
  write("000000000011000", "10101001");
  write("000000000011001", "10001000");
  write("000000000011010", "00100000");
  write("000000000011011", "00100011");
  write("000000000011100", "10000000");
  write("000000000011101", "10100010");
  write("000000000011110", "00000010");
  write("000000000011111", "11001010");
  write("000000000100000", "11010000");
  write("000000000100001", "11111101");
  write("000000000100010", "01100000");
  write("000000000100011", "10000101");
  write("000000000100100", "00000000");
  write("000000000100101", "00100000");
  write("000000000100110", "00011101");
  write("000000000100111", "10000000");
  write("000000000101000", "10000101");
  write("000000000101001", "00000001");
  write("000000000101010", "00100000");
  write("000000000101011", "00011101");
  write("000000000101100", "10000000");
  write("000000000101101", "10000101");
  write("000000000101110", "00000000");
  write("000000000101111", "00100000");
  write("000000000110000", "00011101");
  write("000000000110001", "10000000");
  write("000000000110010", "10101001");
  write("000000000110011", "00110000");
  write("000000000110100", "00100000");
  write("000000000110101", "00100011");
  write("000000000110110", "10000000");
  write("000000000110111", "00100000");
  write("000000000111000", "00011101");
  write("000000000111001", "10000000");
  write("000000000111010", "10101001");
  write("000000000111011", "00110000");
  write("000000000111100", "00100000");
  write("000000000111101", "00100011");
  write("000000000111110", "10000000");
  write("000000000111111", "00100000");
  write("000000001000000", "00011101");
  write("000000001000001", "10000000");
  write("000000001000010", "10101001");
  write("000000001000011", "00110000");
  write("000000001000100", "00100000");
  write("000000001000101", "00100011");
  write("000000001000110", "10000000");
  write("000000001000111", "00100000");
  write("000000001001000", "00011101");
  write("000000001001001", "10000000");
  write("000000001001010", "10101001");
  write("000000001001011", "00100000");
  write("000000001001100", "00100000");
  write("000000001001101", "00100011");
  write("000000001001110", "10000000");
  write("000000001001111", "00100000");
  write("000000001010000", "00011101");
  write("000000001010001", "10000000");
  write("000000001010010", "10101001");
  write("000000001010011", "00100000");
  write("000000001010100", "00100000");
  write("000000001010101", "00100011");
  write("000000001010110", "10000000");
  write("000000001010111", "10101001");
  write("000000001011000", "10000000");
  write("000000001011001", "00100000");
  write("000000001011010", "00100011");
  write("000000001011011", "10000000");
  write("000000001011100", "00100000");
  write("000000001011101", "00011101");
  write("000000001011110", "10000000");
  write("000000001011111", "10101001");
  write("000000001100000", "00000000");
  write("000000001100001", "00100000");
  write("000000001100010", "00100011");
  write("000000001100011", "10000000");
  write("000000001100100", "10101001");
  write("000000001100101", "11000000");
  write("000000001100110", "00100000");
  write("000000001100111", "00100011");
  write("000000001101000", "10000000");
  write("000000001101001", "00100000");
  write("000000001101010", "00011101");
  write("000000001101011", "10000000");
  write("000000001101100", "10101001");
  write("000000001101101", "00000000");
  write("000000001101110", "00100000");
  write("000000001101111", "00100011");
  write("000000001110000", "10000000");
  write("000000001110001", "10101001");
  write("000000001110010", "00010000");
  write("000000001110011", "00100000");
  write("000000001110100", "00100011");
  write("000000001110101", "10000000");
  write("000000001110110", "00100000");
  write("000000001110111", "00011101");
  write("000000001111000", "10000000");
  write("000000001111001", "10101001");
  write("000000001111010", "00000000");
  write("000000001111011", "00100000");
  write("000000001111100", "00100011");
  write("000000001111101", "10000000");
  write("000000001111110", "10101001");
  write("000000001111111", "01100000");
  write("000000010000000", "00100000");
  write("000000010000001", "00100011");
  write("000000010000010", "10000000");
  write("000000010000011", "00100000");
  write("000000010000100", "00011101");
  write("000000010000101", "10000000");
  write("000000010000110", "01100000");

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

