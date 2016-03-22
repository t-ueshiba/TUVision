/*
 *  $Id: main.cc,v 1.1 2012-08-30 00:13:51 ueshiba Exp $
 */
#include <stdexcept>
#include "TU/Image++.h"
#include "TU/cuda/Array++.h"
#include "TU/cuda/algorithm.h"
#include <cuda_runtime.h>
#include <cutil.h>

/************************************************************************
*  Global fucntions							*
************************************************************************/
int
main(int argc, char *argv[])
{
    using namespace	std;
    using namespace	TU;

    typedef float	pixel_t;
    
    try
    {
	Image<pixel_t>	image;
	image.restore(cin);				// 原画像を読み込む
	image.save(cout);
	
	cuda::Array2<pixel_t>	in_d(image),
				out_d(in_d.nrow()/2, in_d.ncol()/2);
	
	u_int		timer = 0;
	CUT_SAFE_CALL(cutCreateTimer(&timer));		// タイマーを作成
	cuda::subsample(in_d.cbegin(), in_d.cend(), out_d.begin());
	CUDA_SAFE_CALL(cudaThreadSynchronize());

	u_int		NITER = 1000;
	CUT_SAFE_CALL(cutStartTimer(timer));
	for (u_int n = 0; n < NITER; ++n)
	    cuda::subsample(in_d.cbegin(), in_d.cend(), out_d.begin());
	CUDA_SAFE_CALL(cudaThreadSynchronize());
	CUT_SAFE_CALL(cutStopTimer(timer));

	cerr << float(NITER * 1000) / cutGetTimerValue(timer) << "fps" << endl;
	CUT_SAFE_CALL(cutDeleteTimer(timer));		// タイマーを消去

	out_d.write(image);
	image.save(cout);
    }
    catch (exception& err)
    {
	cerr << err.what() << endl;
	return 1;
    }

    return 0;
}
