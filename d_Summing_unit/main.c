#include "bnn.h"

void fileInfo(BITMAPFILEHEADER *bh, BITMAPINFOHEADER *bi){
    printf("<BITMAP FILE HEADER>\n");
    printf("bfSize: %d\n",bh->bfSize);
    printf("bfOffBits: %d\n",bh->bfOffBits);
    
    printf("<BITMAP INFO HEADER>\n");
    printf("biSize: %d\n",bi->biSize);
    printf("biWidth: %d\n",bi->biWidth);
    printf("biHeight: %d\n",bi->biHeight);
    printf("biPlanes: %d\n",bi->biPlanes);
    printf("biBitCount: %d\n",bi->biBitCount);
    printf("biSizeImage: %d\n",bi->biSizeImage);
    printf("biXpixels: %d\n",bi->biXPelsPerMeter);
    printf("biYpixels: %d\n",bi->biYPelsPerMeter);
    printf("biCompression: %d\n",bi->biCompression); 
    printf("biClrUsed: %d\n",bi->biClrUsed);
    printf("biClrImportant: %d\n",bi->biClrImportant);
    
}

/* This is a toy model. 
   Input image specification : 50x50 grayscale bmp file
*/
PATTERN * init_patterns(int pattern_length){
    
    PATTERN * new_pattern = (PATTERN*)malloc(sizeof(PATTERN)*pattern_length);

    for(int i=0; i<pattern_length/2; i++){
        new_pattern[i].threshold_level = 16*(0.5);
        new_pattern[i].start[0] = 0+i;
        new_pattern[i].start[1] = 0;
        new_pattern[i].end[0] = 0+i;
        new_pattern[i].end[1] = 15;
        new_pattern[i].isActive = 0;
    }
    for(int i=0; i<pattern_length/2; i++){
        new_pattern[i+pattern_length/2].threshold_level = 16*(0.5);
        new_pattern[i+pattern_length/2].start[0] = 0;
        new_pattern[i+pattern_length/2].start[1] = 0+i;
        new_pattern[i+pattern_length/2].end[0] = 15;
        new_pattern[i+pattern_length/2].end[1] = 0+i;
        new_pattern[i+pattern_length/2].isActive = 0;
    }
    
    return new_pattern;
}

void pattern_Info(PATTERN * patt, int length){
        printf("<PATTERN LIST>\n");
        printf("| No | Threshold |   start   |   end   | isActive |\n");
    for(int i=0; i<length; i++){
        
        printf("  %2d       %2d      (%2d, %2d)  (%2d, %2d)      %d\n",i , patt[i].threshold_level, patt[i].start[0], patt[i].start[1], patt[i].end[0], patt[i].end[1], patt[i].isActive);
        
    }
    
    
}

void pattern_translate(unsigned char * image, PATTERN * patt_list, int gray_padding, int width, int height, int patt_length){

    
float weight= 1.0;
    for(int k= 0; k<patt_length; k++){
        int total_threshold =0;
            for(int i=patt_list[k].start[1]; i<= patt_list[k].end[1] ; i++ ){
                for(int j=patt_list[k].start[0]; j<= patt_list[k].end[0] ; j++ ){
                total_threshold += image[i*(width+gray_padding)+j]*weight;
                }
                
            }
            if(DEBUG)printf("total_threshold is %d\n", total_threshold);
            if(total_threshold>=patt_list[k].threshold_level)  patt_list[k].isActive = 1;
    
    }

    

    

}

void print_input_img(unsigned char* image, int width, int height, int gray_padding){
    printf("<Input Image Pattern> \n");
    printf("===================================\n");
    for(int j=0; j<height; j++){
        printf("| ");
    for(int i=0; i<width; i++){
        if(image[j*(width+gray_padding)+i]==0){
            printf("- ");
        }
        else{
                image[j*(width+gray_padding)+i] = 1;
                printf("X ");
                
        }
        }
        printf("|\n");
    }
    printf("===================================\n");
}


int main(int argc, const char * argv[]){

    if(argc!=2){printf("Usage: <input_image.bmp>");}
    FILE * input_file_pt;                         
    BITMAPFILEHEADER fileHeader;    
    BITMAPINFOHEADER infoHeader;    
    
    unsigned char *image;    // pixel image pointer
    int size;                // pixecel data size
    int width, height;       // bitmap dimension
    int padding;             // pixel padding
    
    PATTERN * Pattern_list; 
    
    
    input_file_pt = fopen(argv[1], "rb");    // 비트맵 파일을 바이너리 모드로 열기
    if (input_file_pt == NULL)    // 파일 열기에 실패하면
        return 0;         // 프로그램 종료
    
    // 비트맵 파일 헤더 읽기. 읽기에 실패하면 파일 포인터를 닫고 프로그램 종료
    if (fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, input_file_pt) < 1)
    {
        fclose(input_file_pt);
        return 0;
    }
    
    // 매직 넘버가 MB가 맞는지 확인(2바이트 크기의 BM을 리틀 엔디언으로 읽었으므로 MB가 됨)
    // 매직 넘버가 맞지 않으면 프로그램 종료
    if (fileHeader.bfType != 'MB')
    {
        fclose(input_file_pt);
        return 0;
    }
    
    // 비트맵 정보 헤더 읽기. 읽기에 실패하면 파일 포인터를 닫고 프로그램 종료
    if (fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, input_file_pt) < 1)
    {
        fclose(input_file_pt);
        return 0;
    }
    
    fileInfo(&fileHeader, &infoHeader);
   
    
    size = infoHeader.biSizeImage;    // 픽셀 데이터 크기
    width = infoHeader.biWidth;       // 비트맵 이미지의 가로 크기
    height = infoHeader.biHeight;     // 비트맵 이미지의 세로 크기
    
    // 이미지의 가로 크기에 픽셀 크기를 곱하여 가로 한 줄의 크기를 구하고 4로 나머지를 구함
    // 그리고 4에서 나머지를 빼주면 남는 공간을 구할 수 있음.
    // 만약 남는 공간이 0이라면 최종 결과가 4가 되므로 여기서 다시 4로 나머지를 구함
    int gray_padding = (PIXEL_ALIGN - ((width * PIXEL_GRAY_SIZE) % PIXEL_ALIGN)) % PIXEL_ALIGN;

    if (size == 0)    // 픽셀 데이터 크기가 0이라면
    {
        // 이미지의 가로 크기 * 픽셀 크기에 남는 공간을 더해주면 완전한 가로 한 줄 크기가 나옴
        // 여기에 이미지의 세로 크기를 곱해주면 픽셀 데이터의 크기를 구할 수 있음
        size = (width * PIXEL_GRAY_SIZE + gray_padding) * height;
    }
    
    image = malloc(size);    // 픽셀 데이터의 크기만큼 동적 메모리 할당
    
    // 파일 포인터를 픽셀 데이터의 시작 위치로 이동
    fseek(input_file_pt, fileHeader.bfOffBits, SEEK_SET);
    
    // 파일에서 픽셀 데이터 크기만큼 읽음. 읽기에 실패하면 파일 포인터를 닫고 프로그램 종료
    if (fread(image, size, 1, input_file_pt) < 1)
    {
        
        fclose(input_file_pt);
        return 0;
    }
    
    fclose(input_file_pt);    // 비트맵 파일 닫기
    int pattern_length = 32;
    Pattern_list = init_patterns(pattern_length);
    pattern_Info(Pattern_list, pattern_length);

    print_input_img(image, width, height, gray_padding);
    
    
    pattern_translate(image, Pattern_list, gray_padding, width, height, pattern_length);
    pattern_Info(Pattern_list, pattern_length);
    

}