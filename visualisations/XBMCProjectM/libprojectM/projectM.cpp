/**
 * projectM -- Milkdrop-esque visualisation SDK
 * Copyright (C)2003-2004 projectM Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * See 'LICENSE.txt' included within this release
 *
 */
#include "wipemalloc.h"
#include "BuiltinFuncs.hpp"
#include "fatal.h"
#include "Common.hpp"
#include "compare.h"
#ifdef WIN32
#include "win32-dirent.h"
#define CMAKE_INSTALL_PREFIX  ""
#endif

#include "timer.h"
#include <iostream>
#ifdef LINUX
#include "time.h"
#endif

#ifdef WIN32
#include <time.h>
#endif

//#include <xmms/plugin.h>
#include <iostream>
#include "projectM.hpp"
#include "BeatDetect.hpp"
#include "Eval.hpp"
#include "Param.hpp"
#include "Parser.hpp"
#include "Preset.hpp"
#include "PerPixelEqn.hpp"
#include "PresetMerge.hpp"
//#include "menu.h"
#include "PCM.hpp"                    //Sound data handler (buffering, FFT, etc.)
#include "CustomWave.hpp"
#include "CustomShape.hpp"
#include "IdlePreset.hpp"

#include <map>

#include "Renderer.hpp"
#include "PresetFrameIO.hpp"
#include "PresetChooser.hpp"
#include "ConfigFile.h"
#include "TextureManager.hpp"
#include "TimeKeeper.hpp"
#ifdef USE_THREADS
#include "pthread.h"
#endif
/*
DLLEXPORT projectM::projectM ( int gx, int gy, int fps, int texsize, int width, int height, std::string preset_url,std::string title_fonturl, std::string title_menuurl ) :beatDetect ( 0 ),  renderer ( 0 ), settings.presetURL ( preset_url ), title_fontURL ( title_fonturl ), menu_fontURL ( menu_fontURL ), smoothFrame ( 0 ), m_presetQueuePos(0)
{
	presetURL = preset_url;
	projectM_reset();
	projectM_init ( gx, gy, fps, texsize, width, height );
	projectM_resetGL ( width, height );
}
*/


projectM::~projectM()
{

 #ifdef USE_THREADS
  	printf("c");
	running = false;
	printf("l");
	pthread_cond_signal(&condition);
	printf("e");
	pthread_mutex_unlock( &mutex );
	printf("a");
	pthread_detach(thread);
	printf("n");
	pthread_cond_destroy(&condition);
	printf("u");
	pthread_mutex_destroy( &mutex );
	printf("p");
#endif
	destroyPresetTools();


	if ( renderer )
		delete ( renderer );
	if ( beatDetect )
		delete ( beatDetect );
	if ( _pcm ) {
		delete ( _pcm );
		_pcm = 0;
	}

	  
}

DLLEXPORT unsigned projectM::initRenderToTexture()
{
	return renderer->initRenderToTexture();
}

DLLEXPORT void projectM::projectM_resetTextures()
{
	renderer->ResetTextures();
}


DLLEXPORT  projectM::projectM ( std::string config_file, int flags) :
		beatDetect ( 0 ), renderer ( 0 ),  _pcm(0), m_presetPos(0), m_flags(flags)
{
	readConfig ( config_file );	
	projectM_reset();
	projectM_resetGL ( _settings.windowWidth, _settings.windowHeight);

}


bool projectM::writeConfig(const std::string & configFile, const Settings & settings) {
	
	ConfigFile config ( configFile );
	
	config.add("Mesh X", settings.meshX);
	config.add("Mesh Y", settings.meshY);
	config.add("Texture Size", settings.textureSize);
	config.add("FPS", settings.fps);
	config.add("Window Width", settings.windowWidth);
	config.add("Window Height", settings.windowHeight);
	config.add("Smooth Preset Duration", settings.smoothPresetDuration);
	config.add("Preset Duration", settings.presetDuration);
	config.add("Preset Path", settings.presetURL);
	config.add("Title Font", settings.titleFontURL);
	config.add("Menu Font", settings.menuFontURL);
	config.add("Hard Cut Sensitivity", settings.beatSensitivity);
	config.add("Aspect Correction", settings.aspectCorrection);
	config.add("Easter Egg Parameter", settings.easterEgg);
	config.add("Shuffle Enabled", settings.shuffleEnabled);
	
	std::fstream file(configFile.c_str());	
	if (file.is_open()) {
		file << config;
		return true;
	} else
		return false;
}



