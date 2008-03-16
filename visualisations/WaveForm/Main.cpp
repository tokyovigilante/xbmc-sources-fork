// Waveform.vis
// A simple visualisation example by MrC

#ifdef HAS_XBOX_HARDWARE
#include <xtl.h>
#endif
#include "../../../XBMC/visualisations/xbmc_vis.h"
#ifdef HAS_SDL_OPENGL
#include <SDL/SDL_opengl.h>
#endif

char g_visName[512];
#ifndef HAS_SDL_OPENGL
LPDIRECT3DDEVICE8 g_device;
#else
void* g_device;
#endif
float g_fWaveform[2][512];

#ifdef HAS_SDL_OPENGL
typedef struct {
  int X;
  int Y;
  int Width;
  int Height;
  int MinZ;
  int MaxZ;
} D3DVIEWPORT8;
#ifdef _WIN32PC
typedef unsigned long D3DCOLOR;
#endif
#endif

D3DVIEWPORT8  g_viewport;

struct Vertex_t
{
  float x, y, z, w;
  D3DCOLOR  col;
};

#ifndef HAS_SDL_OPENGL
#define VERTEX_FORMAT     (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
#endif

//-- Create -------------------------------------------------------------------
// Called once when the visualisation is created by XBMC. Do any setup here.
//-----------------------------------------------------------------------------
#ifndef HAS_SDL_OPENGL
extern "C" void Create(LPDIRECT3DDEVICE8 pd3dDevice, int iPosX, int iPosY, int iWidth, int iHeight, const char* szVisualisationName, float fPixelRatio)
#else
extern "C" void Create(void* pd3dDevice, int iPosX, int iPosY, int iWidth, int iHeight, const char* szVisualisationName, float fPixelRatio)
#endif
{
  //printf("Creating Waveform\n");
  strcpy(g_visName, szVisualisationName);
  g_device = pd3dDevice;
  g_viewport.X = iPosX;
  g_viewport.Y = iPosY;
  g_viewport.Width = iWidth;
  g_viewport.Height = iHeight;
  g_viewport.MinZ = 0;
  g_viewport.MaxZ = 1;
}

//-- Start --------------------------------------------------------------------
// Called when a new soundtrack is played
//-----------------------------------------------------------------------------
extern "C" void Start(int iChannels, int iSamplesPerSec, int iBitsPerSample, const char* szSongName)
{
  //printf("Got Start Command\n");
}

//-- Stop ---------------------------------------------------------------------
// Called when the visualisation is closed by XBMC
//-----------------------------------------------------------------------------
extern "C" void Stop()
{
  //printf("Got Stop Command\n");
}

//-- Audiodata ----------------------------------------------------------------
// Called by XBMC to pass new audio data to the vis
//-----------------------------------------------------------------------------
extern "C" void AudioData(short* pAudioData, int iAudioDataLength, float *pFreqData, int iFreqDataLength)
{
  // Convert the audio data into a floating -1 to +1 range
  int ipos=0;
  while (ipos < 512)
  {
    for (int i=0; i < iAudioDataLength; i+=2)
    {
      g_fWaveform[0][ipos] = pAudioData[i] / 32768.0f;    // left channel
      g_fWaveform[1][ipos] = pAudioData[i+1] / 32768.0f;  // right channel
      ipos++;
      if (ipos >= 512) break;
    }
  }
}


//-- Render -------------------------------------------------------------------
// Called once per frame. Do all rendering here.
//-----------------------------------------------------------------------------
extern "C" void Render()
{
  Vertex_t  verts[512];

#ifndef HAS_SDL_OPENGL
  g_device->SetVertexShader(VERTEX_FORMAT);
  g_device->SetPixelShader(NULL);
#endif

  // Left channel
#ifdef HAS_SDL_OPENGL
  GLenum errcode;
  glColor3f(1.0, 1.0, 1.0);
  glDisable(GL_BLEND);
  glPushMatrix();
  glTranslatef(0,0,-1.0);
  glBegin(GL_LINE_STRIP);
#endif
  for (int i = 0; i < 256; i++)
  {
    verts[i].col = 0xffffffff;
    verts[i].x = g_viewport.X + ((i / 255.0f) * g_viewport.Width);
    verts[i].y = g_viewport.Y + g_viewport.Height * 0.33f + (g_fWaveform[0][i] * g_viewport.Height * 0.15f);
    verts[i].z = 1.0;
    verts[i].w = 1;    
#ifdef HAS_SDL_OPENGL
    glVertex2f(verts[i].x, verts[i].y);
#endif
  }

#ifdef HAS_SDL_OPENGL
  glEnd();
  if ((errcode=glGetError())!=GL_NO_ERROR) {
    printf("Houston, we have a GL problem: %s\n", gluErrorString(errcode));
  }
#elif !defined(HAS_SDL_OPENGL)
  g_device->DrawPrimitiveUP(D3DPT_LINESTRIP, 255, verts, sizeof(Vertex_t));
#endif

  // Right channel
#ifdef HAS_SDL_OPENGL
  glBegin(GL_LINE_STRIP);
#endif
  for (int i = 0; i < 256; i++)
  {
    verts[i].col = 0xffffffff;
    verts[i].x = g_viewport.X + ((i / 255.0f) * g_viewport.Width);
    verts[i].y = g_viewport.Y + g_viewport.Height * 0.66f + (g_fWaveform[1][i] * g_viewport.Height * 0.15f);
    verts[i].z = 1.0;
    verts[i].w = 1;
#ifdef HAS_SDL_OPENGL
    glVertex2f(verts[i].x, verts[i].y);
#endif
  }

#ifdef HAS_SDL_OPENGL
  glEnd();
  glEnable(GL_BLEND);
  glPopMatrix();
  if ((errcode=glGetError())!=GL_NO_ERROR) {
    printf("Houston, we have a GL problem: %s\n", gluErrorString(errcode));
  }
#elif !defined(HAS_SDL_OPENGL)
  g_device->DrawPrimitiveUP(D3DPT_LINESTRIP, 255, verts, sizeof(Vertex_t));
#endif

}

//-- GetInfo ------------------------------------------------------------------
// Tell XBMC our requirements
//-----------------------------------------------------------------------------
extern "C" void GetInfo(VIS_INFO* pInfo)
{
  pInfo->bWantsFreq = false;
  pInfo->iSyncDelay = 0;
}

//-- OnAction -----------------------------------------------------------------
// Handle XBMC actions such as next preset, lock preset, album art changed etc
//-----------------------------------------------------------------------------
extern "C" bool OnAction(long flags, void *param)
{
  bool ret = false;
  return ret;
}

//-- GetPresets ---------------------------------------------------------------
// Return a list of presets to XBMC for display
//-----------------------------------------------------------------------------
extern "C" void GetPresets(char ***pPresets, int *currentPreset, int *numPresets, bool *locked)
{

}

//-- GetSettings --------------------------------------------------------------
// Return the settings for XBMC to display
//-----------------------------------------------------------------------------
extern "C" void GetSettings(vector<VisSetting> **vecSettings)
{
  return;
}

//-- UpdateSetting ------------------------------------------------------------
// Handle setting change request from XBMC
//-----------------------------------------------------------------------------
extern "C" void UpdateSetting(int num)
{

}
