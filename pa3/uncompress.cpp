#include "BitOutputStream.hpp"
#include "BitInputStream.hpp"
#include "HCTree.hpp"
#include <iostream>

int main(int argc, char** argv){
  int a;
  char c;
  int i=0; 
  double totalChars = 0;
  double inSize = 0; 
  int uniqueSymbols = 0;
  double actualTotal = 0;
  vector<int> myFreqs (256, 0);
  HCTree myHCTree;
  std::ifstream infile(argv[1], ios::binary);
  std::ofstream outfile (argv[2], ios::binary);
  BitInputStream instr(infile); 
  BitOutputStream outstr(outfile);
  
  if(argc < 3) {
    std::cout << argv[0] << " called with incorrect arguments." << std::endl;
    std::cout << "Usage: " << argv[0] << " infile outfile" << std::endl;
    return 1;
  }

  if(infile.fail()){
    std::cout << "Error opening " << '"' << "0" << '"' << std::endl;
    return 1;
  }

  std::cout << "Reading from file " << '"' << argv[1] << '"' << "... done." << std::endl;  

  while(i<256){  
    a = instr.readInt();
    myFreqs[i] = a;
    i++;
    totalChars = totalChars + (double)a;
    if(a){
      uniqueSymbols++;
    }
  }

  std::cout << "Uncompressed file will have " << uniqueSymbols << " unique symbols and size " << totalChars <<  " bytes." << std::endl;  
  myHCTree.build(myFreqs);
  std::cout << "Building Huffman code tree... done." << std::endl;

  //decoding 
 /* while(infile.good()){
    if(infile.eof()){
      break;
    }
   */
    
  actualTotal = totalChars;
  while(totalChars > 0){
    outstr.writeByte(myHCTree.decode(instr));
    totalChars--;
  }

  inSize = infile.tellg();
  
  std::cout << "Writing to file " << '"' << argv[2] << '"' << "... done." << std::endl;
  std::cout << "Uncompression ratio: " << actualTotal/inSize << std::endl;
  infile.close();
  outfile.close();
  return 0;
  
}