void projectM::readConfig (const std::string & configFile )
{

	ConfigFile config ( configFile );

	_settings.meshX = config.read<int> ( "Mesh X", 32 );
	_settings.meshY = config.read<int> ( "Mesh Y", 24 );
	_settings.textureSize = config.read<int> ( "Texsize", 512 );
	_settings.fps = config.read<int> ( "FPS", 35 );
	_settings.windowWidth  = config.read<int> ( "Window Width", 512 );
	_settings.windowHeight = config.read<int> ( "Window Height", 512 );
	_settings.smoothPresetDuration =  config.read<int> 
			( "Smooth Preset Duration", config.read<int>("Smooth Transition Duration", 10));
	_settings.presetDuration = config.read<int> ( "Preset Duration", 15 );
	_settings.presetURL = config.read<string> ( "Preset Path", CMAKE_INSTALL_PREFIX "/share/projectM/presets" );
	_settings.titleFontURL = config.read<string> 
			( "Title Font", CMAKE_INSTALL_PREFIX  "/share/projectM/fonts/Vera.ttf" );
	_settings.menuFontURL = config.read<string> 
			( "Menu Font", CMAKE_INSTALL_PREFIX  "/share/projectM/fonts/VeraMono.ttf" );
	_settings.shuffleEnabled = config.read<bool> ( "Shuffle Enabled", true);
			
	_settings.easterEgg = config.read<float> ( "Easter Egg Parameter", 0.0);
	
	
	 projectM_init ( _settings.meshX, _settings.meshY, _settings.fps,
			 _settings.textureSize, _settings.windowWidth,_settings.windowHeight);

	
	 _settings.beatSensitivity = beatDetect->beat_sensitivity = config.read<float> ( "Hard Cut Sensitivity", 10.0 );
	
	if ( config.read ( "Aspect Correction", true ) )
		_settings.aspectCorrection = renderer->correction = true;
	else 
		_settings.aspectCorrection = renderer->correction = false;

	
}

#ifdef USE_THREADS
static void *thread_callback(void *prjm) {
 projectM *p = (projectM *)prjm;

 p->thread_func(prjm); 
return NULL;} 


void *projectM::thread_func(void *vptr_args)
{
   pthread_mutex_lock( &mutex );
  //  printf("in thread: %f\n", timeKeeper->PresetProgressB());
  while (1)
    {   
      pthread_cond_wait( &condition, &mutex );
      if(!running)
	{
	  pthread_mutex_unlock( &mutex );
	  return NULL;
	}
     evaluateSecondPreset();
    }  
}
#endif

void projectM::evaluateSecondPreset()
{	
      setupPresetInputs(&m_activePreset2->presetInputs());
      m_activePreset2->presetInputs().frame = timeKeeper->PresetFrameB();
      m_activePreset2->presetInputs().progress= timeKeeper->PresetProgressB();
      
      assert ( m_activePreset2.get() );
      m_activePreset2->evaluateFrame();
      renderer->PerPixelMath ( &m_activePreset2->presetOutputs(), &presetInputs2 );
      renderer->WaveformMath ( &m_activePreset2->presetOutputs(), &presetInputs2, true );  
}

void projectM::setupPresetInputs(PresetInputs *inputs)
{
  inputs->ResetMesh();

  inputs->time = timeKeeper->GetRunningTime();
  inputs->bass = beatDetect->bass;
  inputs->mid = beatDetect->mid;
  inputs->treb = beatDetect->treb;
  inputs->bass_att = beatDetect->bass_att;
  inputs->mid_att = beatDetect->mid_att;
  inputs->treb_att = beatDetect->treb_att;
}

