#include "BitOutputStream.hpp"
#include "BitInputStream.hpp"
#include "HCTree.hpp"
#include <iostream>

int main(int argc, char** argv){
  int a;
  char c;  
  unsigned char d;
  int uniqueSymbols = 0;
  double totalChars = 0;
  double outSize=0;
  vector<int> myFreqs (256, 0);
  HCTree myHCTree;
  std::ifstream infile(argv[1], ios::binary);
  std::ofstream outfile (argv[2], ios::binary);
  BitOutputStream outstr(outfile); 
   
  //error checks
  if(argc < 3) {
    std::cout << argv[0] << " called with incorrect arguments." << std::endl;
    std::cout << "Usage: " << argv[0] << " infile outfile" << std::endl;
    return 1;
  }

  
  if(infile.fail()){
    std::cout << "Error opening " << '"' << "0" << '"' << std::endl;
    return 1;
  }
  
  while(infile.get(c)){  
    
    if(infile.eof()){
      break;
    } 
    d = (unsigned char)c;
    a = (int)d;
    if(myFreqs[a]){
      myFreqs[a]++;
    }
    else {
      myFreqs[a] = 1;
      uniqueSymbols++;
    } 
    
    totalChars++;
  }
  
 // if(!uniqueSymbols) {
   // std::cout << "Error opening " << '"' << "0" << '"' << "." << std::endl;
   // return 0;
  //}

  std::cout << "Reading from file " << '"' << argv[1] << '"' << "... done." << std::endl;
  std::cout << "Found " << uniqueSymbols << " unique symbols in input file of size " << totalChars <<  " bytes." << std::endl;
  
  //build tree
  myHCTree.build(myFreqs);
  std::cout << "Building Huffman code tree... done." << std::endl;

//header
  for(int i=0; i<myFreqs.size(); i++) {
    outstr.writeInt(myFreqs[i]);
  }
  
  infile.close();
  std::ifstream infile2(argv[1], ios::binary);

  while(infile2.get(c)){  
    if(infile2.eof()){
      break;	
    }
    d = (unsigned char)c;
    a = (int)d;
    myHCTree.encode(a, outstr);
  }
  outstr.flush();
  
  outSize = outfile.tellp();
  
  std::cout << "Writing to file " << '"' << argv[2] << '"' << "... done." << std::endl;
  std::cout << "Output file has size " << outSize << " bytes." << std::endl;
  std::cout << "Compression ratio: " << outSize/totalChars << std::endl;

  infile2.close();  
  outfile.close();

  return 0;
}
