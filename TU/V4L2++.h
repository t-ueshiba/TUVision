/*
 *  $Id$
 */
/*!
  \mainpage	libTUV4L2++ - Video for Linux v.2デバイスを制御するC++ライブラリ
  \anchor	libTUV4L2
*/
#ifndef __TU_V4L2PP_H
#define __TU_V4L2PP_H

#include <asm/types.h>		// for videodev2.h
#include <linux/videodev2.h>
#include <vector>
#include <string>
#include <boost/iterator_adaptors.hpp>
#ifdef HAVE_LIBTUTOOLS__
#  include "TU/Image++.h"
#endif

/*!
  \namespace	TU
  \brief	本ライブラリで定義されたクラスおよび関数を収める名前空間
*/
namespace TU
{
/************************************************************************
*  class V4L2Camera							*
************************************************************************/
//! Video for Linux v.2 に対応するカメラを表すクラス
class V4L2Camera
{
  public:
  //! 出力画像の画素の形式    
    enum PixelFormat
    {
	BGR24	= V4L2_PIX_FMT_BGR24,	//!< 24 bits/pix, BGR-8-8-8
	RGB24	= V4L2_PIX_FMT_RGB24,	//!< 24 bits/pix, RGB-8-8-8
	BGR32	= V4L2_PIX_FMT_BGR32,	//!< 32 bits/pix, BGR-8-8-8-8
	RGB32	= V4L2_PIX_FMT_RGB32,	//!< 32 bits/pix, RGB-8-8-8-8

	GREY	= V4L2_PIX_FMT_GREY,	//!<  8 bits/pix, Greyscale
	Y16	= V4L2_PIX_FMT_Y16,	//!< 16 bits/pix, Greyscale

	YUYV	= V4L2_PIX_FMT_YUYV,	//!< 16 bits/pix, YUV 4:2:2
	UYVY	= V4L2_PIX_FMT_UYVY,	//!< 16 bits/pix, YUV 4:2:2

	SBGGR8	= V4L2_PIX_FMT_SBGGR8,	//!<  8 bits/pix, BGGR bayer pattern
	SGBRG8	= V4L2_PIX_FMT_SGBRG8,	//!<  8 bits/pix, GBRG bayer pattern
	SGRBG8	= V4L2_PIX_FMT_SGRBG8,	//!<  8 bits/pix, GRBG bayer pattern

	UNKNOWN_PIXEL_FORMAT = v4l2_fourcc('U', 'K', 'N', 'W')
    };