DLLEXPORT void projectM::renderFrame()
{

#ifdef DEBUG
	char fname[1024];
	FILE *f = NULL;
	int index = 0;
	int x, y;
#endif

	timeKeeper->UpdateTimers();

	//printf("A:%f, B:%f, S:%f\n", timeKeeper->PresetProgressA(), timeKeeper->PresetProgressB(), timeKeeper->SmoothRatio());
	mspf= ( int ) ( 1000.0/ ( float ) presetInputs.fps ); //milliseconds per frame

	setupPresetInputs(&m_activePreset->presetInputs());
	m_activePreset->presetInputs().frame = timeKeeper->PresetFrameA();
	m_activePreset->presetInputs().progress= timeKeeper->PresetProgressA();

	beatDetect->detectFromSamples();       

	//m_activePreset->evaluateFrame();

	if ( renderer->noSwitch==false && !m_presetChooser->empty() )
	{
		if ( timeKeeper->PresetProgressA()>=1.0 && !timeKeeper->IsSmoothing())
		{
 			
			timeKeeper->StartSmoothing();		      
			//	printf("Start Smooth\n");
			// if(timeKeeper->IsSmoothing())printf("Confirmed\n");
			switchPreset(m_activePreset2, 
				     &m_activePreset->presetInputs() == &presetInputs ? presetInputs2 : presetInputs, 
				&m_activePreset->presetOutputs() == &presetOutputs ? presetOutputs2 : presetOutputs);
		       
			presetSwitchedEvent(false, **m_presetPos);
		}
		
		else if ( ( beatDetect->vol-beatDetect->vol_old>beatDetect->beat_sensitivity ) && timeKeeper->CanHardCut() )
		{
		  // printf("Hard Cut\n");
			switchPreset(m_activePreset, presetInputs, presetOutputs);

			timeKeeper->StartPreset();
			presetSwitchedEvent(true, **m_presetPos);
		}		
	}



	if ( timeKeeper->IsSmoothing() && timeKeeper->SmoothRatio() <= 1.0 && !m_presetChooser->empty() )
	{
	  	  
	  //	 printf("start thread\n");
		      	
		assert ( m_activePreset.get() );
		
#ifdef USE_THREADS
		pthread_cond_signal(&condition);
		pthread_mutex_unlock( &mutex );
#endif
		m_activePreset->evaluateFrame();
		renderer->PerPixelMath ( &m_activePreset->presetOutputs(), &presetInputs );
		renderer->WaveformMath ( &m_activePreset->presetOutputs(), &presetInputs, true );

#ifdef USE_THREADS
		pthread_mutex_lock( &mutex );
#else		
		evaluateSecondPreset();
#endif
		
		
		PresetMerger::MergePresets ( m_activePreset->presetOutputs(),m_activePreset2->presetOutputs(),timeKeeper->SmoothRatio(),presetInputs.gx, presetInputs.gy );	       

	}
	else
	{
		if ( timeKeeper->IsSmoothing() && timeKeeper->SmoothRatio() > 1.0 )
		{
		  //printf("End Smooth\n");
			m_activePreset = m_activePreset2;			
			timeKeeper->EndSmoothing();
		}
		//printf("Normal\n");
	
		m_activePreset->evaluateFrame();

		renderer->PerPixelMath ( &m_activePreset->presetOutputs(), &presetInputs );
		renderer->WaveformMath ( &m_activePreset->presetOutputs(), &presetInputs, false );

	}

	//	std::cout<< m_activePreset->absoluteFilePath()<<std::endl;
	//	renderer->presetName = m_activePreset->absoluteFilePath();

	renderer->RenderFrame ( &m_activePreset->presetOutputs(), &presetInputs );

	count++;
#ifndef WIN32
	/** Frame-rate limiter */
	/** Compute once per preset */
	if ( this->count%100==0 )
	{
		this->renderer->realfps=100.0/ ( ( getTicks ( &timeKeeper->startTime )-this->fpsstart ) /1000 );
		this->fpsstart=getTicks ( &timeKeeper->startTime );
	}

	int timediff = getTicks ( &timeKeeper->startTime )-this->timestart;

	if ( timediff < this->mspf )
	{
		// printf("%s:",this->mspf-timediff);
		int sleepTime = ( unsigned int ) ( this->mspf-timediff ) * 1000;
//		DWRITE ( "usleep: %d\n", sleepTime );
		if ( sleepTime > 0 && sleepTime < 100000 )
		{
			if ( usleep ( sleepTime ) != 0 ) {}}
	}
	this->timestart=getTicks ( &timeKeeper->startTime );
#endif /** !WIN32 */


}

