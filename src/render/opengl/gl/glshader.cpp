#include <UneEtoile/render/opengl/gl/glshader.h>
#ifdef OPENGL_FOUND
GLShader::GLShader(const char* name, std::string_view vertex, std::string_view fragment) : CommonGLShader(name, vertex, fragment) {}
#endif