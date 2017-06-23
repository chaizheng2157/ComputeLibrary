/*
 * Copyright (c) 2017 ARM Limited.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef __ARM_COMPUTE_CLCONVOLUTIONLAYER_H__
#define __ARM_COMPUTE_CLCONVOLUTIONLAYER_H__

#include "arm_compute/runtime/IFunction.h"

#include "arm_compute/core/CL/kernels/CLCol2ImKernel.h"
#include "arm_compute/core/CL/kernels/CLFillBorderKernel.h"
#include "arm_compute/core/CL/kernels/CLGEMMInterleave4x4Kernel.h"
#include "arm_compute/core/CL/kernels/CLGEMMMatrixMultiplyKernel.h"
#include "arm_compute/core/CL/kernels/CLGEMMTranspose1xWKernel.h"
#include "arm_compute/core/CL/kernels/CLIm2ColKernel.h"
#include "arm_compute/core/CL/kernels/CLWeightsReshapeKernel.h"
#include "arm_compute/core/Types.h"
#include "arm_compute/core/Types.h"
#include "arm_compute/runtime/CL/CLTensor.h"
#include "arm_compute/runtime/CL/CLTensor.h"

namespace arm_compute
{
class ICLTensor;

/** Function to reshape and transpose the weights. This function calls the following kernels:
 * -# @ref CLWeightsReshapeKernel
 * -# @ref CLGEMMTranspose1xWKernel
 */
class CLConvolutionLayerReshapeWeights : public IFunction
{
public:
    /** Constructor */
    CLConvolutionLayerReshapeWeights();
    /** Set the input and output tensors.
     *
     * @param[in]  weights      Weights tensor. Weights are 4D tensor with dimensions [kernel_x, kernel_y, IFM, OFM]. Data type supported: F32.
     * @param[in]  biases       Biases tensor. Shared biases supported. Biases are 1D tensor with dimensions [OFM]. Data type supported: Same as @p weights.
     * @param[out] output       Destination tensor. Data types supported: Same as @p weights.
     * @param[in]  transpose1xW True if the weights are to undergo a 1xW transposition after reshaping (in case of GEMM operation), false otherwise.
     *                          Data types supported: Same as @p weights.
     */
    void configure(const ICLTensor *weights, const ICLTensor *biases, ICLTensor *output, bool transpose1xW);
    // Inherited methods overridden:
    void run() override;

private:
    CLConvolutionLayerWeightsReshapeKernel _weights_reshape_kernel;
    CLGEMMTranspose1xWKernel               _weights_transposed_kernel;
    CLTensor                               _weights_reshaped;
    bool                                   _transpose1xW;
};

/** Basic function to compute the convolution layer. This function calls the following OpenCL kernels:
 *
 * -# @ref CLConvolutionLayerWeightsReshapeKernel (executed only once for each configuration)
 * -# @ref CLGEMMTranspose1xWKernel               (executed only once for each configuration)
 * -# @ref CLIm2ColKernel
 * -# @ref CLGEMMInterleave4x4Kernel
 * -# @ref CLGEMMMatrixMultiplyKernel
 * -# @ref CLCol2ImKernel
 */
class CLConvolutionLayer : public IFunction
{
public:
    /** Default constructor */
    CLConvolutionLayer();
    /** Set the input and output tensors.
     *
     * @param[in]  input        Source tensor. 3 lower dimensions represent a single input [width, height, IFM],
     *                          while every optional dimension from 4 and above represent a batch of inputs.
     *                          Data types supported: F16, F32.
     * @param[in]  weights      Weights tensor. Weights are 4D tensor with dimensions [kernel_x, kernel_y, IFM, OFM]. Data type supported:Same as @p input.
     * @param[in]  biases       Biases tensor. Shared biases supported. Biases are 1D tensor with dimensions [OFM]. Data type supported:Same as @p input.
     * @param[out] output       Destination tensor. 3 lower dimensions represent a single output [width, height, OFM], while the rest represent batch of outputs.
     *                          Data types supported: Same as @p input.
     * @param[in]  conv_info    Contains padding and stride information described in @ref PadStrideInfo.
     * @param[in]  weights_info Specifies if the weights tensor has been reshaped with NEWeightsReshapeKernel. If this is not part of the fully connected layer the weights
     *                          tensor has also been transposed with NEGEMMTranspose1xWKernel. Data type supported: Same as @p input.
     */
    void configure(const ICLTensor *input, const ICLTensor *weights, const ICLTensor *biases, ICLTensor *output, const PadStrideInfo &conv_info, const WeightsInfo &weights_info = WeightsInfo());

    // Inherited methods overridden:
    void run() override;

private:
    CLConvolutionLayerReshapeWeights _reshape_weights;
    CLIm2ColKernel                   _input_im2col_kernel;
    CLGEMMInterleave4x4Kernel        _input_interleave_kernel;
    CLGEMMMatrixMultiplyKernel       _mm_kernel;
    CLCol2ImKernel                   _output_col2im_kernel;
    CLTensor                         _input_im2col_reshaped;
    CLTensor                         _input_interleaved_reshaped;
    CLTensor                         _weights_reshaped;
    CLTensor                         _weights_transposed;
    CLTensor                         _gemm_output;
    bool                             _has_bias;
    bool                             _is_fully_connected_convolution;
    bool                             _are_weights_reshaped;
};
}
#endif /* __ARM_COMPUTE_CLCONVOLUTIONLAYER_H__ */