void projectM::projectM_reset()
{

	/** Default variable settings */

	this->wvw = 512;
	this->wvh = 512;      

	/** More other stuff */
	this->mspf = 0;
	this->timed = 0;
	this->timestart = 0;       
	this->count = 0;

	this->fpsstart = 0;

	projectM_resetengine();
}

void projectM::projectM_init ( int gx, int gy, int fps, int texsize, int width, int height )
{

	/** Initialise engine variables */

	projectM_initengine();
	presetInputs.Initialize ( gx, gy );
	presetInputs2.Initialize ( gx, gy );
	presetOutputs.Initialize ( gx, gy );
	presetOutputs2.Initialize ( gx, gy );

	/** Initialise start time */
        timeKeeper = new TimeKeeper(_settings.presetDuration,_settings.smoothPresetDuration, _settings.easterEgg);

	/** Nullify frame stash */


	/** Initialise per-pixel matrix calculations */


	presetInputs.fps = fps;
	presetInputs2.fps = fps;
	/** We need to initialise this before the builtin param db otherwise bass/mid etc won't bind correctly */
	assert ( !beatDetect );

	std::cerr << "pcm new" << std::endl;
	if (!_pcm)
		_pcm = new PCM();
	assert(pcm());
	beatDetect = new BeatDetect ( _pcm );

	initPresetTools();
	if ( presetInputs.fps > 0 )
		mspf= ( int ) ( 1000.0/ ( float ) presetInputs.fps );
	else mspf = 0;
	
	this->presetInputs.gx = gx;
	this->presetInputs.gy = gy;
	this->presetInputs2.gx = gx;
	this->presetInputs2.gy = gy;

	this->renderer = new Renderer ( width, height, gx, gy, texsize,  beatDetect, settings().presetURL, settings().titleFontURL, settings().menuFontURL );

	running = true;

#ifdef USE_THREADS
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&condition, NULL);
	if (pthread_create(&thread, NULL, thread_callback, this) != 0)
	    { 	      
	      printf("oops\n");
	      exit(1);
	    }
	pthread_mutex_lock( &mutex );
	printf("got lock\n");
#endif

	renderer->setPresetName ( m_activePreset->presetName() );
	timeKeeper->StartPreset();
	assert(pcm());
//	printf ( "exiting projectM_init()\n" );
}


