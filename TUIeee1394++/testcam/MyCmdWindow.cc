/*
 *  $Id: MyCmdWindow.cc,v 1.1 2009-07-28 00:00:48 ueshiba Exp $
 */
#include <unistd.h>
#include <sys/time.h>
#include "multicam.h"
#include "MyCmdWindow.h"
#include "MyModalDialog.h"

namespace TU
{
/************************************************************************
*  static functions							*
************************************************************************/
static void
countTime(int& nframes, struct timeval& start)
{
    if (nframes == 10)
    {
	struct timeval	end;
	gettimeofday(&end, NULL);
	double	interval = (end.tv_sec  - start.tv_sec) +
	    (end.tv_usec - start.tv_usec) / 1.0e6;
	std::cerr << nframes / interval << " frames/sec" << std::endl;
	nframes = 0;
    }
    if (nframes++ == 0)
	gettimeofday(&start, NULL);
}

namespace v
{
CmdDef*		createMenuCmds(Ieee1394Camera& camera)		;
CmdDef*		createCaptureCmds()				;
CmdDef*		createFeatureCmds(const Ieee1394Camera& camera)	;
    
/************************************************************************
*  static data								*
************************************************************************/
static int	movieProp[3];

/************************************************************************
*  class MyCmdWindow							*
************************************************************************/
MyCmdWindow::MyCmdWindow(App&			parentApp,
			 Ieee1394Camera&	camera
#ifdef UseTrigger
			 , TriggerGenerator&	trigger
#endif
			)
    :CmdWindow(parentApp, "Ieee1394 camera controller",
	       0, Colormap::RGBColor, 16, 0, 0),
     _camera(camera),
#ifdef UseTrigger
     _trigger(trigger),
#endif
     _movie(),
     _menuCmd(*this, createMenuCmds(_camera)),
     _captureCmd(*this, createCaptureCmds()),
     _featureCmd(*this, createFeatureCmds(_camera)),
     _fileSelection(*this),
     _image(),
     _canvas(*this, _camera.width(), _camera.height(), _image),
     _timer(*this, 0)
{
    _camera.turnOff(Ieee1394Camera::TRIGGER_MODE)
	   .setTriggerMode(Ieee1394Camera::Trigger_Mode0);
	   
    _menuCmd.place(0, 0, 2, 1);
    _captureCmd.place(0, 1, 1, 1);
    _featureCmd.place(1, 1, 1, 1);
    _canvas.place(0, 2, 2, 1);

    show();
}

void
MyCmdWindow::callback(CmdId id, CmdVal val)
{
    using namespace	std;

    try
    {
	switch (id)
	{
	  case M_Exit:
	    app().exit();
	    break;

	  case M_Save:
	  {
	    ofstream	out;
	    if (_fileSelection.open(out))
	    {
#ifdef MONO_IMAGE
		_image.save(out, ImageBase::U_CHAR);
#else
		_image.save(out, ImageBase::YUV_422);
#endif
	    }
	  }
	    break;
	
	  case c_YUV444_160x120:
	  case c_YUV422_320x240:
	  case c_YUV411_640x480:
	  case c_YUV422_640x480:
	  case c_RGB24_640x480:
	  case c_MONO8_640x480:
	  case c_MONO16_640x480:
	  case c_YUV422_800x600:
	  case c_RGB24_800x600:
	  case c_MONO8_800x600:
	  case c_YUV422_1024x768:
	  case c_RGB24_1024x768:
	  case c_MONO8_1024x768:
	  case c_MONO16_800x600:
	  case c_MONO16_1024x768:
	  case c_YUV422_1280x960:
	  case c_RGB24_1280x960:
	  case c_MONO8_1280x960:
	  case c_YUV422_1600x1200:
	  case c_RGB24_1600x1200:
	  case c_MONO8_1600x1200:
	  case c_MONO16_1280x960:
	  case c_MONO16_1600x1200:
	    _camera.setFormatAndFrameRate(Ieee1394Camera::uintToFormat(id),
					  Ieee1394Camera::uintToFrameRate(val));
	    _canvas.resize(_camera.width(), _camera.height());
	    break;

	  case c_Format_7_0:
	  case c_Format_7_1:
	  case c_Format_7_2:
	  case c_Format_7_3:
	  case c_Format_7_4:
	  case c_Format_7_5:
	  case c_Format_7_6:
	  case c_Format_7_7:
	  {
	    Ieee1394Camera::Format	format7  = Ieee1394Camera::uintToFormat(id);
	    Ieee1394Camera::Format_7_Info
		fmt7info = _camera.getFormat_7_Info(format7);
	    MyModalDialog		modalDialog(*this, fmt7info);
	    u_int			u0, v0, width, height;
	    Ieee1394Camera::PixelFormat
		pixelFormat = modalDialog.getROI(u0, v0, width, height);
	    _camera.setFormat_7_ROI(format7, u0, v0, width, height)
		   .setFormat_7_PixelFormat(format7, pixelFormat)
		   .setFormatAndFrameRate(format7,
					  Ieee1394Camera::uintToFrameRate(val));
	    _canvas.resize(_camera.width(), _camera.height());
	  }
	    break;
	
	  case c_Brightness:
	  case c_AutoExposure:
	  case c_Sharpness:
	  case c_Hue:
	  case c_Saturation:
	  case c_Gamma:
	  case c_Shutter:
	  case c_Gain:
	  case c_Iris:
	  case c_Focus:
	  case c_Temperature:
	  case c_Zoom:
	    _camera.setValue(id2feature(id), val);
	    break;

	  case c_WhiteBalance_UB:
	    _camera.setWhiteBalance(val, _featureCmd.getValue(c_WhiteBalance_VR));
	    break;
	  case c_WhiteBalance_VR:
	    _camera.setWhiteBalance(_featureCmd.getValue(c_WhiteBalance_UB), val);
	    break;
      
	  case c_Brightness	 + OFFSET_ONOFF:
	  case c_AutoExposure    + OFFSET_ONOFF:
	  case c_Sharpness	 + OFFSET_ONOFF:
	  case c_WhiteBalance_UB + OFFSET_ONOFF:
	  case c_WhiteBalance_VR + OFFSET_ONOFF:
	  case c_Hue		 + OFFSET_ONOFF:
	  case c_Saturation	 + OFFSET_ONOFF:
	  case c_Gamma		 + OFFSET_ONOFF:
	  case c_Shutter	 + OFFSET_ONOFF:
	  case c_Gain		 + OFFSET_ONOFF:
	  case c_Iris		 + OFFSET_ONOFF:
	  case c_Focus		 + OFFSET_ONOFF:
	  case c_Temperature     + OFFSET_ONOFF:
	  case c_Zoom		 + OFFSET_ONOFF:
	  {
	    Ieee1394Camera::Feature feature = id2feature(id - OFFSET_ONOFF);
	    if (val)
		_camera.turnOn(feature);
	    else
		_camera.turnOff(feature);
	  }
	    break;
      
	  case c_Brightness	 + OFFSET_AUTO:
	  case c_AutoExposure    + OFFSET_AUTO:
	  case c_Sharpness	 + OFFSET_AUTO:
	  case c_WhiteBalance_UB + OFFSET_AUTO:
	  case c_WhiteBalance_VR + OFFSET_AUTO:
	  case c_Hue		 + OFFSET_AUTO:
	  case c_Saturation	 + OFFSET_AUTO:
	  case c_Gamma		 + OFFSET_AUTO:
	  case c_Shutter	 + OFFSET_AUTO:
	  case c_Gain		 + OFFSET_AUTO:
	  case c_Iris		 + OFFSET_AUTO:
	  case c_Focus		 + OFFSET_AUTO:
	  case c_Temperature     + OFFSET_AUTO:
	  case c_Zoom		 + OFFSET_AUTO:
	  {
	    Ieee1394Camera::Feature feature = id2feature(id - OFFSET_AUTO);
	    if (val)
		_camera.setAutoMode(feature);
	    else
	    {
		_camera.setManualMode(feature);
		if (feature == Ieee1394Camera::WHITE_BALANCE)
		    _camera
			.setWhiteBalance(_featureCmd.getValue(c_WhiteBalance_UB),
					 _featureCmd.getValue(c_WhiteBalance_VR));
		else
		    _camera.setValue(feature,
				     _featureCmd.getValue(id - OFFSET_AUTO));
	    }
	  }
	  break;

	  case c_ContinuousShot:
	    if (val)
	    {
		_camera.continuousShot();
		_timer.start(1);
	    }
	    else
	    {
		_timer.stop();
		_camera.stopContinuousShot();
	    }
	    break;
	
	  case c_OneShot:
	    stopContinuousShotIfRunning();
	    _camera.oneShot().snap() >> _image;
	    _canvas.repaintUnderlay();
	    break;

	  case c_Trigger:
	    if (val)
	    {
#ifdef UseTrigger
		_trigger.selectChannel(0xffffffff);
#endif
		_camera.turnOn(Ieee1394Camera::TRIGGER_MODE);
	    }
	    else
		_camera.turnOff(Ieee1394Camera::TRIGGER_MODE);
	    break;

	  case c_PlayMovie:
	    stopContinuousShotIfRunning();
	    _canvas.resize(_movie.width(), _movie.height());
	    for (_movie.rewind(); _movie; ++_movie)
	    {
		static int		nframes = 0;
		static struct timeval	start;
		countTime(nframes, start);

		_image = _movie.image();
		_canvas.repaintUnderlay();
		_captureCmd.setValue(c_StatusMovie, int(_movie.currentFrame()));
	    }
	    break;
	
	  case c_RecordMovie:
	  {
	    stopContinuousShotIfRunning();
#ifdef MONO_IMAGE
	    if (_camera.pixelFormat() != Ieee1394Camera::MONO_8)
	    {
		cerr << "Only MONO(8 bits) format is supported for movie!" << endl;
		break;
	    }
#else
	    if (_camera.pixelFormat() != Ieee1394Camera::YUV_422)
	    {
		cerr << "Only YUV(4:2:2) format is supported for movie!" << endl;
		break;
	    }
#endif
	    Array<pair<u_int, u_int> >	sizes(1);
	    sizes[0] = make_pair<u_int, u_int>(_camera.width(),
					       _camera.height());
	    _movie.alloc(sizes, _menuCmd.getValue(c_NFrames));
	    movieProp[0] = 0;
	    movieProp[1] = _movie.nframes() - 1;
	    movieProp[2] = 1;
	    _captureCmd.setProp(c_StatusMovie, movieProp);
	    _camera.continuousShot();
	    for (_movie.rewind(); _movie; ++_movie)
	    {
		cerr << _movie.currentFrame() << "-th frame captured!" << endl;
		static int		nframes = 0;
		static struct timeval	start;
		countTime(nframes, start);
#ifdef UseTrigger
		if (_captureCmd.getValue(c_Trigger))
		    _trigger.oneShot();
#endif
		_camera.snap() >> _movie.image();
		_captureCmd.setValue(c_StatusMovie, int(_movie.currentFrame()));
	    }
	    _camera.stopContinuousShot();
	  }
	    break;

	  case c_ForwardMovie:
	  {
	    int	frame = _captureCmd.getValue(c_StatusMovie) + 1;
	    if (frame < _movie.nframes())
	    {
		stopContinuousShotIfRunning();
		_movie.setFrame(frame);
		_canvas.resize(_movie.width(), _movie.height());
		_image = _movie.image();
		_canvas.repaintUnderlay();
		_captureCmd.setValue(c_StatusMovie, frame);
	    }
	  }
	    break;
	
	  case c_BackwardMovie:
	  {
	    int	frame = _captureCmd.getValue(c_StatusMovie) - 1;
	    if (frame >= 0)
	    {
		stopContinuousShotIfRunning();
		_movie.setFrame(frame);
		_canvas.resize(_movie.width(), _movie.height());
		_image = _movie.image();
		_canvas.repaintUnderlay();
		_captureCmd.setValue(c_StatusMovie, frame);
	    }
	  }
	    break;
	
	  case c_StatusMovie:
	    stopContinuousShotIfRunning();
	    _movie.setFrame(val);
	    _canvas.resize(_movie.width(), _movie.height());
	    _image = _movie.image();
	    _canvas.repaintUnderlay();
	    break;
	}
    }
    catch (exception& err)
    {
	cerr << err.what();
    }
}

void
MyCmdWindow::tick()
{
    static int			nframes = 0;
    static struct timeval	start;
    countTime(nframes, start);
#ifdef UseTrigger
    if (_captureCmd.getValue(c_Trigger))
	_trigger.oneShot();
#endif
    _camera.snap() >> _image;
    _canvas.repaintUnderlay();
}

void
MyCmdWindow::stopContinuousShotIfRunning()
{
    if (_captureCmd.getValue(c_ContinuousShot))
    {
	_timer.stop();
	_camera.stopContinuousShot();
	_captureCmd.setValue(c_ContinuousShot, 0);
    }
}
 
}
}
