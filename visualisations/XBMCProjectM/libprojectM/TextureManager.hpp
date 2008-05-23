#ifndef TextureManager_HPP
#define TextureManager_HPP

#include "PresetFrameIO.hpp"
#ifdef LINUX
#include <GL/gl.h>
#endif
#ifdef WIN32
#include <GL/glew.h>
#endif
#include "SOIL.h"
#include <iostream>
#include <string>
#include <map>

class TextureManager
{
  std::string presetURL;
  std::map<std::string,GLuint> textures;
public:
  ~TextureManager();
  TextureManager(std::string _presetURL);
  void unloadTextures(const PresetOutputs::cshape_container &shapes);
  void Clear();
  void Preload();
  GLuint getTexture(std::string imageUrl);
  unsigned int getTextureMemorySize();
};

#endif
