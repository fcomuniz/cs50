//
// Created by francisco on 07/01/17.
//

#include <stdio.h>

#define BLOCK_SIZE 512
#define JPEG_FILE_NAME_MAX_SIZE 10

typedef unsigned char block_t[BLOCK_SIZE];

void findJPEGs(FILE * image);

int isBegginingOfJPEG(block_t block);

int main(int argc, char * argv[]){

    if(argc != 2){
        fprintf(stderr, "usage %s input-file", argv[0]);
        return 1;
    }

    char * filePath = argv[1];

    FILE * image = fopen(filePath,"r");

    if(image == NULL){
        fprintf(stderr, "Couldn't read %s input file", filePath);
        return 2;
    }

//    TODO iterate trough the file to find the jpegs

    findJPEGs(image);

    fclose(image);
    return 0;
}


void findJPEGs(FILE * image){
    block_t block;
    do {
        // Find the beggining of the first jpeg
        fread(&block, BLOCK_SIZE, 1,image);
    } while(!isBegginingOfJPEG(block) && !feof(image));
    fseek(image, -BLOCK_SIZE, SEEK_CUR);
    FILE * JPEGFile = NULL;
    int JPEGNumber = 0;
    while(!feof(image)){
        if(fread(&block, 1, BLOCK_SIZE,image) < BLOCK_SIZE){
//            Reached eof
            break;
        }
        if(isBegginingOfJPEG(block)){
//            Start new JPEG
//            close previous JPEG file
            if(JPEGFile !=NULL)
                fclose(JPEGFile);
            char fileName[JPEG_FILE_NAME_MAX_SIZE];
            sprintf(fileName,"%03i.jpg", JPEGNumber);
            JPEGFile = fopen(fileName,"w");
            JPEGNumber++;

        }
        fwrite(&block, BLOCK_SIZE, 1, JPEGFile);
    }
}

int isBegginingOfJPEG(block_t block){
    int valueToRet =(block[0] == 0xff &&
                     block[1] == 0xd8 &&
                     block[2] == 0xff &&
                     (block[3] & 0xf0) == 0xe0);
    return valueToRet;
}
