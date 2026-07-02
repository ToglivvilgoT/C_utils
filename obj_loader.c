#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "d_array.h"

typedef struct {
  float x, y, z, w;
} Vertex;

typedef struct {
  Vertex *items;
  size_t  capacity, size;
} VertexVec;

typedef struct {
  float u, v, w;
} TexCoord;

typedef struct {
  TexCoord *items;
  size_t    capacity, size;
} TexCoordVec;

typedef struct {
  float x, y, z;
} Normal;

typedef struct {
  Normal *items;
  size_t  capacity, size;
} NormalVec;

typedef struct {
  int v_idx, vt_idx, vn_idx;
} FaceElement;

typedef struct {
  FaceElement *items;
  size_t       capacity, size;
} FaceVec;

int parse_v(char const *line, VertexVec *vertices)
{
  Vertex v = {0};

  int n = sscanf(line, "v %f %f %f %f", &v.x, &v.y, &v.z, &v.w);

  if (n < 3) return -1;

  if (n == 3) v.w = 1.0f;

  append((*vertices), v);
  return 0;
}

int parse_vt(char const *line, TexCoordVec *uvs)
{
  (void)line;
  (void)uvs;
  return 0;
}

int parse_vn(char const *line, NormalVec *normals)
{
  (void)line;
  (void)normals;
  return 0;
}

int parse_f(char const *line, FaceVec *faces)
{
  (void)line;
  (void)faces;
  return 0;
}

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    printf("usage: %s <file.obj>\n", argv[0]);
    return 1;
  }

  FILE *f_ptr = fopen(argv[1], "r");
  if (!f_ptr)
  {
    perror("fopen");
    return 1;
  }

  VertexVec   vertices = {0};
  TexCoordVec uvs      = {0};
  NormalVec   normals  = {0};
  FaceVec     faces    = {0};

  char line[256];

  while (fgets(line, sizeof(line), f_ptr))
  {
    if (*line == '\0' || *line == '#' || *line == '\n') continue;

    if (line[0] == 'v')
    {
      if (line[1] == ' ')
      {
        if (parse_v(line, &vertices) < 0) goto error;
      }
      else if (line[1] == 't')
      {
        if (parse_vt(line, &uvs) < 0) goto error;
      }
      else if (line[1] == 'n')
      {
        if (parse_vn(line, &normals) < 0) goto error;
      }
    }
    else if (line[0] == 'f')
    {
      if (parse_f(line, &faces) < 0) goto error;
    }
  }
  if (feof(f_ptr))
  {
    printf("EOF reached successfully\n");
    fclose(f_ptr);
    return 0;
  }

error:
  printf("OBJ parsing error\n");
  fclose(f_ptr);
  return 1;
}
