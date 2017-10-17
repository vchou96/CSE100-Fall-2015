#include "BitInputStream.hpp"

// read next bit
  int BitInputStream::readBit(){
   /* if(buf_index == 8) {
      buf = readByte();
      buf_index = 0;
    }
     
    if(buf & (1 << 7 - buf_index)) {
      buf_index++;
      return 1;
    }
    else{
      buf_index++;
      return 0;
    }*/
    if(buf_index == 8){
      fill();
    }
    int v = bitVal(buf, buf_index + 1);
    buf_index++;
    return v;

  }

char BitInputStream::bitVal(char b, int n){
  unsigned char c;
  c=b>>(n-1) & 1;
  return c;
}

void BitInputStream::fill(){
  buf = in.get();
  buf_index = 0;  
}

// read next byte, used for decoding header
  int BitInputStream::readByte(){
    return in.get(); 
  }

// read next int, used for decoding header
  int BitInputStream::readInt(){
    /*char * str[4];
    in.get(str, 4);
    return((int)*str);*/
    int i;
    in.read((char*) &i, sizeof(int));
    return i;
  }