  //! カメラの属性
    enum Feature
    {
	BRIGHTNESS			= V4L2_CID_BRIGHTNESS,
	BRIGHTNESS_AUTO			= V4L2_CID_AUTOBRIGHTNESS,
	CONTRAST			= V4L2_CID_CONTRAST,
	GAIN				= V4L2_CID_GAIN,
	GAIN_AUTO			= V4L2_CID_AUTOGAIN,
	SATURATION			= V4L2_CID_SATURATION,
	HUE				= V4L2_CID_HUE,
	HUE_AUTO			= V4L2_CID_HUE_AUTO,
	GAMMA				= V4L2_CID_GAMMA,
	SHARPNESS			= V4L2_CID_SHARPNESS,
	BLACK_LEVEL			= V4L2_CID_BLACK_LEVEL,
	WHITE_BALANCE_TEMPERATURE	= V4L2_CID_WHITE_BALANCE_TEMPERATURE,
	WHITE_BALANCE_AUTO		= V4L2_CID_AUTO_WHITE_BALANCE,
	RED_BALANCE			= V4L2_CID_RED_BALANCE,
	BLUE_BALANCE			= V4L2_CID_BLUE_BALANCE,
	HFLIP				= V4L2_CID_HFLIP,
	VFLIP				= V4L2_CID_VFLIP,
	BACKLIGHT_COMPENSATION		= V4L2_CID_BACKLIGHT_COMPENSATION,
	POWER_LINE_FREQUENCY		= V4L2_CID_POWER_LINE_FREQUENCY,
	EXPOSURE_AUTO			= V4L2_CID_EXPOSURE_AUTO,
	EXPOSURE_AUTO_PRIORITY		= V4L2_CID_EXPOSURE_AUTO_PRIORITY,
	EXPOSURE_ABSOLUTE		= V4L2_CID_EXPOSURE_ABSOLUTE,
	FOCUS_ABSOLUTE			= V4L2_CID_FOCUS_ABSOLUTE,
	FOCUS_RELATIVE			= V4L2_CID_FOCUS_RELATIVE,
	FOCUS_AUTO			= V4L2_CID_FOCUS_AUTO,
	ZOOM_ABSOLUTE			= V4L2_CID_ZOOM_ABSOLUTE,
	ZOOM_RELATIVE			= V4L2_CID_ZOOM_RELATIVE,
	ZOOM_CONTINUOUS			= V4L2_CID_ZOOM_CONTINUOUS,
#ifdef V4L2_CID_IRIS_ABSOLUTE
	IRIS_ABSOLUTE			= V4L2_CID_IRIS_ABSOLUTE,
#endif
#ifdef V4L2_CID_IRIS_RELATIVE
	IRIS_RELATIVE			= V4L2_CID_IRIS_RELATIVE,
#endif
	PAN_ABSOLUTE			= V4L2_CID_PAN_ABSOLUTE,
	PAN_RELATIVE			= V4L2_CID_PAN_RELATIVE,
	PAN_RESET			= V4L2_CID_PAN_RESET,
	TILT_ABSOLUTE			= V4L2_CID_TILT_ABSOLUTE,
	TILT_RELATIVE			= V4L2_CID_TILT_RELATIVE,
	TILT_RESET			= V4L2_CID_TILT_RESET,

	CID_PRIVATE0			= V4L2_CID_PRIVATE_BASE + 0,
	CID_PRIVATE1			= V4L2_CID_PRIVATE_BASE + 1,
	CID_PRIVATE2			= V4L2_CID_PRIVATE_BASE + 2,
	CID_PRIVATE3			= V4L2_CID_PRIVATE_BASE + 3,
	CID_PRIVATE4			= V4L2_CID_PRIVATE_BASE + 4,
	CID_PRIVATE5			= V4L2_CID_PRIVATE_BASE + 5,
	CID_PRIVATE6			= V4L2_CID_PRIVATE_BASE + 6,
	CID_PRIVATE7			= V4L2_CID_PRIVATE_BASE + 7,
	CID_PRIVATE8			= V4L2_CID_PRIVATE_BASE + 8,
	CID_PRIVATE9			= V4L2_CID_PRIVATE_BASE + 9,
	CID_PRIVATE10			= V4L2_CID_PRIVATE_BASE + 10,
	CID_PRIVATE11			= V4L2_CID_PRIVATE_BASE + 11,
	CID_PRIVATE12			= V4L2_CID_PRIVATE_BASE + 12,
	CID_PRIVATE13			= V4L2_CID_PRIVATE_BASE + 13,
	CID_PRIVATE14			= V4L2_CID_PRIVATE_BASE + 14,
	CID_PRIVATE15			= V4L2_CID_PRIVATE_BASE + 15,
	CID_PRIVATE16			= V4L2_CID_PRIVATE_BASE + 16,
	CID_PRIVATE17			= V4L2_CID_PRIVATE_BASE + 17,
	CID_PRIVATE18			= V4L2_CID_PRIVATE_BASE + 18,
	CID_PRIVATE19			= V4L2_CID_PRIVATE_BASE + 19,
	CID_PRIVATE20			= V4L2_CID_PRIVATE_BASE + 20,
	CID_PRIVATE21			= V4L2_CID_PRIVATE_BASE + 21,
	CID_PRIVATE22			= V4L2_CID_PRIVATE_BASE + 22,
	CID_PRIVATE23			= V4L2_CID_PRIVATE_BASE + 23,
	CID_PRIVATE24			= V4L2_CID_PRIVATE_BASE + 24,
	CID_PRIVATE25			= V4L2_CID_PRIVATE_BASE + 25,
	CID_PRIVATE26			= V4L2_CID_PRIVATE_BASE + 26,
	CID_PRIVATE27			= V4L2_CID_PRIVATE_BASE + 27,
	CID_PRIVATE28			= V4L2_CID_PRIVATE_BASE + 28,
	CID_PRIVATE29			= V4L2_CID_PRIVATE_BASE + 29,