void projectM::projectM_initengine()
{

	/* PER FRAME CONSTANTS BEGIN */
	this->presetOutputs.zoom=1.0;
	this->presetOutputs.zoomexp= 1.0;
	this->presetOutputs.rot= 0.0;
	this->presetOutputs.warp= 0.0;

	this->presetOutputs.sx= 1.0;
	this->presetOutputs.sy= 1.0;
	this->presetOutputs.dx= 0.0;
	this->presetOutputs.dy= 0.0;
	this->presetOutputs.cx= 0.5;
	this->presetOutputs.cy= 0.5;

	this->presetOutputs.decay=.98;

	this->presetOutputs.wave_r= 1.0;
	this->presetOutputs.wave_g= 0.2;
	this->presetOutputs.wave_b= 0.0;
	this->presetOutputs.wave_x= 0.5;
	this->presetOutputs.wave_y= 0.5;
	this->presetOutputs.wave_mystery= 0.0;

	this->presetOutputs.ob_size= 0.0;
	this->presetOutputs.ob_r= 0.0;
	this->presetOutputs.ob_g= 0.0;
	this->presetOutputs.ob_b= 0.0;
	this->presetOutputs.ob_a= 0.0;

	this->presetOutputs.ib_size = 0.0;
	this->presetOutputs.ib_r = 0.0;
	this->presetOutputs.ib_g = 0.0;
	this->presetOutputs.ib_b = 0.0;
	this->presetOutputs.ib_a = 0.0;

	this->presetOutputs.mv_a = 0.0;
	this->presetOutputs.mv_r = 0.0;
	this->presetOutputs.mv_g = 0.0;
	this->presetOutputs.mv_b = 0.0;
	this->presetOutputs.mv_l = 1.0;
	this->presetOutputs.mv_x = 16.0;
	this->presetOutputs.mv_y = 12.0;
	this->presetOutputs.mv_dy = 0.02;
	this->presetOutputs.mv_dx = 0.02;

//this->presetInputs.meshx = 0;
//this->presetInputs.meshy = 0;


	this->presetInputs.progress = 0;
	this->presetInputs.frame = 1; 
      	this->presetInputs2.progress = 0;
	this->presetInputs2.frame = 1;
//bass_thresh = 0;

	/* PER_FRAME CONSTANTS END */
	this->presetOutputs.fRating = 0;
	this->presetOutputs.fGammaAdj = 1.0;
	this->presetOutputs.fVideoEchoZoom = 1.0;
	this->presetOutputs.fVideoEchoAlpha = 0;
	this->presetOutputs.nVideoEchoOrientation = 0;

	this->presetOutputs.nWaveMode = 7;
	this->presetOutputs.bAdditiveWaves = 0;
	this->presetOutputs.bWaveDots = 0;
	this->presetOutputs.bWaveThick = 0;
	this->presetOutputs.bModWaveAlphaByVolume = 0;
	this->presetOutputs.bMaximizeWaveColor = 0;
	this->presetOutputs.bTexWrap = 0;
	this->presetOutputs.bDarkenCenter = 0;
	this->presetOutputs.bRedBlueStereo = 0;
	this->presetOutputs.bBrighten = 0;
	this->presetOutputs.bDarken = 0;
	this->presetOutputs.bSolarize = 0;
	this->presetOutputs.bInvert = 0;
	this->presetOutputs.bMotionVectorsOn = 1;

	this->presetOutputs.fWaveAlpha =1.0;
	this->presetOutputs.fWaveScale = 1.0;
	this->presetOutputs.fWaveSmoothing = 0;
	this->presetOutputs.fWaveParam = 0;
	this->presetOutputs.fModWaveAlphaStart = 0;
	this->presetOutputs.fModWaveAlphaEnd = 0;
	this->presetOutputs.fWarpAnimSpeed = 0;
	this->presetOutputs.fWarpScale = 0;
	this->presetOutputs.fShader = 0;


	/* PER_PIXEL CONSTANTS BEGIN */

	/* PER_PIXEL CONSTANT END */


	/* Q AND T VARIABLES START */

	this->presetOutputs.q1 = 0;
	this->presetOutputs.q2 = 0;
	this->presetOutputs.q3 = 0;
	this->presetOutputs.q4 = 0;
	this->presetOutputs.q5 = 0;
	this->presetOutputs.q6 = 0;
	this->presetOutputs.q7 = 0;
	this->presetOutputs.q8 = 0;


	/* Q AND T VARIABLES END */

}

