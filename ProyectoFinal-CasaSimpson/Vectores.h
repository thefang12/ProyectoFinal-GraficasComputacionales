#pragma once
#include <Windows.h>
#include <GL/GL.h>
#include <GL/glut.h>
#include <GL/GLU.h>
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
  Vector3F operator* (const float& c) const
  {

    Vector3F result;
    result.x = this->x * c;
    result.y = this->y * c;
    result.z = this->z * c;
    return result;
  }
  Vector3F operator+ (const float& c) const
  {

    Vector3F result;
    result.x = this->x + c;
    result.y = this->y + c;
    result.z = this->z + c;
    return result;
  }
  Vector3F operator+ (const Vector3F& c) const
  {

    Vector3F result;
    result.x = this->x + c.x;
    result.y = this->y + c.y;
    result.z = this->z + c.z;
    return result;
  }
  Vector3F operator+= (const Vector3F& c) const
  {

    Vector3F result;
    result.x = this->x + c.x;
    result.y = this->y + c.y;
    result.z = this->z + c.z;
    return result;
  }
  Vector3F operator-= (const Vector3F& c) const
  {

    Vector3F result;
    result.x = this->x - c.x;
    result.y = this->y - c.y;
    result.z = this->z - c.z;
    return result;
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
  Vector3I operator* (const int& c) const
  {

    Vector3I result;
    result.x = this->x * c;
    result.y = this->y * c;
    result.z = this->z * c;
    return result;
  }
  Vector3I operator+ (const int& c) const
  {

    Vector3I result;
    result.x = this->x + c;
    result.y = this->y + c;
    result.z = this->z + c;
    return result;
  }

};
class Vector4F {
public:
  GLfloat x, y, z, w;

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
  Vector4F operator* (const float& c) const
  {
 
    Vector4F result;
    result.x = this->x * c;
    result.y = this->y * c;
    result.z = this->z * c;
    return result;
  }
  Vector4F operator+ (const float& c) const
  {

    Vector4F result;
    result.x = this->x + c;
    result.y = this->y + c;
    result.z = this->z + c;
    return result;
  }


};