	UNKNOWN_FEATURE			= V4L2_CID_LASTP1
    };

  //! 値の範囲
    template <class T>
    struct Range
    {
      //! 与えられた値がこの範囲に納まっているか調べる
      /*!
	\param val	値
	\return		範囲に納まっていればtrue, そうでなければfalse
      */
	bool	involves(T val) const
		{
		    return (min <= val && val <= max &&
			    (val - min) % step == 0);
		}

	T	min;				//!< 最小値
	T	max;				//!< 最大値
	T	step;				//!< 増分ステップ
    };

  //! フレームレート
    struct FrameRate
    {
	Range<u_int>		fps_n;		//!< 分子
	Range<u_int>		fps_d;		//!< 分母
    };
  //! フレームレートを指す反復子
    typedef std::vector<FrameRate>::const_iterator	FrameRateIterator;
  //! フレームレートの範囲を表す反復子のペア
    typedef std::pair<FrameRateIterator, FrameRateIterator>
							FrameRateRange;
    
  //! 画像サイズ
    struct FrameSize
    {
	FrameRateRange		availableFrameRates()		const	;
	
	Range<u_int>		width;		//!< 画像の幅
	Range<u_int>		height;		//!< 画像の高さ
	std::vector<FrameRate>	frameRates;	//!< フレーム間隔
    };
  //! 画像サイズを指す反復子
    typedef std::vector<FrameSize>::const_iterator	FrameSizeIterator;
  //! 画素サイズの範囲を表す反復子のペア
    typedef std::pair<FrameSizeIterator, FrameSizeIterator>
							FrameSizeRange;

  //! メニュー項目
    struct MenuItem
    {
	int			index;		//!< メニュー項目の識別子
	std::string		name;		//!< メニュー項目名
    };
  //! メニュー項目を指す反復子
    typedef std::vector<MenuItem>::const_iterator	MenuItemIterator;
  //! メニュー項目の範囲を表す反復子のペア
    typedef std::pair<MenuItemIterator, MenuItemIterator>
							MenuItemRange;
    
  private:
    struct Format		//! 画像フォーマット
    {
	PixelFormat		pixelFormat;	//!< 画素フォーマット
	std::string		name;		//!< 画素フォーマット名
	std::vector<FrameSize>	frameSizes;	//!< 画像の大きさ
    };

    struct Control		//! コントロール
    {
      public:
	Feature			feature;	//!< 属性(コントロールの識別子)
	std::string		name;		//!< コントロール名
	u_int			type;		//!< 値の型
	Range<int>		range;		//!< 値の範囲
	int			def;		//!< デフォルト値
	u_int			flags;
	std::vector<MenuItem>	menuItems;
    };

    class Buffer	//! 受信用バッファ
    {
      public:
	Buffer()	:_p(0), _size(0)		{}
	~Buffer()					{unmap();}

	void		map(int fd, u_int index)	;
	void		unmap()				;
	const void*	p()			const	{return _p;}
	u_int		size()			const	{return _size;}
	
      private:
	void*		_p;
	u_int		_size;
    };

