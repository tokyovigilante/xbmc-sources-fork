/* 
xmms-projectM v0.99 - xmms-projectm.sourceforge.net
--------------------------------------------------

Lead Developers:  Carmelo Piccione (cep@andrew.cmu.edu) &
                  Peter Sperl (peter@sperl.com)

We have also been advised by some professors at CMU, namely Roger B. Dannenberg.
http://www-2.cs.cmu.edu/~rbd/    
  
The inspiration for this program was Milkdrop by Ryan Geiss. Obviously. 

This code is distributed under the GPL.


THANKS FOR THE CODE!!!
-------------------------------------------------
The base for this program was andy@nobugs.org's XMMS plugin tutorial
http://www.xmms.org/docs/vis-plugin.html

We used some FFT code by Takuya OOURA instead of XMMS' built-in fft code
fftsg.c - http://momonga.t.u-tokyo.ac.jp/~ooura/fft.html

For font rendering we used GLF by Roman Podobedov
glf.c - http://astronomy.swin.edu.au/~pbourke/opengl/glf/

and some beat detection code was inspired by Frederic Patin @
www.gamedev.net/reference/programming/features/beatdetection/
--

"ported" to XBMC by d4rk
d4rk@xboxmediacenter.com

*/


#include "xbmc_vis.h"
#include <GL/glew.h>
#include "libprojectM/projectM.hpp"
#include "libprojectM/Preset.hpp"
#include "libprojectM/PCM.hpp"
#include <string>
#ifdef _WIN32PC
#include "libprojectM/win32-dirent.h"
#include <io.h>
#else
#include "system.h"
#include "Util.h"
#include <dirent.h>
#endif

#ifdef _WIN32PC
#define PRESETS_DIR "visualisations\\projectM"
#define CONFIG_FILE "visualisations\\projectM.conf"
#else
#define PRESETS_DIR "Q:/visualisations/projectM"
#define CONFIG_FILE "P:/visualisations/projectM.conf"
#endif

projectM *globalPM = NULL;
extern int preset_index;

int maxSamples=512;

int texsize=512;
//int gx=32,gy=24;
int gx=40,gy=30;
int wvw=640,wvh=480;
int fvw=1280,fvh=960;
int g_Width=0, g_Height=0;
int g_PosX=0, g_PosY=0;
int fps=60, fullscreen=0;
char *disp;

char g_visName[512];
void* g_device;
float g_fWaveform[2][512];
char **g_presets=NULL;
int g_numPresets = 0;

std::string configFile;


// Some helper Functions

// case-insensitive alpha sort from projectM's win32-dirent.cc
#ifndef _WIN32PC
int alphasort(const void* lhs, const void* rhs) 
{
  const struct dirent* lhs_ent = *(struct dirent**)lhs;
  const struct dirent* rhs_ent = *(struct dirent**)rhs;
  return strcasecmp(lhs_ent->d_name, rhs_ent->d_name);
}
#endif

// check for a valid preset extension
#ifndef __APPLE__
int check_valid_extension(const struct dirent* ent) 
#else
int check_valid_extension(struct dirent* ent) 
#endif
{
  const char* ext = 0;
  
  if (!ent) return 0;
  
  ext = strrchr(ent->d_name, '.');
  if (!ext) ext = ent->d_name;
  
  if (0 == strcasecmp(ext, ".milk")) return 1;
  if (0 == strcasecmp(ext, ".prjm")) return 1;
  
  return 0;
}


//-- Create -------------------------------------------------------------------
// Called once when the visualisation is created by XBMC. Do any setup here.
//-----------------------------------------------------------------------------
#ifdef HAS_XBOX_HARDWARE
extern "C" void Create(LPDIRECT3DDEVICE8 pd3dDevice, int iPosX, int iPosY, int iWidth, int iHeight, const char* szVisualisationName, float fPixelRatio)
#else
extern "C" void Create(void* pd3dDevice, int iPosX, int iPosY, int iWidth, int iHeight, const char* szVisualisationName, float fPixelRatio)
#endif
{
  strcpy(g_visName, szVisualisationName);

  /** Initialise projectM */

#ifdef _WIN32PC
  std::string presetsDir = string(getenv("XBMC_HOME")) + "\\" + PRESETS_DIR;
  configFile = string(getenv("XBMC_PROFILE_USERDATA")) + "\\" + CONFIG_FILE;
#else
  std::string presetsDir = _P(PRESETS_DIR);
  configFile = _P(CONFIG_FILE);
#endif

  projectM::Settings configPM;
  configPM.meshX = gx;
  configPM.meshY = gy;
  configPM.fps = fps;
  configPM.textureSize = texsize;
  configPM.windowWidth = iWidth;
  configPM.windowHeight = iHeight;
  configPM.presetURL = presetsDir;
  configPM.smoothPresetDuration = 5;
  configPM.presetDuration = 15;
  configPM.beatSensitivity = 10.0;
  configPM.aspectCorrection = true;
  configPM.easterEgg = 0.0;
  configPM.shuffleEnabled = true;

  // workaround: projectM crashes without configFile and 
  // fstream won't create it
  FILE *f = fopen(configFile.c_str(), "r");
  if (f)
    fclose(f);
  else
  {
    f = fopen(configFile.c_str(), "w");
    if (f)
      fclose(f);
    projectM::writeConfig(configFile, configPM);
  }

  if (globalPM)
    delete globalPM;

  globalPM = new projectM(configFile);

  VisSetting setting(VisSetting::CHECK, "Shuffle Mode");
  setting.current = globalPM->isShuffleEnabled();
  m_vecSettings.push_back(setting);

  g_Width = iWidth;
  g_Height = iHeight;
  g_PosX = iPosX;
  g_PosY = iPosY;
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
  if (globalPM) 
  {
    projectM::writeConfig(configFile,globalPM->settings());
    delete globalPM;
    globalPM = NULL;
  }
  if (g_presets)
  {
    for (int i = 0 ; i<g_numPresets ; i++)
    {
      free(g_presets[i]);
    }
    free(g_presets);
    g_presets = NULL;
  }
  m_vecSettings.clear(); 
}

