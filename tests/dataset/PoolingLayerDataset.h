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
#ifndef __ARM_COMPUTE_TEST_DATASET_POOLING_LAYER_DATASET_H__
#define __ARM_COMPUTE_TEST_DATASET_POOLING_LAYER_DATASET_H__

#include "TypePrinter.h"

#include "arm_compute/core/TensorShape.h"
#include "arm_compute/core/Types.h"
#include "dataset/GenericDataset.h"

#include <type_traits>

#ifdef BOOST
#include "boost_wrapper.h"
#endif

namespace arm_compute
{
namespace test
{
class PoolingLayerDataObject
{
public:
    operator std::string() const
    {
        std::stringstream ss;
        ss << "PoolingLayer";
        ss << "_I" << src_shape;
        ss << "_S_" << info.pool_size();
        ss << "_F_" << info.pool_type();
        ss << "_PS" << info.pad_stride_info();
        return ss.str();
    }

    friend std::ostream &operator<<(std::ostream &s, const PoolingLayerDataObject &obj)
    {
        s << static_cast<std::string>(obj);
        return s;
    }

public:
    TensorShape      src_shape;
    TensorShape      dst_shape;
    PoolingLayerInfo info;
};

template <unsigned int Size>
using PoolingLayerDataset = GenericDataset<PoolingLayerDataObject, Size>;

class AlexNetPoolingLayerDataset final : public PoolingLayerDataset<3>
{
public:
    AlexNetPoolingLayerDataset()
        : GenericDataset
    {
        PoolingLayerDataObject{ TensorShape(55U, 55U, 96U), TensorShape(27U, 27U, 96U), PoolingLayerInfo(PoolingType::MAX, 3, PadStrideInfo(2, 2, 0, 0)) },
        PoolingLayerDataObject{ TensorShape(27U, 27U, 256U), TensorShape(13U, 13U, 256U), PoolingLayerInfo(PoolingType::MAX, 3, PadStrideInfo(2, 2, 0, 0)) },
        PoolingLayerDataObject{ TensorShape(13U, 13U, 256U), TensorShape(6U, 6U, 256U), PoolingLayerInfo(PoolingType::MAX, 3, PadStrideInfo(2, 2, 0, 0)) },
    }
    {
    }

    ~AlexNetPoolingLayerDataset() = default;
};

class LeNet5PoolingLayerDataset final : public PoolingLayerDataset<2>
{
public:
    LeNet5PoolingLayerDataset()
        : GenericDataset
    {
        PoolingLayerDataObject{ TensorShape(24U, 24U, 20U), TensorShape(12U, 12U, 20U), PoolingLayerInfo(PoolingType::MAX, 2, PadStrideInfo(2, 2, 0, 0)) },
        PoolingLayerDataObject{ TensorShape(8U, 8U, 50U), TensorShape(4U, 4U, 50U), PoolingLayerInfo(PoolingType::MAX, 2, PadStrideInfo(2, 2, 0, 0)) },
    }
    {
    }