    template <class S, class T>
    struct MemberIterator
	: public boost::iterator_adaptor<MemberIterator<S, T>,
		typename std::vector<T>::const_iterator, const S>
    {
	MemberIterator(typename std::vector<T>::const_iterator iter)
	    :boost::iterator_adaptor<MemberIterator<S, T>,
		typename std::vector<T>::const_iterator, const S>(iter)	{}
	const S&	dereference()				 const	;
    };

  public:
  //! 画素フォーマットを指す反復子
    typedef MemberIterator<PixelFormat, Format>		PixelFormatIterator;
  //! 画素フォーマットの範囲を表す反復子のペア
    typedef std::pair<PixelFormatIterator, PixelFormatIterator>
							PixelFormatRange;
  //! 属性を指す反復子
    typedef MemberIterator<Feature, Control>		FeatureIterator;
  //! 属性の範囲を表す反復子のペア
    typedef std::pair<FeatureIterator, FeatureIterator>	FeatureRange;
    
  public:
    V4L2Camera(const char* dev)						;
    ~V4L2Camera()							;

  // Format stuffs.
    PixelFormatRange	availablePixelFormats()			const	;
    FrameSizeRange	availableFrameSizes(PixelFormat pixelFormat)
								const	;
    bool		isAvailable(PixelFormat pixelFormat)	const	;
    V4L2Camera&		setFormat(PixelFormat pixelFormat,
				  u_int width, u_int height,
				  u_int fps_n, u_int fps_d)		;
    void		getFrameRate(u_int& fps_n, u_int& fps_d) const	;
    const std::string&	getName(PixelFormat pixelFormat)	const	;
    u_int		width()					const	;
    u_int		height()				const	;
    PixelFormat		pixelFormat()				const	;
    std::ostream&	put(std::ostream& out,
			    PixelFormat pixelFormat)		const	;
  
  // Feature stuffs.
    FeatureRange	availableFeatures()			const	;
    MenuItemRange	availableMenuItems(Feature feature)	const	;
    bool		isAvailable(Feature feature)		const	;
    V4L2Camera&		setValue(Feature feature, int value)		;
    int			getValue(Feature feature)		const	;
    void		getMinMaxStep(Feature feature, int& min,
				      int& max, int& step)	const	;
    int			getDefaultValue(Feature feature)	const	;
    const std::string&	getName(Feature feature)		const	;
    std::ostream&	put(std::ostream& out, Feature feature)	const	;
    
  // Capture stuffs.
    V4L2Camera&		continuousShot()				;
    V4L2Camera&		stopContinuousShot()				;
    bool		inContinuousShot()			const	;
    V4L2Camera&		snap()						;
#ifdef HAVE_LIBTUTOOLS__
    template <class T> const V4L2Camera&
			operator >>(Image<T>& image)		const	;
    template <class T> const V4L2Camera&
			captureRGBImage(Image<T>& image)	const	;
    template <class T> const V4L2Camera&
			captureDirectly(Image<T>& image)	const	;
#endif
    const V4L2Camera&	captureRaw(void* image)			const	;
    const V4L2Camera&	captureBayerRaw(void* image)		const	;
    u_int64_t		arrivaltime()				const	;

  // Utility functions.
    static PixelFormat	uintToPixelFormat(u_int pixelFormat)		;
    static Feature	uintToFeature(u_int feature)			;

  private:
    void		enumerateFormats()				;
    void		enumerateControls()				;
    bool		addControl(u_int id)				;
    int			enumerateMenuItems(
			    const v4l2_queryctrl& ctrl,
			    std::vector<MenuItem>& menuItems)		;
    const Format&	pixelFormatToFormat(PixelFormat pixelFormat)
								const	;
    const Control&	featureToControl(Feature feature)	const	;

    void		mapBuffers(u_int n)				;
    void		unmapBuffers()					;
    u_int		requestBuffers(u_int n)				;
    void		enqueueBuffer(u_int index)		const	;
    u_int		dequeueBuffer()					;
    
    int			ioctl(int request, void* arg)		const	;
    int			ioctl(int id, v4l2_queryctrl& ctrl)	const	;

