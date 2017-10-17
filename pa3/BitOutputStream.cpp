#include "BitOutputStream.hpp"

void BitOutputStream::writeBit(int bit){
  /*bit = bit - 48;
  if(buf_index == 8) {
    flush();
    buf_index = 0;
  }
  buf = buf | (bit << 7 - buf_index);
  buf_index++;*/
  if(buf_index==8){
    flush();
  }
  buf = setBit(buf, bit, buf_index+1);
  buf_index++;
}

char BitOutputStream::setBit(char b, int bit, int n){
  unsigned char c;
  if(bit == 1) {
    c = b | (bit <<(n-1)); 
  }
  else {
    c= b & ~ (1<<(n-1));
  }
  return c;
}

// write an byte to the stream (used for header)
void BitOutputStream::writeByte(int i) {
  out.put((unsigned char)i);
}

// write an integer to the stream (used for header)
void BitOutputStream::writeInt(int i) {
 /* out.put((char)i);
  a = i << 8;
  out.put((char)a);
  a = a << 8;
  out.put((char)a);
  a = a << 8;
  out.put((char)a);*/
  out.write((char*) &i, sizeof(int));
}

void BitOutputStream::flush() {
  out.put(buf);
  out.flush();
  buf_index = 0;
  buf = 0;  
}
