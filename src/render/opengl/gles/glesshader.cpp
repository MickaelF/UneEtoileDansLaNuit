#include <UneEtoile/render/opengl/gles/glesshader.h>
#ifdef OPENGLES2_FOUND
GLESShader::GLESShader(const char* name, std::string_view vertex, std::string_view fragment) : CommonGLShader(name, vertex, fragment) {}
#endif