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
#define _USE_MATH_DEFINES
using namespace std;
typedef   void(*Renderer)();
class Vector2F {
public:
  GLfloat u, v;
  Vector2F() {
    u = 0;
    v = 0;
  }
  Vector2F(GLfloat x, GLfloat y) {
    u = x;
    v = y;
  }
};
class Vector3F {
public:
  GLfloat x, y, z;
  Vector3F() {
    x = 0;
    y = 0;
    z = 0;
  }
  Vector3F(GLfloat x, GLfloat y, GLfloat z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }

};
class Vector3I {
public:
  GLint x, y, z;
  Vector3I() {
    x = 0;
    y = 0;
    z = 0;
  }
  Vector3I(GLint x, GLint y, GLint z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }


};
class Vector4F {
public:
  GLfloat x, y, z,w;

  Vector4F() {
    x = 0;
    y = 0;
    z = 0;
    w = 0;
  }
  Vector4F(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
  }

};
class Material {

    Vector4F ambient, diffuse, especular;
    GLfloat exp;

  public:
    Material();
    Material(Vector4F ambient, Vector4F diffuse, Vector4F especular, GLfloat exp);

  private:

};
Material::Material() {
}

inline Material::Material(Vector4F ambient, Vector4F diffuse, Vector4F especular, GLfloat exp)
{
}



class ObjModel {
    string file_path;
    vector<Vector2F> texture_vertices;
    vector<Vector3F> vertices, normals; // v x y z w? | vt u v w? | vn x y z ... los comparten todos los grupos?
    vector <vector<Vector3I>>faces;//vertices of the polygon optionally 
    Material *materials; //pueden o no existir//usualmente cambian con el grupo // normalmente se especifican en un archivo aparte con la instruccion mtllib
    int vi, vti, vni, fi, objects = 0;
    Renderer * render_obj;
  public:
    ObjModel();
    ObjModel(string path);
    ObjModel(GLfloat *vertices, GLfloat *texture_vertices, GLfloat *normals, GLint **faces, Material *materials, Renderer *render_obj);
    ~ObjModel();
    void renderObject();
  private:
    void loadFromObjFile(string path);
    void process(string line);
    int check_error_bits(ifstream* f);

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

ObjModel::ObjModel(GLfloat *vertices, GLfloat *texture_vertices, GLfloat *normals, GLint **faces, Material *materials, Renderer *render_obj) {

}

ObjModel::~ObjModel() {
    //free(vertices);
    //free(texture_vertices);
    //free(normals);
    /*free(faces);*/
    free(materials);
}

void ObjModel::renderObject() {
    for (size_t i = 0; i < faces.size(); i++) {
        if (faces[i].size() == 4)
            glBegin(GL_QUADS);
        else if (faces[i].size() == 3)
            glBegin(GL_TRIANGLES);
        else 
          throw "Bad number of face vertexes";

        for (size_t j = 0; j < faces[i].size(); j++) {
            Vector3F vert = vertices[faces[i][j].x-1];
            glVertex3f(vert.x,vert.y,vert.z);
            Vector3F vn = normals[faces[i][j].z-1];
            glNormal3f(vn.x,vn.y,vn.z);
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
inline void ObjModel::process_matlib(vector<string> tokens) {
    //open file
    //create material
    //add to matrial array
}
inline void ObjModel::process_group(vector<string> tokens) {
    //start contruction new object
    //glBegin
}
inline void ObjModel::process_mat(vector<string> tokens) {

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