    ~LeNet5PoolingLayerDataset() = default;
};

class GoogLeNetPoolingLayerDataset final : public PoolingLayerDataset<10>
{
public:
    GoogLeNetPoolingLayerDataset()
        : GenericDataset
    {
        // pool1/3x3_s2
        PoolingLayerDataObject{ TensorShape(112U, 112U, 64U), TensorShape(56U, 56U, 64U), PoolingLayerInfo(PoolingType::MAX, 3, PadStrideInfo(2, 2, 0, 0, DimensionRoundingType::CEIL)) },
        // pool2/3x3_s2
        PoolingLayerDataObject{ TensorShape(56U, 56U, 192U), TensorShape(28U, 28U, 192U), PoolingLayerInfo(PoolingType::MAX, 3, PadStrideInfo(2, 2, 0, 0, DimensionRoundingType::CEIL)) },
        // inception_3a/pool
        PoolingLayerDataObject{ TensorShape(28U, 28U, 192U), TensorShape(28U, 28U, 192U), PoolingLayerInfo(PoolingType::MAX, 3, PadStrideInfo(1, 1, 1, 1, DimensionRoundingType::CEIL)) },
        // inception_3b/pool
        PoolingLayerDataObject{ TensorShape(28U, 28U, 256U), TensorShape(28U, 28U, 256U), PoolingLayerInfo(PoolingType::MAX, 3, PadStrideInfo(1, 1, 1, 1, DimensionRoundingType::CEIL)) },
        // pool3/3x3_s2
        PoolingLayerDataObject{ TensorShape(28U, 28U, 480U), TensorShape(14U, 14U, 480U), PoolingLayerInfo(PoolingType::MAX, 3, PadStrideInfo(2, 2, 0, 0, DimensionRoundingType::CEIL)) },
        // inception_4a/pool
        PoolingLayerDataObject{ TensorShape(14U, 14U, 480U), TensorShape(14U, 14U, 480U), PoolingLayerInfo(PoolingType::MAX, 3, PadStrideInfo(1, 1, 1, 1, DimensionRoundingType::CEIL)) },
        // inception_4b/pool, inception_4c/pool, inception_4d/pool
        PoolingLayerDataObject{ TensorShape(14U, 14U, 512U), TensorShape(14U, 14U, 512U), PoolingLayerInfo(PoolingType::MAX, 3, PadStrideInfo(1, 1, 1, 1, DimensionRoundingType::CEIL)) },
        // inception_4e/pool
        PoolingLayerDataObject{ TensorShape(14U, 14U, 528U), TensorShape(14U, 14U, 528U), PoolingLayerInfo(PoolingType::MAX, 3, PadStrideInfo(1, 1, 1, 1, DimensionRoundingType::CEIL)) },
        // pool4/3x3_s2
        PoolingLayerDataObject{ TensorShape(14U, 14U, 832U), TensorShape(7U, 7U, 832U), PoolingLayerInfo(PoolingType::MAX, 3, PadStrideInfo(2, 2, 0, 0, DimensionRoundingType::CEIL)) },
        // inception_5a/pool, inception_5b/pool
        PoolingLayerDataObject{ TensorShape(7U, 7U, 832U), TensorShape(7U, 7U, 832U), PoolingLayerInfo(PoolingType::MAX, 3, PadStrideInfo(1, 1, 1, 1, DimensionRoundingType::CEIL)) },
    }
    {
    }

    ~GoogLeNetPoolingLayerDataset() = default;
};

class RandomPoolingLayerDataset final : public PoolingLayerDataset<8>
{
public:
    RandomPoolingLayerDataset()
        : GenericDataset
    {
        PoolingLayerDataObject{ TensorShape(27U, 27U, 16U), TensorShape(13U, 13U, 16U), PoolingLayerInfo(PoolingType::MAX, 3, PadStrideInfo(2, 2, 0, 0)) },
        PoolingLayerDataObject{ TensorShape(13U, 13U, 32U), TensorShape(6U, 6U, 32U), PoolingLayerInfo(PoolingType::MAX, 3, PadStrideInfo(2, 2, 0, 0)) },
        PoolingLayerDataObject{ TensorShape(24U, 24U, 10U), TensorShape(12U, 12U, 10U), PoolingLayerInfo(PoolingType::MAX, 2, PadStrideInfo(2, 2, 0, 0)) },
        PoolingLayerDataObject{ TensorShape(8U, 8U, 30U), TensorShape(4U, 4U, 30U), PoolingLayerInfo(PoolingType::MAX, 2, PadStrideInfo(2, 2, 0, 0)) },
        PoolingLayerDataObject{ TensorShape(27U, 27U, 16U), TensorShape(13U, 13U, 16U), PoolingLayerInfo(PoolingType::AVG, 3, PadStrideInfo(2, 2, 0, 0)) },
        PoolingLayerDataObject{ TensorShape(13U, 13U, 32U), TensorShape(6U, 6U, 32U), PoolingLayerInfo(PoolingType::AVG, 3, PadStrideInfo(2, 2, 0, 0)) },
        PoolingLayerDataObject{ TensorShape(24U, 24U, 10U), TensorShape(12U, 12U, 10U), PoolingLayerInfo(PoolingType::AVG, 2, PadStrideInfo(2, 2, 0, 0)) },
        PoolingLayerDataObject{ TensorShape(8U, 8U, 30U), TensorShape(4U, 4U, 30U), PoolingLayerInfo(PoolingType::AVG, 2, PadStrideInfo(2, 2, 0, 0)) },
    }
    {
    }

    ~RandomPoolingLayerDataset() = default;
};
} // namespace test
} // namespace arm_compute
#endif //__ARM_COMPUTE_TEST_DATASET_POOLING_LAYER_DATASET_H__
