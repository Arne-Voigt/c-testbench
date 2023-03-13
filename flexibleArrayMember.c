#include <stdio.h>
#include <stdlib.h>
//#include <stddef.h>

typedef struct {
    short int id;
    char text[10];
} data_t;

typedef struct {
    int size;
    data_t * data;
} vector_t;

void setData(vector_t * vector, int index, data_t dataToSet){
    if (index >= vector->size){
        vector->data = (data_t *) realloc(vector->data, (index+1) * sizeof(data_t)); // need to resize
        vector->size = index+1;
    }
    (vector->data)[index] = dataToSet; 
}

data_t getData(vector_t vector, int index){
    if (index >= vector.size){
        return (data_t) {.id = 0, .text=""}; // index out of bound -> return default data
    }
    return (vector.data)[index]; 
}

int main() {
    vector_t vector;   
    int initialVectorSize = 3;
    int i;

    // allocate array -> at first for only 3 elements
    vector.size = initialVectorSize;
    vector.data = (data_t * ) malloc(initialVectorSize * sizeof(data_t));
    vector.data[0].id = 0;

    setData(&vector, 0, (data_t) {.id = 12, .text="who?567890"});
    setData(&vector, 1, (data_t) {.id = 23, .text="what?6789"});
    setData(&vector, 2, (data_t) {.id = 34, .text="when?6789"});
    // index 3 is not set
    setData(&vector, 4, (data_t) {.id = 56, .text="... ?"}); // index 4 is out of bound -> vector will be increased

    printf("total size: %d\n", vector.size);
    for (i=0; i <= 4; i++){
        printf("index %2d -> id: %2d\ttext: %s\n", i, getData(vector, i).id, getData(vector, i).text);
    }
    // try accessing an "out of bound" index
    printf("out of bound read for index: 6\n");
    printf("index %2d -> id: %2d\ttext: %s\n", 6, getData(vector, 6).id, getData(vector, 6).text);
    
    free(vector.data);
    return 0;
}