    friend std::ostream&
	operator <<(std::ostream& out, const Format& format)		;
    friend std::ostream&
	operator <<(std::ostream& out, const Control& control)		;
    
  private:
    const int			_fd;
    std::vector<Format>		_formats;
    std::vector<Control>	_controls;
    u_int			_width;
    u_int			_height;
    PixelFormat			_pixelFormat;
    std::vector<Buffer>		_buffers;
    u_int			_current;	// キューから取り出されている
    bool			_inContinuousShot;
    u_int64_t			_arrivaltime;
};

//! このカメラで利用できる画素フォーマットの範囲を返す
/*!
  \return	画素フォーマット(#PixelFormat)を指す定数反復子のペア
*/
inline V4L2Camera::PixelFormatRange
V4L2Camera::availablePixelFormats() const
{
    return std::make_pair(_formats.begin(), _formats.end());
}
    
//! 指定した画素フォーマットのもとでこのカメラで利用できる画像サイズの範囲を返す
/*!
  \param pixelFormat	画素フォーマット
  \return		画像サイズ(#FrameSize)を指す定数反復子のペア
*/
inline V4L2Camera::FrameSizeRange
V4L2Camera::availableFrameSizes(PixelFormat pixelFormat) const
{
    const Format&	format = pixelFormatToFormat(pixelFormat);
    return std::make_pair(format.frameSizes.begin(), format.frameSizes.end());
}
    
//! 指定した画素フォーマットに付けられている名前を返す
/*!
  \param pixelFormat	画素フォーマット
  \return		画素フォーマットの名前
*/
inline const std::string&
V4L2Camera::getName(PixelFormat pixelFormat) const
{
    return pixelFormatToFormat(pixelFormat).name;
}

//! 現在設定されている画像幅を返す
inline u_int
V4L2Camera::width() const
{
    return _width;
}

//! 現在設定されている画像高さを返す
inline u_int
V4L2Camera::height() const
{
    return _height;
}

//! 現在設定されている画素フォーマット(#PixelFormat)を返す
inline V4L2Camera::PixelFormat
V4L2Camera::pixelFormat() const
{
    return _pixelFormat;
}

//! 指定された画素フォーマットの内容を出力する．
/*!
  \param out		出力ストリーム
  \param pixelFormat	画素フォーマット
  \return		outで指定した出力ストリーム
*/ 
inline std::ostream&
V4L2Camera::put(std::ostream& out, PixelFormat pixelFormat) const
{
    return out << pixelFormatToFormat(pixelFormat);
}

//! このカメラで利用できる属性の範囲を返す
/*!
  \return	属性(#Feature)を指す定数反復子のペア
*/
inline V4L2Camera::FeatureRange
V4L2Camera::availableFeatures() const
{
    return std::make_pair(_controls.begin(), _controls.end());
}
    
//! この属性で利用できるメニュー項目の範囲を返す
/*!
  \return	メニュー項目(#MenuItem)を指す定数反復子のペア
*/
inline V4L2Camera::MenuItemRange
V4L2Camera::availableMenuItems(Feature feature) const
{
    const Control&	control = featureToControl(feature);
    return std::make_pair(control.menuItems.begin(), control.menuItems.end());
}

//! 指定された属性の内容を出力する
/*!
  \param out		出力ストリーム
  \param feature	属性
  \return		outで指定した出力ストリーム
*/ 
inline std::ostream&
V4L2Camera::put(std::ostream& out, Feature feature) const
{
    return out << featureToControl(feature);
}

//! 指定された属性のデフォルト値を調べる
/*!
  \param feature	対象となる属性
  \return		デフォルト値
*/
inline int
V4L2Camera::getDefaultValue(Feature feature) const
{
    return featureToControl(feature).def;
}

//! 指定した属性に付けられている名前を返す
/*!
  \param feature	対象となる属性
  \return		属性の名前
*/
inline const std::string&
V4L2Camera::getName(Feature feature) const
{
    return featureToControl(feature).name;
}

//! カメラから画像を出力中であるか調べる
/*!
  \return	画像を出力中であればtrue, そうでなければfalse
*/
inline bool
V4L2Camera::inContinuousShot() const
{
    return _inContinuousShot;
}
    
//! カメラから出力される最初の画像を保持する
/*!
  カメラからの画像出力は, continuousShot() によって行われる. 実際に画像データが
  受信されるまで, 本関数は呼び出し側に制御を返さない. 
  \return	このカメラオブジェクト
 */
inline V4L2Camera&
V4L2Camera::snap()
{
#if 0
    _current = dequeueBuffer();		// データが受信されるのを待つ
    enqueueBuffer(_current);		// キューに戻す
#else
    if (_current != ~0)			// 以前に受信したバッファがあれば...
	enqueueBuffer(_current);	// キューに戻す
    _current = dequeueBuffer();		// データが受信されるのを待つ
#endif
    return *this;
}

#ifdef HAVE_LIBTUTOOLS__
//! カメラから出力された画像を直接的に取り込む
/*!
  #operator >>() との違いは, 画像形式の変換を行わないことと, Image<T> 構造体
  の中のデータ領域へのポインタをV4L2入力バッファへのポインタに書き換えることに
  よって, 実際にはデータのコピーを行わないことである. テンプレートパラメータTは,
  格納先の画像の画素形式を表す. なお, 本関数を呼び出す前に snap() によって
  カメラからの画像を保持しておかなければならない. 
  \param image	画像データを格納する画像オブジェクト. 画像の幅と高さは, 
		現在カメラに設定されている画像サイズに合わせて自動的に
		設定される. 
  \return	このカメラオブジェクト
*/
template <class T> const V4L2Camera&
V4L2Camera::captureDirectly(Image<T>& image) const
{
    if (_current == ~0)
	throw std::runtime_error("V4L2Camera::captureDirectly(): no images snapped!!");
    image.resize((T*)_buffers[_current].p(), height(), width());

    return *this;
}
#endif

//! 画像データがホストに到着した時刻を返す
/*!
  \return	画像データがホストに到着した時刻
*/
inline u_int64_t
V4L2Camera::arrivaltime() const
{
    return _arrivaltime;
}

template <> inline const V4L2Camera::PixelFormat&
V4L2Camera::MemberIterator<V4L2Camera::PixelFormat,
			   V4L2Camera::Format>::dereference() const
{
    return base_reference()->pixelFormat;
}

template <> inline const V4L2Camera::Feature&
V4L2Camera::MemberIterator<V4L2Camera::Feature,
			   V4L2Camera::Control>::dereference() const
{
    return base_reference()->feature;
}

//! 指定した画像サイズのもとでこのカメラで利用できるフレームレートの範囲を返す
/*!
  \return	フレームレート(#FrameRate)を指す定数反復子のペア
*/
inline V4L2Camera::FrameRateRange
V4L2Camera::FrameSize::availableFrameRates() const
{
    return std::make_pair(frameRates.begin(), frameRates.end());
}
    
/************************************************************************
*  global functions							*
************************************************************************/
template <class T>
std::ostream&	operator <<(std::ostream& out,
			    const typename V4L2Camera::Range<T>& range)	;
std::ostream&	operator <<(std::ostream& out,
			    const V4L2Camera::FrameSize& frameSize)	;
std::ostream&	operator <<(std::ostream& out,
			    const V4L2Camera::FrameRate& frameRate)	;
std::ostream&	operator <<(std::ostream& out,
			    const V4L2Camera::MenuItem& menuItem)	;
std::ostream&	operator <<(std::ostream& out, const V4L2Camera& camera);
std::istream&	operator >>(std::istream& in, V4L2Camera& camera)	;
}
#endif	// !__TU_V4L2PP_H
