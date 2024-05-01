#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "lodepng.h"
#include <fstream>


std::vector<unsigned char> decodeOneStep(const char* filename){   //g++ lodepng.cpp example_decode.cpp -ansi -pedantic -Wall -Wextra -O3
  std::vector<unsigned char> image; //the raw pixels
  unsigned width, height;
  //decode
  unsigned error = lodepng::decode(image, width, height, filename);

  //if there's an error, display it
  if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
  std::vector<int> intVal;
  return image;
}
void readRawFile(std::string filename, std::vector<unsigned char> image, int depth){
    std::ifstream hiddenData(filename.c_str(), std::ios::binary);
    if(!hiddenData.is_open()){
        std::cout<<"Error: Failed to open file";
        return;
    }
    int bufferSize = 100;
    char buffer[100];
    hiddenData.read(buffer, sizeof(buffer));
    if(hiddenData.fail()){
        std::cout<<"Error: Failed to read file"<<std::endl;
        //return;
    }
    u_int8_t lastbitMask = 1;
    buffer[0] = buffer[0]>>7;
    for(int i = 0; i<bufferSize; i++){

    }

    //u_int8_t bit8 = 1;



    std::cout<<"Raw Binary:";
    //for(int i = 0; i<hiddenData.gcount(); i++){
        std::cout<<std::endl;
        std::cout<<buffer[0]<<" ";
        std::cout<<std::endl;
        buffer[0] = buffer[0]>>8;
        std::cout<<buffer[0];
    //}
}

int sizeOfFile(std::string filename){
    std::
}

int main(int argc, char *argv[]){   //COMPILER FLAGS: your_program.cpp lodepng.cpp -Wall -Wextra -pedantic -ansi -O3
    int optype = atoi(argv[1]);
    if(optype == 0){        //./exe (int)operationType originalFile newFile msgFile (int)depth 
        if(argc < 6){
            std::cout<<"Error: Operation type must have 4 execution flags";
            return 0;
        }
        std::string newFile = argv[3];
        std::string basePNG = argv[2];
        std::string msgFile = argv[4];
        int depth = atoi(argv[5]);
        //std::cout<<depth<<"?";
        std::vector<unsigned char> decodedBasePNG = decodeOneStep(argv[2]);
        //ecodedBasePNG[3] = decodedBasePNG[3] & 0b0000;
        //std::cout<<(int)decodedBasePNG[3];
        int maxBits = decodedBasePNG.size() * depth;
        std::cout<<"RGBA bytes: "<<decodedBasePNG.size()<<" AvalibleBits: "<<maxBits;

        readRawFIle("phone1.png", decodedBasePNG, depth);
    }

}


//Assign last 2 bits of value:          0b 0000 0010
//Current Value                         0b 1101 1101


//Current Val = CurrentVal + Assign     0b 1101 1111
//
//Assign = Assign + Mask 1              0b 1111 1110
//CurrentVal = CurrentVal & Assign      0b 1101 1110