/* Reinitializes the engine variables to a default (conservative and sane) value */
void projectM::projectM_resetengine()
{

	this->presetOutputs.zoom=1.0;
	this->presetOutputs.zoomexp= 1.0;
	this->presetOutputs.rot= 0.0;
	this->presetOutputs.warp= 0.0;

	this->presetOutputs.sx= 1.0;
	this->presetOutputs.sy= 1.0;
	this->presetOutputs.dx= 0.0;
	this->presetOutputs.dy= 0.0;
	this->presetOutputs.cx= 0.5;
	this->presetOutputs.cy= 0.5;

	this->presetOutputs.decay=.98;

	this->presetOutputs.wave_r= 1.0;
	this->presetOutputs.wave_g= 0.2;
	this->presetOutputs.wave_b= 0.0;
	this->presetOutputs.wave_x= 0.5;
	this->presetOutputs.wave_y= 0.5;
	this->presetOutputs.wave_mystery= 0.0;

	this->presetOutputs.ob_size= 0.0;
	this->presetOutputs.ob_r= 0.0;
	this->presetOutputs.ob_g= 0.0;
	this->presetOutputs.ob_b= 0.0;
	this->presetOutputs.ob_a= 0.0;

	this->presetOutputs.ib_size = 0.0;
	this->presetOutputs.ib_r = 0.0;
	this->presetOutputs.ib_g = 0.0;
	this->presetOutputs.ib_b = 0.0;
	this->presetOutputs.ib_a = 0.0;

	this->presetOutputs.mv_a = 0.0;
	this->presetOutputs.mv_r = 0.0;
	this->presetOutputs.mv_g = 0.0;
	this->presetOutputs.mv_b = 0.0;
	this->presetOutputs.mv_l = 1.0;
	this->presetOutputs.mv_x = 16.0;
	this->presetOutputs.mv_y = 12.0;
	this->presetOutputs.mv_dy = 0.02;
	this->presetOutputs.mv_dx = 0.02;


	if ( beatDetect != NULL )
	{
		beatDetect->reset();
	}
	this->presetInputs.progress = 0;
	this->presetInputs.frame = 1;
	this->presetInputs2.progress = 0;
	this->presetInputs2.frame = 1;
// bass_thresh = 0;

	/* PER_FRAME CONSTANTS END */
	this->presetOutputs.fRating = 0;
	this->presetOutputs.fGammaAdj = 1.0;
	this->presetOutputs.fVideoEchoZoom = 1.0;
	this->presetOutputs.fVideoEchoAlpha = 0;
	this->presetOutputs.nVideoEchoOrientation = 0;

	this->presetOutputs.nWaveMode = 7;
	this->presetOutputs.bAdditiveWaves = 0;
	this->presetOutputs.bWaveDots = 0;
	this->presetOutputs.bWaveThick = 0;
	this->presetOutputs.bModWaveAlphaByVolume = 0;
	this->presetOutputs.bMaximizeWaveColor = 0;
	this->presetOutputs.bTexWrap = 0;
	this->presetOutputs.bDarkenCenter = 0;
	this->presetOutputs.bRedBlueStereo = 0;
	this->presetOutputs.bBrighten = 0;
	this->presetOutputs.bDarken = 0;
	this->presetOutputs.bSolarize = 0;
	this->presetOutputs.bInvert = 0;
	this->presetOutputs.bMotionVectorsOn = 1;

	this->presetOutputs.fWaveAlpha =1.0;
	this->presetOutputs.fWaveScale = 1.0;
	this->presetOutputs.fWaveSmoothing = 0;
	this->presetOutputs.fWaveParam = 0;
	this->presetOutputs.fModWaveAlphaStart = 0;
	this->presetOutputs.fModWaveAlphaEnd = 0;
	this->presetOutputs.fWarpAnimSpeed = 0;
	this->presetOutputs.fWarpScale = 0;
	this->presetOutputs.fShader = 0;


	/* PER_PIXEL CONSTANTS BEGIN */
	this->presetInputs2.x_per_pixel = 0;
	this->presetInputs2.y_per_pixel = 0;
	this->presetInputs2.rad_per_pixel = 0;
	this->presetInputs2.ang_per_pixel = 0;
	this->presetInputs.x_per_pixel = 0;
	this->presetInputs.y_per_pixel = 0;
	this->presetInputs.rad_per_pixel = 0;
	this->presetInputs.ang_per_pixel = 0;

	/* PER_PIXEL CONSTANT END */

	/* Q VARIABLES START */

	this->presetOutputs.q1 = 0;
	this->presetOutputs.q2 = 0;
	this->presetOutputs.q3 = 0;
	this->presetOutputs.q4 = 0;
	this->presetOutputs.q5 = 0;
	this->presetOutputs.q6 = 0;
	this->presetOutputs.q7 = 0;
	this->presetOutputs.q8 = 0;


	/* Q VARIABLES END */

}

