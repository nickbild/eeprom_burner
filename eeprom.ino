// fffc
// 1111111111111100
// 111111111111100 = 32764
//
// Set FFFC-FFFD to 32752:
// 111111111111100 -> 01111111
// 111111111111101 -> 11110000
//
// Program at 32752 (7ff0) - 32756:
// nop
// nop
// jmp $7FF0
//
// ea ea 4c f0 7f
// 111111111110000 -> 11101010
// 111111111110001 -> 11101010
// 111111111110010 -> 01001100
// 111111111110011 -> 11110000
// 111111111110100 -> 01111111

int io0 = 2;
int io1 = 3;
int io2 = 4;
int io3 = 5;
int io4 = 6;
int io5 = 7;
int io6 = 8;
int io7 = 9;

int a0 = A0;
int a1 = A1;
int a2 = A2;
int a3 = A3;

int ce = 10;
int oe = 11;
int we = 12;

void setup() {
  pinMode(a0, OUTPUT);
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(a3, OUTPUT);

  pinMode(ce, OUTPUT);
  pinMode(oe, OUTPUT);
  pinMode(we, OUTPUT);

  // Disable chip.
  digitalWrite(we, HIGH);
  delay(10);
  digitalWrite(ce, HIGH);
  delay(10);
  digitalWrite(oe, HIGH);
  delay(10);

  Serial.begin(9600);
}

int doWrite = 1;

void loop(){
  delay(500);

  if (doWrite == 1) {
    // 111111111111100 -> 01111111
    write(HIGH, HIGH, LOW, LOW, 0,1,1,1,1,1,1,1);
    // 111111111111101 -> 11110000
    write(HIGH, HIGH, LOW, HIGH, 1,1,1,1,0,0,0,0);
    // 111111111110000 -> 11101010
    write(LOW, LOW, LOW, LOW, 1,1,1,0,1,0,1,0);
    // 111111111110001 -> 11101010
    write(LOW, LOW, LOW, HIGH, 1,1,1,0,1,0,1,0);
    // 111111111110010 -> 01001100
    write(LOW, LOW, HIGH, LOW, 0,1,0,0,1,1,0,0);
    // 111111111110011 -> 11110000
    write(LOW, LOW, HIGH, HIGH, 1,1,1,1,0,0,0,0);
    // 111111111110100 -> 01111111
    write(LOW, HIGH, LOW, LOW, 0,1,1,1,1,1,1,1);
  }
  
  delay(10000);

  String result = "--------\n";
  
  // 111111111111100 -> 01111111
  result += read(HIGH, HIGH, LOW, LOW) + "\n";
  // 111111111111101 -> 11110000
  result += read(HIGH, HIGH, LOW, HIGH) + "\n";
  // 111111111110000 -> 11101010
  result += read(LOW, LOW, LOW, LOW) + "\n";
  // 111111111110001 -> 11101010
  result += read(LOW, LOW, LOW, HIGH) + "\n";
  // 111111111110010 -> 01001100
  result += read(LOW, LOW, HIGH, LOW) + "\n";
  // 111111111110011 -> 11110000
  result += read(LOW, LOW, HIGH, HIGH) + "\n";
  // 111111111110100 -> 01111111
  result += read(LOW, HIGH, LOW, LOW) + "\n";

  Serial.println(result);

}

String read(unsigned int ad3, unsigned int ad2, unsigned int ad1, unsigned int ad0) {
  // From datasheet:
  // When CE and OE are low and WE is high, the
  // data stored at the memory location determined by the address pins is asserted on the outputs.

  digitalWrite(we, HIGH);
  digitalWrite(ce, HIGH);
  digitalWrite(oe, HIGH);
  delay(10);
  
  pinMode(io0, INPUT);
  pinMode(io1, INPUT);
  pinMode(io2, INPUT);
  pinMode(io3, INPUT);
  pinMode(io4, INPUT);
  pinMode(io5, INPUT);
  pinMode(io6, INPUT);
  pinMode(io7, INPUT);

  digitalWrite(a3, ad3);
  digitalWrite(a2, ad2);
  digitalWrite(a1, ad1);
  digitalWrite(a0, ad0);

  digitalWrite(ce, LOW);
  digitalWrite(oe, LOW);
  delay(10);

  String output = String(digitalRead(io7)) + String(digitalRead(io6)) + String(digitalRead(io5)) + String(digitalRead(io4)) + String(digitalRead(io3)) + String(digitalRead(io2)) + String(digitalRead(io1)) + String(digitalRead(io0));

  delay(10);
  digitalWrite(oe, HIGH);
  digitalWrite(ce, HIGH);

  delay(10);
  digitalWrite(ce, LOW);
  digitalWrite(oe, LOW);

  delay(10);
  digitalWrite(oe, HIGH);
  digitalWrite(ce, HIGH);

  return output;
}

void write(unsigned int ad3, unsigned int ad2, unsigned int ad1, unsigned int ad0, unsigned int i7, unsigned int i6, unsigned int i5, unsigned int i4, unsigned int i3, unsigned int i2, unsigned int i1, unsigned int i0) {
  // From datasheet:
  // A low pulse on the WE or CE input with CE or WE low (respectively) and OE high initiates a write cycle. The address is latched on the falling edge of CE or WE,
  // whichever occurs last. The data is latched by the first rising edge of CE or WE.
  
  digitalWrite(we, HIGH);
  digitalWrite(ce, HIGH);
  digitalWrite(oe, HIGH);

  pinMode(io0, OUTPUT);
  pinMode(io1, OUTPUT);
  pinMode(io2, OUTPUT);
  pinMode(io3, OUTPUT);
  pinMode(io4, OUTPUT);
  pinMode(io5, OUTPUT);
  pinMode(io6, OUTPUT);
  pinMode(io7, OUTPUT);

  digitalWrite(ce, LOW);
  delay(10);

  digitalWrite(a3, ad3);
  digitalWrite(a2, ad2);
  digitalWrite(a1, ad1);
  digitalWrite(a0, ad0);

  digitalWrite(io7, i7);
  digitalWrite(io6, i6);
  digitalWrite(io5, i5);
  digitalWrite(io4, i4);
  digitalWrite(io3, i3);
  digitalWrite(io2, i2);
  digitalWrite(io1, i1);
  digitalWrite(io0, i0);

  delay(10);
  digitalWrite(we, LOW);
  delay(10);
  
  digitalWrite(we, HIGH);
  delay(10);
  digitalWrite(ce, HIGH);
  delay(10);
}

