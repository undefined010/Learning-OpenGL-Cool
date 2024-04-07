#include "Shader.h"

#include <stdio.h>
#include <stdlib.h>

char* read_shader(const char* file_name)
{
    if (file_name == NULL)
    {
        fprintf
        (
            stderr,
            "file_name param is empty (NULL)\n"
        );
        exit(-1);
    }

    FILE* shader_file = fopen(file_name,"r");

    

    fseek(shader_file,0,SEEK_END);
    long file_size = ftell(shader_file);
    fseek(shader_file,0,SEEK_SET);

    if (shader_file == NULL)
    {
        fprintf(
            stderr,
            "failed to create a file pointer (failed to read shader file)\n"
        );

        fclose(shader_file);
        exit(-1);
    }

    char* file_content = malloc(file_size + 1);

    fread((char*)file_content,1,file_size,shader_file);

    file_content[file_size] = '\0';

    return file_content;

}