#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<string> // for string class
#include <Windows.h>
#include <GL/GL.h>
#include <GL/glut.h>
#include <GL/GLU.h>
#include <math.h>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>    // std::find
#include "Vectores.h"
#define _USE_MATH_DEFINES

using namespace std;

class Material {

public:
  string name;
  Vector4F ambient, diffuse, especular;
  GLfloat exp;

  Material();
  Material(string);
  Material(string ,Vector4F , Vector4F , Vector4F , GLfloat);

private:

};
Material::Material() {
}

inline Material::Material(string n)
{

  name = n;
}

inline Material::Material(string n, Vector4F a, Vector4F d, Vector4F es, GLfloat xp)
{

  name = n;
  ambient = a;
  diffuse = d;
  especular = es;
  exp = xp;
}



class ObjModel {
  string file_path;
  vector<Vector2F> texture_vertices;
  vector<Vector3F> vertices, normals; // v x y z w? | vt u v w? | vn x y z ... los comparten todos los grupos?
  vector <vector<Vector3I>>faces;//vertices of the polygon optionally 
  //Material *materials; //pueden o no existir//usualmente cambian con el grupo // normalmente se especifican en un archivo aparte con la instruccion mtllib
  vector<Material> materials;
  std::map<int, Material> mat_dict;
public:
  ObjModel();
  ObjModel(string path);
  void renderObject();
private:
  void loadFromObjFile(string path);
  void process(string line);
  int check_error_bits(ifstream* f);
  void addMaterials(string line);
  void process_matlib(vector<string>  tokens);
  void process_group(vector<string> tokens);
  void process_mat(vector<string>  tokens);
  void process_vector(vector<string>  tokens);
  void process_texture_vector(vector<string>  tokens);
  void process_normal(vector<string>  tokens);
  void process_face(vector<string> tokens);
};

ObjModel::ObjModel() {
}
ObjModel::ObjModel(string path) {
  loadFromObjFile(path);
}

vector<string> split_str(string s, string delimiter) {
  size_t pos = 0;
  vector <string> tokens;
  while ((pos = s.find(delimiter)) != std::string::npos) {
    string test(s.substr(0, pos));
    tokens.push_back(test);
    s.erase(0, pos + delimiter.length());
  }
  if (!s.empty())
    tokens.push_back(s);
  return tokens;
}
void ObjModel::renderObject() {
  for (size_t i = 0; i < faces.size(); i++) {
    if (mat_dict.find(i-1) != mat_dict.end()) {
      Material m = mat_dict[i-1];
      GLfloat mat_amb[] = { m.ambient.x, m.ambient.y,m.ambient.z, 1 };
      GLfloat mat_shiny[] = { m.exp };
      GLfloat mat_espc[] = { m.especular.x, m.especular.y, m.especular.z, 1.0 };
      GLfloat mat_def[] = { m.diffuse.x,m.diffuse.y,m.diffuse.z, 1.0 };
      glMaterialfv(GL_FRONT, GL_SPECULAR, mat_espc);
      glMaterialfv(GL_FRONT, GL_SHININESS, mat_shiny);
      glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_def);
    }
    if (faces[i].size() == 4)
      glBegin(GL_QUADS);
    else if (faces[i].size() == 3)
      glBegin(GL_TRIANGLES);
    else
      glBegin(GL_POLYGON);

    for (size_t j = 0; j < faces[i].size(); j++) {
      Vector3F vert = vertices[faces[i][j].x - 1];
      glVertex3f(vert.x, vert.y, vert.z);
      Vector3F vn = normals[faces[i][j].z - 1];
      glNormal3f(vn.x, vn.y, vn.z);
    }
    glEnd();
  }
}
int ObjModel::check_error_bits(ifstream* f) {
  int stop = 0;
  if (f->eof()) {
    perror("stream eofbit. error state");
    // EOF after std::getline() is not the criterion to stop processing
    // data: In case there is data between the last delimiter and EOF,
    // getline() extracts it and sets the eofbit.
    stop = 0;
  }
  if (f->fail()) {
    perror("stream failbit (or badbit). error state");
    stop = 1;
  }
  if (f->bad()) {
    perror("stream badbit. error state");
    stop = 1;
  }
  return stop;
}
inline void ObjModel::addMaterials(string line) {
  string del(" ");
  vector<string> tokens = split_str(line, del);

  if (tokens.size() <= 0) {
    return;
  }
  string name = "newmtl";
  string ambient = "Ka";
  string diffuse = "Kd";
  string especular = "Ks";
  string exp = "Ns";

  if (!tokens[0].compare(ambient)) {
    std::string::size_type sz;     // alias of size_t
    GLfloat x = std::stof(tokens[1], &sz);
    GLfloat y = std::stof(tokens[2], &sz);
    GLfloat z = std::stof(tokens[3], &sz);
    materials[materials.size() - 1].ambient = Vector4F(x,y,z,1);
  }
  else if (!tokens[0].compare(diffuse)) {
    std::string::size_type sz;     // alias of size_t
    GLfloat x = std::stof(tokens[1], &sz);
    GLfloat y = std::stof(tokens[2], &sz);
    GLfloat z = std::stof(tokens[3], &sz);
    materials[materials.size() - 1].diffuse = Vector4F(x, y, z, 1);
  }
  else if (!tokens[0].compare(especular)) {
    std::string::size_type sz;     // alias of size_t
    GLfloat x = std::stof(tokens[1], &sz);
    GLfloat y = std::stof(tokens[2], &sz);
    GLfloat z = std::stof(tokens[3], &sz);
    materials[materials.size() - 1].especular = Vector4F(x, y, z, 1);

  }
  else if (!tokens[0].compare(exp)) {
    std::string::size_type sz;     // alias of size_t
    GLint x = std::stoi(tokens[1], &sz);
    materials[materials.size() - 1].exp = x;
  }
  else if (!tokens[0].compare(name)) {
    Material mat(tokens[1]);
    materials.push_back(mat);
  }
  else {
    //ignore
  }
}
inline void ObjModel::process_matlib(vector<string> tokens) {
  //open file
  //create material
  //add to material array
  std::string line;
  int getlinecount = 1;
  //cout << "* trying to open and read: " << path << endl;
  ifstream f("pruebas/"+tokens[1]);
  //perror("error state after ifstream constructor");
  if (!f.is_open())
    perror("is_open() returned false. error state");
  else
    cout << "is_open() returned true." << endl;
  //cout << "* checking error bits once before first getline" << endl;
  check_error_bits(&f);
  while (1) {
    //cout << "* perform getline() # " << getlinecount << endl;
    getline(f, line);
    //cout << "* checking error bits after getline" << endl;
    if (check_error_bits(&f)) {
      //cout << "* skip operation on data, break loop" << endl;
      break;
    }
    // This is the actual operation on the data obtained and we want to
    // protect it from errors during the last IO operation on the stream
    addMaterials(line);
    getlinecount++;
  }
  f.close();
  cout << "finished reading file." << endl;


}

