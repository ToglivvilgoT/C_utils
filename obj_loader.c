#include <stdio.h>

#include "vector.h"


typedef struct {
  float x, y, z, w;
} Vertex;

INITIALIZE_VECTOR_TEMPLATE(Vertex);

typedef struct {
  float u, v, w;
} TexCoord;

INITIALIZE_VECTOR_TEMPLATE(TexCoord);

typedef struct {
  float x, y, z;
} Normal;

INITIALIZE_VECTOR_TEMPLATE(Normal);

typedef struct {
  int v_i, vt_i, vn_i;
} FaceElement;

typedef struct {
  FaceElement triangles[3];
} Face;

INITIALIZE_VECTOR_TEMPLATE(Face);


int parse_v(char const *line, VertexVec *vertices)
{
  Vertex v = {0};

  int n = sscanf(line, "v %f %f %f %f", &v.x, &v.y, &v.z, &v.w);

  if (n < 3) return -1;

  if (n == 3) v.w = 1.0f;

  Vertex_append(vertices, v);
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
  FaceElement f1 = {0};
  FaceElement f2 = {0};
  FaceElement f3 = {0};
  Face        f  = {0};
  // NOTE: assume all faces are triangles, implement triangulation in the future
  int n = sscanf(line,
                 "f %d/%d/%d %d/%d/%d %d/%d/%d",
                 &f1.v_i,
                 &f1.vt_i,
                 &f1.vn_i,
                 &f2.v_i,
                 &f2.vt_i,
                 &f2.vn_i,
                 &f3.v_i,
                 &f3.vt_i,
                 &f3.vn_i);
  if (n < 9) return -1;
  f.triangles[0] = f1;
  f.triangles[1] = f2;
  f.triangles[2] = f3;
  Face_append(faces, f);
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