/** Resets OpenGL state */
DLLEXPORT void projectM::projectM_resetGL ( int w, int h )
{

	/** Stash the new dimensions */

	renderer->reset ( w,h );
}

/** Sets the title to display */
DLLEXPORT void projectM::projectM_setTitle ( std::string title )
{
	if ( title != renderer->title )
	{
		renderer->title=title;
		renderer->drawtitle=1;
	}
}


int projectM::initPresetTools()
{

	/* Initializes the builtin function database */
	BuiltinFuncs::init_builtin_func_db();

	/* Initializes all infix operators */
	Eval::init_infix_ops();

	/* Set the seed to the current time in seconds */
	srand ( time ( NULL ) );

	std::string url = (m_flags & FLAG_DISABLE_PLAYLIST_LOAD) ? std::string() : settings().presetURL;
	
	if ( ( m_presetLoader = new PresetLoader ( url) ) == 0 )
	{
		m_presetLoader = 0;
		std::cerr << "[projectM] error allocating preset loader" << std::endl;
		return PROJECTM_FAILURE;
	}

	if ( ( m_presetChooser = new PresetChooser ( *m_presetLoader ) ) == 0 )
	{
		delete ( m_presetLoader );

		m_presetChooser = 0;
		m_presetLoader = 0;

		std::cerr << "[projectM] error allocating preset chooser" << std::endl;
		return PROJECTM_FAILURE;
	}

	// Start the iterator
	if (!m_presetPos)
		m_presetPos = new PresetIterator();

	// Initialize a preset queue position as well
//	m_presetQueuePos = new PresetIterator();

	// Start at end ptr- this allows next/previous to easily be done from this position.
	*m_presetPos = m_presetChooser->end();

	// Load idle preset
	//std::cerr << "[projectM] Allocating idle preset..." << std::endl;
	m_activePreset = IdlePreset::allocate ( presetInputs, presetOutputs );

	// Case where no valid presets exist in directory. Could also mean 
	// playlist initialization was deferred
	//if ( m_presetChooser->empty() )
	//{
		//std::cerr << "[projectM] warning: no valid files found in preset directory \""
		//<< m_presetLoader->directoryName() << "\"" << std::endl;
	//}

	//std::cerr << "[projectM] Idle preset allocated." << std::endl;

	projectM_resetengine();

	//std::cerr << "[projectM] engine has been reset." << std::endl;
	return PROJECTM_SUCCESS;
}

void projectM::destroyPresetTools()
{

	if ( m_presetPos )
		delete ( m_presetPos );

	/// @slow might not be necessary
	m_presetPos = 0;

	if ( m_presetChooser )
		delete ( m_presetChooser );

	/// @slow might not be necessary
	m_presetChooser = 0;

	if ( m_presetLoader )
		delete ( m_presetLoader );

	/// @slow might not be necessary
	m_presetLoader = 0;

	Eval::destroy_infix_ops();
	BuiltinFuncs::destroy_builtin_func_db();

}

/// @bug queuePreset case isn't handled
void projectM::removePreset(unsigned int index) {
	
	unsigned int chooserIndex = **m_presetPos;

	m_presetLoader->removePreset(index);


	// Case: no more presets, set iterator to end
	if (m_presetChooser->empty()) 
		*m_presetPos = m_presetChooser->end();
	
	// Case: chooser index has become one less due to removal of an index below it
	else if (chooserIndex > index) {
		chooserIndex--;
		*m_presetPos = m_presetChooser->begin(chooserIndex);
	}

	// Case: we have deleted the active preset position
	// Set iterator to end of chooser
	else if (chooserIndex == index) { 
		//*m_presetPos = m_presetChooser->begin(chooserIndex);
		std::cerr << "deleted active preset!";
		*m_presetPos = m_presetChooser->end();
	}

	

}