//-- Audiodata ----------------------------------------------------------------
// Called by XBMC to pass new audio data to the vis
//-----------------------------------------------------------------------------
extern "C" void AudioData(short* pAudioData, int iAudioDataLength, float *pFreqData, int iFreqDataLength)
{
  globalPM->pcm()->addPCM16Data(pAudioData, iAudioDataLength);
}


//-- Render -------------------------------------------------------------------
// Called once per frame. Do all rendering here.
//-----------------------------------------------------------------------------
extern "C" void Render()
{
  glClearColor(0,0,0,0);

  glMatrixMode(GL_TEXTURE);
  glPushMatrix();

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  // get current viewport since projectM modifies and does not reset
  GLint params[4];
  glGetIntegerv(GL_VIEWPORT, params);

  globalPM->projectM_resetGL(params[2], params[3]);

  glDisable(GL_DEPTH_TEST);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  globalPM->renderFrame();

  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  glMatrixMode(GL_TEXTURE);
  glPopMatrix();
  
  glEnable(GL_BLEND);          // Turn Blending On
  glDisable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  glEnable(GL_TEXTURE_2D);

  // reset viewport to what we got it
  glMatrixMode(GL_MODELVIEW);
  glViewport(params[0], params[1], params[2], params[3]);

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

  if (flags == VIS_ACTION_LOAD_PRESET && param)
  {
    int pindex = *((int *)param);
    globalPM->selectPreset(pindex);
    ret = true;
  }
  else if (flags == VIS_ACTION_NEXT_PRESET)
  {
//    switchPreset(ALPHA_NEXT, SOFT_CUT);
    ret = false;
  }
  else if (flags == VIS_ACTION_PREV_PRESET)
  {
//    switchPreset(ALPHA_PREVIOUS, SOFT_CUT);
    ret = false;
  }
  else if (flags == VIS_ACTION_RANDOM_PRESET)
  {
    globalPM->setShuffleEnabled(!globalPM->isShuffleEnabled());
    ret = true;
  }
  else if (flags == VIS_ACTION_LOCK_PRESET)
  {
    globalPM->setPresetLock(!globalPM->isPresetLocked());
    ret = true;
  }
  return ret;
}

//-- GetPresets ---------------------------------------------------------------
// Return a list of presets to XBMC for display
//-----------------------------------------------------------------------------
extern "C" void GetPresets(char ***pPresets, int *currentPreset, int *numPresets, bool *locked)
{
  if (!g_presets)
  {
    struct dirent** entries;
    fprintf(stderr, "Preset Dir: %s\n",globalPM->settings().presetURL.c_str());
    int dir_size = scandir(globalPM->settings().presetURL.c_str(), &entries,
                           check_valid_extension, alphasort);

    if (dir_size>0)
    {
      g_numPresets = dir_size;
      g_presets = (char **)malloc(sizeof(char*)*dir_size);
      if (g_presets)
      {
        for (int i = 0 ; i<dir_size ; i++)
        {
          g_presets[i] = (char*)malloc(strlen(entries[i]->d_name)+2);
          if (g_presets[i])
          {
            strcpy(g_presets[i], entries[i]->d_name);
          }
          free(entries[i]);
        }
        free(entries);
      }
    }
  }
  if (g_presets)
  {
    *pPresets = g_presets;
    *numPresets = g_numPresets;
    unsigned int presetIndex;
    if (globalPM->selectedPresetIndex(presetIndex) && presetIndex >= 0 &&
        (int)presetIndex < g_numPresets)
      *currentPreset = presetIndex;
  }
}

//-- GetSettings --------------------------------------------------------------
// Return the settings for XBMC to display
//-----------------------------------------------------------------------------
extern "C" void GetSettings(vector<VisSetting> **vecSettings)
{
  if (!vecSettings)
    return;
  *vecSettings = &m_vecSettings;
}

//-- UpdateSetting ------------------------------------------------------------
// Handle setting change request from XBMC
//-----------------------------------------------------------------------------
extern "C" void UpdateSetting(int num)
{
  VisSetting &setting = m_vecSettings[num];
  if (strcasecmp(setting.name, "Use Preset")==0)
    OnAction(34, (void*)&setting.current);
  else if (strcasecmp(setting.name, "Shuffle Mode")==0)
    OnAction(VIS_ACTION_RANDOM_PRESET, (void*)&setting.current);
}
