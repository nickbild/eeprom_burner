// fffc
// 1111111111111100
// 111111111111100 = 32764
//
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
int a4 = A4;

int ce = 10;
int oe = 11;
int we = 12;

void setup() {
  pinMode(a0, OUTPUT);
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(a3, OUTPUT);
  pinMode(a4, OUTPUT);

  pinMode(ce, OUTPUT);
  pinMode(oe, OUTPUT);
  pinMode(we, OUTPUT);

  // Disable chip.
  digitalWrite(we, HIGH);
  digitalWrite(ce, HIGH);
  digitalWrite(oe, HIGH);
  delay(10);

  Serial.begin(115200);
}

int doWrite = 0;
int diff = -1;
String last_result = "";

void loop(){
  delay(500);

  if (doWrite == 1) {
    // 111111111111100 -> 11100000
    write(1,1,1,0,0, 1,1,1,0,0,0,0,0);
    // 111111111111101 -> 11111111
    write(1,1,1,0,1, 1,1,1,1,1,1,1,1);
    
    //1111 1111 1110 0000 -> 1010 1001
    write(0,0,0,0,0, 1,0,1,0,1,0,0,1);
    //1111 1111 1110 0001 -> 1110 0000
    write(0,0,0,0,1, 1,1,1,0,0,0,0,0);
    //1111 1111 1110 0010 -> 1000 0101
    write(0,0,0,1,0, 1,0,0,0,0,1,0,1);
    //1111 1111 1110 0011 -> 0000 0000
    write(0,0,0,1,1, 0,0,0,0,0,0,0,0);
    
    //1111 1111 1110 0100 -> 1010 1001
    write(0,0,1,0,0, 1,0,1,0,1,0,0,1);
    //1111 1111 1110 0101 -> 1111 1111
    write(0,0,1,0,1, 1,1,1,1,1,1,1,1);
    //1111 1111 1110 0110 -> 1000 0101
    write(0,0,1,1,0, 1,0,0,0,0,1,0,1);
    //1111 1111 1110 0111 -> 0000 0001
    write(0,0,1,1,1, 0,0,0,0,0,0,0,1);
    
    //1111 1111 1110 1000 -> 0110 1100
    write(0,1,0,0,0, 0,1,1,0,1,1,0,0);
    //1111 1111 1110 1001 -> 0000 0000
    write(0,1,0,0,1, 0,0,0,0,0,0,0,0);
    //1111 1111 1110 1010 -> 0000 0000
    write(0,1,0,1,0, 0,0,0,0,0,0,0,0);

    Serial.println("Done writing.");
  }

  doWrite = 0;
  
  delay(5000);

  String result = "--------\n";

    // 111111111111100 -> 11100000
    result += read(1,1,1,0,0) + "\n";
    // 111111111111101 -> 11111111
    result += read(1,1,1,0,1) + "\n";
    
    //1111 1111 1110 0000 -> 1010 1001
    result += read(0,0,0,0,0) + "\n";
    //1111 1111 1110 0001 -> 1110 0000
    result += read(0,0,0,0,1) + "\n";
    //1111 1111 1110 0010 -> 1000 1101
    result += read(0,0,0,1,0) + "\n";
    //1111 1111 1110 0011 -> 0000 0000
    result += read(0,0,0,1,1) + "\n";
    
    //1111 1111 1110 0100 -> 1010 1001
    result += read(0,0,1,0,0) + "\n";
    //1111 1111 1110 0101 -> 1111 1111
    result += read(0,0,1,0,1) + "\n";
    //1111 1111 1110 0110 -> 1000 1101
    result += read(0,0,1,1,0) + "\n";
    //1111 1111 1110 0111 -> 0000 0001
    result += read(0,0,1,1,1) + "\n";
    
    //1111 1111 1110 1000 -> 0110 1100
    result += read(0,1,0,0,0) + "\n";
    //1111 1111 1110 1001 -> 0000 0000
    result += read(0,1,0,0,1) + "\n";
    //1111 1111 1110 1010 -> 0000 0000
    result += read(0,1,0,1,0) + "\n";
  
  Serial.println(result);

  if (last_result != result) {
    diff++;
  }
  last_result = result;
  Serial.println(diff);

}

String read(unsigned int ad4, unsigned int ad3, unsigned int ad2, unsigned int ad1, unsigned int ad0) {
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

  digitalWrite(a4, ad4);
  digitalWrite(a3, ad3);
  digitalWrite(a2, ad2);
  digitalWrite(a1, ad1);
  digitalWrite(a0, ad0);

  digitalWrite(ce, LOW);
  digitalWrite(oe, LOW);
  delay(10);

  String output = String(digitalRead(io7)) + String(digitalRead(io6)) + String(digitalRead(io5)) + String(digitalRead(io4)) + String(digitalRead(io3)) + String(digitalRead(io2)) + String(digitalRead(io1)) + String(digitalRead(io0));

  digitalWrite(oe, HIGH);
  digitalWrite(ce, HIGH);
  delay(10);

  return output;
}

void write(unsigned int ad4, unsigned int ad3, unsigned int ad2, unsigned int ad1, unsigned int ad0, unsigned int i7, unsigned int i6, unsigned int i5, unsigned int i4, unsigned int i3, unsigned int i2, unsigned int i1, unsigned int i0) {
  // From datasheet:
  // A low pulse on the WE or CE input with CE or WE low (respectively) and OE high initiates a write cycle. The address is latched on the falling edge of CE or WE,
  // whichever occurs last. The data is latched by the first rising edge of CE or WE.
  
  digitalWrite(we, HIGH);
  digitalWrite(ce, HIGH);
  digitalWrite(oe, HIGH);
  delay(10);

  pinMode(io0, OUTPUT);
  pinMode(io1, OUTPUT);
  pinMode(io2, OUTPUT);
  pinMode(io3, OUTPUT);
  pinMode(io4, OUTPUT);
  pinMode(io5, OUTPUT);
  pinMode(io6, OUTPUT);
  pinMode(io7, OUTPUT);

  digitalWrite(a4, ad4);
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

  digitalWrite(ce, LOW);
  delay(10);

  digitalWrite(we, LOW);
  delay(10);
  
  digitalWrite(we, HIGH);
  digitalWrite(ce, HIGH);
  delay(100);
}