inline void ObjModel::process_group(vector<string> tokens) {
  //start contruction new object
  //glBegin
}
inline void ObjModel::process_mat(vector<string> tokens) {
  string name = tokens[1];
  auto it = find_if(materials.begin(), materials.end(), [&name](const Material& obj) {return obj.name == name; });

  if (it != materials.end())
  {
    // found element. it is an iterator to the first matching element.
    // if you really need the index, you can also get it:

    mat_dict[faces.size()] = *it;

  }
}
inline void ObjModel::process_vector(vector<string> tokens) {
  //get x y z
  //convert to float
  std::string::size_type sz;     // alias of size_t
  GLfloat x = std::stof(tokens[1], &sz);
  GLfloat y = std::stof(tokens[2], &sz);
  GLfloat z = std::stof(tokens[3], &sz);
  Vector3F v(x, y, z);
  //add to vertices array
  vertices.push_back(v);

}
inline void ObjModel::process_texture_vector(vector<string> tokens) {
  //get x y z
  //convert to float
  std::string::size_type sz;     // alias of size_t
  GLfloat u = std::stof(tokens[1], &sz);
  GLfloat v = std::stof(tokens[2], &sz);
  GLfloat temp[2] = { u,v };
  Vector2F vec(u, v);
  //add to texture_vertices array=
  texture_vertices.push_back(vec);

}
inline void ObjModel::process_normal(vector<string> tokens) {
  //get x y z
  //convert to float
  std::string::size_type sz;     // alias of size_t
  GLfloat x = std::stof(tokens[1], &sz);
  GLfloat y = std::stof(tokens[2], &sz);
  GLfloat z = std::stof(tokens[3], &sz);
  GLfloat temp[3] = { x,y,z };
  Vector3F vec(x, y, z);
  //add to normals array
  normals.push_back(vec);
}


void ObjModel::loadFromObjFile(string path) {
  std::string line;
  int getlinecount = 1;
  //cout << "* trying to open and read: " << path << endl;
  ifstream f(path);
  //perror("error state after ifstream constructor");
  if (!f.is_open())
    perror("is_open() returned false. error state");
  else
    cout << "is_open() returned true." << endl;
  //cout << "* checking error bits once before first getline" << endl;
  check_error_bits(&f);
  while (1) {
    //cout << "* perform getline() # " << getlinecount << endl;
    getline(f, line);
    //cout << "* checking error bits after getline" << endl;
    if (check_error_bits(&f)) {
      //cout << "* skip operation on data, break loop" << endl;
      break;
    }
    // This is the actual operation on the data obtained and we want to
    // protect it from errors during the last IO operation on the stream
    process(line);
    getlinecount++;
  }
  f.close();
  cout << "finished reading file." << endl;
}

inline void ObjModel::process_face(vector<string> tokens) {

  //separate in v,vt,vn
  //create new Glint array
  //store v,vt,vn
  //store new array in faces array
  vector<Vector3I>  ftemp;
  std::string::size_type sz;
  for (size_t i = 1; i < tokens.size(); i++) {

    vector<string> vd = split_str(tokens[i], "/");
    GLint xd = !vd[0].empty() ? std::stoi(vd[0], &sz) : 0;
    GLint yd = !vd[1].empty() ? std::stoi(vd[1], &sz) : 0;
    GLint zd = !vd[2].empty() ? std::stoi(vd[2], &sz) : 0;
    Vector3I vec(xd, yd, zd);
    ftemp.push_back(vec);
  }
  faces.push_back(ftemp);

}
void ObjModel::process(string line) {
  string del(" ");
  vector<string> tokens = split_str(line, del);

  if (tokens.size() <= 0) {
    return;
  }
  string matlib = "mtllib";
  string mat = "usemtl";
  string g = "group";
  string v = "v";
  string vn = "vn";
  string vt = "vt";
  string f = "f";

  if (!tokens[0].compare(matlib))
    process_matlib(tokens);
  else if (!tokens[0].compare(g))
    process_group(tokens);
  else if (!tokens[0].compare(mat))
    process_mat(tokens);
  else if (!tokens[0].compare(v))
    process_vector(tokens);
  else if (!tokens[0].compare(vt))
    process_texture_vector(tokens);
  else if (!tokens[0].compare(vn))
    process_normal(tokens);
  else if (!tokens[0].compare(f))
    process_face(tokens);
  else {
    //ignore
  }
}