unsigned int projectM::addPresetURL ( const std::string & presetURL, const std::string & presetName, int rating )
{	
	bool restorePosition = false;
	
	if (*m_presetPos == m_presetChooser->end()) 
		restorePosition = true;
	
	int index = m_presetLoader->addPresetURL ( presetURL, presetName, rating);
	
	if (restorePosition)
		*m_presetPos = m_presetChooser->end();
	
	return index;
}

void projectM::selectPreset ( unsigned int index )
{

	if ( m_presetChooser->empty() )
		return;

	assert ( index < m_presetLoader->getNumPresets() );
	assert ( index >= 0 );

	*m_presetPos = m_presetChooser->begin ( index );

	m_activePreset = m_presetPos->allocate ( presetInputs, presetOutputs );

	renderer->setPresetName ( m_activePreset->presetName() );

	timeKeeper->StartPreset();
}

void projectM::switchPreset(std::auto_ptr<Preset> & targetPreset, PresetInputs & inputs, PresetOutputs & outputs) {

	if (_settings.shuffleEnabled)
		*m_presetPos = m_presetChooser->weightedRandom();
	else
		m_presetChooser->nextPreset(*m_presetPos);
					
	targetPreset = m_presetPos->allocate( inputs, outputs );

	// Set preset name here- event is not done because at the moment this function is oblivious to smooth/hard switches
	renderer->setPresetName ( targetPreset->presetName() );


}

void projectM::setPresetLock ( bool isLocked )
{
	renderer->noSwitch = isLocked;
}

bool projectM::isPresetLocked() const
{
	return renderer->noSwitch;
}

std::string projectM::getPresetURL ( unsigned int index ) const
{
	return m_presetLoader->getPresetURL(index);
}

int projectM::getPresetRating ( unsigned int index ) const
{
	return m_presetLoader->getPresetRating(index);
}

std::string projectM::getPresetName ( unsigned int index ) const
{
	return m_presetLoader->getPresetName(index);
}

void projectM::clearPlaylist ( ) 
{
	
	m_presetLoader->clear();
	*m_presetPos = m_presetChooser->end();
	
}

/// Sets preset iterator position to the passed in index
void projectM::selectPresetPosition(unsigned int index) {
	*m_presetPos = m_presetChooser->begin(index);
}

bool projectM::selectedPresetIndex(unsigned int & index) const {
	
	if (*m_presetPos == m_presetChooser->end())
		return false;
	
	index = **m_presetPos;
	return true;
}


bool projectM::presetPositionValid() const {
	
	return (*m_presetPos != m_presetChooser->end());
}		
	
unsigned int projectM::getPlaylistSize() const
{
	return m_presetLoader->getNumPresets();
}

void projectM:: changePresetRating (unsigned int index, int rating) {
	m_presetLoader->setRating(index, rating);
}

void projectM::insertPresetURL(unsigned int index, const std::string & presetURL, const std::string & presetName, int rating)
{
	bool atEndPosition = false;
	
	int newSelectedIndex;
	
	
	if (*m_presetPos == m_presetChooser->end()) // Case: preset not selected
	{
		atEndPosition = true;	
	}
	
	else if (**m_presetPos < index) // Case: inserting before selected preset
	{
		newSelectedIndex = **m_presetPos;			
	} 
	
	else if (**m_presetPos > index) // Case: inserting after selected preset	
	{
		newSelectedIndex++;
	} 
	
	else  // Case: inserting at selected preset
	{
		newSelectedIndex++;
	}
	
	m_presetLoader->insertPresetURL (index, presetURL, presetName, rating);
	
	if (atEndPosition)
		*m_presetPos = m_presetChooser->end();
	else
		*m_presetPos = m_presetChooser->begin(newSelectedIndex);
	
	
}


 

